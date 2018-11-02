#pragma once

#ifndef CAPPEMPTY_H
#define CAPPEMPTY_H

#include "../Include/Globals.h"
#include "../Include/CApp.h"
#include "../Include/C3DModel_FBX.h"

class CAppGeometria : public CApp
{
private:

	unsigned int m_shaderID;
	unsigned int m_geoVAOID;
	unsigned int m_textureID;

	int m_numFaces;
	int m_numVertex;
	int m_numNormals;

	bool m_initialized;

	float* m_vertexData;
	unsigned short* m_vertexIndex;

	float* m_normalsData;
	unsigned short* m_normalsIndex;

	float* m_UVData;
	unsigned short* m_UVIndex;

	double m_currentDeltaTime;
	double m_objectRotation;
	double m_rotationSpeed;

	CVector3 m_objectPosition;

protected:

	bool initializeMenu() { return false; }

public:

	CAppGeometria();
	CAppGeometria(int window_width, int window_height);
	~CAppGeometria();

	void initialize();
	void update(double deltaTime);
	void run();
	void render();
	void executeMenuAction();
	void onMouseMove(float deltaX, float deltaY);

private:

	void LoadMesh(std::string filename);
};

#endif