#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32.lib")

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <gl/GL.h>

#include "Util.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera* camera;

struct Triangle
{
	GLfloat vertexs[9];
	GLuint vaoId;
	GLuint vboId;
	GLuint progId;
};

void InitTriangle(Triangle& t)
{
	t.vertexs[0] = -1.f;
	t.vertexs[1] = -1.f;
	t.vertexs[2] = 0.f;
	t.vertexs[3] = 1.f;
	t.vertexs[4] = -1.f;
	t.vertexs[5] = 0.f;
	t.vertexs[6] = 0.f;
	t.vertexs[7] = 1.f;
	t.vertexs[8] = 0.f;

	glGenVertexArrays(1, &t.vaoId);
	glGenBuffers(1, &t.vboId);
	glBindBuffer(GL_ARRAY_BUFFER, t.vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t.vertexs), t.vertexs, GL_STATIC_DRAW);

	t.progId = Util::LoadShader("shader/simple.vs", "shader/simple.fs");
}

void DestroyTriangle(Triangle& t)
{
	glDeleteBuffers(1, &t.vboId);
	glDeleteVertexArrays(1, &t.vaoId);
	glDeleteProgram(t.progId);
}

void DrawTriangle(Triangle& t)
{
	GLuint mvpId = glGetUniformLocation(t.progId, "MVP");

	glm::mat4x4 m = glm::mat4x4(1.f);
	m = glm::rotate(m, 0.8f, glm::vec3(1.f, 1.f, 0.f));
	camera->setModel(m);
	camera->update();

	glm::mat4x4 mvp;
	camera->getTransform(mvp);
	glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvp[0][0]);

	glUseProgram(t.progId);
	glBindVertexArray(t.vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, t.vboId);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}

int main(void)
{
	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	camera = new Camera();
	camera->init(640, 480);

	Triangle t;
	InitTriangle(t);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawTriangle(t);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events 
		glfwPollEvents();
	}

	DestroyTriangle(t);

	delete camera;

	glfwTerminate();

	return 0;
}