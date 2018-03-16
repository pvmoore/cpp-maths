#include "_pch.h"
#include "../Maths/maths.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace maths;
using std::string;
using std::vector;

namespace UnitTests {

TEST_CLASS(test_maths) {
public:
	TEST_METHOD(test_toRadians) {
		Assert::IsTrue(toRadians(90)== 1.5707963268f);
	}
	TEST_METHOD(test_toDegrees) {
		Assert::IsTrue(toDegrees(1.5707963268f)==90);
	}
	TEST_METHOD(test_approxEqual) {
		Assert::IsTrue(approxEqual(3.14f, 3.14f));
		Assert::IsTrue(approxEqual(3.14f, 3.1401f));

		Assert::IsFalse(approxEqual(3.14f, 3.1402f));
	}
	TEST_METHOD(test_factorsOf) {
		Assert::IsTrue(factorsOf(12) == vector<unsigned int>{12,6,4,3,2,1});
	}
};

}