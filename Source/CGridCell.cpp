#pragma once
#include "../Include/CGridCell.h"

CGridCell::CGridCell(int faces, int orientation, CVector3 center, float size)
{
	m_center = center;

	if (faces == HEXAGON)
	{
		m_pVertices = new CVector3[HEXAGON];
		
		int angle;

		if (orientation == FLAT)
		{
			angle = 0;
		}

		else
		{
			angle = 30;
		}

		float toAdd = 60;

		for (size_t i = 0; i < HEXAGON; i++)
		{
			m_pVertices[i] = CVector3((m_center.X + ((size / 2) * cos(angle * DEGREES_TO_RADIANS))),
									   m_center.Y + (((size / 2) * sin(angle* DEGREES_TO_RADIANS))), 
									   m_center.Z);
			angle += toAdd;
		}
	}

	else
	{

	}
}

CGridCell::~CGridCell()
{
	delete[] m_pVertices;
}