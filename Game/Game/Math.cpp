#include "Math.h"
#include <math.h>
#include <iostream>

namespace Math
{

	//Extra math

	template <typename T>
	constexpr auto Squared(const T& x)
	{
		return x * x;
	}

	//Vec2

	Vec2::Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float Vec2::LengthSquared()
	{
		return (float)Squared((Vec2)*this);
	}

	float Vec2::Length()
	{
		return sqrt(LengthSquared());
	}

	Vec2& Vec2::Normalize()
	{
		const float length = Length();
		x /= length;
		y /= length;
		return *this;
	}

	Vec2 Vec2::GetNormalized()
	{
		Vec2 v = *this;
		v.Normalize();
		return v;
	}

	float Vec2::operator*(const Vec2& v) const
	{
		return (x * v.x + y * v.y);
	}

	Vec2 Vec2::operator-()
	{
		return Vec2(-x, -y);
	}

	Vec2& Vec2::operator=(const Vec2& v)
	{
		x = v.x;
		y = v.y;
		return *this;

	}

	Vec2& Vec2::operator+=(const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& Vec2::operator-=(const Vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2& Vec2::operator*=(const float& f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	Vec2& Vec2::operator/=(const float& f)
	{
		x /= f;
		y /= f;
		return *this;
	}

	Vec2 Vec2::operator+(const Vec2& v) const
	{
		return Vec2(*this) += v;
	}

	Vec2 Vec2::operator-(const Vec2& v) const
	{
		return Vec2(*this) -= v;
	}

	Vec2 Vec2::operator*(const float& f) const
	{
		return Vec2(*this) *= f;
	}

	Vec2 Vec2::operator/(const float& f) const
	{
		return Vec2(*this) /= f;
	}

	bool Vec2::operator==(const Vec2& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool Vec2::operator!=(const Vec2& v) const
	{
		return !(*this == v);
	}

	//Vec3& Vec2::ToVec3(const Vec2& v)
	//{
	//	return Vec3(v.x, v.y, 0.0f);
	//}
	//
	//Vec4& Vec2::ToVec4(const Vec2& v)
	//{
	//	return Vec4(v.x, v.y, 0.0f);
	//}

	//Vec3

	Vec3::Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Vec3::LengthSquared()
	{
		return (float)Squared((Vec3)*this);
	}

	float Vec3::Length()
	{
		return sqrt(LengthSquared());
	}

	Vec3& Vec3::Normalize()
	{
		const float length = Length();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vec3 Vec3::GetNormalized()
	{
		Vec3 v = *this;
		v.Normalize();
		return v;
	}

	float Vec3::operator*(const Vec3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	Vec3 Vec3::operator-()
	{
		return Vec3(-x, -y, -z);
	}

	Vec3& Vec3::operator=(const Vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;

	}

	Vec3& Vec3::operator+=(const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec3& Vec3::operator-=(const Vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3& Vec3::operator*=(const float& f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Vec3& Vec3::operator/=(const float& f)
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	Vec3 Vec3::operator+(const Vec3& v) const
	{
		return Vec3(*this) += v;
	}

	Vec3 Vec3::operator-(const Vec3& v) const
	{
		return Vec3(*this) -= v;
	}

	Vec3 Vec3::operator*(const float& f) const
	{
		return Vec3(*this) *= f;
	}

	Vec3 Vec3::operator/(const float& f) const
	{
		return Vec3(*this) /= f;
	}

	bool Vec3::operator==(const Vec3& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	bool Vec3::operator!=(const Vec3& v) const
	{
		return !(*this == v);
	}

	//Vec2& Vec3::ToVec2(const Vec3& v)
	//{
	//	return Vec2(v.x, v.y);
	//}
	//
	//Vec4& Vec3::ToVec4(const Vec3& v)
	//{
	//	return Vec4(v.x, v.y, v.z);
	//}

	//Vec4

	Vec4::Vec4(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 0.0f;
	}

	Vec4::Vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float Vec4::LengthSquared()
	{
		return (float)Squared((Vec4)*this);
	}

	float Vec4::Length()
	{
		return sqrt(LengthSquared());
	}

	Vec4& Vec4::Normalize()
	{
		const float length = Length();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vec4 Vec4::GetNormalized()
	{
		Vec4 v = *this;
		v.Normalize();
		return v;
	}

	float Vec4::operator*(const Vec4& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	Vec4 Vec4::operator-()
	{
		return Vec4(-x, -y, -z, w);
	}

	Vec4& Vec4::operator=(const Vec4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;

	}

	Vec4& Vec4::operator+=(const Vec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec4& Vec4::operator-=(const Vec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec4& Vec4::operator*=(const float& f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Vec4& Vec4::operator/=(const float& f)
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	Vec4 Vec4::operator+(const Vec4& v) const
	{
		return Vec4(*this) += v;
	}

	Vec4 Vec4::operator-(const Vec4& v) const
	{
		return Vec4(*this) -= v;
	}

	Vec4 Vec4::operator*(const float& f) const
	{
		return Vec4(*this) *= f;
	}

	Vec4 Vec4::operator/(const float& f) const
	{
		return Vec4(*this) /= f;
	}

	bool Vec4::operator==(const Vec4& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	bool Vec4::operator!=(const Vec4& v) const
	{
		return !(*this == v);
	}

	//Vec2& Vec4::ToVec2(const Vec4& v)
	//{
	//	return Vec2(v.x, v.y);
	//}
	//
	//Vec3& Vec4::ToVec3(const Vec4& v)
	//{
	//	return Vec3(v.x, v.y, v.z);
	//}

	//Mat3

	Mat3::Mat3(const Mat3& m)
	{
		memcpy(this->elements, m.elements, sizeof(m.elements));
	}

	Mat3::Mat3(float f[3][3])
	{
		memcpy(this->elements, f, sizeof(f) * 9);
	}

	Mat3& Mat3::operator=(const Mat3& m)
	{
		memcpy(this->elements, m.elements, sizeof(m.elements));
		return *this;
	}

	Mat3& Mat3::operator*=(const float f)
	{
		for (auto& row : this->elements)
		{
			for (float& element : row)
			{
				element *= f;
			}
		}
		return *this;
	}

	Mat3& Mat3::operator*=(const Mat3& m)
	{
		Mat3 result;

		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				float sum = 0.0f;
				for (size_t i = 0; i < 3; i++)
				{
					sum += elements[j][i] * m.elements[i][k];
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}

	Mat3& Mat3::operator*(const float& f) const
	{
		Mat3 result = *this;
		return result *= f;
	}

	Mat3& Mat3::operator*(const Mat3& m) const
	{
		Mat3 result = *this;
		return result *= m;
	}

	Mat3 Mat3::operator!() const
	{
		Mat3 result;

		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				result.elements[j][k] = elements[k][j];
			}
		}

		return result;
	}

	Mat3& Mat3::Identity()
	{
		float array[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f } ,
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};


		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat3& Mat3::Scaling(float f)
	{
		float array[3][3] =
		{
			{    f, 0.0f, 0.0f } ,
			{ 0.0f,    f, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat3& Mat3::RotationZ(float theta)
	{
		const float sinTheta = sin(theta);
		const float cosTheta = cos(theta);

		float array[3][3] =
		{
			 cosTheta, sinTheta, 1.0f,
			-sinTheta, cosTheta, 1.0f,
				 0.0f,     0.0f, 1.0f
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat3& Mat3::Translation(const Vec2& v)
	{
		return Translation(v.x, v.y);
	}

	Mat3& Mat3::Translation(float x, float y)
	{
		float array[3][3] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			x,    y, 1.0f
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}
	
	Vec3 Math::operator*(const Vec3& lhs, const Mat3& rhs)
	{
		//float array[3] =
		Vec3 result =
		{
			lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0],
			lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1],
			lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2]

		};

		//memcpy(this->elements, array, sizeof(array));

		return result;
	}

	Vec3& operator*=(const Vec3& lhs, const Mat3& rhs)
	{
		Vec3& result = lhs * rhs;

		return result;// (lhs * rhs);
	}

	//Mat4

	Mat4::Mat4(const Mat4& m)
	{
		memcpy(this->elements, m.elements, sizeof(m.elements));
	}

	Mat4::Mat4(float f[4][4])
	{
		memcpy(this->elements, f, sizeof(f) * 16);
	}

	Mat4& Mat4::operator=(const Mat4& m)
	{
		memcpy(this->elements, m.elements, sizeof(m.elements));
		return *this;
	}

	Mat4& Mat4::operator*=(const float f)
	{
		for (auto& row : this->elements)
		{
			for (float& element : row)
			{
				element *= f;
			}
		}
		return *this;
	}

	Mat4& Mat4::operator*=(const Mat4& m)
	{
		Mat4 result;

		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				float sum = 0.0f;
				for (size_t i = 0; i < 4; i++)
				{
					sum += elements[j][i] * m.elements[i][k];
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}

	Mat4& Mat4::operator*(const float& f) const
	{
		Mat4 result = *this;
		return result *= f;
	}

	Mat4& Mat4::operator*(const Mat4& m) const
	{
		Mat4 result = *this;
		return result *= m;
	}

	Mat4 Mat4::operator!() const
	{
		Mat4 result;

		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				result.elements[j][k] = elements[k][j];
			}
		}

		return result;
	}

	Mat4& Mat4::Identity()
	{
		float array[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat4& Mat4::Scaling(float f)
	{
		float array[4][4] =
		{
			{    f, 0.0f, 0.0f, 1.0f } ,
			{ 0.0f,    f, 0.0f, 1.0f },
			{ 0.0f, 0.0f,    f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat4& Mat4::RotationZ(float theta)
	{
		const float sinTheta = sin(theta);
		const float cosTheta = cos(theta);

		float array[4][4] =
		{
			 cosTheta, sinTheta, 0.0f, 1.0f,
			-sinTheta, cosTheta, 0.0f, 1.0f,
				 0.0f,     0.0f, 1.0f, 1.0f,
				 0.0f,     0.0f, 0.0f, 1.0f
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat4& Mat4::RotationY(float theta)
	{
		const float sinTheta = sin(theta);
		const float cosTheta = cos(theta);

		float array[4][4] =
		{
		cosTheta, 0.0f, sinTheta, 1.0f,
			0.0f, 1.0f,     0.0f, 1.0f,
		-sinTheta, 0.0f, cosTheta, 1.0f,
			0.0f, 0.0f,     0.0f, 1.0f
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat4& Mat4::RotationX(float theta)
	{
		const float sinTheta = sin(theta);
		const float cosTheta = cos(theta);

		float array[4][4] =
		{
			1.0f,      0.0f,     0.0f, 1.0f,
			0.0f,  cosTheta, sinTheta, 1.0f,
			0.0f, -sinTheta, cosTheta, 1.0f,
			0.0f,      0.0f,     0.0f, 1.0f
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat4& Mat4::Translation(const Vec4& v)
	{
		return Translation(v.x, v.y, v.z);
	}

	Mat4& Mat4::Translation(float x, float y, float z)
	{
		float array[4][4] =
		{
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			   x,    y,    z, 1.0f
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Vec4 operator*(const Vec4& lhs, const Mat4& rhs)
	{
		//float array[3] =
		Vec4 result =
		{
			lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0] + lhs.z * rhs.elements[3][0],
			lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1] + lhs.z * rhs.elements[3][1],
			lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2] + lhs.z * rhs.elements[3][2],
			lhs.x * rhs.elements[0][3] + lhs.y * rhs.elements[1][3] + lhs.z * rhs.elements[2][3] + lhs.z * rhs.elements[3][3],
		};

		//memcpy(this->elements, array, sizeof(array));

		return result;
	}

	Vec4& operator*=(const Vec4& lhs, const Mat4& rhs)
	{
		Vec4& result = lhs * rhs;

		return result;// (lhs * rhs);
	}
} //namespace Math
