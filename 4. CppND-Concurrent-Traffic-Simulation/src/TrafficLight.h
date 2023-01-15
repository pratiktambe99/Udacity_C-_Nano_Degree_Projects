#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"// Include TrafficObject.h

enum TrafficLightPhase
{
    red,
    green,
};

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue
{
public:
	T receive();
	void send(T &&msg);

private:
	std::mutex _mutex;
	std::condition_variable _cond;
	std::deque<T> _queue;
};



class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
	TrafficLight();

    // getters / setters

    // typical behaviour methods
	void waitForGreen();
	void simulate();
	TrafficLightPhase getCurrentPhase();

private:
    // typical behaviour methods
	void cycleThroughPhases();

    MessageQueue<TrafficLightPhase> _messageQueue;

	TrafficLightPhase _currentPhase;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif