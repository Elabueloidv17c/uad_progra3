#pragma once
#include "../Include/CVector3.h"
#include "../Include/CGridCell.h"

class CGrid
{
	ShortVector3* m_pDefaultIndices;
	CVector3* m_pCellCenters;

	ShortVector3* m_pGridIndices;
	CVector3* m_pGridVertices;
	
	ShortVector3* m_pNormalIndices;
	CVector3* m_pNormals;

	int m_numVertices;
	int m_numNormals;
	int m_numFaces;

	unsigned short m_cellOrientation;
	unsigned short m_cellVertices;
	unsigned short m_cellFaces;

	unsigned short m_gridSizeX;
	unsigned short m_gridSizeY;

	float m_radius;

	float m_apothem;
	float m_jump;

public:

	CGrid(unsigned short sizeX, unsigned short sizeY, unsigned short cellFaces, unsigned short cellOrientation, float cellSize);
	CGrid() = default;
	~CGrid();

	void CalcIndices(ShortVector3* cell, int currentCell);
	void CreateCell(CVector3 center, CVector3* cell);
	void CalcNormals(int size);
	void CalcCenters(short orientation);
	void CreateGrid();

	unsigned short* const GetVerticesIndices();
	unsigned short* const GetNormalsIndices();
	
	float* const GetVertices();
	float* const GetNormals();

	int GetNumVertices();
	int GetNumNormals();
	int GetNumFaces();
};