#pragma once
#include "../Include/CGrid.h"

CGrid::CGrid(unsigned short sizeX, unsigned short sizeY, unsigned short cellFaces, unsigned short cellOrientation, float cellSize)
{
	m_gridSizeX = sizeX;
	m_gridSizeY = sizeY;

	m_radius = cellSize / 2;

	m_cellVertices = cellFaces;
	m_cellOrientation = cellOrientation;

	m_numVertices = m_gridSizeX * m_gridSizeY * m_cellVertices;
	m_numNormals = m_numVertices;

	m_pDefaultIndices = nullptr;
	m_pNormalIndices = nullptr;
	m_pGridVertices = nullptr;
	m_pGridIndices = nullptr;
	m_pCellCenters = nullptr;
	m_pNormals = nullptr;

	if (m_cellVertices == HEXAGON)
	{
		m_numFaces = m_gridSizeX * m_gridSizeY * 4;
		m_cellFaces = 4;

		m_pDefaultIndices = new ShortVector3[4];

		m_pDefaultIndices[0] = ShortVector3(0, 1, 3);
		m_pDefaultIndices[1] = ShortVector3(1, 2, 3);
		m_pDefaultIndices[2] = ShortVector3(0, 3, 4);
		m_pDefaultIndices[3] = ShortVector3(0, 4, 5);

		m_apothem = cos(30 * DEGREES_TO_RADIANS) * m_radius;
		m_jump = m_radius * 1.5f;
	}

	else
	{
		//Construir variables para grid cuadrado
	}

	CreateGrid();
}

CGrid::~CGrid()
{
	delete[] m_pDefaultIndices;
	delete[] m_pNormalIndices;
	delete[] m_pGridVertices;
	delete[] m_pCellCenters;
	delete[] m_pNormals;

	m_pDefaultIndices = nullptr;
	m_pNormalIndices = nullptr;
	m_pGridVertices = nullptr;
	m_pCellCenters = nullptr;
	m_pNormals = nullptr;
}

void CGrid::CalcCenters(short orientation)
{
	m_pCellCenters = new CVector3[m_gridSizeX * m_gridSizeY];

	CVector3 currentCenterCoord = CVector3((-m_gridSizeX * m_jump) / 2, (-m_gridSizeY * m_apothem * 2) / 2, 0);

	short currentJump = orientation;
	short flipX = 1;

	if (m_cellVertices == HEXAGON)
	{
		for (size_t i = 0; i < m_gridSizeY; i++)
		{
			for (size_t j = 0; j < m_gridSizeX; j++)
			{
				m_pCellCenters[(i * m_gridSizeX) + j] = currentCenterCoord;

				if (orientation == FLAT)
				{
					currentCenterCoord += CVector3(m_jump, m_apothem * currentJump, 0);
				}

				else
				{
					currentCenterCoord += CVector3(m_apothem * 2, 0, 0);
				}

				currentJump *= -1;
			}

			currentJump = orientation;

			if (orientation == FLAT)
			{
				currentCenterCoord = CVector3 ( m_pCellCenters[0].X, 
												m_pCellCenters[0].Y + (m_apothem * 2) * (i + 1), 
												0 );
			}

			else
			{
				currentCenterCoord = CVector3(m_pCellCenters[m_gridSizeX * i].X + m_apothem * flipX,
											  m_pCellCenters[0].Y + (m_jump * (i + 1)),
											  0);

				flipX *= -1;
			}
		}
	}

	else
	{
		//Calcular centros de grid cuadrado
	}

}

void CGrid::CreateGrid()
{
	m_pGridVertices = new CVector3[m_gridSizeX * m_gridSizeY * m_cellVertices];
	m_pGridIndices = new ShortVector3[m_gridSizeX * m_gridSizeY * m_cellFaces];

	CalcCenters(m_cellOrientation);

	int currentCell = 0;

	for (size_t i = 0; i < m_gridSizeY; i++)
	{
		for (size_t j = 0; j < m_gridSizeX; j++)
		{
			CreateCell(m_pCellCenters[(m_gridSizeX * i) + j], m_pGridVertices + (((m_gridSizeX * i) + j) * m_cellVertices));
			CalcIndices(m_pGridIndices + (((m_gridSizeX * i) + j) * m_cellFaces), currentCell);

			currentCell++;
		}
	}

	CalcNormals(m_gridSizeX * m_gridSizeY * m_cellVertices);
	m_pNormalIndices = m_pGridIndices;
}

void CGrid::CreateCell(CVector3 center, CVector3* cell)
{
	short toAdd = 360 / m_cellVertices;
	short angle = 0;

	if (m_cellVertices == HEXAGON)
	{
		if (m_cellOrientation == POINTY)
		{
			angle = 30;
		}

		for (size_t i = 0; i < m_cellVertices; i++)
		{
			cell[i] = CVector3 (center.X + (m_radius * cos(angle * DEGREES_TO_RADIANS)),
								center.Y + (m_radius * sin(angle* DEGREES_TO_RADIANS)),
								0);

			angle += toAdd;
		}
	}

	else
	{
		//Calcular cuadrados
	}
}

void CGrid::CalcIndices(ShortVector3* cell, int currentCell)
{
	if (m_cellVertices == HEXAGON)
	{
		for (size_t i = 0; i < 4; i++)
		{
			cell[i].X = m_pDefaultIndices[i].X + (currentCell * m_cellVertices);
			cell[i].Y = m_pDefaultIndices[i].Y + (currentCell * m_cellVertices);
			cell[i].Z = m_pDefaultIndices[i].Z + (currentCell * m_cellVertices);
		}
	}

	else
	{
		for (size_t i = 0; i < 2; i++)
		{
			cell[i].X = m_pDefaultIndices[i].X + (currentCell * m_cellVertices);
			cell[i].Y = m_pDefaultIndices[i].Y + (currentCell * m_cellVertices);
			cell[i].Z = m_pDefaultIndices[i].Z + (currentCell * m_cellVertices);
		}
	}
}

void CGrid::CalcNormals(int size)
{
	m_pNormals = new CVector3[size];

	for (size_t i = 0; i < size; i++)
	{
		m_pNormals[i] = CVector3(i, i, i);
	}
}

float* const CGrid::GetVertices()
{
	return (float*) m_pGridVertices;
}

unsigned short* const CGrid::GetVerticesIndices()
{
	return (unsigned short*) m_pGridIndices;
}

float* const CGrid::GetNormals()
{
	return (float*) m_pNormals;
}

unsigned short* const CGrid::GetNormalsIndices()
{
	return (unsigned short*) m_pNormalIndices;
}

int CGrid::GetNumVertices()
{
	return m_numVertices;
}

int CGrid::GetNumNormals()
{
	return m_numNormals;
}

int CGrid::GetNumFaces()
{
	return m_numFaces;
}