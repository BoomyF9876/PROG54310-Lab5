#pragma once

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class GameController
{
public:
	GameController() = default;
	~GameController() = default;

	void Initialize();
	void RunGame();

private:
	Shader* shaderColor = nullptr;
	Shader* shaderDiffuse = nullptr;

	std::list<Mesh*> meshes;
	Mesh* meshLight = nullptr;

	Camera* camera = nullptr;
};

#endif

