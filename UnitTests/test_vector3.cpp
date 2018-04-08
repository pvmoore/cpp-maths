#include "_pch.h"
#include "CppUnitTest.h"
#include "../Maths/maths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace maths;
using std::string;

namespace UnitTests {

TEST_CLASS(test_vector3) {
public:

	TEST_METHOD(Construction) {
		float3 v;
		Assert::IsTrue(v.x == 0 && v.y == 0 && v.z==0);
		float3 a{1, 2, 3};
		Assert::IsTrue(a.x == 1 && a.y == 2 && a.z==3);
		int3 i{1, 2, 3};
		Assert::IsTrue(i.x == 1 && i.y == 2 && i.z==3);
		uint3 u{1, 2, 3};
		Assert::IsTrue(u.x == 1 && u.y == 2 && u.z==3);
		double3 d{1, 2, 3};
		Assert::IsTrue(d.x == 1 && d.y == 2 && d.z==3);

		float3 b{i};
		float3 c{u};
		Assert::IsTrue(b.x == 1 && b.y == 2 && b.z==3);
		Assert::IsTrue(c.x == 1 && c.y == 2 && c.z == 3);

		int3 i2{float3{-1, 2, 3}};
		Assert::IsTrue(i2.x == -1 && i2.y == 2 && i2.z==3);

		uint3 u2{float3{-2, 2, 0}};
		Assert::IsTrue(u2.x == 0xfffffffe && u2.y == 2 && u2.z==0);

		float3 e{double3{1, 2, 3}};
		Assert::IsTrue(e.x==1 && e.y==2 && e.z==3);
	}
	TEST_METHOD(operator_index) {
		float3 v{1, 2, 3};
		v[1] = 10;
		Assert::IsTrue(v[0] == 1 && v[1] == 10 && v[2] == 3);
	}
	TEST_METHOD(operator_neg) {
		Assert::IsTrue(-float3{1, 2, -3} == float3{-1, -2, 3});
	}
	TEST_METHOD(operator_equals) {
		Assert::IsTrue(float3{1, 2, 3} == float3{1, 2, 3});
		Assert::IsTrue(float3{-1, -2, -3} == float3{-1, -2, -3});

		Assert::IsTrue(float3{1, 2, 3} != float3{1, 1, 1});
		Assert::IsTrue(float3{2, 1, 3} != float3{1, 1, 3});
	}
	TEST_METHOD(approx) {
		Assert::IsTrue(float3{0.1f, 0.2f, 0.3f}.approx({0.10009f, 0.20009f, 0.30009f}));
	}
	TEST_METHOD(operator_add) {
		Assert::IsTrue(float3{1, 2, 3} + 10			     == float3{11, 12, 13});
		Assert::IsTrue(float3{1, 2, 3} + float3{5, 6, 7} == float3{6, 8, 10});
	}
	TEST_METHOD(operator_sub) {
		Assert::IsTrue(float3{1, 2, 3} -1                == float3{0, 1, 2});
		Assert::IsTrue(float3{1, 2, 3} - float3{1, 1, 1} == float3{0, 1, 2});
	}
	TEST_METHOD(operator_mul) {
		Assert::IsTrue(float3{1, 2, 3} *2                == float3{2, 4, 6});
		Assert::IsTrue(float3{1, 2, 3} * float3{2, 3, 4} == float3{2, 6, 12});
	}
	TEST_METHOD(operator_div) {
		Assert::IsTrue(float3{10, 20, 30} / 2               == float3{5, 10, 15});
		Assert::IsTrue(float3{10, 20, 30} / float3{2, 5, 5} == float3{5, 4, 6});
	}
	TEST_METHOD(operator_add_assign) {
		float3 a{10, 20, 30};
		float3 b{10, 20, 30};
		Assert::IsTrue((a += 10) == float3{20, 30, 40});
		Assert::IsTrue((b += float3{10, 20, 30}) == float3{20, 40, 60});
	}
	TEST_METHOD(operator_sub_assign) {
		float3 a{10, 20, 30};
		float3 b{10, 20, 30};
		Assert::IsTrue((a -= 10) == float3{0, 10, 20});
		Assert::IsTrue((b -= float3{10, 20, 30}) == float3{0, 0, 0});
	}
	TEST_METHOD(operator_mul_assign) {
		float3 a{10, 20, 30};
		float3 b{10, 20, 30};
		Assert::IsTrue((a *= 10) == float3{100, 200, 300});
		Assert::IsTrue((b *= float3{10, 20, 30}) == float3{100, 400, 900});
	}
	TEST_METHOD(operator_div_assign) {
		float3 a{10, 20, 30};
		float3 b{10, 20, 30};
		Assert::IsTrue((a /= 10) == float3{1, 2, 3});
		Assert::IsTrue((b /= float3{10, 20, 30}) == float3{1, 1, 1});
	}
	TEST_METHOD(any) {
        Assert::IsTrue(float3{1, 2, 3}.anyEQ(1) == true);
        Assert::IsTrue(float3{1, 2, 3}.anyEQ(2) == true);
        Assert::IsTrue(float3{1, 2, 3}.anyEQ(3) == true);
        Assert::IsTrue(float3{1, 2, 3}.anyEQ(4) == false);

		Assert::IsTrue(float3{1, 3, 5}.anyLT(5) == true);
		Assert::IsTrue(float3{1, 3, 5}.anyLT(2) == true);
		Assert::IsTrue(float3{1, 3, 5}.anyLT(1) == false);

		Assert::IsTrue(float3{1, 3, 5}.anyLTE(5) == true);
		Assert::IsTrue(float3{1, 3, 5}.anyLTE(3) == true);
		Assert::IsTrue(float3{1, 1, 5}.anyLTE(1) == true);
		Assert::IsTrue(float3{1, 1, 5}.anyLTE(0.5f) == false);

		Assert::IsTrue(float3{1, 3, 5}.anyGT(0) == true);
		Assert::IsTrue(float3{1, 3, 5}.anyGT(4.5f) == true);
		Assert::IsTrue(float3{1, 3, 5}.anyGT(5) == false);

		Assert::IsTrue(float3{1, 3, 5}.anyGTE(0) == true);
		Assert::IsTrue(float3{1, 3, 5}.anyGTE(3) == true);
		Assert::IsTrue(float3{1, 3, 5}.anyGTE(5.1f) == false);
	}
	TEST_METHOD(all) {
		Assert::IsTrue(float3{1, 3, 5}.allLT(6) == true);
		Assert::IsTrue(float3{1, 3, 5}.allLT(5) == false);
		Assert::IsTrue(float3{1, 3, 5}.allLT(1) == false);

		Assert::IsTrue(float3{1, 3, 5}.allLTE(5) == true);
		Assert::IsTrue(float3{1, 3, 5}.allLTE(3) == false);
		Assert::IsTrue(float3{1, 3, 5}.allLTE(1) == false);
		Assert::IsTrue(float3{1, 1, 5}.allLTE(0.5f) == false);

		Assert::IsTrue(float3{1, 3, 5}.allGT(0) == true);
		Assert::IsTrue(float3{1, 3, 5}.allGT(1) == false);
		Assert::IsTrue(float3{1, 3, 5}.allGT(10) == false);

		Assert::IsTrue(float3{1, 3, 5}.allGTE(0) == true);
		Assert::IsTrue(float3{1, 3, 5}.allGTE(1) == true);
		Assert::IsTrue(float3{1, 3, 5}.allGTE(3) == false);
	}
	TEST_METHOD(hadd) {
		Assert::IsTrue(float3{3, 6, 9}.hadd() == 18);
	}
	TEST_METHOD(hmul) {
		Assert::IsTrue(float3{3, 6, 9}.hmul() == 162);
	}
	TEST_METHOD(floor) {
		Assert::IsTrue(float3{5.4f, -9.1f, 1.1f}.floor() == float3{5, -10, 1});
	}
	TEST_METHOD(ceil) {
		Assert::IsTrue(float3{5.4f, -9.1f, 1.1f}.ceil() == float3{6, -9, 2});
	}
	TEST_METHOD(min_max) {
		Assert::IsTrue(float3{3, 5, 9}.min() == 3);
		Assert::IsTrue(float3{3, 5, 9}.max() == 9);

		Assert::IsTrue(float3{3, 5, 9}.min({1, 10, 7}) == float3{1, 5, 7});
	}
	TEST_METHOD(dot) {
		Assert::IsTrue(float3{2, 4, 5}.dot({10, 20, 30}) == 250);
	}
	TEST_METHOD(length) {
		Assert::IsTrue(float3{10, 10, 10}.lengthSquared() == 300);

		Assert::IsTrue(approxEqual(float3{5, 7, 8}.length(), 11.747340124470f));

		Assert::IsTrue(approxEqual(float3{8, 10, 15}.invLength(), 0.050702012656f));
	}
	TEST_METHOD(normalise) {
		float3 v = {5, 5, 5};
		float3 n = v.normalised();	// 8.6602540378443864676372317075294

		Assert::IsTrue(v.normalise().approx({0.577350f, 0.577350f, 0.577350f}));

		Assert::IsTrue(n.approx({0.577350f, 0.577350f, 0.577350f}));
	}
	TEST_METHOD(reciprocal) {
		Assert::IsTrue(float3{10, 20, 30}.reciprocal().approx({0.1f, 0.05f, 0.0333333f}));
	}
	TEST_METHOD(cross_product) {
		float3 v = {1, 2, 3};
		float3 u = {-2, 6, 4};
		Assert::IsTrue(v.cross(u).approx({-10, -10, 10}));
	}
	TEST_METHOD(triple_product) {
		float3 a = {-2, 3, 1};
		float3 b = {0, 4, 0};
		float3 c = {-1, 3, 3};

		Assert::IsTrue(a.tripleProduct(b,c) == -20);
	}
	TEST_METHOD(abs) {
		Assert::IsTrue(float3{-1, -4.4f, 0.1f}.abs().approx({1, 4.4f, 0.1f}));
	}
	TEST_METHOD(isParallelTo) {
		Assert::IsTrue(float3{1, 0, 0}.isParallelTo({1,0,0}));
		Assert::IsTrue(float3{1, 0, 0}.isParallelTo({-1, 0, 0}));

		Assert::IsFalse(float3{1, 0, 0}.isParallelTo({0, 1, 0}));
	}
	TEST_METHOD(angleTo) {
		float3 a = {0, 10, 0};
		float3 b = {10, 0, 0};
		float3 c = {0, -10, 0};
		float3 d = {-10, 0, 0};
		Assert::IsTrue(a.angleTo(a) == 0);
		Assert::IsTrue(a.angleTo(b) == toRadians(90));
		Assert::IsTrue(a.angleTo(c) == toRadians(180));
		Assert::IsTrue(a.angleTo(d) == toRadians(90));
	}
	TEST_METHOD(rotateTowards) {
		float3 a = {0, 10, 0};
		Assert::IsTrue(a.rotatedTowards({10,0,0}, toRadians(45)).approx({7.071f, 7.071f, 0}));
	}
	TEST_METHOD(distanceFromPlane) {
		// origin is (0,0,0)
		float3 v{0, 20, 0};
		float3 v1{10, 0, 0};
		float3 v2{0, 0, 10};
		Assert::IsTrue(v.distanceFromPlane(v1, v2)==20);
	}
	TEST_METHOD(rotatedAroundX) {
		float3 a{0, 10, 0};
		Assert::IsTrue(a.rotatedAroundX(toRadians(90)).approx({0,0,10}));
		Assert::IsTrue(a.rotatedAroundX(toRadians(-90)).approx({0, 0, -10}));
	}
	TEST_METHOD(rotatedAroundY) {
		float3 a{10, 0, 0};
		Assert::IsTrue(a.rotatedAroundY(toRadians(90)).approx({0, 0, -10}));
		Assert::IsTrue(a.rotatedAroundY(toRadians(-90)).approx({0, 0, 10}));
	}
	TEST_METHOD(rotatedAroundZ) {
		float3 a{10, 0, 0};
		Assert::IsTrue(a.rotatedAroundZ(toRadians(90)).approx({0, 10, 0}));
		Assert::IsTrue(a.rotatedAroundZ(toRadians(-90)).approx({0, -10, 0}));
	}
	TEST_METHOD(left_right) {
		float3 a{10, 0, 0};
		float3 up{0, 10, 0};

		Assert::IsTrue(a.right(up).normalised().approx({0,0,1}));
		Assert::IsTrue(a.left(up).normalised().approx({0, 0, -1}));
	}
    TEST_METHOD(toString) {
        float3 f{1.1f, 2.2f, 3.3f};

        Assert::IsTrue(f.toString("%.1f") =="[1.1, 2.2, 3.3]");
        Assert::IsTrue(f.toString("%.2f") == "[1.10, 2.20, 3.30]");

        int3 i{1, 2, 3};
        Assert::IsTrue(i.toString() == "[1, 2, 3]");

        vector3<unsigned long long> sl{1,2,3};
        Assert::IsTrue(sl.toString() == "[1, 2, 3]");
    }
};

}