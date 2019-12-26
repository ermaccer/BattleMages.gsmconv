#pragma once


#define MODEL_INFO_IDENT   2
#define VERTICES_IDENT     3
#define FACES_IDENT        61441
#define END_INFO_IDENT     61442


enum modelTypes {
	MODEL_TYPE_STATIC = 5,
	MODEL_TYPE_ANIMATED
};


struct m3dSection {
	int   sectionSize;
	int   sectionOffset;
	int   _pad = 0;
	int   sectionIdentifier;
};

struct gsmHeader {
	char  strHeader[8] = {}; // ecbnt,t
	int   modelType;
	int   version;
	m3dSection modelInfo;
	m3dSection vertices;
	m3dSection faces;
	m3dSection endInfo;
	int   valueSize;
	int   valueOffset;
	int   value_pad;
};

struct modelInfo {
	int    header; // GSSM
	int    type;
	int    vertices; // verticesCount / 4  / 4 / 2
	int    faces; // faceCount / 2 / 3
	char   unk; // always 1
	char   textName[131] = {};
};
#pragma pack (push,1)
struct endInfo {
	int header; // GSM
	char pad[26] = {};
}; 
#pragma (pop)