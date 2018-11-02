#pragma once
#include "../Include/Globals.h"
#include "../Include/Cvector3.h"
#include "../Include/C3DModel_FBX.h"

class CGameObject
{
	C3DModel* m_mesh;

	CVector3 m_position;
	CVector3 m_rotation;
	float m_scale;

public:
	CGameObject();
	~CGameObject();
};

