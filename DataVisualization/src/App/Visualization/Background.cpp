#include <Visualization/Background.h>


const std::string Background::_fragmentShaderPath = "data/Shaders/BackgroundFragment.glsl";

void Background::OnStart() {
	_camera = AppObject::GetObjectOfType<Camera>();
	_screen = AppObject::GetObjectOfType<Screen>();
	_render = _screen->GetRender();

	BuildShader();
}

void Background::OnDraw() {
	auto size = _screen->GetSize().ToSFML();

	// ========== SET SCREEN SIZE ==========
	_shader.setUniform("u_resolution", size);
	_drawZone.setSize(size);

	// ========== CAMERA ==========
	auto position = _camera->GetPosition().ToSFML();
	auto rotation = _camera->GetRotation().ToSFML();
	_shader.setUniform("u_camera_position", position);
	_shader.setUniform("u_camera_rotation", rotation);

	// ========== DRAW ==========
	_render->draw(_drawZone, &_shader);
}

void Background::BuildShader() {
	_shader.loadFromFile(_fragmentShaderPath, sf::Shader::Fragment);
}
