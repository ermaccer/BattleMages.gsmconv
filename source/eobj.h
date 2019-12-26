#pragma once
#include <vector>

struct obj_v { float x, y, z; };
struct obj_uv { float u, v; };
struct obj_vn { float norm[3]; };
struct obj_face { int face[3]; };
struct obj_verts
{
	std::vector<obj_v> v;
	std::vector<obj_vn> vn;
	std::vector<obj_uv> uv;
};



class eObj {
	obj_verts TheModel;
	std::vector<obj_face> faces;
public:
	bool LoadFile(const char* name);
	void Print();
	std::vector<obj_face> GetFaces();
	obj_verts GetVertexes();
	std::vector<obj_v> gvVerts;
	std::vector<obj_uv> gvMaps;
	std::vector<obj_vn> gvNorm;
	// battle mages specific

	int CalcVertSize();
	int CalcFaceSize();
};