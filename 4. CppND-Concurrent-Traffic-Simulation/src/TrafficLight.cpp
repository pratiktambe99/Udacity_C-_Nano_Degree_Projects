#include <iostream>
#include <random>
#include <time.h>
#include "TrafficLight.h"//Include TrafficLight.h

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{

    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_queue.empty(); }); // pass unique lock to condition variable

    // remove last deque element from queue
    T msg = std::move(_queue.back());
    _queue.pop_back();

    return msg; // will not be copied due to return value optimization (RVO) in C++
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add message to queue
    std::cout << "   Message #" << msg << " has been sent to the queue" << std::endl;
    _queue.push_back(std::move(msg));
    _cond.notify_one(); // notify client after pushing new Message into deque
}


/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{

    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // popBack wakes up when a new element is available in the queue
        TrafficLightPhase lightPhaseMessage = _messageQueue.receive();

        if (lightPhaseMessage == TrafficLightPhase::green) {
            return;
        }
    }

}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{

    
    _threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));

}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
   
    // Init our random generation between 4000 and 6000 miliseconds
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<> distr(4000.0, 6000.0);
    
    // setup variables
    double cycleDuration = distr(eng); // duration of a single simulation cycle in ms, is randomly chosen
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();

    while (true)
    {

        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
       //It is time to toggle our traffic light
        if (timeSinceLastUpdate >= cycleDuration)
        {
            // Toggle current phase of traffic light
            if (_currentPhase == TrafficLightPhase::red) {
                _currentPhase =  TrafficLightPhase::green;
            } else {
                _currentPhase = TrafficLightPhase::red;
            }

            //  Send an update to the message queue and wait for it to be sent 
            //std::async(&MessageQueue<int>::send, _messageQueue, std::move(_currentPhase));
            _messageQueue.send(std::move(_currentPhase));

            // reset stop watch for next cycle
            lastUpdate = std::chrono::system_clock::now();

        }

    }
}