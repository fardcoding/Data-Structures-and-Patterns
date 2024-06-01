#include "Matrix3x3.h"

#include <math.h>
#include <assert.h>
#include <sstream>

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept {
	Vector3D resultRow1(
		row(0).dot(aOther.column(0)),

		row(0).dot(aOther.column(1)),

		row(0).dot(aOther.column(2))
	);

	Vector3D resultRow2(
		(row(1).dot(aOther.column(0))),

		(row(1).dot(aOther.column(1))),

		(row(1).dot(aOther.column(2)))
	);

	Vector3D resultRow3(
		row(2).dot(aOther.column(0)),

		row(2).dot(aOther.column(1)),

		row(2).dot(aOther.column(2))

	);

	return Matrix3x3(resultRow1, resultRow2, resultRow3);
}

float Matrix3x3::det() const noexcept {
	float result = 0.0f;

	result += row(0)[0] * (row(1)[1]) * row(2)[2] - row(1)[2] * row(2)[1];

	result -= row(0)[1] * (row(1)[0] * row(2)[2] - row(1)[2] * row(2)[0]);

	result += row(0)[2] * (row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0]);

	return result;
}

Matrix3x3 Matrix3x3::transpose() const noexcept {

	return Matrix3x3(column(0), column(1), column(2));
}

bool Matrix3x3::hasInverse() const noexcept {

	return (det() != 0) ? true : false;
}

Matrix3x3 Matrix3x3::inverse() const noexcept {
	assert(det() != 0);
	//First row of the result matrix
	Vector3D resultRow1(
		row(1)[1] * row(2)[2] - row(1)[2] * row(2)[1],

		row(0)[2] * row(2)[1] - row(0)[1] * row(2)[2],

		row(0)[1] * row(1)[2] - row(0)[2] * row(1)[1]
	);

	//Second row of the result matrix
	Vector3D resultRow2(

		row(1)[2] * row(2)[0] - row(1)[0] * row(2)[2],

		row(0)[0] * row(2)[2] - row(0)[2] * row(2)[0],

		row(0)[2] * row(1)[0] - row(0)[0] * row(1)[2]
	);
	//Third row of the result matrix
	Vector3D resultRow3(
		

		row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0],

		row(0)[1] * row(2)[0] - row(0)[0] * row(2)[1],

		row(0)[0] * row(1)[1] - row(0)[1] * row(1)[0]
	);


	return Matrix3x3(resultRow1, resultRow2, resultRow3) * (1 / (det()));
}

std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix) {
	return aOStream << "[" << aMatrix.row(0).toString()

		<< "," << aMatrix.row(1).toString()

		<< "," << aMatrix.row(2).toString() << "]";
}