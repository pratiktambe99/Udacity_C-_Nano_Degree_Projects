#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h" //Include process header 
#include "processor.h"// Include processor header
#include "system.h"//Include system header

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(){
  cpu_ = Processor();
  Processes();
}

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
    processes_.clear();
    vector<int> pids = LinuxParser::Pids();
    for (int pid: pids) {
        processes_.emplace_back(Process(pid));    
    }
    for (Process& process: processes_){
        process.CpuUtilization(LinuxParser::ActiveJiffies(process.Pid()),
        LinuxParser::Jiffies());
    }
    std::sort(processes_.begin(),processes_.end(),std::greater<Process>());
    return processes_; 
}

// Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization();}

//Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses();}

// Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }