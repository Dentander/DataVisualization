#pragma once
#include <Visualization/Camera.h>


class Background : public AppObject {
private:
	static const std::string _fragmentShaderPath;

	Camera* _camera;
	Screen* _screen;
	sf::RenderWindow* _render;
	sf::RectangleShape _drawZone;
	sf::Shader _shader;

	void OnStart();
	void OnDraw();

	void BuildShader();
};

