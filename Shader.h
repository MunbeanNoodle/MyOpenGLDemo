/*
	��Ӳ�̶�ȡ��ɫ����Ȼ����벢�������ǣ������д�����
*/

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	//��ȡ��������ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//ʹ��/�������
	void use();
	//uniform���ߺ�������ѯuniform��λ�ò���������ֵ
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void setVec3(const std::string& name, glm::vec3 vec) const;
	void setMat4(const std::string& name, glm::mat4 mat) const;

	//����ID
	unsigned int ID;
};

#endif

