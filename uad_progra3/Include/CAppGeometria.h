#pragma once
#define DEDREES_TO_RADIANS 0.0174533

#ifndef CAPPEMPTY_H
#define CAPPEMPTY_H


#include "Globals.h"
#include "CApp.h"

// --------------------------------------------------------------------------------------------------------------------------------------
// Class that inherits from Base class CApp
// Base class CApp has members for: CGameWindow, CGameMenu, and COpenGLRenderer, which we can access through the public/protected methods
// --------------------------------------------------------------------------------------------------------------------------------------
class CAppGeometria : public CApp
{
private:
	// ---------------------------------------------------
	// Private member variables specific to CAppEmpty only
	// ---------------------------------------------------
	unsigned int m_shaderID;
	unsigned int m_geoVAOID;

	int m_numFaces;
	int m_numVertex;

	bool m_initialized;

	float* m_vData;
	unsigned short* m_vIndices;

	float* m_nData;
	unsigned short* m_nIndices;


	//Variables de renderizado
	double m_currentDeltaTime;
	double m_objectRotation;
	CVector3 m_objectPosition;
	double m_rotationSpeed;
	// ---------------------------------------------------

protected:

	// Method to initialize the menu 
	// (not needed in CAppEmpty, so return false)
	bool initializeMenu() { return false; }

public:
	// Constructors and destructor
	CAppGeometria();
	CAppGeometria(int window_width, int window_height);
	~CAppGeometria();

	// --------------------------------------------------------------------------------------------------------------------------
	// Inherited methods from CApp
	// Initialize(), update(), run(), and render() are PURE VIRTUAL methods, so they need to be implemented in this DERIVED class
	// --------------------------------------------------------------------------------------------------------------------------

	// Method to initialize any objects for this class
	void initialize();

	// Method to update any objecs based on time elapsed since last frame
	void update(double deltaTime);

	// Method to run the app
	void run();

	// Method to render the app
	void render();

	// -----------------------------------------------------------------------------------------------------------------------
	// Other inherited methods from CApp. These are optional to override.
	// Only provide an implementation in this DERIVD class if you need them to do something different than the base class CApp
	// -----------------------------------------------------------------------------------------------------------------------

	// Executes the action corresponding to the selected menu item
	void executeMenuAction();

	// Called when mouse moves within the window
	void onMouseMove(float deltaX, float deltaY);

	// -----------------------------------------
	// Public methods specific to CAppEmpty only
	// -----------------------------------------
	//
	// -----------------------------------------

private:

	// ------------------------------------------
	// Private methods specific to CAppEmpty only
	// ------------------------------------------
	void CreatePiramid();
	void CreateSphere(float Radius, int Horizontal, int Vertical);
	void CreateToroid(int CentralRadius, int OutRadius, int Horizontal, int Vertical);
	// ------------------------------------------

};

#endif // !CAPPEMPTY_H