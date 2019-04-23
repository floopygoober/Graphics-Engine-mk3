#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"

GameObject::GameObject(Mesh *mesh_, Shader *shader_, Texture *texture_): 
	mesh(nullptr), shader(nullptr), texture(nullptr) {
	mesh = mesh_;
	shader = shader_;
	texture = texture_;
}

GameObject::~GameObject() {
	if (mesh) delete mesh;
}

void GameObject::Update(float deltaTime_) {
}
void GameObject::Render() const {
	GLint modelMatrixID = glGetUniformLocation(shader->getProgram(), "modelMatrix");
	GLint normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, model);
	Matrix3 normalMatrix = model;
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);

	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	mesh->Render();
}