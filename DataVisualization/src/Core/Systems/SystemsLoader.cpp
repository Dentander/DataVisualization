#include <limits>
#include <Systems/SystemsLoader.h>
#include <Systems/Input.h>
#include <Systems/Screen.h>
#include <Systems/UserPrefs.h>


void SystemsLoader::OnInstaniate() {
	UserPrefs* userPrefs = new UserPrefs();
	Screen* screen = new Screen();
	Input* input = new Input();

	userPrefs->Instaniate("UserPrefs", -1, -1, false);
	screen->Instaniate("Screen", -1, std::numeric_limits<int>::max(), false);
	input->Instaniate("Input", -1, -1, false);
}
