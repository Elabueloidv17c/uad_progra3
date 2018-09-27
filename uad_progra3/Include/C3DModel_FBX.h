#pragma once
#ifndef C3DMODEL_H_FBX
#define C3DMODEL_H_FBX

#include <string>
#include "C3DModel.h"

class C3DModel_FBX : public C3DModel
{
private:

	std::string m_file;

	int m_numVerticesIndex, m_numNormalsIndex, m_numUVIndex;


	bool loadFromFile(const char* const filename);
	bool parser(std::string dataToFind, int &arraySize, float* &arrayDestination);
	bool parser(std::string dataToFind, int &arraySize, unsigned short* &arrayDestination);
	void normalIndicesParser(int arraySizeSource, int &arraySizeDestination, unsigned short* arraySource, unsigned short* &arrayDestination);

public:

	C3DModel_FBX();
	~C3DModel_FBX();

	bool loader(const char* const filename);
	int getNumNormalsIndices() { return m_numNormalsIndex; }
	int getNumVertexIndices() { return m_numVerticesIndex; }
	int getNumUVIndices() { return m_numUVIndex; }
};

#endif // !C3DMODEL_H_FBX

