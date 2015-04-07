
#include <iostream>

#include <cpptest.h>

#include "BlackDogEngineTest.h"

int main(int argc, char *argv[]){

  Test::Suite ts;

  ts.add(std::auto_ptr<Test::Suite>(new BlackDogEngineTest));

  Test::TextOutput output(Test::TextOutput::Verbose);

  if(ts.run(output)){
    return 0;
  }

  return -1;
}
