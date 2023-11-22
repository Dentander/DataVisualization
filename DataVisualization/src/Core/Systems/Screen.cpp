#include <Systems/Screen.h>


void Screen::OnInstaniate() {
    _userPrefs = AppObject::GetObjectOfType<UserPrefs>();

    sf::ContextSettings settings;
    settings.depthBits         = 24;
    settings.stencilBits       = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion      = 0;
    settings.minorVersion      = 0;

    _render = new sf::RenderWindow(); 
    _render->create(
        sf::VideoMode(
            _userPrefs->GetInt("windowWidth", 1000), 
            _userPrefs->GetInt("windowHeight", 600)
        ),
        _userPrefs->GetString("appName", "Data Visualization"),
        7u, 
        settings
    );
}

void Screen::OnDraw() {
    _render->display();
    _render->clear();
}

void Screen::EnableGL() {
    _render->popGLStates();
}

void Screen::DisableGL() {
    _render->pushGLStates();
}

float Screen::GetWidth() {
    return _render->getSize().x;
}

float Screen::GetHeight() {
    return _render->getSize().y;
}

vec2f Screen::GetSize() {
    return vec2f(GetWidth(), GetHeight());
}

float Screen::GetHalfWidth() {
    return GetWidth() * 0.5f;
}

float Screen::GetHalfHeight() {
    return GetHeight() * 0.5f;
}

vec2f Screen::GetHalfSize() {
    return GetSize() * 0.5f;
}

sf::RenderWindow* Screen::GetRender() {
    return _render;
}
