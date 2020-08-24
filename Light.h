#ifndef LIGHT_H
#define LIGHT

#include <glm/glm.hpp>

class Light
{
public:
	Light(const glm::vec3& position)
	{
		m_position = position;
	}
	Light(float x, float y, float z)
	{
		m_position = glm::vec3(x, y, z);
	}
	
	glm::vec3 m_position;
	//点光源位置
	glm::vec3 pointLightPositions[4] =
	{
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
};
#endif // !LIGHT_H

