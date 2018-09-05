#include "_pch.h"
#include "CppUnitTest.h"
#include "../Maths/maths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace maths;

namespace UnitTests {

TEST_CLASS(test_noise) {
public:

    TEST_METHOD(Construction) {
        PerlinNoise2D noise(10,10, 1);
        noise.setOctaves(7)
             .setPersistence(0.5)
             .generate();

        float v = noise.get(0,0);
        Logger::WriteMessage(std::to_string(v).c_str());


    }
};

}