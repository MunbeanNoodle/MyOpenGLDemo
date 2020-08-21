#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

//��������
float vertices[] = 
{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//10���������λ��
glm::vec3 cubePositions[] =
{
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
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
//����¼�
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
//��ʼ���λ��
float lastX = 400;
float lastY = 300;
//�Ƿ��һ�λ�ȡ�������
bool firstMouse = true;
//��������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float fov = 45.0f;

//�����
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
Camera camera(cameraPos);

//�ƶ��ٶȣ�ʱ���Deltatime
float deltaTime = 0.0f;//��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f;//��һ֡��ʱ��

//����
glm::vec3 lightColor(0.33f, 0.42f, 0.18f);//��Դ��ɫ�������
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);//������ɫ
glm::vec3 resultColor = lightColor * toyColor;//������ɫ

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��������
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader ourShader("./shaders/shader.vs", "./shaders/shader.fs");

	//��������ľ�䣩
	int width, height, nrChannels;
	unsigned char* data = stbi_load("./textures/container.jpg", &width, &height, &nrChannels, 0);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
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
		std::cout << "Failed to load texture1" << std::endl;
	}
	//�ͷ�ͼ���ڴ�
	//stbi_image_free(data);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("./textures/awesomeface.jpg", &width, &height, &nrChannels, 0);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
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
		std::cout << "Failed to load texture2" << std::endl;
	}
	//�ͷ�ͼ���ڴ�
	stbi_image_free(data);
	
	//ÿ����ɫ�������������ĸ�����Ԫ
	ourShader.use();
	ourShader.setInt("ourTexture1", 0);
	ourShader.setInt("ourTexture2", 1);
	
	//�۲����
	glm::mat4 view;

	//ͶӰ����
	glm::mat4 projection;

	//�任����
	glm::mat4 trans(1.0f);

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��׽��ꣻ���ع��
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//����¼�
	glfwSetCursorPosCallback(window, mouse_callback);
	//�����¼�
	glfwSetScrollCallback(window, scroll_callback);

	int ii = 0;

	//��Ⱦѭ��/����
	while (!glfwWindowShouldClose(window))//ÿ��ѭ����ʼ���GLFW�Ƿ�Ҫ���˳�
	{
		//std::cout << "Rendering\n" << std::endl;
		processInput(window);//������룬��ÿһ֡��������

		//
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//��ѭ����ʼʱ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//����������ɫ��״̬���á�
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ���壬������ɫ�������Ϊ������ɫ��״̬ʹ�á�
		glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ���

		//��Ⱦָ��
		//......
		ourShader.use();
		//����uniform��ɫ
		//float timeValue = float(glfwGetTime());//��ȡ����
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");//��ѯuniform ourColor��λ��
		glUniform3fv(vertexColorLocation, 1, glm::value_ptr(resultColor));
		
		//����Ԫ������Ƭ����ɫ�������ö������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.zoom), 1.0f * 800 / 600, 0.1f, 100.0f);

		for (unsigned int i = 0; i < 10; i++)
		{
			//ģ�;���
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f *(i + 1);
			angle += ii;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));//����������ת��������ת���ģ��ǶȲ�ͬ
			
			trans = projection * view * model;

			int transLoc = glGetUniformLocation(ourShader.ID, "trans");
			glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		ii = ii+1;
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProceesMouseScroll(yoffset);
}