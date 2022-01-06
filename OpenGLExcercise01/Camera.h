#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	~Camera();
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	glm::mat4 GetViewMatrix();
	float Pitch;
	float Yaw;
	float SenseX = 0.001f;
	float SenseY = 0.001f;
	void ProcessMouseMovement(float deltaX, float deltaY);
	void ProcessPositionMovement(float lastW, float lastA, float lastD, float lastS);
private:
	void UpdateCameraVectors();
	void UpdateCameraMovement(float lastW, float lastA, float lastD, float lastS);
	
};
#endif

