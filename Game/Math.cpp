#include "Math.h"
#include <math.h>
#include <iostream>
#include "RendererFront.h"

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
		this->w = 1.0f;
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
		w = v.w;
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
	
	Vec3 operator*(const Vec3& lhs, const Mat3& rhs)
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

	Vec3 operator*=(const Vec3& lhs, const Mat3& rhs)
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
					sum += this->elements[j][i] * m.elements[i][k];
				}
				result.elements[j][k] = sum;
			}
		}

		memcpy(this->elements, result.elements, sizeof(result.elements));

		return *this;
	}

	//Mat4& Mat4::operator*(const float& f) const
	//{
	//	Mat4 result = *this;
	//	return result *= f;
	//}

	//Mat4& Mat4::operator*(const Mat4& m) const
	//{
	//	//BAD
	//	//Mat4 result = *this;
	//	//return result *= m;

	//	//BAD
	//	//Mat4& result = (Mat4)*this;
	//	//return result *= m;

	//	//GOOD
	//	//Mat4& result = (Mat4&)*this;
	//	//result *= m;
	//	//return (Mat4&)*this;

	//	//GOOD
	//	//Mat4& result = (Mat4&)*this;
	//	//result *= m;
	//	//return result;

	//	//BAD
	//	Mat4 result = *this;
	//	result *= m;
	//	return result;
	//}


	Mat4 Mat4::operator*(const float& f) const
	{
		Mat4 result = *this;
		return result *= f;
	}

	Mat4 Mat4::operator*(const Mat4& m) const
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
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat4& Mat4::Scaling(float f)
	{
		float array[4][4] =
		{
			{    f, 0.0f, 0.0f, 0.0f } ,
			{ 0.0f,    f, 0.0f, 0.0f },
			{ 0.0f, 0.0f,    f, 0.0f },
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
			 cosTheta, sinTheta, 0.0f, 0.0f,
			-sinTheta, cosTheta, 0.0f, 0.0f,
				 0.0f,     0.0f, 1.0f, 0.0f,
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
		 cosTheta, 0.0f, sinTheta, 0.0f,
		 	 0.0f, 1.0f,     0.0f, 0.0f,
		-sinTheta, 0.0f, cosTheta, 0.0f,
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
			1.0f,      0.0f,     0.0f, 0.0f,
			0.0f,  cosTheta, sinTheta, 0.0f,
			0.0f, -sinTheta, cosTheta, 0.0f,
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
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			   x,    y,    z, 1.0f
		};

		memcpy(this->elements, array, sizeof(array));

		return *this;
	}

	Mat4& Mat4::ProjectPerspective(float fov, float aspectRatioMeh, float nearPlane, float farPlane)
	{
		float tanHalfTheta = tanf(Math::DegreeToRadian(fov * 0.5));
		float scale = 1.0f / tanHalfTheta;

		float aspectRatio = (float)RendererFront::GetWindowHeight() / (float)RendererFront::GetWindowWidth();

		Mat4& matrix = *this;

		matrix.Identity();

		//matrix.elements[0][0] = scale; // Scale the X coordinates of the projected point
		//matrix.elements[1][1] = aspectRatioMeh * scale;  // Scale the Y coordinates of the projected point fixed by the aspect ratio
		//matrix.elements[2][2] = -farPlane / (farPlane - nearPlane);
		//matrix.elements[3][2] = -farPlane * nearPlane / (farPlane - nearPlane);
		//matrix.elements[2][3] = -1;
		//matrix.elements[3][3] = 0;

		//matrix.elements[0][0] = 1;//aspectRatio* scale; // Scale the X coordinates of the projected point
		//matrix.elements[1][1] = 1;//scale;  // Scale the Y coordinates of the projected point fixed by the aspect ratio
		//matrix.elements[2][2] = 1;//farPlane / (farPlane - nearPlane);
		//matrix.elements[3][2] = 0;//(-farPlane * nearPlane) / (farPlane - nearPlane);
		//matrix.elements[2][3] = 0;//-1.0f;
		//matrix.elements[3][3] = 1.0f;

		matrix.elements[0][0] = 1;//aspectRatio* scale; // Scale the X coordinates of the projected point
		matrix.elements[1][1] = 1;//scale;  // Scale the Y coordinates of the projected point fixed by the aspect ratio
		matrix.elements[2][2] = (-farPlane) / (farPlane - nearPlane);
		matrix.elements[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
		matrix.elements[2][3] = -1.0f;
		matrix.elements[3][3] = 0.0f;


		return *this;
	}


	Vec4 operator*(const Vec4& lhs, const Mat4& rhs)
	{
		//float array[3] =
		Vec4 result =
		{
			//lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0] + lhs.w * rhs.elements[3][0],
			//lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1] + lhs.w * rhs.elements[3][1],
			//lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2] + lhs.w * rhs.elements[3][2],
			//1.0f
			////lhs.x * rhs.elements[0][3] + lhs.y * rhs.elements[1][3] + lhs.z * rhs.elements[2][3] + lhs.w * rhs.elements[3][3],

			//lhs.x* rhs.elements[0][0] + lhs.y * rhs.elements[0][1] + lhs.z * rhs.elements[0][2] + lhs.z * rhs.elements[0][3],
			//lhs.x* rhs.elements[1][0] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[1][2] + lhs.z * rhs.elements[1][3],
			//lhs.x* rhs.elements[2][0] + lhs.y * rhs.elements[2][1] + lhs.z * rhs.elements[2][2] + lhs.z * rhs.elements[2][3],
			//lhs.x* rhs.elements[3][0] + lhs.y * rhs.elements[3][1] + lhs.z * rhs.elements[3][2] + lhs.z * rhs.elements[3][3],

			lhs.x* rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0] + lhs.w * rhs.elements[3][0],
			lhs.x* rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1] + lhs.w * rhs.elements[3][1],
			lhs.x* rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2] + lhs.w * rhs.elements[3][2],
			lhs.x* rhs.elements[0][3] + lhs.y * rhs.elements[1][3] + lhs.z * rhs.elements[2][3] + lhs.w * rhs.elements[3][3],

			//lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0] + rhs.elements[3][0],
			//lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1] + rhs.elements[3][1],
			//lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2] + rhs.elements[3][2],
			////0.0f
			//lhs.x* rhs.elements[0][3] + lhs.y * rhs.elements[1][3] + lhs.z * rhs.elements[2][3] + rhs.elements[3][3]
		};

		//float w = lhs.x * rhs.elements[0][3] + lhs.y * rhs.elements[1][3] + lhs.z * rhs.elements[2][3] + rhs.elements[3][3];

		//if (w != 0.0f)
		//{
		//	result.x /= w;
		//	result.y /= w;
		//	result.z /= w;
		//}

		//memcpy(this->elements, array, sizeof(array));

		return result;
	}

	Vec4& operator*=(const Vec4& lhs, const Mat4& rhs)
	{
		Vec4 result = lhs * rhs;

		return result;// (lhs * rhs);
	}

	Vec3 CrossVec3(const Vec3& v1, const Vec3& v2)
	{
		float resX = v1.y * v2.z - v1.z * v2.y;
		float resY = v1.z * v2.x - v1.x * v2.z;
		float resZ = v1.x * v2.y - v1.y * v2.x;

		return Vec3(resX, resY, resZ);

	}

	Vec4 CrossVec4(const Vec4& v1, const Vec4& v2)
	{
		Vec3 vec1 = Vec3(v1.x, v1.y, v1.z);
		Vec3 vec2 = Vec3(v2.x, v2.y, v2.z);
		Vec3 res = CrossVec3(vec1, vec2);

		return Vec4(res.x, res.y, res.z, 1);
	}

	Vertex::Vertex(Vec4& pos)
	{
		this->pos = pos;
	}

	Vertex::Vertex(float x, float y, float z)
	{
		this->pos = Vec4(x, y, z, 1.0f);
	}

	Vertex::Vertex(Vec4& pos, Vec4& color)
	{
		this->pos = pos;
		this->color = color;
	}

	Vertex::Vertex(Vec4& pos, Vec2& uv)
	{
		this->pos = pos;
		this->uv = uv;
	}

	void Sort(Vertex& v0, Vertex& v1, Vertex& v2)
	{
		if (v1.pos.y < v0.pos.y)
		{
			Swap(v0, v1);
		}

		if (v2.pos.y < v1.pos.y)
		{
			Swap(v1, v2);
			if (v1.pos.y < v0.pos.y)
			{
				Swap(v0, v1);
			}
		}
	}

	void Swap(float& f0, float& f1)
	{
		float temp = f0;
		f0 = f1;
		f1 = temp;
	}

	void Swap(Vertex& v0, Vertex& v1)
	{
		Vertex temp = v0;
		v0 = v1;
		v1 = temp;
	}

	float DegreeToRadian(float degree)
	{
		return degree * 3.14159f / 180.0f;
	}

	void Triangle::DoProject(Mat4& projMatrix, float screenWidth, float screenHeight)
	{
		this->v0.pos *= projMatrix;
		this->v1.pos *= projMatrix;
		this->v2.pos *= projMatrix;

		//////objectVertex.pos.z += 3.0f;


		//Disable these to switch off projection
		if (v0.pos.w != 0)
		{
			v0.pos.x /= v0.pos.z;
			v0.pos.y /= v0.pos.z;
		}					   
		if (v1.pos.w != 0)	   
		{					   
			v1.pos.x /= v1.pos.z;
			v1.pos.y /= v1.pos.z;
		}					   
		if (v2.pos.w != 0)	   
		{					   
			v2.pos.x /= v2.pos.z;
			v2.pos.y /= v2.pos.z;
		}

		v0.pos.x = (v0.pos.x + 1.0f) * screenWidth * 0.5f;
		v0.pos.y = (v0.pos.y + 1.0f) * screenHeight * 0.5f;
		v1.pos.x = (v1.pos.x + 1.0f) * screenWidth * 0.5f;
		v1.pos.y = (v1.pos.y + 1.0f) * screenHeight * 0.5f;
		v2.pos.x = (v2.pos.x + 1.0f) * screenWidth * 0.5f;
		v2.pos.y = (v2.pos.y + 1.0f) * screenHeight * 0.5f;
	}


	Vec4 Math::LinePlaneIntersection(Vec4& planePoint, Vec4& planeNormal, Vec4& linePoint0, Vec4& linePoint1, float& t)
	{
		planeNormal = planeNormal.Normalize();
		
		//Using DotProducts
		float planeD = -(planeNormal * planePoint);
		float point0D = linePoint0 * planeNormal;
		float point1D = linePoint1 * planeNormal;

		t = (-planeD - point0D) / (point1D - point0D);
		Vec4 lineStartToEnd = linePoint1 - linePoint0;
		Vec4 lineToIntersect = lineStartToEnd * t;

		return linePoint0 + lineToIntersect;
	}

	float Math::DistanceFromPointToPlane(Vec4& planePoint, Vec4& planeNormal, Vec4& point)
	{
//		Vec4 pointNormalized = point.Normalize();
		return (planeNormal.x * point.x + planeNormal.y * point.y + planeNormal.z * point.z - (planeNormal * planePoint)); //Last one is DotProd

		//vec3d n = VectorNormalize(p);
		//return (plane_n.x * p.x + plane_n.y * y * p.y + plane_n.z * p.z - DotProd(plane_n, plane_p));
	}

	int Math::ClipTriangle(Vec4& planePoint, Vec4& planeNormal, Triangle& triangle, Triangle& triangleClipped0, Triangle& triangleClipped1)
	{
		planeNormal = planeNormal.Normalize();

		int pointsInsideCount = 0;
		int pointsOutsideCount = 0;
		Vec4 pointsInside[3];
		Vec4 pointsOutside[3];

		float distanceP0 = DistanceFromPointToPlane(planePoint, planeNormal, triangle.v0.pos);
		float distanceP1 = DistanceFromPointToPlane(planePoint, planeNormal, triangle.v1.pos);
		float distanceP2 = DistanceFromPointToPlane(planePoint, planeNormal, triangle.v2.pos);

		if (distanceP0 >= 0)
		{
			pointsInside[pointsInsideCount] = triangle.v0.pos;
			pointsInsideCount++;
		}
		else
		{
			pointsOutside[pointsOutsideCount] = triangle.v0.pos;
			pointsOutsideCount++;
		}

		if (distanceP1 >= 0)
		{
			pointsInside[pointsInsideCount] = triangle.v1.pos;
			pointsInsideCount++;
		}
		else
		{
			pointsOutside[pointsOutsideCount] = triangle.v1.pos;
			pointsOutsideCount++;
		}

		if (distanceP2 >= 0)
		{
			pointsInside[pointsInsideCount] = triangle.v2.pos;
			pointsInsideCount++;
		}
		else
		{
			pointsOutside[pointsOutsideCount] = triangle.v2.pos;
			pointsOutsideCount++;
		}

		if (pointsInsideCount == 0)
		{
			return 0;
		}

		if (pointsInsideCount == 3)
		{
			triangleClipped0 = triangle;
			return 1;
		}

		if (pointsInsideCount == 1 && pointsOutsideCount == 2)
		{
			float t = 0; //Distance from plane
			//Code-It-Yourself! 3D Graphics Engine Part #4 - Texturing & Depth Buffers 11:41

			//Triangle needs clipping
			
			triangleClipped0.v0 = pointsInside[0];
			triangleClipped0.v1 = Math::LinePlaneIntersection(planePoint, planeNormal, pointsInside[0], pointsOutside[0], t);
			triangleClipped0.v2 = Math::LinePlaneIntersection(planePoint, planeNormal, pointsInside[0], pointsOutside[1], t);

			return 1;
		}

		if (pointsInsideCount == 2 && pointsOutsideCount == 1)
		{
			float t = 0; //Distance from plane

			//Triangle needs clipping
			triangleClipped0.v0 = pointsInside[0];
			triangleClipped0.v1 = pointsInside[1];
			triangleClipped0.v2 = Math::LinePlaneIntersection(planePoint, planeNormal, pointsInside[0], pointsOutside[0], t);

			triangleClipped1.v0 = pointsInside[1];
			//triangleClipped1.v1 = triangleClipped0.v2; //Math::LinePlaneIntersection(planePoint, planeNormal, pointsInside[0], pointsOutside[0], t);
			triangleClipped1.v1 = Math::LinePlaneIntersection(planePoint, planeNormal, pointsInside[0], pointsOutside[0], t);
			triangleClipped1.v2 = Math::LinePlaneIntersection(planePoint, planeNormal, pointsInside[1], pointsOutside[0], t);

			return 2;
		}

	}

	Plane::Plane(Vec4 planePoint, Vec4 planeNormal)
	{
		this->planePoint = planePoint;
		this->planeNormal = planeNormal;
	}

} //namespace Math
