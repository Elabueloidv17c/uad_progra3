#pragma once
#include "../Include/CVector3.h"
#include"../Include/CGameObject.h"

class CGridCell
{
	CGameObject* m_pGameObject;
	CVector3* m_pVertices;
	CVector3 m_center;

public:

	CGridCell(int faces, int orientation, CVector3 center, float size);
	CGridCell() = default;
	~CGridCell();
};