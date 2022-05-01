#include "Camera3D.h"

Camera3D::Camera3D()
{
	cameraPosition = Vec4(0.0f, 0.0f, 3.0f);
	viewMatrix.Identity();
	scaling = 1.0f;
	angleX = 0.0;
	angleY = 0.0;
	angleZ = 0.0;
	posX = 0.0;
	posY = 0.0;
	posZ = 0.0;
}

Camera3D::~Camera3D()
{
}

Mat4& Camera3D::GetViewMatrix()
{
	Mat4 viewMatrix;
	viewMatrix.Identity();

	Mat4 translationMatrix;

	translationMatrix.Translation(posX, posY, posZ);

	Mat4 rotationMatrixX;
	Mat4 rotationMatrixY;
	Mat4 rotationMatrixZ;
	
	rotationMatrixX.RotationX(angleX);
	rotationMatrixY.RotationY(angleY);
	rotationMatrixZ.RotationZ(angleZ); 

	Mat4 rotationMatrixAll;

	rotationMatrixAll = rotationMatrixY * rotationMatrixX * rotationMatrixZ;

	Mat4 scalingMatrix;
	scalingMatrix.Scaling(scaling);

	//viewMatrix *= scalingMatrix * rotationMatrixAll * translationMatrix;
	viewMatrix *= scalingMatrix;
	viewMatrix *= rotationMatrixAll;
	viewMatrix *= translationMatrix;

	this->viewMatrix = viewMatrix;

	return this->viewMatrix;
}

void Camera3D::SetCameraPosition(const Vec4& newPosition)
{
	cameraPosition = newPosition;
}

void  Camera3D::CameraLookAt(const Vec4& cameraPosition, const Vec4& cameraTarget, const Vec4& upVector)
{
	this->cameraPosition = cameraPosition;

	Vec4& directionVector = (cameraPosition - cameraTarget).Normalize();

	Vec4& rightVector = CrossVec4(directionVector, upVector).Normalize();

	float viewArray[4][4] =
	{
		{     rightVector.x,     rightVector.y,     rightVector.z, 0.0f },
		{        upVector.x,        upVector.y,        upVector.z, 0.0f },
		{ directionVector.x, directionVector.y, directionVector.z, 0.0f },
		{              0.0f,              0.0f,              0.0f, 1.0f }
	};

	float positionArray[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ -cameraPosition.x, -cameraPosition.y, -cameraPosition.z, 1.0f }
	};

	Mat4& viewMatrix = Mat4(viewArray);
	Mat4& positionMatrix = Mat4(positionArray);

	viewMatrix *= positionMatrix;

	this->viewMatrix = viewMatrix;
}



void Camera3D::CameraRotate(float angleX, float angleY, float angleZ)
{
	Mat4 viewMatrix;
	Mat4 rotationMatrixX;
	Mat4 rotationMatrixY;
	Mat4 rotationMatrixZ;

	viewMatrix.Identity();
	rotationMatrixX.RotationX(angleX);
	rotationMatrixY.RotationY(angleY);
	rotationMatrixZ.RotationZ(angleZ);

	//viewMatrix *= rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	viewMatrix *= rotationMatrixY * rotationMatrixX * rotationMatrixZ;

	this->viewMatrix = viewMatrix;
}

Mat4 Camera3D::GetProjection()
{
	return this->projectionMatrix;
}

void Camera3D::SetProjection(Mat4 projectionMatrix)
{
	this->projectionMatrix = projectionMatrix;
}
