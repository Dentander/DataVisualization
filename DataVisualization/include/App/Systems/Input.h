#pragma once
#include <iostream>
#include <Systems/UserPrefs.h>
#include <Systems/Screen.h>
#include <DataStorage/vec2.h>


class Input : public AppObject {
private:
    Screen* _screen;
    UserPrefs* _userPrefs;
    sf::RenderWindow* _render;

    bool _viewerMode = false;
    bool _previousViewerMode = false;
    vec2f _mouseSensitivity;
    vec2f _moveDirection = vec2f(0);
    vec2f _angleDirection = vec2f(0);

    std::vector<sf::Keyboard::Key> _forward  = { sf::Keyboard::Key::W     , sf::Keyboard::Key::Up     };
    std::vector<sf::Keyboard::Key> _backward = { sf::Keyboard::Key::S     , sf::Keyboard::Key::Down   };
    std::vector<sf::Keyboard::Key> _left     = { sf::Keyboard::Key::A     , sf::Keyboard::Key::Left   };
    std::vector<sf::Keyboard::Key> _right    = { sf::Keyboard::Key::D     , sf::Keyboard::Key::Right  };
    std::vector<sf::Keyboard::Key> _up       = { sf::Keyboard::Key::Space , sf::Keyboard::Key::Space  };
    std::vector<sf::Keyboard::Key> _down     = { sf::Keyboard::Key::C     , sf::Keyboard::Key::C      };
    std::vector<sf::Keyboard::Key> _run      = { sf::Keyboard::Key::LShift, sf::Keyboard::Key::RShift };

    void OnInstaniate();
    void OnUpdate();

    void UpdateMouse();
    void UpdateKeys();
    void Exit();

    static bool AreKeysPressed(const std::vector<sf::Keyboard::Key>& keys);

public:
    vec2f GetMoveDirection();
    vec2f GetAngleDirection();
};

