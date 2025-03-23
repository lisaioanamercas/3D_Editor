#include "FilesOp.h"

punct3d extractVertex(char line[256])
{
	punct3d vertex;

	strcpy(line, line + 2);

	float puncte[3];
	int index = 0;
	char* valoare = strtok(line, " ");
	while (valoare)
	{
		puncte[index] = (float)atof(valoare);

		index++;
		valoare = strtok(NULL, " ");
	}

	vertex.x = puncte[0];
	vertex.y = puncte[1];
	vertex.z = puncte[2];

	return vertex;
}

void extractEdge(char line[256], std::vector<Lista>& graph)
{
	vector<int> relatii;
	strcpy(line, line + 2);

	char* element = strtok(line, " ");
	while (element)
	{
		char index[256];
		strcpy(index, element);

		if (strchr(index, '/'))
		{
			int nullpos = strchr(index, '/') - index;
			index[nullpos] = '\0';
		}

		relatii.push_back(atoi(index) - 1);

		element = strtok(NULL, " ");
	}

	int relatii_size = relatii.size() - 1; /// am facut o schema

	for (int i = 0; i < relatii_size; i++)
		insereazaLista(graph[relatii[i]], 0, relatii[i + 1]);

	int size = relatii.size();
	insereazaLista(graph[relatii[size - 1]], 0, relatii[0]);
}

void readObject(const char* filepath, Engine& currentEngine)
{
	ifstream file(filepath);
	unsigned lastObject = currentEngine.eObjects.size() - 1;

	while (!file.eof())
	{
		char line[256];
		file.getline(line, 256);

		if (line[0] == 'v' && line[1] == ' ')
		{
			punct3d currentPoint;
			currentPoint = extractVertex(line);

			currentEngine.eObjects[lastObject].objViewPoints.push_back(currentPoint);
			currentEngine.eObjects[lastObject].nrOfPoints++;
		}

		if (line[0] == 'f')
			break;
	}

	for (int i = 0; i < currentEngine.eObjects[lastObject].objViewPoints.size(); i++)
	{
		Lista temp;
		listaVida(temp);

		currentEngine.eObjects[lastObject].objEdges.push_back(temp);
	}

	while (!file.eof())
	{
		char line[256];
		file.getline(line, 256);

		if (line[0] == 'f' && line[1] == ' ')
			extractEdge(line, currentEngine.eObjects[lastObject].objEdges);
	}

	file.close();
}

void loadObject(const char* filepath, Engine& currentEngine)
{
	Object temp;
	currentEngine.eObjects.push_back(temp);
	currentEngine.nrOfObjects++;

	int lastObject = currentEngine.eObjects.size() - 1;
	currentEngine.eObjects[lastObject].nrOfPoints = 0;

	readObject(filepath, currentEngine);

	int lastNrPts = currentEngine.eObjects[lastObject].nrOfPoints;
	currentEngine.eObjects[lastObject].nrOfClippedPoints = lastNrPts;

	//initializeaza toate multimile de puncte 
	for (int i = 0; i < lastNrPts; i++)
	{
		punct3d temp1;
		punct3d temp2;

		currentEngine.eObjects[lastObject].worldViewPoints.push_back(temp1);
		currentEngine.eObjects[lastObject].cameraViewPoints.push_back(temp2);
	}

	//initial tranformed view si camera view sunt identice cu object view
	for (int i = 0; i < lastNrPts; i++)
	{
		currentEngine.eObjects[lastObject].worldViewPoints[i] = currentEngine.eObjects[lastObject].objViewPoints[i];
		currentEngine.eObjects[lastObject].cameraViewPoints[i] = currentEngine.eObjects[lastObject].objViewPoints[i];
	}

	currentEngine.eObjects[lastObject].objOrigin.x = 0;
	currentEngine.eObjects[lastObject].objOrigin.y = 0;
	currentEngine.eObjects[lastObject].objOrigin.z = 0;
}
