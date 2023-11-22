#include <Visualization/CameraInput.h>


void CameraInput::OnStart() {
	_input = AppObject::GetObjectOfType<Input>();
	_screen = AppObject::GetObjectOfType<Screen>();
	_userPrefs = AppObject::GetObjectOfType<UserPrefs>();

	_render = _screen->GetRender();

	_moveSpeed = _userPrefs->GetFloat("moveSpeed", 0.1);
	_mouseSensitivity = vec2f(
		_userPrefs->GetFloat("mouseSensitivityX", 0.003),
		_userPrefs->GetFloat("mouseSensitivityY", 0.003)
	);
}

void CameraInput::OnUpdate() {
	if (_input->IsKeyJustPressed("V")) { _viewerMode = !_viewerMode; }

	if (_viewerMode) {
		_render->setMouseCursorVisible(false);
		UpdateMouse();
		UpdateKeys();
	}
	else { _render->setMouseCursorVisible(true); }
	_previousViewerMode = _viewerMode;
}

void CameraInput::UpdateMouse() {
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

void CameraInput::UpdateKeys() {
	_moveDirection = vec2f(0);
	if (_input->AreKeysPressed(_forward))  { _moveDirection += vec2f( 1,  0); }
	if (_input->AreKeysPressed(_backward)) { _moveDirection += vec2f(-1,  0); }
	if (_input->AreKeysPressed(_right))    { _moveDirection += vec2f( 0,  1); }
	if (_input->AreKeysPressed(_left))     { _moveDirection += vec2f( 0, -1); }
	_moveDirection = _moveDirection * _moveSpeed;
}

vec2f CameraInput::GetMoveDirection() {
	return _moveDirection;
}

vec2f CameraInput::GetAngleDirection() {
	return _angleDirection;
}
