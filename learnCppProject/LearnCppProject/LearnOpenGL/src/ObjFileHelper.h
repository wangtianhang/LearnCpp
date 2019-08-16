#pragma once

#include <vector>

#include "../GL/gl3w.h"
#include "./Learn3D/Vector3.h"

#include "./MeshFliter.h"

//using namespace std;

/*
struct ObjFileHelper
{
	
public:
	static void load_obj(const char* filename, std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<GLushort> &elements);

	static MeshFliter loadObjAsVAO(const char* filename);
};
*/

struct ObjFileHelper
{
public:
	static bool loadObjAsVAO(std::string path, std::vector<MeshFliter> & ret);

	//static void load_obj(const char* filename, std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<GLuint> &elements);

	//static MeshFliter loadObjAsVAO2(const char* filename);
};