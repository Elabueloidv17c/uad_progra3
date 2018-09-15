#include "../stdafx.h"

#include <iostream>
#include <cmath>

using namespace std;

#include "../Include/Globals.h"
#include "../Include/CAppGeometria.h"
#include "../Include/CWideStringHelper.h"

/* */
CAppGeometria::CAppGeometria() :
	CApp(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{

	cout << "Constructor: CAppGeometria()" << endl;

	m_geoVAOID = 0;
	m_shaderID = 0;
	
	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;

	// Initialize class member variables here
	// ======================================
	m_geoVAOID = 0;
	m_shaderID = 0;
	m_currentDeltaTime = 0;
	m_objectRotation = 0;

	m_vData = nullptr;
	m_vIndices = nullptr;

	m_nData = nullptr;
	m_nIndices = nullptr;

	m_initialized = false;

	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;
	// ======================================
}

/* */
CAppGeometria::CAppGeometria(int window_width, int window_height) :
	CApp(window_width, window_height)
{
	cout << "Constructor: CAppGeometria(int window_width, int window_height)" << endl;

	// Initialize class member variables here
	// ======================================
	m_geoVAOID = 0;
	m_shaderID = 0;
	m_currentDeltaTime = 0;
	m_objectRotation = 0;

	m_vData = nullptr;
	m_vIndices = nullptr;

	m_nData = nullptr;
	m_nIndices = nullptr;

	m_initialized = false;

	m_objectPosition = CVector3::ZeroVector();
	m_rotationSpeed = DEFAULT_ROTATION_SPEED;
	// ======================================
}

/* */
CAppGeometria::~CAppGeometria()
{
	cout << "Destructor: ~CAppGeometria()" << endl;

	if (m_geoVAOID)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_shaderID, &m_geoVAOID);
	}

	// Free memory allocated in this class instance here
	// =================================================
	delete[] m_vData;
	m_vData = nullptr;

	delete[] m_vData;
	m_vData = nullptr;
	
	delete[] m_vIndices;
	m_vIndices = nullptr;

	delete[] m_nData;
	m_nData = nullptr;
	
	delete[] m_nIndices;
	m_nIndices = nullptr;
	// =================================================
}

/* */
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
		//CreatePiramid();
		CreateSphere(2, 100, 100);
	}

	// Initialize app-specific stuff here
	// ==================================
	//
	// ==================================
}

/* */
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

/* */
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

/* */
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
		unsigned int noTexture = 0;

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
				&noTexture,
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

/* */
void CAppGeometria::onMouseMove(float deltaX, float deltaY)
{
	// Update app-specific stuff when mouse moves here 
	// ===============================================
	//
	// ===============================================
}

/* */
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

void CAppGeometria::CreatePiramid()
{
	bool loaded = false;
	float h = 2.5f;
	float halfZ = 2.0f;
	float halfX = 2.0f;

	//Para calcular normales
	float v1v3[3], v1v2[3], normal[3];

	m_numFaces = 6;

	float m_vData[15] =
	{
		0.0, h, 0.0,
		-halfX, 0.0, halfZ,
		halfX, 0.0, halfZ,
		-halfX, 0.0, -halfZ,
		halfX, 0.0, -halfZ,
	};

	unsigned short m_vIndices[18] =
	{
		0,1,2,
		0,2,4,
		0,4,3,
		0,3,1,
		1,4,2,
		4,3,1
	};

	float m_nData[18] = 
	{
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
	};

	unsigned short m_nIndices[18] =
	{
		0, 0, 0,
		1, 1, 1,
		2, 2, 2,
		3, 3, 3,
		4, 4, 4,
		5, 5, 5,
	};

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		m_vData,			// vertices
		5,				// Numero de vertices
		m_nData,			// Normales
		6,				// Numero de normales
		m_vData,			// UV coords
		5,				// Numero de UV coords
		m_vIndices,		// Indices de vertices
		6,				// Numero de vertices
		m_nIndices,		// Indices a normales
		6,				// Numero de indices a normales
		m_vIndices,		// Indices a las UV coords
		6				// Numero de indices a UV coords
		);

	if (!loaded)
	{
		m_geoVAOID = 0;
	}
}

void CAppGeometria::CreateSphere(float Radius, int Horizontal, int Vertical)
{
	//--------------------------------------------------------
	bool loaded = false;

	float radius = Radius;
	float divisionsH = Horizontal - 1; 	//Subdivisiones horizontales
	float divisionsV = Vertical;		//Subdivisiones verticales

	float hDegrees = 180.0f/Horizontal;
	float vDegrees = 360.0f/Vertical;

	//Numero de caras y vertices en el mesh
	m_numVertex = (divisionsV * (divisionsH)) + 2;
	m_numFaces = (m_numVertex - 2) * 2;

	//--------------------------------------------------------
	//Para calcular normales
	float v1v3[3], v1v2[3], normal[3];

	//Numero de vertices
	m_vData = new float[m_numVertex * 3];
	//Indices de los vertices
	m_vIndices = new unsigned short[m_numFaces * 3];

	//Normales
	m_nData = new float[m_numFaces * 3];
	//Indices de las normales
	m_nIndices = new unsigned short[m_numFaces * 3];
	//--------------------------------------------------------

	int iLoop = 1;
	int currentVertex = 0;

	float currentRadius = radius * sin((hDegrees * iLoop) * DEDREES_TO_RADIANS);
	float height = radius * cos((hDegrees * iLoop) * DEDREES_TO_RADIANS);

	//--------------------------------------------------------
	//Calculo las posiciones de los vertices
 	for (int i = 0; i < m_numVertex * 3; i += 3)
	{
		if (divisionsV == currentVertex)
		{
			iLoop++;
			currentRadius = radius * sin((hDegrees * iLoop) * DEDREES_TO_RADIANS);
			height = radius * cos((hDegrees * iLoop) * DEDREES_TO_RADIANS);

			currentVertex = 0;
		}

		if (iLoop < divisionsV)
		{
			m_vData[i] = currentRadius * cos((vDegrees * currentVertex) * DEDREES_TO_RADIANS);
			m_vData[i + 1] = height;
			m_vData[i + 2] = currentRadius * sin((vDegrees * currentVertex) * DEDREES_TO_RADIANS);
		}

		else
		{
			m_vData[i] = 0;
			m_vData[++i] = radius;
			m_vData[++i] = 0;
			m_vData[++i] = 0;
			m_vData[++i] = -radius;
			m_vData[++i] = 0;
		}

		currentVertex++;
	}
	//--------------------------------------------------------
	
	//Calculo los indices a los vertices
	iLoop = 1;
	currentVertex = 0;

	for (int i = 0; i < m_numFaces * 3; i += 6)
	{
		if (divisionsV == currentVertex)
		{
			iLoop++;
			currentVertex = 0;
		}

		if (iLoop < divisionsH)
		{
			m_vIndices[i] = ((iLoop - 1) * divisionsV) + currentVertex;

			if (currentVertex == divisionsH)
			{
				m_vIndices[i + 1] = ((iLoop - 1) * divisionsV);
				m_vIndices[i + 3] = (iLoop - 1) * divisionsV;
				m_vIndices[i + 4] = (((iLoop - 1) * divisionsV) + divisionsV);
			}

			else
			{
				m_vIndices[i + 1] = (((iLoop - 1) * divisionsV) + 1) + currentVertex;
				m_vIndices[i + 3] = (((iLoop - 1) * divisionsV) + 1) + currentVertex;
				m_vIndices[i + 4] = (((iLoop - 1) * divisionsV) + 1 + divisionsV) + currentVertex;
			}

			m_vIndices[i + 2] = (((iLoop - 1) * divisionsV) + divisionsV) + currentVertex;
			m_vIndices[i + 5] = (((iLoop - 1) * divisionsV) + divisionsV) + currentVertex;
		}

		else
		{
			unsigned short bottomVertex = m_vIndices[i - 1] + 1;
			unsigned short topVertex = bottomVertex + 1;

			unsigned short topLoop = (divisionsH * divisionsV) - divisionsV;

			for (int j = 0; j < divisionsV; j += 2)
			{
				m_vIndices[i++] = topLoop + j;
				m_vIndices[i++] = topLoop + j + 1;
				m_vIndices[i++] = topVertex;

				m_vIndices[i++] = topLoop + j + 1;

				m_vIndices[i++] = topLoop + j + 2;

				if (m_vIndices[i - 1] >= (topLoop + divisionsV))
				{
					m_vIndices[i - 1] = topLoop;
				}

				m_vIndices[i++] = topVertex;
			}

			for (int j = 0; j < divisionsV; j += 2)
			{
				m_vIndices[i++] = bottomVertex;
				m_vIndices[i++] = j + 1;
				m_vIndices[i++] = j;

				m_vIndices[i++] = bottomVertex;

				m_vIndices[i++] = j + 2;

				if (m_vIndices[i - 1] >= divisionsV)
				{
					m_vIndices[i - 1] = 0;
				}

				m_vIndices[i++] = j + 1;
			}
		}

		currentVertex++;
	}

	//--------------------------------------------------------
	//Le asigno el valor 0 a todos los indices
	for (int i = 0; i < m_numFaces; i += 3)
	{
		m_nData[i] = 0.0f;
		m_nData[i + 1] = 0.0f;
		m_nData[i + 2] = 0.0f;
	}

	//m_nIndices
	int nIndex = 0;

	for (int i = 0; i < m_numFaces * 3; i += 3)
	{
		m_nIndices[i] = nIndex;
		m_nIndices[i + 1] = nIndex;
		m_nIndices[i + 2] = nIndex;

		nIndex++;
	}

	//--------------------------------------------------------
	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		m_vData,			// vertices
		m_numVertex,	// Numero de vertices
		m_nData,			// Normales
		m_numFaces,		// Numero de normales
		m_vData,			// UV coords
		m_numVertex,	// Numero de UV coords
		m_vIndices,		// Indices de vertices
		m_numFaces,		// Numero de vertices
		m_nIndices,		// Indices a normales
		m_numFaces,		// Numero de indices a normales
		m_vIndices,		// Indices a las UV coords
		m_numFaces		// Numero de indices a UV coords
	);

	if (!loaded)
	{
		m_geoVAOID = 0;
	}
}

void CAppGeometria::CreateToroid(int CentralRadius, int OutRadius, int Horizontal, int Vertical)
{
	//--------------------------------------------------------
	bool loaded = false;

	float centralRadius = CentralRadius;
	float outRadius = OutRadius;

	float divisionsH = Horizontal;	 		//Subdivisiones horizontales
	float divisionsV = Vertical;			//Subdivisiones verticales

	float hDegrees = 360.0f / Horizontal;
	float vDegrees = 360.0f / Vertical;

	//--------------------------------------------------------
	//Numero de caras y vertices en el mesh
	m_numVertex = 0;
	m_numFaces = 0;

	int iLoop = 1;
	int currentVertex = 0;

	float currentRadius = 0;
	float height = 0;

	//--------------------------------------------------------
	//Para calcular normales
	float v1v3[3], v1v2[3], normal[3];

	//Numero de vertices
	m_vData = new float[m_numVertex * 3];
	//Indices de los vertices
	m_vIndices = new unsigned short[m_numFaces * 3];

	//Normales
	m_nData = new float[m_numFaces * 3];
	//Indices de las normales
	m_nIndices = new unsigned short[m_numFaces * 3];

	//--------------------------------------------------------
	//Calculo las posiciones de los vertices

	//Calculo los indices a los vertices

	//--------------------------------------------------------
	//Le asigno el valor 0 a todos los indices
	for (int i = 0; i < m_numFaces; i += 3)
	{
		m_nData[i] = 0.0f;
		m_nData[i + 1] = 0.0f;
		m_nData[i + 2] = 0.0f;
	}

	//Le asigno el valor de nIndex a cada normal
	int nIndex = 0;

	for (int i = 0; i < m_numFaces * 3; i += 3)
	{
		m_nIndices[i] = nIndex;
		m_nIndices[i + 1] = nIndex;
		m_nIndices[i + 2] = nIndex;

		nIndex++;
	}

	//--------------------------------------------------------
	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		m_vData,		// vertices
		m_numVertex,	// Numero de vertices
		m_nData,		// Normales
		m_numFaces,		// Numero de normales
		m_vData,		// UV coords
		m_numVertex,	// Numero de UV coords
		m_vIndices,		// Indices de vertices
		m_numFaces,		// Numero de vertices
		m_nIndices,		// Indices a normales
		m_numFaces,		// Numero de indices a normales
		m_vIndices,		// Indices a las UV coords
		m_numFaces		// Numero de indices a UV coords
	);

	if (!loaded)
	{
		m_geoVAOID = 0;
	}
}