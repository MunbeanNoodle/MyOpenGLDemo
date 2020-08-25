#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
using namespace std;

//顶点结构体
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

//纹理结构体
struct Texture
{
	unsigned int id;
	string type;
};

class Mesh
{
public:
	//网格数据
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	//函数
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader& shader);
	
private:
	//渲染数据
	unsigned int VAO, VBO, EBO;
	//函数
	void setupMesh();//初始化
};
#endif
