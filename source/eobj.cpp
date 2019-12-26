#include "eobj.h"
#include <iostream>
#include <string>
#include <algorithm>

bool eObj::LoadFile(const char * name)
{
	char szLine[1024];
	FILE* pFile = fopen(name, "rb");
	if (!pFile)
	{
		std::cout << "ERROR: Could not open " << name << "!" << std::endl;
		return false;
	}


	std::vector<obj_v> vVerts;
	std::vector<obj_uv> vMaps;
	std::vector<obj_vn> vNorm;

	while (fgets(szLine, 1024, pFile))
	{
		if (szLine[0] == '#' || szLine[0] == ';')
			continue;

		if (szLine[0] == 'f' && szLine[1] == ' ')
		{
			obj_face f;
			int fa; 
			int i = 0;
			while (szLine[i] != '\0')
			{
				if (szLine[i] == '/')
					szLine[i] = ' ';
				i++;
			}
			sscanf(szLine + 2, "%d %d %d %d %d %d %d %d %d", &f.face[0], &fa, &fa, &f.face[1], &fa, &fa, &f.face[2], &fa, &fa);

			f.face[0] -= 1;
			f.face[1] -= 1;
			f.face[2] -= 1;
			faces.push_back(f);
		}
		if (szLine[0] == 'v' && szLine[1] == ' ')
		{
			obj_v vert;
			sscanf(szLine + 2, "%f %f %f", &vert.x, &vert.y, &vert.z);
			vVerts.push_back(vert);
		}
		if (szLine[0] == 'v' && szLine[1] == 't' && szLine[2] == ' ')
		{
			obj_uv map;
			sscanf(szLine + 2, "%f %f", &map.u, &map.v);
			vMaps.push_back(map);
		}
		if (szLine[0] == 'v' && szLine[1] == 'n' && szLine[2] == ' ')
		{
			// unknown, todo
			obj_vn vn = { 0.0,0.0,0.0 };
			vNorm.push_back(vn);
		}
	}

	TheModel.v = vVerts;
	TheModel.uv = vMaps;
	TheModel.vn = vNorm;
	gvMaps = vMaps;
	gvVerts = vVerts;
	gvNorm = vNorm;


}

void eObj::Print()
{
	printf("Loaded vertex coords:\n");
	for (int i = 0; i < TheModel.v.size(); i++)
		printf("X:%f Y:%f Z:%f\n", TheModel.v[i].x, TheModel.v[i].y, TheModel.v[i].z);

	printf("Loaded vertex uv maps:\n");
	for (int i = 0; i < TheModel.uv.size(); i++)
		printf("U:%f V:%f\n", TheModel.uv[i].u, TheModel.uv[i].v);

	printf("Loaded vertex normals:\n");
	for (int i = 0; i < TheModel.vn.size(); i++)
		printf("%f %f %f\n", TheModel.vn[i].norm[0], TheModel.vn[i].norm[1], TheModel.vn[i].norm[2]);

	printf("Loaded faces:\n");
	for (int i = 0; i < faces.size(); i++)
		printf("%d %d %d\n", faces[i].face[0], faces[i].face[1], faces[i].face[2]);

	printf("Faces :%d | Verts: %d\n", faces.size(), TheModel.v.size());
}

std::vector<obj_face> eObj::GetFaces()
{
	return faces;
}

obj_verts eObj::GetVertexes()
{
	return TheModel;
}

int eObj::CalcVertSize()
{
	return TheModel.v.size() * 4 * 4 * 2;
}

int eObj::CalcFaceSize()
{
	return faces.size() * 3 * 2;
}
