#pragma once

#ifndef CAPPEMPTY_H
#define CAPPEMPTY_H

#include "../Include/Globals.h"
#include "../Include/CApp.h"
#include "../Include/C3DModel_FBX.h"

#include "CGameObject.h"
#include "CVector3.h"
#include "CGrid.h"


class CGridGame : public CApp
{
	CGrid* m_pGrid;

	std::vector <CGameObject*> m_pGameObject;
	std::vector <C3DModel*> m_pMesh;

	unsigned int m_shaderID;
	unsigned int m_geoVAOID;
	unsigned int m_textureID;

	bool m_initialized;

	float* m_UVData;
	unsigned short* m_UVIndex;

	double m_currentDeltaTime;
	double m_objectRotation;
	double m_rotationSpeed;

	CVector3 m_objectPosition;

	void LoadGrid();

protected:
	bool initializeMenu() { return false; }

public:
	CGridGame(int window_width, int window_height);
	CGridGame();
	~CGridGame();

	void onMouseMove(float deltaX, float deltaY);
	void update(double deltaTime);
	void executeMenuAction();
	void initialize();
	void render();
	void run();
};

#endif