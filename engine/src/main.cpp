#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"
using namespace std;
#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];

float x = 0.0f;
float inc = 0.01f;
void display(GLFWwindow *window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	x += inc; // move the triangle along x axis
	if (x > 30) inc = -1.0f;
	if (x < 10) inc = 1.0f;			

	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get ptr to "offset"
	glProgramUniform1f(renderingProgram, offsetLoc, 0.0f);

	glPointSize(x);
	glDrawArrays(GL_POINTS, 0, 1);


}
GLFWwindow *createWindow(int width, int height, const char *name)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	return glfwCreateWindow(width, height, name, NULL, NULL);
}

string readShaderSource(const char *filePath)
{
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}
GLuint createShader(const char *filePath, GLenum type)
{
	string vertShaderStr = readShaderSource(filePath);
	const char *vertShaderSrc = vertShaderStr.c_str();
	GLint vertCompiled;
	GLuint vShader = glCreateShader(type);
	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vShader);
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		cout << "vertex compilation failed" << endl;
		printShaderLog(vShader);
	}
	return vShader;
}

GLuint createShaderProgram()
{
	GLuint vShader = createShader("vertShader.glsl",
								  GL_VERTEX_SHADER);
	GLuint fShader = createShader("fragShader.glsl",
								  GL_FRAGMENT_SHADER);
	GLint linked;
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	checkOpenGLError();
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		cout << "linking failed" << endl;
		printProgramLog(shaderProgram);
	}
	return shaderProgram;
}

void init(GLFWwindow *windows)
{
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}
void release(GLFWwindow *window)
{
	printf("release");
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main(int, char **)
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	auto *window = createWindow(600, 600, "MyProgram");
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);
	init(window);
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	release(window);
	exit(EXIT_SUCCESS);
}
