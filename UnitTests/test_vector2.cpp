#include "_pch.h"
#include "CppUnitTest.h"
#include "../Maths/maths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace maths;

namespace UnitTests {	

TEST_CLASS(test_vector2)
{
public:
		
	TEST_METHOD(Construction)
	{
		float2 v;
		Assert::IsTrue(v.x==0 && v.y==0);
		float2 a{1,2};
		Assert::IsTrue(a.x==1 && a.y==2);
		int2 i{1, 2};
		Assert::IsTrue(i.x == 1 && i.y == 2);
		uint2 u{1, 2};
		Assert::IsTrue(u.x == 1 && u.y == 2);
		double2 d{1,2};
		Assert::IsTrue(d.x == 1 && d.y == 2);

		float2 b{i};
		float2 c{u};
		Assert::IsTrue(b.x == 1 && b.y == 2);
		Assert::IsTrue(c.x == 1 && c.y == 2);

		int2 i2{float2{-1, 2}};
		Assert::IsTrue(i2.x == -1 && i2.y == 2);

		uint2 u2{float2{-2, 2}};
		Assert::IsTrue(u2.x == 0xfffffffe && u2.y == 2);

		float2 e{double2{1, 2}};
		Assert::IsTrue(e.x == 1 && e.y == 2);
	}
	TEST_METHOD(operator_neg) {
		Assert::IsTrue(-float2{1, -3} == float2{-1,3});
	}
	TEST_METHOD(operator_equals) {
		Assert::IsTrue(float2{1, 2} == float2{1,2});
		Assert::IsTrue(float2{-1, -2} == float2{-1, -2});

		Assert::IsTrue(float2{1, 2} != float2{1, 1});
		Assert::IsTrue(float2{2, 1} != float2{1, 1});
	}
	TEST_METHOD(approx) {
		Assert::IsTrue(float2{0.1f, 0.2f}.approx({0.10009f, 0.20009f}));
	}
	TEST_METHOD(operator_add) {
		Assert::IsTrue(float2{1, 2} + 10		   == float2{11, 12});
		Assert::IsTrue(float2{1, 2} + float2{5, 6} == float2{6, 8});
	}
	TEST_METHOD(operator_sub) {
		Assert::IsTrue(float2{1, 2} - 1		      == float2{0, 1});
		Assert::IsTrue(float2{1, 2} - float2{1,1} == float2{0,1});
	}
	TEST_METHOD(operator_mul) {
		Assert::IsTrue(float2{1, 2} * 2			   == float2{2, 4});
		Assert::IsTrue(float2{1, 2} * float2{2, 3} == float2{2, 6});
	}
	TEST_METHOD(operator_div) {
		Assert::IsTrue(float2{10, 20} / 2			 == float2{5, 10});
		Assert::IsTrue(float2{10, 20} / float2{2, 5} == float2{5, 4});
	}
	TEST_METHOD(operator_add_assign) {
		float2 a{10, 20};
		float2 b{10, 20};
		Assert::IsTrue((a += 10)			 == float2{20, 30});
		Assert::IsTrue((b += float2{10, 20}) == float2{20, 40});
	}
	TEST_METHOD(operator_sub_assign) {
		float2 a{10, 20};
		float2 b{10, 20};
		Assert::IsTrue((a -= 10) == float2{0, 10});
		Assert::IsTrue((b -= float2{10, 20}) == float2{0, 0});
	}
	TEST_METHOD(operator_mul_assign) {
		float2 a{10, 20};
		float2 b{10, 20};
		Assert::IsTrue((a *= 10) == float2{100, 200});
		Assert::IsTrue((b *= float2{10, 20}) == float2{100, 400});
	}
	TEST_METHOD(operator_div_assign) {
		float2 a{10, 20};
		float2 b{10, 20};
		Assert::IsTrue((a /= 10) == float2{1, 2});
		Assert::IsTrue((b /= float2{10, 20}) == float2{1, 1});
	}
	TEST_METHOD(any) {
		Assert::IsTrue(float2{1, 3}.anyLT(5) == true);
		Assert::IsTrue(float2{1, 3}.anyLT(2) == true);
		Assert::IsTrue(float2{1, 3}.anyLT(1) == false);

		Assert::IsTrue(float2{1, 3}.anyLTE(5) == true);
		Assert::IsTrue(float2{1, 3}.anyLTE(3) == true);
		Assert::IsTrue(float2{1, 1}.anyLTE(1) == true);
		Assert::IsTrue(float2{1, 1}.anyLTE(0.5f) == false);

		Assert::IsTrue(float2{1, 3}.anyGT(0) == true);
		Assert::IsTrue(float2{1, 3}.anyGT(2.5f) == true);
		Assert::IsTrue(float2{1, 3}.anyGT(3) == false);

		Assert::IsTrue(float2{1, 3}.anyGTE(0) == true);
		Assert::IsTrue(float2{1, 3}.anyGTE(3) == true);
		Assert::IsTrue(float2{1, 3}.anyGTE(3.1f) == false);
	}
	TEST_METHOD(all) {
		Assert::IsTrue(float2{1, 3}.allLT(5) == true);
		Assert::IsTrue(float2{1, 3}.allLT(2) == false);
		Assert::IsTrue(float2{1, 3}.allLT(1) == false);

		Assert::IsTrue(float2{1, 3}.allLTE(5) == true);
		Assert::IsTrue(float2{1, 3}.allLTE(3) == true);
		Assert::IsTrue(float2{1, 3}.allLTE(1) == false);
		Assert::IsTrue(float2{1, 1}.allLTE(0.5f) == false);

		Assert::IsTrue(float2{1, 3}.allGT(0) == true);
		Assert::IsTrue(float2{1, 3}.allGT(2.5f) == false);
		Assert::IsTrue(float2{1, 3}.allGT(3) == false);

		Assert::IsTrue(float2{1, 3}.allGTE(0) == true);
		Assert::IsTrue(float2{1, 3}.allGTE(1) == true);
		Assert::IsTrue(float2{1, 3}.allGTE(3) == false);
	}
	TEST_METHOD(hadd) {
		Assert::IsTrue(float2{3, 6}.hadd()==9);
	}
	TEST_METHOD(hmul) {
		Assert::IsTrue(float2{3, 6}.hmul() == 18);
	}
	TEST_METHOD(floor) {
		Assert::IsTrue(float2{5.4f, -9.1f}.floor() == float2{5, -10});
	}
	TEST_METHOD(ceil) {
		Assert::IsTrue(float2{5.4f, -9.1f}.ceil() == float2{6, -9});
	}
	TEST_METHOD(min_max) {
		Assert::IsTrue(float2{3, 5}.min() == 3);
		Assert::IsTrue(float2{3, 5}.max() == 5);

		Assert::IsTrue(float2{3, 5}.min({1, 10}) == float2{1,5});
	}
	TEST_METHOD(dot) {
		Assert::IsTrue(float2{2, 4}.dot({10,20}) == 100);
	}
	TEST_METHOD(length) {
		Assert::IsTrue(float2{10,10}.lengthSquared() == 200);

		Assert::IsTrue(float2{5,7}.length() == 8.602325267042626f);

		Assert::IsTrue(float2{8,10}.invLength() == 0.078086880f);
	}
	TEST_METHOD(normalise) {
		float2 v  = {5,5};
		float2 n  = v.normalised();
		float len = (float)sqrt(5*5 + 5*5); // 7.07106781

		Assert::IsTrue(v.normalise().approx({0.707106f, 0.707106f}));

		Assert::IsTrue(n.approx({0.707106f, 0.707106f}));
	}
	TEST_METHOD(reciprocal) {
		Assert::IsTrue(float2{10, 20}.reciprocal().approx({0.1f, 0.05f}));
	}
	TEST_METHOD(abs) {
		Assert::IsTrue(float2{-1, -4.4f}.abs().approx({1, 4.4f}));
	}
	TEST_METHOD(angleTo) {
		float2 a = {0, 10};
		float2 b = {10, 0};
		float2 c = {0, -10};
		float2 d = {-10, 0};
		Assert::IsTrue(a.angleTo(a) == 0);
		Assert::IsTrue(a.angleTo(b)==toRadians(90));
		Assert::IsTrue(a.angleTo(c) == toRadians(180));
		Assert::IsTrue(a.angleTo(d) == toRadians(90));
	}
	TEST_METHOD(left_right) {
		Assert::IsTrue(float2{1, 2}.left() == float2{-2, 1});
		Assert::IsTrue(float2{1, 2}.right() == float2{2, -1});
	}
};

}