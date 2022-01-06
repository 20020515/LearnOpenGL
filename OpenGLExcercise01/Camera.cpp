#include "Camera.h"
#include<iostream>
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	Forward = glm::normalize(target - position);
	WorldUp = worldup;
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Forward, Right);
		
}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Forward, Right);
}
Camera::~Camera()
{
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position,Position+Forward,WorldUp);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * SenseX;
	Yaw -= deltaX*SenseY;
	UpdateCameraVectors();
}

void Camera::ProcessPositionMovement(float lastW, float lastA, float lastD, float lastS)
{
	UpdateCameraMovement(lastW,lastA, lastD,lastS);
}

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::cross(Forward, WorldUp);
	Up = glm::cross(Forward, Right);
}

void Camera::UpdateCameraMovement(float lastW, float lastA, float lastD, float lastS)
{
	float z = lastW - lastS;
	float x = lastA - lastD;
	float y = 0;
	glm::vec3 movement(z, y, x);
	float moveSpeed = 0.01f;
	float Vec3mode = sqrt(x * x + y * y + z * z);
	if (lastW > 0) {
		Position += Vec3mode* moveSpeed * Forward;
	}
	else if (lastS > 0) {
		Position -= Vec3mode * moveSpeed * Right;
		
	}
	else if (lastD > 0) {
		Position += Vec3mode* moveSpeed * Right;
	}
	else if (lastA > 0) {
		Position -= Vec3mode * moveSpeed * Forward;
	}
	std::cout << Position.x << " " << Position.y <<" " << Position.z << std::endl;
}
