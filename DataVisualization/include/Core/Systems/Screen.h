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
	void UpdateView();
	void Clear();

public:
	void EnableGL();
	void DisableGL();

	float GetRatio() const;
	float GetWidth() const;
	float GetHeight() const;
	vec2f GetSize() const;
	float GetHalfWidth() const;
	float GetHalfHeight() const;
	vec2f GetHalfSize() const;
	sf::RenderWindow* GetRender();
};

