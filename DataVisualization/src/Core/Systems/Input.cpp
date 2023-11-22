#include <Systems/Input.h>
#include <AdditionalStd/String.h>


void Input::OnInstaniate() {
	sf::err().rdbuf(0);

	_userPrefs = AppObject::GetObjectOfType<UserPrefs>();
	_render = AppObject::GetObjectOfType<Screen>()->GetRender();

	_stringToSfmlKey["Control"] = sf::Keyboard::Key::LControl;
	_stringToSfmlKey["Escape"]  = sf::Keyboard::Key::Escape;
	_stringToSfmlKey["Shift"]   = sf::Keyboard::Key::LShift;
	_stringToSfmlKey["Space"]   = sf::Keyboard::Key::Space;
	_stringToSfmlKey["Alt"]     = sf::Keyboard::Key::LAlt;
	
	_stringToSfmlKey["Right"]   = sf::Keyboard::Key::Right;
	_stringToSfmlKey["Left"]    = sf::Keyboard::Key::Left;
	_stringToSfmlKey["Down"]    = sf::Keyboard::Key::Down;
	_stringToSfmlKey["Up"]      = sf::Keyboard::Key::Up;
	

	for (char symbole = 'A'-1; symbole <= 'Z'; ++symbole) {
		_stringToSfmlKey[ToString(symbole)] = sf::Keyboard::Key(sf::Keyboard::Key::A + (symbole - 'A'));
	}
}

void Input::OnUpdate() {
	_keysJustPressed.clear();

	sf::Event sfmlEvent;
	while (_render->pollEvent(sfmlEvent)) {
		if (sfmlEvent.type == sf::Event::Closed) { Exit(); }
		if (sfmlEvent.type == sf::Event::KeyPressed) { _keysJustPressed.insert(sfmlEvent.key.code); }
	}

	if (IsKeyJustPressed("Escape")) { Exit(); }
}

void Input::Exit() {
	AppObject::DestroyScene();
	AppObject::DestroyAll();
	exit(0);
}

bool Input::IsKeyPressed(std::string key) {
	return sf::Keyboard::isKeyPressed(_stringToSfmlKey[key]);
}

bool Input::IsKeyJustPressed(std::string key) {
	return (_keysJustPressed.find(_stringToSfmlKey[key]) != _keysJustPressed.end());
}

bool Input::AreKeysPressed(const std::vector<std::string>& keys) {
	for (auto& key : keys) {
		if (IsKeyPressed(key)) { return true; }
	}
	return false;
}

