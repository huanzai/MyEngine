#include "Util.h"
#include <stdio.h>

char* ReadFile(const char* file)
{
	FILE *pFile = fopen(file, "r");
	if (!pFile) {
		return NULL;
	}

	char *pBuf;
	fseek(pFile, 0, SEEK_END);
	int len = ftell(pFile);
	pBuf = new char[len + 1];
	rewind(pFile);
	fread(pBuf, 1, len, pFile);
	pBuf[len] = 0;
	fclose(pFile);
	return pBuf;
}

GLuint Util::LoadShader(const char* vertex_path, const char* fragment_path)
{
	GLint result = GL_FALSE;
	int infoLenght;

	GLuint vId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fId = glCreateShader(GL_FRAGMENT_SHADER);

	char* pFile;
	pFile = ReadFile(vertex_path);
	if (!pFile) {
		return 0;
	}

	glShaderSource(vId, 1, &pFile, NULL);
	glCompileShader(vId);
	delete pFile;

	glGetShaderiv(vId, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		int infoLen;
		glGetShaderiv(vId, GL_INFO_LOG_LENGTH, &infoLen);
		char* buf = new char[infoLen];
		glGetShaderInfoLog(vId, infoLen, NULL, buf);
		printf("%s\n", buf);
		delete buf;
		return 0;
	}

	pFile = ReadFile(fragment_path);
	if (!pFile) {
		return 0;
	}

	glShaderSource(fId, 1, &pFile, NULL);
	glCompileShader(fId);
	delete pFile;

	glGetShaderiv(fId, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		int infoLen;
		glGetShaderiv(fId, GL_INFO_LOG_LENGTH, &infoLen);
		char* buf = new char[infoLen];
		glGetShaderInfoLog(fId, infoLen, NULL, buf);
		printf("%s\n", buf);
		delete buf;
		return 0;
	}

	GLint pId = glCreateProgram();
	glAttachShader(pId, vId);
	glAttachShader(pId, fId);
	glLinkProgram(pId);

	glGetProgramiv(pId, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		return 0;
	}

	glDeleteShader(vId);
	glDeleteShader(fId);

	return pId;
}