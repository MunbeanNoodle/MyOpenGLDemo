#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"

//顶点数据
//float vertices[] =
//{
//	//第一个三角形
//	 0.5f,  0.5f,  0.0f,//右上角
//	 0.5f, -0.5f,  0.0f,//右下角
//	-0.5f,  0.5f,  0.0f,//左上角
//	//第二个三角形
//	 0.5f, -0.5f,  0.0f,//右下角
//	-0.5f, -0.5f,  0.0f,//左下角
//	-0.5f,  0.5f,  0.0f,//左上角
//};
//有重复顶点
float vertices[] =
{	
	//位置					//颜色				//纹理坐标
	 0.5f,  0.5f,  0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,//右上角
	 0.5f, -0.5f,  0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,//右下角
	-0.5f, -0.5f,  0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,//左下角
	-0.5f,  0.5f,  0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f//左上角
};
//float vertices[] =
//{	//位置					//颜色
//	  0.5f, -0.5f,  0.0f,	1.0f,  0.0f,  0.0f,//右上角
//	 -0.5f, -0.5f,  0.0f,	0.0f,  1.0f,  0.0f,//左下角
//	  0.0f,  0.5f,  0.0f,	0.0f,  0.0f,  1.0f//顶部
//};

float texCoordsp[] =
{
	0.0f, 0.0f,//左下
	1.0f, 0.0f,//右下
	0.5f, 1.0f//顶部
};

//索引，用于索引绘制(Indexed Drawing)
unsigned int indices[] =
{
	0, 1, 3, //第一个三角形
	1, 2, 3  //第二个三角形
};

//窗口大小改变时，视口也应调整
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//简单的输入控制
void processInput(GLFWwindow *window);

int main()
{
	//实例化GLFW窗口
	glfwInit();//初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//para1是选项的名称，来自很多以GLFW_开头的枚举值
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//para2接受一个整型，来设置这个选项
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
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
	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//视口(Viewport)，即OpenGL渲染窗口的尺寸
	glViewport(0, 0, 800, 600);//para1和para2控制窗口左下角的位置，para3和para4控制渲染窗口宽度和高度
	//注册视口调整回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//顶点数组对象(Vertex Array Object, VAO)，之后的顶点属性调用都会储存在这个VAO中
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//顶点缓冲对象(Vertex Buffer Object, VBO)，把顶点数据储存在显卡的内存中
	unsigned int VBO;//ID
	glGenBuffers(1, &VBO);//生成VBO对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//把定义的顶点数据复制到缓冲的内存中
	//GL_STATIC_DRAW 数据(几乎)不会改变; GL_DYNAMIC_DRAW 数据会改变; GL_STREAM_DRAW 数据每次绘制时都会改变

	//索引缓冲对象(Element Buffer Object, EBO or Index Buffer Object, IBO)，储存不同的点
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//可声明的顶点属性数上限
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	//链接顶点属性，必须手动指定输入数据的哪一部分对应顶点着色器的哪一个顶点属性
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader ourShader("./shaders/shader.vs", "./shaders/shader.fs");

	//加载纹理（木箱）
	int width, height, nrChannels;
	unsigned char* data = stbi_load("./textures/container.jpg", &width, &height, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		//生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//生成mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//释放图像内存
	stbi_image_free(data);

	//渲染循环/迭代
	while (!glfwWindowShouldClose(window))//每次循环开始检查GLFW是否被要求退出
	{
		//std::cout << "Rendering\n" << std::endl;
		processInput(window);//检查输入，在每一帧做出处理

		//在循环开始时清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清屏颜色【状态设置】
		glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲，整个颜色缓冲填充为清屏颜色【状态使用】

		//渲染指令
		//......
		ourShader.use();
		//更新uniform颜色
		//float timeValue = float(glfwGetTime());//获取秒数
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//查询uniform ourColor的位置
		////glUseProgram(shaderProgram);//更新uniform必须先使用shaderProgram
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式(Wireframe Mode)，para1 指应用到所有三角形正、背面
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);//交换颜色缓冲（储存GLFW窗口每一个像素颜色值的大缓冲），在本次循环中用来绘制并输出
		glfwPollEvents();//检查是否触发事件（键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
	}

	//释放/删除所有分配的资源
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
}