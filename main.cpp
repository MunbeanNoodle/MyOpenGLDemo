#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "Model.h"
#include "Light.h"

//窗口大小改变时，视口也应调整
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//简单的输入控制
void processInput(GLFWwindow *window);
//鼠标事件
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
//初始鼠标位置
float lastX = 400;
float lastY = 300;
//是否第一次获取鼠标输入
bool firstMouse = true;
//滚轮输入
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//立方体
Model cube;

//摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

//光源
Light light(1.2f, 1.0f, 2.0f);

//移动速度，时间差Deltatime
float deltaTime = 0.0f;//当前帧与上一帧的时间差
float lastFrame = 0.0f;//上一帧的时间

int main()
{
	//实例化GLFW窗口
	glfwInit();//初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//Mac OS X系统需要

	//创建窗口对象
	GLFWwindow *window = glfwCreateWindow(800, 600, "MyOpenGLDemo", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//通知GLFW将窗口上下文设置为当前线程的主上下文

	//GLAD管理OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//视口(Viewport)，即OpenGL渲染窗口的尺寸
	glViewport(0, 0, 800, 600);
	//注册视口调整回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube.vertices), cube.vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//灯立方体VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader ourShader("./shaders/shader.vs", "./shaders/shader.fs");
	Shader lampShader("./shaders/light_shader.vs", "./shaders/light_shader.fs");

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//观察矩阵
	glm::mat4 view;
	//投影矩阵
	glm::mat4 projection;
	//变换矩阵
	glm::mat4 trans(1.0f);
	
	//材质/纹理
	Material material("./textures/container2.jpg");
	material.genTexture();
	Material specMaterial("./textures/container2_specular.jpg");
	specMaterial.genTexture();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.ID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specMaterial.ID);

	ourShader.use();
	ourShader.setInt("material.diffuse", 0);
	ourShader.setInt("material.specular", 1);
	ourShader.setFloat("material.shininess", 32.0f);

	//定向光
	ourShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	ourShader.setVec3("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	ourShader.setVec3("dirLight.diffuse", glm::vec3(0.05f, 0.05f, 0.05));
	ourShader.setVec3("dirLight.specular", glm::vec3(0.2f, 0.2f, 0.2f));

	//点光源
	// point light 1
	ourShader.setVec3("pointLights[0].position", light.pointLightPositions[0]);
	ourShader.setVec3("pointLights[0].ambient", light.pointLightColors[0] * glm::vec3(0.1f));
	ourShader.setVec3("pointLights[0].diffuse", light.pointLightColors[0]);
	ourShader.setVec3("pointLights[0].specular", light.pointLightColors[0]);
	ourShader.setFloat("pointLights[0].constant", 1.0f);
	ourShader.setFloat("pointLights[0].linear", 0.14);
	ourShader.setFloat("pointLights[0].quadratic", 0.07);
	// point light 2
	ourShader.setVec3("pointLights[1].position", light.pointLightPositions[1]);
	ourShader.setVec3("pointLights[1].ambient", light.pointLightColors[1] * glm::vec3(0.1f));
	ourShader.setVec3("pointLights[1].diffuse", light.pointLightColors[1]);
	ourShader.setVec3("pointLights[1].specular", light.pointLightColors[1]);
	ourShader.setFloat("pointLights[1].constant", 1.0f);
	ourShader.setFloat("pointLights[1].linear", 0.14);
	ourShader.setFloat("pointLights[1].quadratic", 0.07);
	// point light 3
	ourShader.setVec3("pointLights[2].position", light.pointLightPositions[2]);
	ourShader.setVec3("pointLights[2].ambient", light.pointLightColors[2] * glm::vec3(0.1f));
	ourShader.setVec3("pointLights[2].diffuse", light.pointLightColors[2]);
	ourShader.setVec3("pointLights[2].specular", light.pointLightColors[2]);
	ourShader.setFloat("pointLights[2].constant", 1.0f);
	ourShader.setFloat("pointLights[2].linear", 0.14);
	ourShader.setFloat("pointLights[2].quadratic", 0.07);
	// point light 4
	ourShader.setVec3("pointLights[3].position", light.pointLightPositions[3]);
	ourShader.setVec3("pointLights[3].ambient", light.pointLightColors[3] * glm::vec3(0.1f));
	ourShader.setVec3("pointLights[3].diffuse", light.pointLightColors[3]);
	ourShader.setVec3("pointLights[3].specular", light.pointLightColors[3]);
	ourShader.setFloat("pointLights[3].constant", 1.0f);
	ourShader.setFloat("pointLights[3].linear", 0.14);
	ourShader.setFloat("pointLights[3].quadratic", 0.07);

	//聚光
	ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
	ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	ourShader.setFloat("spotLight.constant", 1.0f);
	ourShader.setFloat("spotLight.linear", 0.09);
	ourShader.setFloat("spotLight.quadratic", 0.032);
	ourShader.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	ourShader.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	ourShader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	//渲染循环/迭代
	while (!glfwWindowShouldClose(window))//每次循环开始检查GLFW是否被要求退出
	{

		processInput(window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//在循环开始时清屏
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		//模型矩阵
		glm::mat4 model(1.0f);

		//渲染指令
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.zoom), 1.0f * 800 / 600, 0.1f, 100.0f);

		//绘制灯光立方体
		lampShader.use();

		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, light.pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			trans = projection * view * model;		
			
			lampShader.setMat4("trans", trans);
			lampShader.setVec3("outColor", light.pointLightColors[i]);

			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//绘制目标立方体
		ourShader.use();

		ourShader.setVec3("viewPos", camera.m_position);
		//聚光
		ourShader.setVec3("spotLight.position", camera.m_position);
		ourShader.setVec3("spotLight.direction", camera.m_front);

		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cube.positions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			trans = projection * view * model;

			ourShader.setMat4("trans", trans);
			ourShader.setMat4("model", model);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//检查返回键（Esc）是否被按下
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
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
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