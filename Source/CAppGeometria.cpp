#include "../Include/CWideStringHelper.h"
#include "../Include/CAppGeometria.h"
#include "../Include/Globals.h"
#include "../stdafx.h"
#include <iostream>
#include <cmath>

CAppGeometria::CAppGeometria() :
	CApp(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{

	cout << "Constructor: CAppGeometria()" << endl;

	m_geoVAOID = 0;
	m_shaderID = 0;
	m_textureID = 0;

	m_numNormals = 0;
	m_numFaces = 0;
	m_numVertex = 0;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;

	m_initialized = false;
	
	m_vertexData = nullptr;
	m_vertexIndex = nullptr;

	m_normalsData = nullptr;
	m_normalsIndex = nullptr;

	m_UVData = nullptr;
	m_UVIndex = nullptr;
}

CAppGeometria::CAppGeometria(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CAppGeometria(int window_width, int window_height)" << endl;

	m_geoVAOID = 0;
	m_shaderID = 0;
	m_textureID = 0;

	m_numNormals = 0;
	m_numFaces = 0;
	m_numVertex = 0;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;

	m_geoVAOID = 0;
	m_shaderID = 0;
	m_currentDeltaTime = 0;
	m_objectRotation = 0;

	m_initialized = false;

	m_vertexData = nullptr;
	m_vertexIndex = nullptr;

	m_normalsData = nullptr;
	m_normalsIndex = nullptr;

	m_UVData = nullptr;
	m_UVIndex = nullptr;
}

CAppGeometria::~CAppGeometria()
{
	cout << "Destructor: ~CAppGeometria()" << endl;

	if (m_geoVAOID)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_shaderID, &m_geoVAOID);
	}

	delete[] m_vertexData;
	m_vertexData = nullptr;

	delete[] m_vertexData;
	m_vertexData = nullptr;
	
	delete[] m_vertexIndex;
	m_vertexIndex = nullptr;

	delete[] m_normalsData;
	m_normalsData = nullptr;
	
	delete[] m_normalsIndex;
	m_normalsIndex = nullptr;

	delete[] m_UVData;
	m_UVData = nullptr;

	delete[] m_UVIndex;
	m_UVIndex = nullptr;
}

void CAppGeometria::initialize()
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

	getOpenGLRenderer()->createShaderProgram(
		&m_shaderID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str()
	);

	if (m_shaderID > 0)
	{
		//CreatePyramid();
		//CreateSphere(2, 8, 8);
		LoadMesh("Vato_guapo");
	}

}

void CAppGeometria::run()
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

void CAppGeometria::update(double deltaTime)
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

void CAppGeometria::render()
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

		if (m_geoVAOID > 0 && m_numFaces > 0)       // Cambiar por la variable pertinente
		{
			getOpenGLRenderer()->renderObject(
				&m_shaderID,
				&m_geoVAOID,
				&m_textureID,
				m_numFaces,
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

void CAppGeometria::onMouseMove(float deltaX, float deltaY)
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

void CAppGeometria::executeMenuAction()
{
	if (getMenu() != NULL)
	{
		// Execute app-specific menu actions here
		// ======================================
		//
		// ======================================
	}
}

void CAppGeometria::LoadMesh(std::string filename)
{
	bool loaded = false;

	C3DModel_FBX object;

	std::string mesh = "Resources/MEDIA/MODELS/FBX/" + filename + ".fbx";
	const char* meshPath = &mesh[0];

	if (!object.loader(meshPath))
	{
		m_geoVAOID = 0;
		cout << "Mesh not found" << endl;
	}

	//----------------------------------------------------------------------------------
	m_numFaces = object.getNumVertexIndices() / 3;

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		object.getModelVertices(),
		m_numFaces,
		object.getModelNormals(),
		object.getNumNormals() / 3,
		object.getModelUVCoords(),
		object.getNumUVCoords() / 2,
		object.getModelVertexIndices(),
		object.getNumVertexIndices() / 3,
		object.getModelNormalIndices(),
		object.getNumNormalsIndices() / 3,
		object.getModelUVCoordIndices(),
		object.getNumUVIndices() / 3
	);

	if (!loaded)
	{
		m_geoVAOID = 0;
		cout << "Couldn't read mesh correctly" << endl;
	}

	cout << "Finished reading 3D model" << endl;
	cout << "Vertices: " << m_numFaces << endl;
	cout << "Normals: " << object.getNumNormals() / 3 << endl;
	cout << "UVCoords: " << object.getNumUVCoords() / 2 << endl;
}