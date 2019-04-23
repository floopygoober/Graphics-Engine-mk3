#include "GameSceneManager.h"

int main(int argc, char* args[]) {
	GameSceneManager* gsm = new GameSceneManager();
	gsm->Init("Engine", 1280,720);
	gsm->Run();
	delete gsm;
	exit(0);
}