#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"

//��������
//float vertices[] =
//{
//	//��һ��������
//	 0.5f,  0.5f,  0.0f,//���Ͻ�
//	 0.5f, -0.5f,  0.0f,//���½�
//	-0.5f,  0.5f,  0.0f,//���Ͻ�
//	//�ڶ���������
//	 0.5f, -0.5f,  0.0f,//���½�
//	-0.5f, -0.5f,  0.0f,//���½�
//	-0.5f,  0.5f,  0.0f,//���Ͻ�
//};
//���ظ�����
float vertices[] =
{	
	//λ��					//��ɫ				//��������
	 0.5f,  0.5f,  0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,//���Ͻ�
	 0.5f, -0.5f,  0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,//���½�
	-0.5f, -0.5f,  0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,//���½�
	-0.5f,  0.5f,  0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f//���Ͻ�
};
//float vertices[] =
//{	//λ��					//��ɫ
//	  0.5f, -0.5f,  0.0f,	1.0f,  0.0f,  0.0f,//���Ͻ�
//	 -0.5f, -0.5f,  0.0f,	0.0f,  1.0f,  0.0f,//���½�
//	  0.0f,  0.5f,  0.0f,	0.0f,  0.0f,  1.0f//����
//};

float texCoordsp[] =
{
	0.0f, 0.0f,//����
	1.0f, 0.0f,//����
	0.5f, 1.0f//����
};

//������������������(Indexed Drawing)
unsigned int indices[] =
{
	0, 1, 3, //��һ��������
	1, 2, 3  //�ڶ���������
};

//���ڴ�С�ı�ʱ���ӿ�ҲӦ����
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//�򵥵��������
void processInput(GLFWwindow *window);

int main()
{
	//ʵ����GLFW����
	glfwInit();//��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//para1��ѡ������ƣ����Ժܶ���GLFW_��ͷ��ö��ֵ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//para2����һ�����ͣ����������ѡ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//Mac OS Xϵͳ��Ҫ

	//�������ڶ���
	GLFWwindow *window = glfwCreateWindow(800, 600, "MyOpenGLDemo", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//֪ͨGLFW����������������Ϊ��ǰ�̵߳���������

	//GLAD����OpenGL����ָ��
	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//�ӿ�(Viewport)����OpenGL��Ⱦ���ڵĳߴ�
	glViewport(0, 0, 800, 600);//para1��para2���ƴ������½ǵ�λ�ã�para3��para4������Ⱦ���ڿ�Ⱥ͸߶�
	//ע���ӿڵ����ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//�����������(Vertex Array Object, VAO)��֮��Ķ������Ե��ö��ᴢ�������VAO��
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//���㻺�����(Vertex Buffer Object, VBO)���Ѷ������ݴ������Կ����ڴ���
	unsigned int VBO;//ID
	glGenBuffers(1, &VBO);//����VBO����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�Ѷ���Ķ������ݸ��Ƶ�������ڴ���
	//GL_STATIC_DRAW ����(����)����ı�; GL_DYNAMIC_DRAW ���ݻ�ı�; GL_STREAM_DRAW ����ÿ�λ���ʱ����ı�

	//�����������(Element Buffer Object, EBO or Index Buffer Object, IBO)�����治ͬ�ĵ�
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//�������Ķ�������������
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	//���Ӷ������ԣ������ֶ�ָ���������ݵ���һ���ֶ�Ӧ������ɫ������һ����������
	//λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader ourShader("./shaders/shader.vs", "./shaders/shader.fs");

	//��������ľ�䣩
	int width, height, nrChannels;
	unsigned char* data = stbi_load("./textures/container.jpg", &width, &height, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//���û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		//��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//����mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//�ͷ�ͼ���ڴ�
	stbi_image_free(data);

	//��Ⱦѭ��/����
	while (!glfwWindowShouldClose(window))//ÿ��ѭ����ʼ���GLFW�Ƿ�Ҫ���˳�
	{
		//std::cout << "Rendering\n" << std::endl;
		processInput(window);//������룬��ÿһ֡��������

		//��ѭ����ʼʱ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//����������ɫ��״̬���á�
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ���壬������ɫ�������Ϊ������ɫ��״̬ʹ�á�

		//��Ⱦָ��
		//......
		ourShader.use();
		//����uniform��ɫ
		//float timeValue = float(glfwGetTime());//��ȡ����
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//��ѯuniform ourColor��λ��
		////glUseProgram(shaderProgram);//����uniform������ʹ��shaderProgram
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ(Wireframe Mode)��para1 ָӦ�õ�������������������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);//������ɫ���壨����GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩���ڱ���ѭ�����������Ʋ����
		glfwPollEvents();//����Ƿ񴥷��¼����������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����
	}

	//�ͷ�/ɾ�����з������Դ
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//��鷵�ؼ���Esc���Ƿ񱻰���
	{
		glfwSetWindowShouldClose(window, true);
	}
}