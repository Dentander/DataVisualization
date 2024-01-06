#include <imgui.h>
#include <GL/glew.h>
#include <GL/freeglut_std.h>
#include <Systems/Screen.h>


void Screen::OnInstaniate() {
    _userPrefs = AppObject::GetObjectOfType<UserPrefs>();

    sf::ContextSettings settings;
    settings.depthBits         = 24;
    settings.stencilBits       = 8;

    _render = new sf::RenderWindow();
    _render->create(
        sf::VideoMode(
            1000, 
            600
        ),
        _userPrefs->GetString("appName", "Data Visualization"),
        sf::Style::Default,
        settings
    );    
}

void Screen::OnDraw() {
    ImGui::SFML::Render(*_render);
    _render->display();
    Clear();
    UpdateView();
}

void Screen::UpdateView() {
    _render->setView(
        sf::View(sf::FloatRect(0.0f, 0.0f, GetWidth(), GetHeight()))
    );
}

void Screen::Clear() {
    EnableGL();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    DisableGL();
}

inline void Screen::EnableGL() {
    _render->popGLStates();
}

inline void Screen::DisableGL() {
    _render->pushGLStates();
}

float Screen::GetRatio() const {
    return (float)GetWidth() / GetHeight();
}

float Screen::GetWidth() const {
    return _render->getSize().x;
}

float Screen::GetHeight() const {
    return _render->getSize().y;
}

vec2f Screen::GetSize() const {
    return vec2f(GetWidth(), GetHeight());
}

float Screen::GetHalfWidth() const {
    return GetWidth() * 0.5f;
}

float Screen::GetHalfHeight() const {
    return GetHeight() * 0.5f;
}

vec2f Screen::GetHalfSize() const {
    return GetSize() * 0.5f;
}

sf::RenderWindow* Screen::GetRender() {
    return _render;
}
