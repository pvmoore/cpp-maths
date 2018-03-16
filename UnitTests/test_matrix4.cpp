#include "_pch.h"
#include "CppUnitTest.h"
#include "../Maths/maths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace maths;

namespace UnitTests {

TEST_CLASS(test_matrix4) {
public:

	TEST_METHOD(Construction) {
		matrix m;
		Assert::IsTrue(m[0] == float4{0, 0, 0, 0});
		Assert::IsTrue(m[1] == float4{0, 0, 0, 0});
		Assert::IsTrue(m[2] == float4{0, 0, 0, 0});
		Assert::IsTrue(m[3] == float4{0, 0, 0, 0});
	}
	TEST_METHOD(ptr) {
		matrix m;
		m[1][1] = 3;
		Assert::IsTrue(m.ptr()[5]==3);
	}
	TEST_METHOD(rowMajor) {
		matrix v = matrix::rowMajor({
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15
		});
		Assert::IsTrue(v[0][0] == 0 && v[0][1] == 4 && v[0][2] == 8  && v[0][3] == 12);
		Assert::IsTrue(v[1][0] == 1 && v[1][1] == 5 && v[1][2] == 9  && v[1][3] == 13);
		Assert::IsTrue(v[2][0] == 2 && v[2][1] == 6 && v[2][2] == 10 && v[2][3] == 14);
		Assert::IsTrue(v[3][0] == 3 && v[3][1] == 7 && v[3][2] == 11 && v[3][3] == 15);
	}
	TEST_METHOD(columnMajor) {
		matrix v = matrix::columnMajor({
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15
		});
		Assert::IsTrue(v[0][0] == 0  && v[0][1] == 1  && v[0][2] == 2  && v[0][3] == 3);
		Assert::IsTrue(v[1][0] == 4  && v[1][1] == 5  && v[1][2] == 6  && v[1][3] == 7);
		Assert::IsTrue(v[2][0] == 8  && v[2][1] == 9  && v[2][2] == 10 && v[2][3] == 11);
		Assert::IsTrue(v[3][0] == 12 && v[3][1] == 13 && v[3][2] == 14 && v[3][3] == 15);
	}
	TEST_METHOD(operator_index) {
		matrix v = matrix::columnMajor({
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15
		});
		for(int i = 0; i < 4; i++) {
			float4& c = v[i];
			Assert::IsTrue(c[0] == i*4 && c[1] == i*4+1 && c[2]==i*4+2 && c[3]==i*4+3);
		}
	}
	TEST_METHOD(identity) {
		matrix m = matrix::identity();
		Assert::IsTrue(m[0] == float4{1, 0, 0, 0});
		Assert::IsTrue(m[1] == float4{0, 1, 0, 0});
		Assert::IsTrue(m[2] == float4{0, 0, 1, 0});
		Assert::IsTrue(m[3] == float4{0, 0, 0, 1});
	}
	TEST_METHOD(translate) {
		auto t = matrix::translate({1,2,3});
		Assert::IsTrue(t[0] == float4{1, 0, 0, 0});
		Assert::IsTrue(t[1] == float4{0, 1, 0, 0});
		Assert::IsTrue(t[2] == float4{0, 0, 1, 0});
		Assert::IsTrue(t[3] == float4{1, 2, 3, 1});
	}
	TEST_METHOD(scale) {
		auto t = matrix::scale({2,3,4});
		Assert::IsTrue(t[0] == float4{2, 0, 0, 0});
		Assert::IsTrue(t[1] == float4{0, 3, 0, 0});
		Assert::IsTrue(t[2] == float4{0, 0, 4, 0});
		Assert::IsTrue(t[3] == float4{0, 0, 0, 1});
	}
	TEST_METHOD(rotateX) {
		float r = toRadians(90);
		auto t = matrix::rotateX(r);
		Assert::IsTrue(t[0][0] == 1.0f);
		Assert::IsTrue(t[1][1] == cos(r));
		Assert::IsTrue(t[1][2] == sin(r));
		Assert::IsTrue(t[2][1] == -sin(r));
		Assert::IsTrue(t[2][2] == cos(r));
		Assert::IsTrue(t[3][3] == 1.0f);
	}
	TEST_METHOD(rotateY) {
		float r = toRadians(90);
		auto t = matrix::rotateY(r);
		Assert::IsTrue(t[0][0] == cos(r));
		Assert::IsTrue(t[0][2] == -sin(r));
		Assert::IsTrue(t[1][1] == 1.0f);
		Assert::IsTrue(t[2][0] == sin(r));
		Assert::IsTrue(t[2][2] == cos(r));
		Assert::IsTrue(t[3][3] == 1.0f);
	}
	TEST_METHOD(rotateZ) {
		float r = toRadians(90);
		auto t = matrix::rotateZ(r);

		Assert::IsTrue(t[0][0] == cos(r));
		Assert::IsTrue(t[0][1] == sin(r));
		Assert::IsTrue(t[1][0] == -sin(r));
		Assert::IsTrue(t[1][1] == cos(r));
		Assert::IsTrue(t[2][2] == 1.0f);
		Assert::IsTrue(t[3][3] == 1.0f);
	}
	TEST_METHOD(lookAtLH) {
		float3 eye{0,0,100};
		float3 target{0,0,0};
		float3 up{0,1,0};
		auto t = matrix::lookAtLH(eye, target, up);

		matrix m;
		m.toString();

	}
	TEST_METHOD(orthoLH) {

	}
	TEST_METHOD(perspectiveFovLH) {

	}
	TEST_METHOD(operator_neg) {

	}
	TEST_METHOD(operator_add_scalar) {

	}
	TEST_METHOD(operator_sub_scalar) {

	}
	TEST_METHOD(operator_mul_scalar) {

	}
	TEST_METHOD(operator_div_scalar) {

	}
	TEST_METHOD(operator_add_matrix) {

	}
	TEST_METHOD(operator_sub_matrix) {

	}
	TEST_METHOD(operator_mul_matrix) {

	}
	TEST_METHOD(operator_div_matrix) {

	}
	TEST_METHOD(operator_mul_vector4) {

	}
	TEST_METHOD(transposed) {
		
	}
	TEST_METHOD(determinant) {

	}
	TEST_METHOD(inversed) {

	}
};

}