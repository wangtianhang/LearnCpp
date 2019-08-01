#pragma once

#include <string>

#include "../ApplicationBase.h"
#include "../FileIO.h"
#include "../Learn3D/Mathf.h"
#include "../Learn3D/Vector4.h"
#include "../Learn3D/Vector3.h"
#include "../Learn3D/Matrix4x4.h"
#include "../GLHelper.h"
#include "../Camera.h"
#include "../PNGHelper.h"

// direction light demo
class Demo17 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;

	virtual void startup()
	{
		application::startup();

		GLuint renderProgram = GLHelper::CreateShader("./Assets/shader/Demo17Vertex.txt", "./Assets/shader/Demo17Pixel.txt");
		Vector3 lightEuler = Vector3(50, -30, 0);
		Vector3 lightDir = Quaternion::Euler(lightEuler) * Vector3::forward();
		lightDir.Normalize();
		glUseProgram(renderProgram);
		glUniform3f(glGetUniformLocation(renderProgram, "light_dir"), lightDir.x, lightDir.y, lightDir.z);

		{
			MeshFliter meshFilter = GLHelper::CreateSphereMesh();

			Material mat;
			mat.m_renderProgram = renderProgram;
			//GLuint albedo = PNGHelper::LoadPngAsGLTexture("./Assets/texture/Rock_Ground_01_Dif_Spec.png");
			//GLuint normal = PNGHelper::LoadPngAsGLTexture("./Assets/texture/Rock_Ground_01_Nor.png");

// 			glUseProgram(mat.m_renderProgram);
// 			GLuint unit = 0;
// 			glActiveTexture(GL_TEXTURE0 + unit);
// 			glBindTexture(GL_TEXTURE_2D, albedo);
// 			int location = glGetUniformLocation(mat.m_renderProgram, "tex_color");
// 			glUniform1i(location, unit);
// 
// 			unit = 1;
// 			glActiveTexture(GL_TEXTURE0 + unit);
// 			glBindTexture(GL_TEXTURE_2D, normal);
// 			int location2 = glGetUniformLocation(mat.m_renderProgram, "tex_normal");
// 			glUniform1i(location2, unit);

			MeshRenderObject obj;
			obj.m_meshData = meshFilter;
			obj.m_material = mat;
			obj.m_transform.SetLocalScale(Vector3::one() * 1);
			obj.m_transform.SetPosition(Vector3(0, 0.5, 0));
			m_sceneRenderMgr.m_renderGoVec.push_back(obj);
		}

		{
			MeshFliter meshFilter = GLHelper::CreateCubeMesh();

			//std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo12Vertex.txt");
			//std::string fragment_shader_source = LoadTextFile("./Assets/shader/Demo12Pixel.txt");
			Material mat;
			mat.m_renderProgram = renderProgram;

			MeshRenderObject obj;
			obj.m_meshData = meshFilter;
			obj.m_material = mat;
			obj.m_transform.SetLocalScale(Vector3(5, 1, 5));
			obj.m_transform.SetPosition(Vector3(0, -0.5, 0));
			m_sceneRenderMgr.m_renderGoVec.push_back(obj);
		}

		m_camera.m_transform.SetPosition(Vector3(0, 2, -5));
		m_camera.m_transform.SetEulerAngles(Vector3(20, 0, 0));
	}

	virtual void render(double currentTime)
	{
		float delta = currentTime - m_accTime;
		m_accTime = currentTime;

		RenderUpdate(delta);
	}

	virtual void RenderUpdate(float delta)
	{
		// 进入渲染流程时 应该已经全部移动完毕 相机应该在稳定后计算位置
		application::RenderCamera(delta);

		// Simply clear the window with red
		static const GLfloat white[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		static const GLfloat ones[] = { 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);
		glClearBufferfv(GL_DEPTH, 0, ones);

		application::RenderScene(delta);


	}


	virtual void shutdown()
	{
		application::shutdown();

		//glDeleteProgram(m_rendering_program);
	}
};