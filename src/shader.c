#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <glad/glad.h>

char *read_file(const char *path)
{
	FILE *file = fopen(path, "r");
	fseek(file, 0, SEEK_END);

	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* string = malloc(file_size + 1);
	fread(string, file_size, 1, file);

	fclose(file);
	string[file_size] = 0;

	return string;
}

void check_compile_errors(unsigned int shader, char* type)
{
	int success;
	char info_log[1024];

	if (strcmp(type, "PROGRAM") != 0)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, info_log);
			printf("Shader compilation error of type: %s\n%s\n", type, info_log);
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, info_log);
			printf("Program linking error of type: %s\n%s\n", type, info_log);
		}

	}
}

unsigned int create_shader(const char *vertex_path, const char *fragment_path)
{
	const char *vertex_code = read_file(vertex_path);
	const char *fragment_code = read_file(fragment_path);
	
	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_code, NULL);
	glCompileShader(vertex);
	
	check_compile_errors(vertex, "VERTEX");
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_code, NULL);
	glCompileShader(fragment);
	
	check_compile_errors(fragment, "FRAGMENT");

	unsigned int id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);

	glLinkProgram(id);
	check_compile_errors(id, "PROGRAM");	

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	free((void*)vertex_code);
	free((void*)fragment_code);

	return id;
}

void use_shader(unsigned int id)
{
	glUseProgram(id);
}

void set_bool(unsigned int id, const char *name, bool value)
{
	glUniform1i(glGetUniformLocation(id, name), value);
}

void set_int(unsigned int id, const char *name, int value)
{
	glUniform1i(glGetUniformLocation(id, name), value);
}

void set_float(unsigned int id, const char *name, float value)
{
	glUniform1f(glGetUniformLocation(id, name), value);
}
