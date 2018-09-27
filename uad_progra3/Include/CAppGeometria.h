#pragma once
#define DEGREES_TO_RADIANS 0.0174533

#ifndef CAPPEMPTY_H
#define CAPPEMPTY_H

#include "Globals.h"
#include "CApp.h"
#include "../Include/C3DModel_FBX.h"

class CAppGeometria : public CApp
{
private:

	unsigned int m_shaderID;
	unsigned int m_geoVAOID;

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
	CVector3 m_objectPosition;
	double m_rotationSpeed;

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

	void LoadMesh();
	void CreatePiramid();
	void CreateSphere(float Radius, int Horizontal, int Vertical);
	void CreateToroid(int CentralRadius, int OutRadius, int Horizontal, int Vertical);

};

#endif