#include <string>

#include "format.h"//Include format header file

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds

// REMOVE: [[maybe_unused]] once you define the function
std::string Format::ElapsedTime(long seconds) { 

    const int SECPERMIN =60;//Define a standard for a minute in seconds
    const int SECPERHOUR =3600;//Define a standard for an hour in seconds
    // INPUT: Long int measuring seconds 
    long lseconds = seconds % SECPERMIN;//Find seconds elapsed
    long lminutes = (seconds / SECPERMIN) %SECPERMIN;//Find minutes elapsed
    long lhours   = seconds /SECPERHOUR; //Find hours elapsed

    std::stringstream ssresult;
	// OUTPUT: HH:MM:SS
    ssresult << std::setfill('0') << std::setw(2) << lhours << ":";
    ssresult << std::setfill('0') << std::setw(2) << lminutes << ":";  
    ssresult << std::setfill('0') << std::setw(2) << lseconds; 

    return ssresult.str();
}