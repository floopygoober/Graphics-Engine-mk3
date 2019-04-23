#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Debug.h"
#include "Scene1.h"
#include "Camera.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"



Scene1::Scene1() {
}


Scene1::~Scene1() {
}

bool Scene1::OnCreate() {

	camera = new Camera();

	if (ObjLoader::loadOBJ("sphere.obj") == false) {
		return false;
	}
	Mesh *meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	Shader *shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");
	Texture *moonTexturePtr = new Texture();
	moonTexturePtr->LoadImage("moon.jpg");

	Texture *earthTexturePtr = new Texture();
	earthTexturePtr->LoadImage("earthclouds.jpg");

	ball = new GameObject(meshPtr, shaderPtr, moonTexturePtr);
	earth = new GameObject(meshPtr, shaderPtr, earthTexturePtr);

	lightSource = Vec3(3.0, 6.0, 0.0);

	return true;
}

void Scene1::OnDestroy() {
	delete earth;
	earth = nullptr;
	
	delete ball;
	ball = nullptr;
	
	delete camera;
	camera = nullptr;
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene1::Update(const float deltaTime_) {
	static float rotate = 0.0f;
	rotate += 0.5f;

	Matrix4 moonModel = MMath::rotate(rotate, Vec3(0.0f,1.0f,0.0f)) * MMath::translate(0.0f, 0.0f, 5.0f) 
							* MMath::scale(0.272f, 0.272f, 0.272f) * MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));
	ball->setModelMatrix(moonModel);
	ball->Update(deltaTime_);

	Matrix4 earthModel = MMath::rotate(-rotate, Vec3(0.0f, 1.0f, 0.131f))
						* MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

	earth->setModelMatrix(earthModel);
	earth->Update(deltaTime_);
}

void Scene1::Render() const {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	GLuint program = ball->getShader()->getProgram();
	glUseProgram(program);

	/// This should not be done here. You only need to get these
	/// ID's once after the sharder has been created - TODO
	GLint projectionMatrixID = glGetUniformLocation(program, "projectionMatrix");
	GLint viewMatrixID = glGetUniformLocation(program, "viewMatrix");
	GLint lightPosID = glGetUniformLocation(program, "lightPos");


	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(lightPosID, 1, lightSource);



	ball->Render();
	earth->Render();
	glUseProgram(0);
}
