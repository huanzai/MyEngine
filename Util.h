#pragma once

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GL.h>

class Util
{
public:
	static GLuint LoadShader(const char* vertex_path, const char* fragment_path);
};