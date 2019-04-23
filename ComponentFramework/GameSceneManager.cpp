#include <SDL.h>
#include "GameSceneManager.h"
#include "Timer.h"
#include "Window.h"
#include "Scene0.h"
#include "Scene1.h"

GameSceneManager::GameSceneManager(): currentScene(nullptr), 
									window(nullptr), timer(nullptr),
									fps(60), isRunning(false) {}

GameSceneManager::~GameSceneManager() {
	
	currentScene->OnDestroy();
	delete currentScene;
	currentScene = nullptr; 

	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	Debug::Info("Deleting the GameSceneManager", __FILE__, __LINE__);

}

bool GameSceneManager::Init(std::string name_, int width_, int height_) {
	Debug::DebugInit(name_ + "_Log");
	Debug::SetSeverity(MessageType::TYPE_INFO);


	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}
	timer = new Timer();
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}
	
	currentScene = BuildScene(SCENE1);
	if (!currentScene) {
		Debug::FatalError("Failed to initialize Opening Scene", __FILE__, __LINE__);
		return false;
	}
	return true;
}


void GameSceneManager::Run() {
	
	timer->Start();
	isRunning = true;
	while (isRunning) {
		timer->UpdateFrameTicks();
		HandleEvents();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		SDL_GL_SwapWindow(window->GetWindow());
		SDL_Delay(timer->GetSleepTime(fps));
	}
	//frees up memmory to clear the pointers from memory
//	currentScene->OnDestroy;
}

void GameSceneManager::HandleEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_EventType::SDL_QUIT:
			isRunning = false;
			return;
		default:
			currentScene->HandleEvents(sdlEvent);
			break;
		}
	}
}

Scene* GameSceneManager::BuildScene(SCENE_NUMBER scene_) {
	
	Scene* newScene = nullptr;
	switch (scene_) {
	case SCENE0:  
		newScene = new Scene0();
		newScene->OnCreate();
		break;
	case SCENE1:
		newScene = new Scene1();
		newScene->OnCreate();
		break;
	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		newScene = nullptr;
		break;
	}
	return newScene;
	
}


