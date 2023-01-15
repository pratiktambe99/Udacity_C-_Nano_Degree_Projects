#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"//Include process header file
#include "processor.h"//Include processor header file
#include "linux_parser.h"//Include linux_parser header file

class System {
  //Define public members
 public:
  
  Processor& Cpu();                  
  std::vector<Process>& Processes(); 
  float MemoryUtilization();         
  long UpTime();                    
  int TotalProcesses();               
  int RunningProcesses();            
  std::string Kernel();               
  std::string OperatingSystem();      
  System();                           

  //Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif