#pragma once

//Extra math
namespace Math
{
	template <typename T>
	constexpr auto Squared(const T& x);

	class Vec2
	{
	public:
		float x;
		float y;

		//Constructor
		Vec2(float x, float y);

		float LengthSquared();
		float Length();
		Vec2& Normalize();
		Vec2 GetNormalized();

		//Dot Product
		float operator*(const Vec2& v) const;

		//Inverse Vector
		Vec2 operator-();

		//ASSIGNMENT OPERATORS
		//Assignment
		Vec2& operator=(const Vec2& v);

		//Traslation
		Vec2& operator+=(const Vec2& v);
		Vec2& operator-=(const Vec2& v);

		//Scaling
		Vec2& operator*=(const float& f);
		Vec2& operator/=(const float& f);

		//ARITHMETIC OPERATORS
		Vec2 operator+(const Vec2& v) const;
		Vec2 operator-(const Vec2& v) const;
		Vec2 operator*(const float& f) const;
		Vec2 operator/(const float& f) const;

		//RELATIONAL OPERATORS
		//Equals
		bool operator==(const Vec2& v) const;
		//Not equals
		bool operator!=(const Vec2& v) const;

		//CASTING
		//Vec3& ToVec3(const Vec2& v);
		//Vec4& ToVec4(const Vec2& v);
	};

	class Vec3
	{
	public:
		float x;
		float y;
		float z;

		//Constructor
		Vec3(float x, float y, float z);

		float LengthSquared();
		float Length();
		Vec3& Normalize();
		Vec3 GetNormalized();

		//Dot Product
		float operator*(const Vec3& v) const;

		//Inverse Vector
		Vec3 operator-();

		//ASSIGNMENT OPERATORS
		//Assignment
		Vec3& operator=(const Vec3& v);

		//Traslation
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);

		//Scaling
		Vec3& operator*=(const float& f);
		Vec3& operator/=(const float& f);

		//ARITHMETIC OPERATORS
		Vec3 operator+(const Vec3& v) const;
		Vec3 operator-(const Vec3& v) const;
		Vec3 operator*(const float& f) const;
		Vec3 operator/(const float& f) const;

		//RELATIONAL OPERATORS
		//Equals
		bool operator==(const Vec3& v) const;
		//Not equals
		bool operator!=(const Vec3& v) const;

		//CASTING
		//Vec2& ToVec2(const Vec3& v);
		//Vec4& ToVec4(const Vec3& v);
	};

	class Vec4
	{
	public:
		float x;
		float y;
		float z;
		float w;

		//Constructors
		Vec4() = default;
		Vec4(float x, float y, float z);
		Vec4(float x, float y, float z, float w);

		float LengthSquared();
		float Length();
		Vec4& Normalize();
		Vec4 GetNormalized();

		//Dot Product
		float operator*(const Vec4& v) const;

		//Inverse Vector
		Vec4 operator-();

		//ASSIGNMENT OPERATORS
		//Assignment
		Vec4& operator=(const Vec4& v);

		//Traslation
		Vec4& operator+=(const Vec4& v);
		Vec4& operator-=(const Vec4& v);

		//Scaling
		Vec4& operator*=(const float& f);
		Vec4& operator/=(const float& f);

		//ARITHMETIC OPERATORS
		Vec4 Vec4::operator+(const Vec4& v) const;
		Vec4 Vec4::operator-(const Vec4& v) const;
		Vec4 Vec4::operator*(const float& f) const;
		Vec4 Vec4::operator/(const float& f) const;

		//RELATIONAL OPERATORS
		//Equals
		bool Vec4::operator==(const Vec4& v) const;
		//Not equals
		bool Vec4::operator!=(const Vec4& v) const;

		//CASTING
		Vec2& Vec4::ToVec2(const Vec4& v);
		Vec3& Vec4::ToVec3(const Vec4& v);
	};


	class Mat3
	{
	public:
		float elements[3][3]; //[row][column]

		//Constructor
		Mat3() = default;

		//Copy-constructors
		Mat3(const Mat3& m);
		Mat3(float f[3][3]);

		//ASSIGNMENT OPERATORS
		//Assign
		Mat3& operator=(const Mat3& m);

		//Matrix Scaling
		Mat3& operator*=(const float f);

		//Matrix-matrix multiplication
		Mat3& operator*=(const Mat3& m);

		//ARITHMETIC OPERATORS
		Mat3& operator*(const float& f) const;
		Mat3& operator*(const Mat3& m) const;

		//SPECIAL MATRICES
		//Inverse Matrix
		Mat3 operator!() const;

		//Identity Matrix
		Mat3& Identity();

		//Scaling Matrix
		Mat3& Scaling(float f);

		//Rotation Matrices
		Mat3& RotationZ(float theta); // In 2D only rotation around the Z axis is meaningful 

		//Matrix-vector opertaions
		Mat3& Translation(const Vec2& v);
		Mat3& Translation(float x, float y);
		Vec3& operator*(const Vec3 rhs);
	};

	Vec3 operator*(const Vec3& lhs, const Mat3& rhs);
	Vec3& operator*=(const Vec3& lhs, const Mat3& rhs);

	class Mat4
	{
	public:
		float elements[4][4]; //[row][column]

		//Constructor
		Mat4() = default;

		//Copy-constructors
		Mat4(const Mat4& m);
		Mat4(float f[4][4]);

		//ASSIGNMENT OPERATORS
		//Assign
		Mat4& operator=(const Mat4& m);

		//Matrix Scaling
		Mat4& operator*=(const float f);

		//Matrix-matrix multiplication
		Mat4& operator*=(const Mat4& m);

		//ARITHMETIC OPERATORS
		Mat4& operator*(const float& f) const;
		Mat4& operator*(const Mat4& m) const;

		//SPECIAL MATRICES
		//Inverse Matrix
		Mat4 operator!() const;

		//Identity Matrix
		Mat4& Identity();

		//Scaling Matrix
		Mat4& Scaling(float f);

		//Rotation Matrices
		Mat4& RotationZ(float theta);
		Mat4& RotationY(float theta);
		Mat4& RotationX(float theta);

		//Matrix-vector opertaions
		Mat4& Translation(const Vec4& v);
		Mat4& Translation(float x, float y, float z);
		Vec4 operator*(const Mat4& rhs);
	};

	Vec4 operator*(const Vec4& lhs, const Mat4& rhs);
	Vec4& operator*=(const Vec4& lhs, const Mat4& rhs);

} //namespace Math