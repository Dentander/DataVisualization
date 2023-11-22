#pragma once
#include <SFML/Graphics.hpp>
#include <Systems/UserPrefs.h>
#include <AdditionalStd/vec2.h>


class Screen : public AppObject {
private:
	UserPrefs* _userPrefs;
	sf::RenderWindow* _render;

	void OnInstaniate();
	void OnDraw();

public:
	void EnableGL();
	void DisableGL();

	float GetWidth();
	float GetHeight();
	vec2f GetSize();
	float GetHalfWidth();
	float GetHalfHeight();
	vec2f GetHalfSize();
	sf::RenderWindow* GetRender();
};

