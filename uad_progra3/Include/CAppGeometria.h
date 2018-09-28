#pragma once
#define DEGREES_TO_RADIANS 0.0174533

#ifndef CAPPEMPTY_H
#define CAPPEMPTY_H

#include "../Include/Globals.h"
#include "../Include/CApp.h"
#include "../Include/C3DModel_FBX.h"
#include "../Include/LoadTGA.h"

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

	void CreatePyramid();
	void LoadMesh(std::string filename);
	void CreateSphere(float Radius, int Horizontal, int Vertical);
	void CreateToroid(int CentralRadius, int OutRadius, int Horizontal, int Vertical);
	bool readTexture(const char *filename, unsigned int *newTextureID);
	void loadTexture(std::string textureName);
};

#endif