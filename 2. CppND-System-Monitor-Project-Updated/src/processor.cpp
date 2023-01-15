#include "processor.h"//Include Processor header file

Processor::Processor(){
  tAll_  = LinuxParser::Jiffies();
  tIdle_ = LinuxParser::IdleJiffies();  
}

//Return the aggregate CPU utilization
float Processor::Utilization() { 
  

  float tAllOld = tAll_;
  float tIdleOld = tIdle_;  
  tAll_  = LinuxParser::Jiffies();
  tIdle_ = LinuxParser::IdleJiffies();

  float rValue= (((tAll_-tAllOld)-(tIdle_-tIdleOld)) / (tAll_-tAllOld));
  return (rValue>0.0)? rValue : 0.0;
 }