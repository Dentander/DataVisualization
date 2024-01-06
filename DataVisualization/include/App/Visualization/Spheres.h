#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Visualization/Data.h>
#include <Visualization/Camera.h>
#include <Systems/Screen.h>


class Spheres : public AppObject {
private:
	static const std::string _vertexShaderPath;
	static const std::string _fragmentShaderPath;

	Data* _data;
	Camera* _camera;
	Screen* _screen;

	GLuint _hProgram;
	GLint location_attribute_0;

	void OnStart();
	void OnDraw();

	void Init();
	bool ReadAndCompileShader(const std::string fileName, GLuint& hdlr, GLenum shaderType);
	void SetShaders();
	void UpdateResolution();
	void PassCameraToShader();
	void PassDataToShader();

	void SetUniform(const char* name, int value);
	void SetUniform(const char* name, float value);
	void SetUniform(const char* name, vec2f value);
	void SetUniform(const char* name, vec3f value);
	void SetUniform(const char* name, GLfloat value[4]);
};
