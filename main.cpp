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

//顶点数据
float vertices[] = 
{
	// positions          // normals           // texture coords
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
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

float fov = 45.0f;

//摄像机
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
Camera camera(cameraPos);

//移动速度，时间差Deltatime
float deltaTime = 0.0f;//当前帧与上一帧的时间差
float lastFrame = 0.0f;//上一帧的时间

//光照
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);//光源颜色
glm::vec3 objectColor(1.0f, 0.5f, 0.4f);//物体颜色

//光源位置
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//灯（光源）VAO
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
	//trans uniform location
	int transLoc;
	
	ourShader.use();
	//材质
	int ambientLoc = glGetUniformLocation(ourShader.ID, "material.ambient");
	glUniform3fv(ambientLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
	int diffuseLoc = glGetUniformLocation(ourShader.ID, "material.diffuse");
	glUniform3fv(diffuseLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
	int specularLoc = glGetUniformLocation(ourShader.ID, "material.specular");
	glUniform3fv(specularLoc, 1, glm::value_ptr(glm::vec3(0.5f)));
	int shininessLoc = glGetUniformLocation(ourShader.ID, "material.shininess");
	glUniform1f(shininessLoc, 32.0f);

	//光的属性
	//int lDirectionLoc = glGetUniformLocation(ourShader.ID, "light.direction");
	//glUniform3fv(lDirectionLoc, 1, glm::value_ptr(glm::vec3(-0.2f, -1.0f, -0.3f)));
	int lSpecularLoc = glGetUniformLocation(ourShader.ID, "light.specular");
	glUniform3fv(lSpecularLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	int lAmbientLoc = glGetUniformLocation(ourShader.ID, "light.ambient");
	glUniform3fv(lAmbientLoc, 1, glm::value_ptr(glm::vec3(0.2f)));
	int lDiffuseLoc = glGetUniformLocation(ourShader.ID, "light.diffuse");
	glUniform3fv(lDiffuseLoc, 1, glm::value_ptr(glm::vec3(0.8f)));
	//衰减
	/*glUniform1f(glGetUniformLocation(ourShader.ID, "light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(ourShader.ID, "light.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(ourShader.ID, "light.quadratic"), 0.032f);
	glUniform3fv(glGetUniformLocation(ourShader.ID, "light.position"), 1, glm::value_ptr(lightPos));*/
	//聚光/手电筒
	glUniform1f(glGetUniformLocation(ourShader.ID, "light.cutOff"), glm::cos(glm::radians(12.5f)));

	//纹理
	Material material("./textures/container2.jpg");
	material.genTexture();
	Material specMaterial("./textures/container2_specular.jpg");
	specMaterial.genTexture();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material.ID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specMaterial.ID);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(ourShader.ID, "material.specular"), 1);

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

		/*lightPos.x = sin(glfwGetTime())*3.0f;
		lightPos.z = cos(glfwGetTime())*3.0f;*/
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		trans = projection * view * model;

		transLoc = glGetUniformLocation(lampShader.ID, "trans");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(lightVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//绘制目标立方体
		ourShader.use();

		int vertexColorLocation = glGetUniformLocation(ourShader.ID, "lightColor");//查询uniform的位置
		glUniform3fv(vertexColorLocation, 1, glm::value_ptr(lightColor));

		vertexColorLocation = glGetUniformLocation(ourShader.ID, "objectColor");//查询uniform的位置
		glUniform3fv(vertexColorLocation, 1, glm::value_ptr(objectColor));

		int lightPosLoc = glGetUniformLocation(ourShader.ID, "lightPos");//查询uniform的位置
		glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

		int viewPosLoc = glGetUniformLocation(ourShader.ID, "viewPos");
		glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.m_position));

		//聚光/手电筒
		glUniform3fv(glGetUniformLocation(ourShader.ID, "light.position"), 1, glm::value_ptr(camera.m_position));
		glUniform3fv(glGetUniformLocation(ourShader.ID, "light.direction"), 1, glm::value_ptr(camera.m_front));

		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			trans = projection * view * model;

			transLoc = glGetUniformLocation(ourShader.ID, "trans");
			glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

			int modelLoc = glGetUniformLocation(ourShader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

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