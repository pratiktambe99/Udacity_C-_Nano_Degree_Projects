
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"//Include linux_parser header file

class Processor {
 public:
  Processor(); 
  float Utilization();  //See src/processor.cpp
   
  //Declare any necessary private members
 private:
   int tAll_  =0;
   int tIdle_ =0;
};

#endif