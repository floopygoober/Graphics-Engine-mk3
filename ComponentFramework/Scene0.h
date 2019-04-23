#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;
union SDL_Event;
class Camera;
class GameObject;

class Scene0 : public Scene {
private:
	Camera *camera;
	GameObject *ball;
	Vec3 lightSource;
public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H