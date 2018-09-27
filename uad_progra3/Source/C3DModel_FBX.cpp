#include "../stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "../Include/C3DModel.h"
#include "../Include/C3DModel_FBX.h"

C3DModel_FBX::C3DModel_FBX() :
	C3DModel(),
	m_numVerticesIndex(0),
	m_numNormalsIndex(0),
	m_numUVIndex(0)
{
	cout << "Constructor: C3DModel_FBX()" << endl;

	m_numVertices = 0;
	m_numNormals = 0;
	m_numUVCoords = 0;
	m_numFaces = 0;
}

C3DModel_FBX::~C3DModel_FBX()
{
	cout << "Destructor: ~C3DModel_FBX()" << endl;
	reset();
}

void C3DModel_FBX::normalIndicesParser(int arraySizeSource, int &arraySizeDestination, unsigned short* arraySource, unsigned short* &arrayDestination)
{
	arraySizeDestination = arraySizeSource * 3;
	arrayDestination = new unsigned short[arraySizeDestination];


	size_t index = 0;

	for (size_t i = 0; i < arraySizeDestination; i += 3)
	{
		arrayDestination[i] = arraySource[index];
		arrayDestination[i + 1] = arraySource[index];
		arrayDestination[i + 2] = arraySource[index];

		index++;
	}
}

bool C3DModel_FBX::loadFromFile(const char* const filename)
{
	reset();

	string file = filename;

	//Crea un Fstream que abre el archivo a leer en modo binario y busca el final del mismo
	std::ifstream reader;
	reader.open(file, std::ios::in | std::ios::binary | std::ios::ate);

	//Si el archivo no se lee correctamente, devuelve falso
	if (reader.fail())
	{
		return false;
	}

	//Retorna el tamaño del archivo
	size_t sizeOfFile = reader.tellg();

	//Posiciona al buffer en la primera direccion del archivo
	reader.seekg(std::ios::beg);

	//Crea un string del tamaño del archivo
	m_file = std::string(sizeOfFile, 0);

	//Lee todo el archivo y lo almacena en el string "textFile"
	reader.read(&m_file[0], sizeOfFile);

	return true;
}

bool C3DModel_FBX::parser(std::string dataToFind, int &arraySize, float* &arrayDestination)
{

	size_t posIni = m_file.find(dataToFind + ": *") + dataToFind.length() + 3;
	size_t posFin = m_file.find(' ', posIni);

	arraySize = stoi(m_file.substr(posIni, posFin - posIni));

	if (arrayDestination == nullptr)
	{
		arrayDestination = new float[arraySize];
	}

	else
	{
		return false;
	}

	posIni = m_file.find("a: ", posFin) + 3;
	posFin = m_file.find('}', posFin);


	std::string dataToConvert = m_file.substr(posIni, posFin - posIni);
	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), '\r'), dataToConvert.end());
	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), '\n'), dataToConvert.end());
	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), '\t'), dataToConvert.end());
	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), ' '), dataToConvert.end());

	posIni = 0;
	posFin = dataToConvert.find(',');
	int index = 0;

	while (posFin < dataToConvert.length())
	{
		posFin = dataToConvert.find(',', posIni);
		arrayDestination[index] = stof(dataToConvert.substr(posIni, posFin - posIni));
		posIni = posFin + 1;

		index++;
	}

	return true;
}

bool C3DModel_FBX::parser(std::string dataToFind, int &arraySize, unsigned short* &arrayDestination)
{
	size_t posIni = m_file.find(dataToFind + ": *") + dataToFind.length() + 3;
	size_t posFin = m_file.find(' ', posIni);

	arraySize = stoi(m_file.substr(posIni, posFin - posIni));
	arrayDestination = new unsigned short[arraySize];

	posIni = m_file.find("a: ", posFin) + 3;
	posFin = m_file.find('}', posFin);


	std::string dataToConvert = m_file.substr(posIni, posFin - posIni);

	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), '\r'), dataToConvert.end());
	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), '\n'), dataToConvert.end());
	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), '\t'), dataToConvert.end());
	dataToConvert.erase(std::remove(dataToConvert.begin(), dataToConvert.end(), ' '), dataToConvert.end());

	posIni = 0;
	posFin = dataToConvert.find(',');

	int index = 0;
	int parsedNumber = 0;

	while (posFin < dataToConvert.length())
	{
		posFin = dataToConvert.find(',', posIni);

		parsedNumber = (stoi(dataToConvert.substr(posIni, posFin - posIni)));

		if (dataToFind == "PolygonVertexIndex" && parsedNumber < 0)
		{
			parsedNumber = (parsedNumber * -1) - 1;
		}

		arrayDestination[index] = parsedNumber;
		posIni = posFin + 1;

		index++;
	}

	return true;
}

bool C3DModel_FBX::loader(const char* const filename)
{
	if (!loadFromFile(filename))
	{
		return false;
	}

	parser("Vertices", m_numVertices, m_verticesRaw);
	parser("PolygonVertexIndex", m_numVerticesIndex, m_vertexIndices);

	parser("Normals", m_numNormals, m_normalsRaw);
	normalIndicesParser(m_numVerticesIndex, m_numNormalsIndex, m_vertexIndices, m_normalIndices);

	parser("UV", m_numUVCoords, m_uvCoordsRaw);
	parser("UVIndex", m_numUVIndex, m_UVindices);

	return true;
}