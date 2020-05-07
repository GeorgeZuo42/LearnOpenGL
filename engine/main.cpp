#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];
void display(GLFWwindow *window, double currentTime)
{
    glUseProgram(renderingProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);
    // glClearColor(0.0, 0.0, 0.0, 1.0); //set color buffer at clear
    // glClear(GL_COLOR_BUFFER_BIT);  //clear all
}
GLFWwindow *createWindow(int width, int height, const char *name)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    return glfwCreateWindow(width, height, name, NULL, NULL);
}
GLuint createShaderProgram()
{
    const char *vshaderSource =
    "#version 430 \n"
    "void main(void) \n"
    "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
    const char *fshaderSource =
    "#version 430 \n"
    "out vec4 color; \n"
    "void main(void) \n"
    "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    return vfProgram;
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
