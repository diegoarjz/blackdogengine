#ifndef BLACKDOGENGINETEST_H_
#define BLACKDOGENGINETEST_H_

#include <iostream>

#include <cpptest.h>

#include "../source/BlackDogEngine.h"

class BlackDogEngineTest : public Test::Suite{
public:
  BlackDogEngineTest(){
    TEST_ADD(BlackDogEngineTest::BlackDogEngine_TestCreation);
    TEST_ADD(BlackDogEngineTest::BlackDogEngine_MultipleCreations);
    TEST_ADD(BlackDogEngineTest::BlackDogEngine_Rtti);
  }
private:
  void BlackDogEngine_TestCreation(){
    TEST_ASSERT_MSG(bde::BlackDogEngine::GetInstance() == nullptr, "Engine Instance should be null before creation.");

    bde::BlackDogEnginePtr engine = bde::BlackDogEngine::Create();
    engine->Init();

    TEST_ASSERT_MSG(engine != nullptr, "Engine Instance should have been created.");
    TEST_ASSERT_MSG(engine == bde::BlackDogEngine::GetInstance(), "The singleton instance should be the one created.");
    TEST_THROWS_ANYTHING_MSG( bde::BlackDogEngine::Create(), "Should not be possible to create more instances.");

    bde::BlackDogEngine::Destroy();

    TEST_ASSERT_MSG(bde::BlackDogEngine::GetInstance() == nullptr, "Should have destroyed the singleton instance.");
  }

  void BlackDogEngine_MultipleCreations(){
    bde::BlackDogEnginePtr engine = bde::BlackDogEngine::Create();

    bde::BlackDogEngine::Destroy();

    engine = bde::BlackDogEngine::Create();

    TEST_ASSERT_MSG(engine != nullptr, "Engine should have been recreated.");
    TEST_ASSERT_MSG(engine == bde::BlackDogEngine::GetInstance(), "Singleton instance should be equal to created instance.");

    bde::BlackDogEngine::Destroy();
  }

  void BlackDogEngine_Rtti(){
    bde::Rtti rtti = bde::BlackDogEngine::TYPE;
    TEST_ASSERT_MSG( rtti.GetName() == "bde.Object.BlackDogEngine", "The Rtti name should be \"bde.Object.BlackDogEngine\"" );
    TEST_ASSERT_MSG( rtti.GetBaseType() == bde::Object::TYPE, "The Rtti should be descendant from bde::Object" );

    auto engine = bde::BlackDogEngine::Create();

    TEST_ASSERT_MSG( engine->GetType() == rtti, "An object type should be equal to the class type.");

    bde::BlackDogEngine::Destroy();
  }
}; // class BlackDogEngineTest

#endif
