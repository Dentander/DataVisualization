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

	GLuint prog_hdlr;
	GLint location_attribute_0, location_viewport;

	void OnStart();
	void OnDraw();

	void Init();
	bool ReadAndCompileShader(const std::string fileName, GLuint& hdlr, GLenum shaderType);
	void SetShaders();
	void UpdateResolution();
	void SetData();

	void SetUniform(const std::string name, int value);
	void SetUniform(const std::string name, float value);
	void SetUniform(const std::string name, vec2f value);
	void SetUniform(const std::string name, vec3f value);
};