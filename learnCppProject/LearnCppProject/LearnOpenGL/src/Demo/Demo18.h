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

// hard shadow demo
class Demo18 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;

	MeshRenderObject * m_sphere = NULL;

	GLuint m_depth_fbo;

	int m_DEPTH_TEXTURE_SIZE = 1024;

	GLuint m_depth_tex;
	GLuint m_depth_debug_tex;

	GLuint m_drawDepthProgram;

	virtual void startup()
	{
		application::startup();

		InitScene();

		InitDepthFBO();
	}

	void InitScene()
	{
		m_drawDepthProgram = GLHelper::CreateShader("./Assets/shader/Demo18Vertex-drawDepth.txt", "./Assets/shader/Demo18Pixel-drawDepth.txt");

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
			mat.m_renderProgram = renderProgram;

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
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_DEPTH_TEXTURE_SIZE, m_DEPTH_TEXTURE_SIZE);
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
		glUseProgram(m_drawDepthProgram);
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



		for (int i = 0; i < application::app->m_sceneRenderMgr.m_renderGoVec.size(); ++i)
		{
			MeshRenderObject * iter = application::app->m_sceneRenderMgr.m_renderGoVec[i];

			//Matrix4x4 view = application::app->m_camera.GetViewMatrix();
			float aspect = (float)application::app->info.windowWidth / application::app->info.windowHeight;
			//float fov = 60;
			//float nearPlane = 0.3;
			//float farPlane = 10;
			//Matrix4x4 project = Matrix4x4::Perspective(fov, aspect, nearPlane, farPlane);

			float size = 5;
			Matrix4x4 orthoProject = Matrix4x4::Ortho(-size * aspect, size * aspect, -size, +size, 0.3, 50);
			Matrix4x4 mvp = orthoProject * view * iter->m_transform.GetLocalToWorldMatrix();
			//Matrix4x4 mv = view * iter->m_transform.GetLocalToWorldMatrix();
			//glUseProgram(iter->m_material.GetRenderProgram());

			GLuint mvpLocation = glGetUniformLocation(m_drawDepthProgram, "mvp");
			float mvpMatrixArray[16];
			mvp.GetMatrixArray(mvpMatrixArray);
			glUniformMatrix4fv(mvpLocation, 1, true, mvpMatrixArray);
// 			GLuint mvLocation = glGetUniformLocation(iter->m_material.GetRenderProgram(), "mv_matrix");
// 			float mvMatrixArray[16];
// 			mv.GetMatrixArray(mvMatrixArray);
// 			glUniformMatrix4fv(mvLocation, 1, true, mvMatrixArray);
// 
// 			GLuint viewLocation = glGetUniformLocation(iter->m_material.GetRenderProgram(), "view_matrix");
// 			float viewMatrixArray[16];
// 			view.GetMatrixArray(viewMatrixArray);
// 			glUniformMatrix4fv(viewLocation, 1, true, viewMatrixArray);
// 
// 
// 			GLuint projLocation = glGetUniformLocation(iter->m_material.GetRenderProgram(), "proj_matrix");
// 			float projMatrixArray[16];
// 			project.GetMatrixArray(projMatrixArray);
// 			glUniformMatrix4fv(projLocation, 1, true, projMatrixArray);

			Vector3 test = mvp.MultiplyPoint(Vector3::zero());

			iter->m_material.m_useOutProgram = true;
			iter->m_material.m_outProgram = m_drawDepthProgram;
			iter->RenderObj();
			iter->m_material.m_useOutProgram = false;
		}

		glViewport(0, 0, application::app->info.windowWidth, application::app->info.windowHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	static float Modulo(float a, int b)
	{
		return a - ((int)a / b) * b;
	}

	static Vector3 PingPong(Vector3 a, Vector3 b, float t)
	{
		float modt = Modulo(t, 2);
		//t = t % 2;
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
		//application::RenderCamera(delta);

		// Simply clear the window with red
		static const GLfloat white[] = { 0.f, 0.f, 0.f, 1.0f };
		static const GLfloat ones[] = { 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);
		glClearBufferfv(GL_DEPTH, 0, ones);

		//application::RenderScene(delta);

		GLHelper::DrawFullTexture(m_depth_debug_tex);
	}


	virtual void shutdown()
	{
		application::shutdown();

		//glDeleteProgram(m_rendering_program);
	}
};