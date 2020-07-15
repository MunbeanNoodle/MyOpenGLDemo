#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	 0.5f,  0.5f,  0.0f,//���Ͻ�
	 0.5f, -0.5f,  0.0f,//���½�
	-0.5f, -0.5f,  0.0f,//���½�
	-0.5f,  0.5f,  0.0f,//���Ͻ�
};

//������������������(Indexed Drawing)
unsigned int indices[] =
{
	0, 1, 3, //��һ��������
	1, 2, 3  //�ڶ���������
};

//������ɫ��Դ�룬ʹ����ɫ������GLSL(OpenGL Shading Language)��д
const char *vertexShaderSrc = "#version 330 core\n"//��ʼ�ڰ汾��������OpenGL�汾��ƥ��
	"layout (location = 0) in vec3 aPos;\n"//in�ؼ��֣������������붥������(Input Vertex Attribute); layout(location = 0)�趨���������λ��ֵ
	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"//��gl_Position������ֵ�������
	"}\n\0";

//Ƭ����ɫ��Դ��
const char *fragmentShaderSrc = "#version 330 core\n"
	"out vec4 FragColor;"//out�ؼ��֣����������������ʾ�����������ɫ
	"void main()\n"
	"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

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
	
	//������ɫ������������ʱ��̬���붥����ɫ��Դ��
	unsigned int vertexShader;//ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//����������ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);//����ɫ��Դ�븽�ŵ���ɫ��������; para2 Դ���ַ�������
	glCompileShader(vertexShader);
	
	//��ⶥ����ɫ���Ƿ����ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Ƭ����ɫ������
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	//���Ƭ����ɫ���Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//��ɫ���������(Shader Program Object)���Ƕ����ɫ���ϲ�������������ɵİ汾������Ⱦ����ʱ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//���������ɫ�������Ƿ�ʧ��
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	//����������
	glUseProgram(shaderProgram);

	//����ɫ���������ӵ���������Ӧɾ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//���Ӷ������ԣ������ֶ�ָ���������ݵ���һ���ֶ�Ӧ������ɫ������һ����������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ(Wireframe Mode)��para1 ָӦ�õ�������������������
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