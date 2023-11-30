#pragma once
#include <Systems/Input.h>
#include <Systems/Screen.h>
#include <Systems/UserPrefs.h>
#include <AdditionalStd/vec2.h>



class CameraInput : public AppObject {
private:
    Input* _input;
    Screen* _screen;
    UserPrefs* _userPrefs;
    
    sf::RenderWindow* _render;

    bool _viewerMode = false;
    bool _previousViewerMode = false;

    float _moveSpeed;
    vec2f _mouseSensitivity;
    vec2f _moveDirection = vec2f(0);
    vec2f _angleDirection = vec2f(0);

    std::vector<std::string> _forward =  { "W"     , "Up"   }; 
    std::vector<std::string> _backward = { "S"     , "Down" };
    std::vector<std::string> _left =     { "A"     , "Left" };
    std::vector<std::string> _right =    { "D"     , "Right"};
    std::vector<std::string> _up =       { "Space"          };

	void OnStart();
	void OnUpdate();

    void UpdateMouse();
    void UpdateKeys();

public:
    bool IsViewerMode();
    vec2f GetMoveDirection();
    vec2f GetAngleDirection();
};

