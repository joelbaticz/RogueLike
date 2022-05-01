#pragma once
#include "Math.h"

using namespace Math;

class Camera3D
{
private:
	Vec4 cameraPosition = Vec4();
	Mat4 viewMatrix = Mat4();
	Mat4 projectionMatrix = Mat4();

	void CalculateCameraMatrix();
public:
	float scaling;
	float angleX;
	float angleY;
	float angleZ;
	float posX;
	float posY;
	float posZ;

	Camera3D();
	~Camera3D();

	
	void SetCameraPosition(const Vec4& newPosition);
	void CameraLookAt(const Vec4& cameraPosition, const Vec4& cameraTarget, const Vec4& upVector);
	void CameraRotate(float angleX, float angleY, float angleZ);
	Mat4 GetProjection();
	void SetProjection(Mat4 projectionMatrix);
	Mat4& GetViewMatrix();
};
