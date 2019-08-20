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

// vsm demo
class Demo20 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;

	MeshRenderObject * m_sphere = NULL;

	GLuint m_depth_fbo;

	int m_DEPTH_TEXTURE_SIZE = 128;

	GLuint m_depth_tex;
	GLuint m_depth_debug_tex;

	//GLuint m_drawDepthProgram;
	Material m_drawDepthMat;

	GLuint m_renderProgram;

	Matrix4x4 m_worldToLightViewAndProjectMatrix;


	virtual void startup()
	{
		application::startup();

		InitScene();

		InitDepthFBO();
	}

	void InitScene()
	{
		m_drawDepthMat.m_renderProgram = GLHelper::CreateShader("./Assets/shader/Demo18Vertex-drawDepth.txt", "./Assets/shader/Demo20Pixel-drawDepth.txt");

		m_renderProgram = GLHelper::CreateShader("./Assets/shader/Demo19Vertex-withShadow.txt", "./Assets/shader/Demo20Pixel-withShadow.txt");
		Vector3 lightEuler = Vector3(50, -30, 0);
		Vector3 lightDir = Quaternion::Euler(lightEuler) * Vector3::forward();
		lightDir.Normalize();
		glUseProgram(m_renderProgram);
		glUniform3f(glGetUniformLocation(m_renderProgram, "light_dir"), lightDir.x, lightDir.y, lightDir.z);

		{
			MeshFliter meshFilter = GLHelper::CreateSphereMesh();

			Material mat;
			mat.m_renderProgram = m_renderProgram;

			MeshRenderObject * obj = new MeshRenderObject();
			obj->m_meshData = meshFilter;
			obj->m_material = mat;
			obj->m_transform.SetLocalScale(Vector3::one() * 1);
			obj->m_transform.SetPosition(Vector3(0, 0.5, 0));
			m_sceneRenderMgr.m_renderGoVec.push_back(obj);

			m_sphere = obj;
		}

		{
			MeshFliter meshFilter = GLHelper::CreateCubeMesh();

			Material mat;
			mat.m_renderProgram = m_renderProgram;

			MeshRenderObject * obj = new MeshRenderObject();
			obj->m_meshData = meshFilter;
			obj->m_material = mat;
			obj->m_transform.SetLocalScale(Vector3(5, 1, 5));
			obj->m_transform.SetPosition(Vector3(0, -0.5, 0));
			m_sceneRenderMgr.m_renderGoVec.push_back(obj);
		}

		m_camera.m_transform.SetPosition(Vector3(0, 2, -5));
		m_camera.m_transform.SetEulerAngles(Vector3(20, 0, 0));
	}

	void InitDepthFBO()
	{
		glGenFramebuffers(1, &m_depth_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_depth_fbo);

		glGenTextures(1, &m_depth_tex);
		glBindTexture(GL_TEXTURE_2D, m_depth_tex);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, m_DEPTH_TEXTURE_SIZE, m_DEPTH_TEXTURE_SIZE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth_tex, 0);

		glGenTextures(1, &m_depth_debug_tex);
		glBindTexture(GL_TEXTURE_2D, m_depth_debug_tex);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16, m_DEPTH_TEXTURE_SIZE, m_DEPTH_TEXTURE_SIZE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_depth_debug_tex, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void DrawDepth()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_depth_fbo);
		glViewport(0, 0, m_DEPTH_TEXTURE_SIZE, m_DEPTH_TEXTURE_SIZE);
		glUseProgram(m_drawDepthMat.m_renderProgram);
		static const GLenum buffs[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffs);
		static const GLfloat zero[] = { 1.0f, 1, 1, 1 };
		glClearBufferfv(GL_COLOR, 0, zero);
		static const GLfloat ones[] = { 1.0f };
		glClearBufferfv(GL_DEPTH, 0, ones);

		Vector3 lightCameraPos = Vector3(3.9, 7.4, -6.1);
		Vector3 lightCameraEuler = Vector3(50, -30, 0);
		Matrix4x4 lightCameraLocalToWorld = Matrix4x4::TRS(lightCameraPos, Quaternion::Euler(lightCameraEuler), Vector3::one());
		Matrix4x4 view = GLHelper::worldToCameraMatrix(lightCameraLocalToWorld);

		float aspect = (float)application::s_app->info.windowWidth / application::s_app->info.windowHeight;
		float size = 5;
		Matrix4x4 orthoProject = Matrix4x4::Ortho(-size * aspect, size * aspect, -size, +size, 0.3, 50);

		m_worldToLightViewAndProjectMatrix = orthoProject * view;

		for (int i = 0; i < application::s_app->m_sceneRenderMgr.m_renderGoVec.size(); ++i)
		{
			MeshRenderObject * iter = application::s_app->m_sceneRenderMgr.m_renderGoVec[i];


			Matrix4x4 mvp = orthoProject * view * iter->m_transform.GetLocalToWorldMatrix();

			GLuint mvpLocation = glGetUniformLocation(m_drawDepthMat.m_renderProgram, "mvp");
			float mvpMatrixArray[16];
			mvp.GetMatrixArray(mvpMatrixArray);
			glUniformMatrix4fv(mvpLocation, 1, true, mvpMatrixArray);


			Vector3 test = mvp.MultiplyPoint(Vector3::zero());

			Material cacheMat = iter->m_material;
			iter->m_material = m_drawDepthMat;
			iter->RenderObj();
			//iter->m_material.m_useOutProgram = false;
			iter->m_material = cacheMat;
		}

		glViewport(0, 0, application::s_app->info.windowWidth, application::s_app->info.windowHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


	}

	static float Modulo(float a, int b)
	{
		return a - ((int)a / b) * b;
	}

	static Vector3 PingPong(Vector3 a, Vector3 b, float t)
	{
		float modt = Modulo(t, 2);
		if (modt < 1)
		{
			return Vector3::Lerp(a, b, modt);
		}
		else
		{
			return Vector3::Lerp(b, a, modt - 1);
		}
	}

	virtual void render(double currentTime)
	{
		float delta = currentTime - m_accTime;
		m_accTime = currentTime;

		RenderUpdate(delta);
	}

	virtual void RenderUpdate(float delta)
	{
		Vector3 newPos = PingPong(Vector3(0, 0.5, 0), Vector3(0, 1.5, 0), m_accTime);
		m_sphere->m_transform.SetPosition(newPos);


		DrawDepth();


		// 进入渲染流程时 应该已经全部移动完毕 相机应该在稳定后计算位置
		application::RenderCamera(delta);

		// Simply clear the window with red
		static const GLfloat white[] = { 0.f, 0.f, 0.f, 1.0f };
		static const GLfloat ones[] = { 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);
		glClearBufferfv(GL_DEPTH, 0, ones);


		glUseProgram(m_renderProgram);
		GLuint unit = 0;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_depth_debug_tex);
		int location = glGetUniformLocation(m_renderProgram, "shadowMap");
		glUniform1i(location, unit);

		int depthSizeLocation = glGetUniformLocation(m_renderProgram, "depthSize");
		glUniform2i(depthSizeLocation, m_DEPTH_TEXTURE_SIZE, m_DEPTH_TEXTURE_SIZE);

		GLuint worldToLightViewAndProjectLocation = glGetUniformLocation(m_renderProgram, "worldToLightViewAndProject_matrix");
		float worldToLightViewAndProjectArray[16];
		m_worldToLightViewAndProjectMatrix.GetMatrixArray(worldToLightViewAndProjectArray);
		glUniformMatrix4fv(worldToLightViewAndProjectLocation, 1, true, worldToLightViewAndProjectArray);

		application::RenderScene(delta);

		//GLHelper::DrawFullTexture(m_depth_debug_tex);
	}


	virtual void shutdown()
	{
		application::shutdown();
	}
};