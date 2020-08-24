#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW,
		float pitch = PITCH) :
		m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movement_speed(SPEED),
		mouse_sensitivity(SENSITIVITY),
		zoom(ZOOM)
	{
		m_position = position;
		m_worldUp = up;
		m_yaw = yaw;
		m_pitch = pitch;
		updateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
		m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
		movement_speed(SPEED),
		mouse_sensitivity(SENSITIVITY),
		zoom(ZOOM)
	{
		m_position = glm::vec3(posX, posY, posZ);
		m_worldUp = glm::vec3(upX, upY, upZ);
		m_yaw = yaw;
		m_pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constainPitch = true);
	void ProceesMouseScroll(float yoffset);

	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;

	float movement_speed;
	float mouse_sensitivity;
	float zoom;

private:
	void updateCameraVectors();
};

#endif

