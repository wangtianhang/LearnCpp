#pragma once

//#include <iostream>
//#include <string>
#include <fstream>
#include<sstream>

#include "./ObjFileHelper.h"

void ObjFileHelper::load_obj(const char* filename, std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<GLushort> &elements)
{
	using namespace std;
	ifstream in(filename, ios::in);
	if (!in)
	{
		cerr << "Cannot open " << filename << endl; exit(1);
	}

	string line;
	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			istringstream s(line.substr(2));
			Vector3 v;
			s >> v.x; 
			s >> v.y; 
			s >> v.z; 
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; 
			s >> b; 
			s >> c;
			a--; 
			b--; 
			c--;
			elements.push_back(a); elements.push_back(b); elements.push_back(c);
		}
		else if (line[0] == '#')
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}

	normals.resize(vertices.size(), Vector3(0.0, 0.0, 0.0));
	for (int i = 0; i < elements.size(); i += 3)
	{
		GLushort ia = elements[i];
		GLushort ib = elements[i + 1];
		GLushort ic = elements[i + 2];
		Vector3 normal = Vector3::Normalize(Vector3::Cross(
			Vector3(vertices[ib]) - Vector3(vertices[ia]),
			Vector3(vertices[ic]) - Vector3(vertices[ia])));
		normals[ia] = normals[ib] = normals[ic] = normal;
	}
	
}

MeshData ObjFileHelper::loadObjAsVAO(const char* filename)
{
	MeshData ret;

	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<GLushort> indexs;
	load_obj(filename, vertices, normals, indexs);
	GLfloat * vertex_positions = new GLfloat[vertices.size() * 3];
	GLushort * vertex_indices = new GLushort[indexs.size()];
	GLfloat * vertex_normals = new GLfloat[normals.size() * 3];

	int size_vertex_positions = vertices.size() * 3 * 4;
	int size_vertex_indices = indexs.size() * 2;
	ret.drawVerticesCount = indexs.size();
	int size_vertex_normals = normals.size() * 3 * 4;

	//GLuint vao = 0;
	glGenVertexArrays(1, &ret.m_vao);
	glBindVertexArray(ret.m_vao);

	glGenBuffers(1, &ret.m_positionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.m_positionVBO);
	glBufferData(GL_ARRAY_BUFFER,
		size_vertex_positions,
		vertex_positions,
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ret.m_normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.m_normalVBO);
	glBufferData(GL_ARRAY_BUFFER,
		size_vertex_normals,
		vertex_normals,
		GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);

	glGenBuffers(1, &ret.m_indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.m_indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		size_vertex_indices,
		vertex_indices,
		GL_STATIC_DRAW);

	return ret;
}
