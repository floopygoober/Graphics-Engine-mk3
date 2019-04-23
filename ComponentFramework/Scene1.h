#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
union SDL_Event;
using namespace MATH;
class Camera;
class GameObject;

class Scene1 : public Scene {
private:
	Camera * camera;
	GameObject *ball;
	GameObject *earth;
	Vec3 lightSource;

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
};


#endif // !SCENE1_H