#include <Systems/Input.h>


void Input::OnInstaniate() {
	_screen = AppObject::GetObjectOfType<Screen>();
	_render = _screen->GetRender();
	_userPrefs = AppObject::GetObjectOfType<UserPrefs>();

	_mouseSensitivity = vec2f(
		_userPrefs->GetFloat("mouseSensitivityX", 0.003), 
		_userPrefs->GetFloat("mouseSensitivityY", 0.003)
	);
}

void Input::OnUpdate() {
	sf::Event event;
	while (_render->pollEvent(event)) {
		if (event.type == sf::Event::Closed) { Exit(); }
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) { Exit(); }
			if (event.key.code == sf::Keyboard::V) { _viewerMode = !_viewerMode; }
		}
	}

	if (_viewerMode) {
		_render->setMouseCursorVisible(false);
		UpdateMouse();
		UpdateKeys();
	}
	else { _render->setMouseCursorVisible(true); }
	_previousViewerMode = _viewerMode;
}


void Input::UpdateMouse() {
	sf::Vector2i center = sf::Vector2i(_screen->GetHalfWidth(), _screen->GetHalfHeight());
	if (_previousViewerMode == false) { 
		sf::Mouse::setPosition(center, *_render);
		return;
	}
	
	sf::Vector2i deltaPosition = sf::Mouse::getPosition(*_render) - center;
	_angleDirection.x = deltaPosition.x * _mouseSensitivity.x;
	_angleDirection.y = -deltaPosition.y * _mouseSensitivity.y;
	sf::Mouse::setPosition(center, *_render);
}

void Input::UpdateKeys() {
	_moveDirection = vec2f(0);
	if (AreKeysPressed(_forward))  { _moveDirection += vec2f( 1,  0); }
	if (AreKeysPressed(_backward)) { _moveDirection += vec2f(-1,  0); }
	if (AreKeysPressed(_right))    { _moveDirection += vec2f( 0,  1); }
	if (AreKeysPressed(_left))     { _moveDirection += vec2f( 0, -1); }
}

void Input::Exit() {
	AppObject::DestroyScene();
	AppObject::DestroyAll();
	exit(0);
}

vec2f Input::GetMoveDirection() {
	return _moveDirection;
}

vec2f Input::GetAngleDirection() {
	return _angleDirection;
}

bool Input::AreKeysPressed(const std::vector<sf::Keyboard::Key>& keys) {
	for (auto& key : keys) {
		if (sf::Keyboard::isKeyPressed(key)) { return true; }
	}
	return false;
}
