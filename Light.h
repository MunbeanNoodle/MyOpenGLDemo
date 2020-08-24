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
};
#endif // !LIGHT_H

