#include <stdlib.h>
#include <BaseClasses/App.h>
#include <Systems/Input.h>
#include <Systems/Screen.h>
#include <Systems/SystemsLoader.h>


void App::Start() {
	SystemsLoader* _systemsLoader = new SystemsLoader();
	_systemsLoader->Load();
	Update();
}

void App::Run() {
	while (true) {
		Draw();
		Update();
	}
}

void App::Update() { 
	AppObject::UpdateScene(); 
}

void App::Draw() { 
	AppObject::DrawScene(); 
}

