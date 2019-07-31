#pragma once

#include <vector>

#include "../GL/gl3w.h"
#include "../Learn3D/Vector3.h"

#include "./MeshData.h"

//using namespace std;

struct ObjFileHelper
{
	
public:
	void load_obj(const char* filename, std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<GLushort> &elements);

	MeshData loadObjAsVAO(const char* filename);
};