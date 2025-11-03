#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "StandardIncludes.h"
#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
	~Mesh();

	void SetPosition(glm::vec3 _position) { position = _position; }
	glm::vec3 GetPosition() { return position; }
	void SetScale(glm::vec3 _scale) { scale = _scale; }
	void SetRotation(glm::vec3 _rotation) { rotation = _rotation; }
	glm::vec3 GetRotation() { return rotation; }
	
	void SetLightColor(glm::vec3 _lightColor) { lightColor = _lightColor; }
	glm::vec3 GetLightColor() { return lightColor; }
	void SetLightDirection(glm::vec3 _lightDirection) { lightDirection = _lightDirection; }
	glm::vec3 GetLightDirection() { return lightDirection; }

	void SetCameraPosition(glm::vec3 _cameraPosition) { cameraPosition = _cameraPosition; };

	void Create(Shader* _shader);
	void CalculateTransform();
	void Render(glm::mat4 _pv, const std::list<Mesh*>& _lights);

	void RotateWorld(float _angle, glm::vec3 axis);
	void MoveTexture(float _dx, float _dy);

private:
	Shader* shader = nullptr;
	Texture* diffuseTexture = nullptr;
	Texture* specularTexture = nullptr;
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLubyte> indexData;
	
	glm::mat4 world = glm::mat4(1);
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

	glm::vec3 lightDirection{ 0.0f, 0.0f, 0.0f };
	glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
	glm::vec3 cameraPosition{ 0, 0, 0 };

	glm::vec2 texTranslation = glm::vec2(0.0);

	void SetShaderVariables(glm::mat4 _pv, const std::list<Mesh*>& _lights);
	void BindAttributes();
	std::string Concat(const std::string& _s1, int _index, const std::string& _s2);
};

#endif

