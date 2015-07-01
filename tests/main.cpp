
#include <iostream>
#include <map>

#include <cpptest.h>

#include "BlackDogEngineTest.h"
#include "GeometryTests.h"
#include "ThreadTests.h"
#include "MetaVariableTests.h"
#include "MetaFunctionTests.h"

#define ADD_TEST(NAME, CLASS) \
functions[NAME] = [&ts](){ \
  ts.add(std::auto_ptr<Test::Suite>(new CLASS)); \
};

int main(int argc, char *argv[]){

  Test::Suite ts;

  std::map<std::string, std::function<void()>> functions;

  ADD_TEST("BlackDogEngine", BlackDogEngineTest);
  ADD_TEST("Geometry", GeometryTests);
  ADD_TEST("Thread", ThreadTests);
  ADD_TEST("MetaVariable", MetaVariableTests);
  ADD_TEST("MetaFunction", MetaFunctionTests);

  if(argc == 1){
    for(auto s : functions){
      s.second();
    }
  }else{
    functions[argv[1]]();
  }

  Test::TextOutput output(Test::TextOutput::Verbose);

  if(ts.run(output)){
    return 0;
  }

  return -1;
}
