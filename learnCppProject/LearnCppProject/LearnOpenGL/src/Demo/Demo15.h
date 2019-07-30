#pragma once

#include <string>

#include "../LearnOpengl/ApplicationBase.h"
#include "../IO/FileIO.h"
#include "../Learn3D/Mathf.h"
#include "../Learn3D/Vector4.h"
#include "../Learn3D/Vector3.h"
#include "../Learn3D/Matrix4x4.h"
#include "../GL/GLUtil.h"

// skybox demo
class Demo15 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	//GLuint m_vertex_array_object = 0;

	//GLuint m_buffer;
	//GLuint m_vao;
	//int m_sphereDrawVertexCount = 0;

	//GLuint m_albedo = 0;
	//GLuint m_normal = 0;
	GLuint m_skyBoxCubemap = 0;

	GLuint m_skyBoxVao = 0;
	GLuint m_skyBoxVbo = 0;

	virtual void startup()
	{
		application::startup();

		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo15Vertex.txt");
		std::string fragment_shader_source = LoadTextFile("./Assets/shader/Demo15Pixel.txt");

		GLuint vertex = CreateShaderFromString(vertex_shader_source.c_str(), GL_VERTEX_SHADER, true);
		GLuint pixel = CreateShaderFromString(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER, true);
		m_rendering_program = CreateShaderProgram(vertex, pixel, true, true);
		//glCreateVertexArrays(1, &m_vertex_array_object);
		//glBindVertexArray(m_vertex_array_object);

		//TestBufferWithVAO();

		//m_vao = GLUtil::CreateSphereVAO(m_sphereDrawVertexCount);

		//m_albedo = PNGHelper::LoadPngAsGLTexture("./Assets/texture/Rock_Ground_01_Dif_Spec.png");
		//m_normal = PNGHelper::LoadPngAsGLTexture("./Assets/texture/Rock_Ground_01_Nor.png");

		InitSkyBox();
	}

	virtual void render(double currentTime)
	{
		float delta = currentTime - m_accTime;
		m_accTime = currentTime;

		RenderUpdate(delta);
	}



	void RenderUpdate(float delta)
	{
		// Simply clear the window with red
		static const GLfloat white[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		static const GLfloat ones[] = { 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);
		glClearBufferfv(GL_DEPTH, 0, ones);

		DrawSkyBox();

// 		Vector3 euler = Vector3(m_accTime * 10, 0, 0);
// 		Matrix4x4 model_localToWorld = Matrix4x4::TRS(Vector3(-0, 0, 0), Quaternion::Euler(euler), Vector3::one() * 5);
// 		Vector3 cameraPos = Vector3(0, 0, -10);
// 		Vector3 cameraEuler = Vector3::zero();
// 		Matrix4x4 cameraLocalToWorld = Matrix4x4::TRS(cameraPos, Quaternion::Euler(cameraEuler), Vector3::one());
// 		// camera worldToLocal
// 		Matrix4x4 view = GLUtil::worldToCameraMatrix(cameraLocalToWorld);
// 		float aspect = (float)info.windowWidth / info.windowHeight;
// 		float fov = 60;
// 		float nearPlane = 0.3;
// 		float farPlane = 1000;
// 		Matrix4x4 project = Matrix4x4::Perspective(fov, aspect, nearPlane, farPlane);
// 		Matrix4x4 mvp = project * view * model_localToWorld;
// 		Matrix4x4 mv = view * model_localToWorld;
// 		glUseProgram(m_rendering_program);
// 
// 
// 		GLuint mvLocation = glGetUniformLocation(m_rendering_program, "mv_matrix");
// 		float mvMatrixArray[16];
// 		mv.GetMatrixArray(mvMatrixArray);
// 		glUniformMatrix4fv(mvLocation, 1, true, mvMatrixArray);

		// 		GLuint viewLocation = glGetUniformLocation(m_rendering_program, "view_matrix");
		// 		float viewMatrixArray[16];
		// 		view.GetMatrixArray(viewMatrixArray);
		// 		glUniformMatrix4fv(viewLocation, 1, true, viewMatrixArray);

// 		GLuint projLocation = glGetUniformLocation(m_rendering_program, "proj_matrix");
// 		float projMatrixArray[16];
// 		project.GetMatrixArray(projMatrixArray);
// 		glUniformMatrix4fv(projLocation, 1, true, projMatrixArray);

		//GLuint lightPosLocation = glGetUniformLocation(m_rendering_program, "light_pos");
		//Vector3 mvLightPos = view.MultiplyPoint(Vector3(-20, 20, -20));
		//glUniform3f(lightPosLocation, mvLightPos.x, mvLightPos.y, mvLightPos.z);
		//Vector3 test = mv.MultiplyPoint(Vector3(0, 0, 0));
// 		GLuint unit = 0;
// 		glActiveTexture(GL_TEXTURE0 + unit);
// 		glBindTexture(GL_TEXTURE_2D, m_albedo);
// 		int location = glGetUniformLocation(m_rendering_program, "tex_color");
// 		glUniform1i(location, unit);
// 
// 		unit = 1;
// 		glActiveTexture(GL_TEXTURE0 + unit);
// 		glBindTexture(GL_TEXTURE_2D, m_normal);
// 		int location2 = glGetUniformLocation(m_rendering_program, "tex_normal");
// 		glUniform1i(location2, unit);

		//glEnable(GL_CULL_FACE);
		// unity内部顺时针
		//glFrontFace(GL_CCW);
		//glCullFace(GL_BACK);
		//glDisable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// 这种先bind再draw很蛋疼。。
		//glBindVertexArray(m_vao);
		//glDrawElements(GL_TRIANGLES, m_sphereDrawVertexCount, GL_UNSIGNED_SHORT, 0);
		//glDrawArrays(m_vertex_array_object, )


	}

	void InitSkyBox()
	{
		std::vector<std::string> facesList;
		facesList.push_back("./Assets/texture/skybox/Sky_Day Sun High ClearHazy_Cam_1_Right+X.png");
		facesList.push_back("./Assets/texture/skybox/Sky_Day Sun High ClearHazy_Cam_3_Left-X.png");
		facesList.push_back("./Assets/texture/skybox/Sky_Day Sun High ClearHazy_Cam_4_Top+Y.png");
		facesList.push_back("./Assets/texture/skybox/Sky_Day Sun High ClearHazy_Cam_5_Down-Y.png");
		facesList.push_back("./Assets/texture/skybox/Sky_Day Sun High ClearHazy_Cam_0_Front+Z.png");
		facesList.push_back("./Assets/texture/skybox/Sky_Day Sun High ClearHazy_Cam_2_Back-Z.png");
		m_skyBoxCubemap = PNGHelper::LoadCubemap(facesList);

		GLfloat skyboxVertices[] = {
			// Positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		glGenVertexArrays(1, &m_skyBoxVao);
		glGenBuffers(1, &m_skyBoxVbo);
		glBindVertexArray(m_skyBoxVao);
		glBindBuffer(GL_ARRAY_BUFFER, m_skyBoxVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glBindVertexArray(0);

	}

	void UnInitSkyBox()
	{

	}

	void DrawSkyBox()
	{
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CCW);

		glUseProgram(m_rendering_program);

		Vector3 cameraPos = Vector3(0, 0, -10);
		Vector3 cameraEuler = Vector3::zero();
		Matrix4x4 cameraLocalToWorld = Matrix4x4::TRS(cameraPos, Quaternion::Euler(cameraEuler), Vector3::one());
		Matrix4x4 view = GLUtil::worldToCameraMatrix(cameraLocalToWorld);
		// 移除位移分量
		view = Matrix4x4::RemoveTranslationComponent(view);

		float aspect = (float)info.windowWidth / info.windowHeight;
		float fov = 60;
		float nearPlane = 0.3;
		float farPlane = 1000;
		Matrix4x4 project = Matrix4x4::Perspective(fov, aspect, nearPlane, farPlane);

		float viewArray[16];
		float projectArray[16];
		view.GetMatrixArray(viewArray);
		project.GetMatrixArray(projectArray);
		glUniformMatrix4fv(glGetUniformLocation(m_rendering_program, "view"), 1, true, viewArray);
		glUniformMatrix4fv(glGetUniformLocation(m_rendering_program, "projection"), 1, true, projectArray);

		glBindVertexArray(m_skyBoxVao);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(m_rendering_program, "skybox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyBoxCubemap);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		glDepthMask(GL_TRUE);
	}

	virtual void shutdown()
	{
		application::shutdown();

		UnInitSkyBox();

		glDeleteProgram(m_rendering_program);
		//glDeleteVertexArrays(1, &m_vao);
		//glDeleteBuffers(1, &m_buffer);
	}
};