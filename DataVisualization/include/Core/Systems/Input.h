#pragma once
#include <unordered_map>
#include <unordered_set>
#include <Systems/UserPrefs.h>
#include <Systems/Screen.h>


class Input : public AppObject {
private:
    UserPrefs* _userPrefs;
    sf::Clock _clock;
    sf::RenderWindow* _render;
    std::unordered_map<std::string, sf::Keyboard::Key> _stringToSfmlKey;
    std::unordered_set<sf::Keyboard::Key> _keysJustPressed;

    void OnInstaniate();
    void OnUpdate();
    void Exit();

public:
    bool IsKeyPressed(std::string key);
    bool IsKeyJustPressed(std::string key);
    bool AreKeysPressed(const std::vector<std::string>& keys);
};

