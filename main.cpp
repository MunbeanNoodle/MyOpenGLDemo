#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	 0.5f,  0.5f,  0.0f,//右上角
	 0.5f, -0.5f,  0.0f,//右下角
	-0.5f, -0.5f,  0.0f,//左下角
	-0.5f,  0.5f,  0.0f,//左上角
};

//索引，用于索引绘制(Indexed Drawing)
unsigned int indices[] =
{
	0, 1, 3, //第一个三角形
	1, 2, 3  //第二个三角形
};

//顶点着色器源码，使用着色器语言GLSL(OpenGL Shading Language)编写
const char *vertexShaderSrc = "#version 330 core\n"//起始于版本声明，与OpenGL版本相匹配
	"layout (location = 0) in vec3 aPos;\n"//in关键字，声明所有输入顶点属性(Input Vertex Attribute); layout(location = 0)设定输入变量的位置值
	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"//对gl_Position变量赋值设置输出
	"}\n\0";

//片段着色器源码
const char *fragmentShaderSrc = "#version 330 core\n"
	"out vec4 FragColor;"//out关键字，声明输出变量，表示最终输出的颜色
	"void main()\n"
	"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

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
	
	//顶点着色器对象，在运行时动态编译顶点着色器源码
	unsigned int vertexShader;//ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);//把着色器源码附着到着色器对象上; para2 源码字符串数量
	glCompileShader(vertexShader);
	
	//检测顶点着色器是否编译成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//片段着色器对象
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	//检测片段着色器是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//着色器程序对象(Shader Program Object)，是多个着色器合并并最终链接完成的版本，在渲染对象时被激活
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//检测链接着色器程序是否失败
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	//激活程序对象
	glUseProgram(shaderProgram);

	//在着色器对象链接到程序对象后，应删除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//链接顶点属性，必须手动指定输入数据的哪一部分对应顶点着色器的哪一个顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式(Wireframe Mode)，para1 指应用到所有三角形正、背面
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