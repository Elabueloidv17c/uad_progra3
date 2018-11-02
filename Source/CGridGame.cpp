#include "../Include/CWideStringHelper.h"
#include "../Include/CGridGame.h"
#include "../Include/Globals.h"
#include "../stdafx.h"
#include <iostream>
#include <cmath>

CGridGame::CGridGame() :
	CApp(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{

	cout << "Constructor: CAppGeometria()" << endl;

	m_geoVAOID = 0;
	m_shaderID = 0;
	m_textureID = 0;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;

	m_initialized = false;

	m_UVData = nullptr;
	m_UVIndex = nullptr;
}

CGridGame::CGridGame(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CAppGeometria(int window_width, int window_height)" << endl;

	m_geoVAOID = 0;
	m_shaderID = 0;
	m_textureID = 0;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_objectPosition = CVector3::ZeroVector();
	
	m_rotationSpeed = 20;
	//m_rotationSpeed = DEFAULT_ROTATION_SPEED;

	m_geoVAOID = 0;
	m_shaderID = 0;
	m_currentDeltaTime = 0;
	m_objectRotation = 0;

	m_initialized = false;

	m_UVData = nullptr;
	m_UVIndex = nullptr;

	m_pGrid = new CGrid(6, 5, HEXAGON, FLAT, 1.0f);
}

CGridGame::~CGridGame()
{
	cout << "Destructor: ~CAppGeometria()" << endl;

	if (m_geoVAOID)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_shaderID, &m_geoVAOID);
	}

	delete[] m_UVData;
	m_UVData = nullptr;

	delete[] m_UVIndex;
	m_UVIndex = nullptr;

	m_pGrid->~CGrid();
}

void CGridGame::initialize()
{
	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	char *vertexShaderToLoad = VERTEX_SHADER_3D_OBJECT;
	char *fragmentShaderToLoad = FRAGMENT_SHADER_3D_OBJECT;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(vertexShaderToLoad, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(fragmentShaderToLoad, wresourceFilenameFS, resourceFilenameFS))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << vertexShaderToLoad << endl;
		cout << "  " << fragmentShaderToLoad << endl;

		m_initialized = false;
	}

	getOpenGLRenderer()->createShaderProgram(&m_shaderID, resourceFilenameVS.c_str(), resourceFilenameFS.c_str());

	if (m_shaderID > 0)
	{
		LoadGrid();
	}
}

void CGridGame::run()
{
	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_EMPTYAPP_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);

			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());

			initialize();
			// Enter main loop
			cout << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

void CGridGame::update(double deltaTime)
{
	double degreesToRotate = 0.0f;

	// Do not update if delta time is < 0
	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;

	// Calculate degrees to rotate
	// ----------------------------------------------------------------------------------------------------------------------------------------
	// degrees = rotation speed * delta time
	// deltaTime is expressed in milliseconds, but our rotation speed is expressed in seconds (convert delta time from milliseconds to seconds)
	degreesToRotate = m_rotationSpeed * (deltaTime / 1000.0);
	// accumulate rotation degrees
	m_objectRotation += degreesToRotate;

	// Reset rotation if needed
	while (m_objectRotation > 360.0)
	{
		m_objectRotation -= 360.0;
	}

	if (m_objectRotation < 0.0)
	{
		m_objectRotation = 0.0;
	}
	// Update app-specific stuff here
	// ===============================
	//
	// ===============================
}

void CGridGame::render()
{
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL
		&& menu->isInitialized()
		&& menu->isActive())
	{
		//...
	}
	else // Otherwise, render app-specific stuff here...
	{
		float color[3] = { 1.0f, 1.0f, 1.0f };

		// convert total degrees rotated to radians;
		double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

		// Get a matrix that has both the object rotation and translation
		MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix(
			(float)totalDegreesRotatedRadians, m_objectPosition);

		if (m_geoVAOID > 0 && m_pGrid->GetNumFaces() > 0)       // Cambiar por la variable pertinente
		{
			getOpenGLRenderer()->renderObject(
				&m_shaderID,
				&m_geoVAOID,
				&m_textureID,
				m_pGrid->GetNumFaces(),
				color,
				&modelMatrix,
				COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
				false
			);
		}
		// =================================
		//
		// =================================
	}
}

void CGridGame::onMouseMove(float deltaX, float deltaY)
{
	if (deltaX < 100.0f && deltaY < 100.0f)
	{
		float moveX = -deltaX * DEFAULT_CAMERA_MOVE_SPEED;
		float moveZ = -deltaY * DEFAULT_CAMERA_MOVE_SPEED;

		float currPos[3];
		m_objectPosition.getValues(currPos);
		currPos[0] += moveX;
		currPos[2] += moveZ;
		m_objectPosition.setValues(currPos);
	}
}

void CGridGame::executeMenuAction()
{
	if (getMenu() != NULL)
	{
		// Execute app-specific menu actions here
		// ======================================
		//
		// ======================================
	}
}

void  CGridGame::LoadGrid()
{
	bool loaded = false;

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID, 
		&m_geoVAOID,
		m_pGrid->GetVertices(),
		m_pGrid->GetNumVertices(),
		m_pGrid->GetNormals(),
		m_pGrid->GetNumNormals(),
		m_pGrid->GetVertices(),
		m_pGrid->GetNumVertices(),
		m_pGrid->GetVerticesIndices(),
		m_pGrid->GetNumFaces(),
		m_pGrid->GetNormalsIndices(),
		m_pGrid->GetNumFaces(),
		m_pGrid->GetVerticesIndices(),
		m_pGrid->GetNumFaces()
		);

	if (!loaded)
	{
		m_geoVAOID = 0;
		cout << "Couldn't read Grid correctly" << endl;
	}
}