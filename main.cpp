#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

	//渲染循环/迭代
	while (!glfwWindowShouldClose(window))//每次循环开始检查GLFW是否被要求退出
	{
		processInput(window);//检查输入，在每一帧做出处理

		//在循环开始时清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清屏颜色【状态设置】
		glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲，整个颜色缓冲填充为清屏颜色【状态使用】

		//渲染指令
		//......

		glfwSwapBuffers(window);//交换颜色缓冲（储存GLFW窗口每一个像素颜色值的大缓冲），在本次循环中用来绘制并输出
		glfwPollEvents();//检查是否触发事件（键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
	}

	//释放/删除所有分配的资源
	glfwTerminate();
	return 0;

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