/*
	��Ӳ�̶�ȡ��ɫ����Ȼ����벢�������ǣ������д�����
*/

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

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

	//����ID
	unsigned int ID;
};

#endif

