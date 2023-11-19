#pragma once


class App {
private:
	bool _isRunning = true;

	void Update();
	void Draw();
	void Exit();

public:
	void Start();
	void Run();
};

