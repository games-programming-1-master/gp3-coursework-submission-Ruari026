#pragma once
#include "Entity.h"

#define WINDOW_W Application::GetInstance()->GetWindowWidth()
#define WINDOW_H Application::GetInstance()->GetWindowHeight()

enum AppState
{
	INITILISING, RUNNING, QUITTING
};

class Application
{
private:
	//private variables
	static Application* m_application;
	AppState m_appState = AppState::INITILISING;

	// Window Details
	SDL_Window *m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;
	int m_windowWidth = 1280;
	int m_windowHeight = 720;

	// Time Details
	float m_worldDeltaTime = 0.f;
	float m_updateTimeScale = 1.0f;
	float m_physicsTimeScale = 1.0f;

	//private functions
	Application();
	void Init();
	void OpenGlInit();
	void GameInit();
	void Loop();
	void Quit();

public:
	//public functions
	~Application();
	static Application* GetInstance();
	void Run();

	SDL_Window* GetApplicationWindow() { return m_window; }
	inline int GetWindowHeight() { return m_windowHeight; }
	inline int GetWindowWidth() { return m_windowWidth; }

	void SetUpdateTimeScale(float newupdateScale) { m_updateTimeScale = newupdateScale; }
	void SetPhysicsTimeScale(float newphysicsScale) { m_physicsTimeScale = newphysicsScale; }
	
	void ChangeAppState(AppState newState) { m_appState = newState; }
};

