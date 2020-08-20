/*
	从硬盘读取着色器，然后编译并链接它们，并进行错误检测
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
	//读取并构建着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//使用/激活程序
	void use();
	//uniform工具函数：查询uniform的位置并设置它的值
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	//程序ID
	unsigned int ID;
};

#endif

