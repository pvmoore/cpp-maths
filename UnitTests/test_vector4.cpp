#include "_pch.h"
#include "CppUnitTest.h"
#include "../Maths/maths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace maths;

namespace UnitTests {

TEST_CLASS(test_vector4) {
public:

	TEST_METHOD(Construction) {
		float4 v;
		Assert::IsTrue(v.x == 0 && v.y == 0 && v.z == 0 && v.w==0);
		float4 a{1, 2, 3, 4};
		Assert::IsTrue(a.x == 1 && a.y == 2 && a.z == 3 && a.w==4);
		int4 i{1, 2, 3, 4};
		Assert::IsTrue(i.x == 1 && i.y == 2 && i.z == 3 && i.w==4);
		uint4 u{1, 2, 3, 4};
		Assert::IsTrue(u.x == 1 && u.y == 2 && u.z == 3 && u.w==4);
		double4 d{1, 2, 3, 4};
		Assert::IsTrue(d.x == 1 && d.y == 2 && d.z == 3 && d.w==4);

		float4 b{i};
		float4 c{u};
		Assert::IsTrue(b.x == 1 && b.y == 2 && b.z == 3 && b.w==4);
		Assert::IsTrue(c.x == 1 && c.y == 2 && c.z == 3 && c.w==4);

		int4 i2{float4{-1, 2, 3, -2}};
		Assert::IsTrue(i2.x == -1 && i2.y == 2 && i2.z == 3 && i2.w==-2);

		uint4 u2{float4{-2, 2, 0, -1}};
		Assert::IsTrue(u2.x == 0xfffffffe && u2.y == 2 && u2.z == 0 && u2.w==0xffffffff);

		float4 e{double4{1, 2, 3, -1}};
		Assert::IsTrue(e.x == 1 && e.y == 2 && e.z == 3 && e.w==-1);
	}
	TEST_METHOD(operator_index) {
		float4 v{1,2,3,4};
		v[1] = 10;
		Assert::IsTrue(v[0] == 1 && v[1] == 10 && v[2] == 3 && v[3] == 4);
	}
	TEST_METHOD(operator_neg) {
		Assert::IsTrue(-float4{1, 2, -3, -10} == float4{-1, -2, 3, 10});
	}
	TEST_METHOD(operator_equals) {
		Assert::IsTrue(float4{1, 2, 3, 4} == float4{1, 2, 3, 4});
		Assert::IsTrue(float4{-1, -2, -3, -4} == float4{-1, -2, -3, -4});

		Assert::IsTrue(float4{1, 2, 3, 4} != float4{1, 1, 1, 1});
		Assert::IsTrue(float4{2, 1, 3, 4} != float4{1, 1, 3, 4});
	}
	TEST_METHOD(approx) {
		Assert::IsTrue(float4{0.1f, 0.2f, 0.3f, 0.4f}.approx({0.10009f, 0.20009f, 0.30009f, 0.40009f}));
	}
	TEST_METHOD(operator_add) {
		Assert::IsTrue(float4{1, 2, 3, 4} +10			       == float4{11, 12, 13, 14});
		Assert::IsTrue(float4{1, 2, 3, 4} +float4{5, 6, 7, 10} == float4{6, 8, 10, 14});
	}
	TEST_METHOD(operator_sub) {
		Assert::IsTrue(float4{1, 2, 3, 4} -1				  == float4{0, 1, 2, 3});
		Assert::IsTrue(float4{1, 2, 3, 4} -float4{1, 1, 1, 1} == float4{0, 1, 2, 3});
	}
	TEST_METHOD(operator_mul) {
		Assert::IsTrue(float4{1, 2, 3, 4} *2				  == float4{2, 4, 6, 8});
		Assert::IsTrue(float4{1, 2, 3, 4} *float4{2, 3, 4, 5} == float4{2, 6, 12, 20});
	}
	TEST_METHOD(operator_div) {
		Assert::IsTrue(float4{10, 20, 30, 40} / 2				    == float4{5, 10, 15, 20});
		Assert::IsTrue(float4{10, 20, 30, 40} / float4{2, 5, 5, 10} == float4{5, 4, 6, 4});
	}
	TEST_METHOD(operator_add_assign) {
		float4 a{10, 20, 30, 40};
		float4 b{10, 20, 30, 40};
		Assert::IsTrue((a += 10) == float4{20, 30, 40, 50});
		Assert::IsTrue((b += float4{10, 20, 30, 40}) == float4{20, 40, 60, 80});
	}
	TEST_METHOD(operator_sub_assign) {
		float4 a{10, 20, 30, 40};
		float4 b{10, 20, 30, 40};
		Assert::IsTrue((a -= 10)					 == float4{0, 10, 20, 30});
		Assert::IsTrue((b -= float4{10, 20, 30, 40}) == float4{0, 0, 0, 0});
	}
	TEST_METHOD(operator_mul_assign) {
		float4 a{10, 20, 30, 40};
		float4 b{10, 20, 30, 40};
		Assert::IsTrue((a *= 10)					 == float4{100, 200, 300, 400});
		Assert::IsTrue((b *= float4{10, 20, 30, 40}) == float4{100, 400, 900, 1600});
	}
	TEST_METHOD(operator_div_assign) {
		float4 a{10, 20, 30, 40};
		float4 b{10, 20, 30, 40};
		Assert::IsTrue((a /= 10)					 == float4{1, 2, 3, 4});
		Assert::IsTrue((b /= float4{10, 20, 30, 40}) == float4{1, 1, 1, 1});
	}
	TEST_METHOD(any) {
        Assert::IsTrue(float4{1, 2, 3, 4}.anyEQ(1) == true);
        Assert::IsTrue(float4{1, 2, 3, 4}.anyEQ(2) == true);
        Assert::IsTrue(float4{1, 2, 3, 4}.anyEQ(3) == true);
        Assert::IsTrue(float4{1, 2, 3, 4}.anyEQ(4) == true);
        Assert::IsTrue(float4{1, 2, 3, 4}.anyEQ(5) == false);

		Assert::IsTrue(float4{1, 3, 5, 7}.anyLT(8) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.anyLT(2) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.anyLT(1) == false);

		Assert::IsTrue(float4{1, 3, 5, 7}.anyLTE(7) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.anyLTE(2) == true);
		Assert::IsTrue(float4{1, 1, 5, 7}.anyLTE(1) == true);
		Assert::IsTrue(float4{1, 1, 5, 7}.anyLTE(0.5f) == false);

		Assert::IsTrue(float4{1, 3, 5, 7}.anyGT(0) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.anyGT(6.5f) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.anyGT(7) == false);

		Assert::IsTrue(float4{1, 3, 5, 7}.anyGTE(0) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.anyGTE(7) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.anyGTE(7.1f) == false);
	}
	TEST_METHOD(all) {
		Assert::IsTrue(float4{1, 3, 5, 7}.allLT(8) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.allLT(7) == false);
		Assert::IsTrue(float4{1, 3, 5, 7}.allLT(-1) == false);

		Assert::IsTrue(float4{1, 3, 5, 7}.allLTE(7) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.allLTE(5) == false);
		Assert::IsTrue(float4{1, 3, 5, 7}.allLTE(-1) == false);
		Assert::IsTrue(float4{1, 1, 5, 7}.allLTE(0.5f) == false);

		Assert::IsTrue(float4{1, 3, 5, 7}.allGT(0) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.allGT(1) == false);
		Assert::IsTrue(float4{1, 3, 5, 7}.allGT(10) == false);

		Assert::IsTrue(float4{1, 3, 5, 7}.allGTE(0) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.allGTE(1) == true);
		Assert::IsTrue(float4{1, 3, 5, 7}.allGTE(3) == false);
	}
	TEST_METHOD(hadd) {
		Assert::IsTrue(float4{3, 6, 9, 10}.hadd() == 28);
	}
	TEST_METHOD(hmul) {
		Assert::IsTrue(float4{3, 6, 9, 10}.hmul() == 1620);
	}
	TEST_METHOD(floor) {
		Assert::IsTrue(float4{5.4f, -9.1f, 1.1f, -0.1f}.floor() == float4{5, -10, 1, -1});
	}
	TEST_METHOD(ceil) {
		Assert::IsTrue(float4{5.4f, -9.1f, 1.1f, 0.1f}.ceil() == float4{6, -9, 2, 1});
	}
	TEST_METHOD(min_max) {
		Assert::IsTrue(float4{3, 5, 9, 1}.min() == 1);
		Assert::IsTrue(float4{3, 5, 9, 1}.max() == 9);

		Assert::IsTrue(float4{3, 5, 9, 1}.min({1, 10, 7, 1}) == float4{1, 5, 7, 1});
	}
	TEST_METHOD(dot) {
		Assert::IsTrue(float4{2, 4, 5, 5}.dot({10, 20, 30, 10}) == 300);
	}
	TEST_METHOD(length) {
		Assert::IsTrue(float4{10, 10, 10, 10}.lengthSquared() == 400);

		Assert::IsTrue(approxEqual(float4{5, 7, 8, 10}.length(), 15.427248620541f));

		Assert::IsTrue(approxEqual(float4{5, 7, 8, 10}.invLength(), 0.0648203723552f));
	}
	TEST_METHOD(normalise) {
		float4 v = {5, 5, 5, 5};
		float4 n = v.normalised();	

		Assert::IsTrue(v.normalise().approx({0.5f, 0.5f, 0.5f, 0.5f}));

		Assert::IsTrue(n.approx({0.5f, 0.5f, 0.5f, 0.5f}));
	}
	TEST_METHOD(reciprocal) {
		Assert::IsTrue(float4{10, 20, 30, 40}.reciprocal().approx({0.1f, 0.05f, 0.0333333f, 0.025f}));
	}
	TEST_METHOD(abs) {
		Assert::IsTrue(float4{-1, -4.4f, 0.1f, 0}.abs().approx({1, 4.4f, 0.1f, 0}));
	}
    TEST_METHOD(toString) {
        float4 f{1.1f, 2.2f, 3.3f, 4.4f};

        Assert::IsTrue(f.toString("%.1f") == "[1.1, 2.2, 3.3, 4.4]");
        Assert::IsTrue(f.toString("%.2f") == "[1.10, 2.20, 3.30, 4.40]");

        int4 i{1, 2, 3, 4};
        Assert::IsTrue(i.toString() == "[1, 2, 3, 4]");

        vector4<unsigned long long> sl{1, 2, 3, 4};
        Assert::IsTrue(sl.toString() == "[1, 2, 3, 4]");
    }
};

}