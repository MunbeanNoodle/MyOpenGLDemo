#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
using namespace std;

//����ṹ��
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

//����ṹ��
struct Texture
{
	unsigned int id;
	string type;
};

class Mesh
{
public:
	//��������
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	//����
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader& shader);
	
private:
	//��Ⱦ����
	unsigned int VAO, VBO, EBO;
	//����
	void setupMesh();//��ʼ��
};
#endif
