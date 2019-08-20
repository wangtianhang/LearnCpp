#include "./DebugMemory.h"

#include "./SceneRenderMgr.h"
#include "./ApplicationBase.h"

void SceneRenderMgr::Update(float delta)
{
	
	// step1 draw shadow depth

	// step2 draw opaque render go with shadow

	// step3 draw skybox

	for (int i = 0; i < m_renderGoVec.size(); ++i)
	{
		MeshRenderObject iter = *m_renderGoVec[i];

		

		Matrix4x4 view = application::s_app->m_camera.GetViewMatrix();
		float aspect = (float)application::s_app->info.windowWidth / application::s_app->info.windowHeight;
		float fov = 60;
		float nearPlane = 0.3;
		float farPlane = 1000;
		Matrix4x4 project = Matrix4x4::Perspective(fov, aspect, nearPlane, farPlane);
		Matrix4x4 mvp = project * view * iter.m_transform.GetLocalToWorldMatrix();
		Matrix4x4 mv = view * iter.m_transform.GetLocalToWorldMatrix();
		glUseProgram(iter.m_material.m_renderProgram);

		Vector3 test = (project * view).MultiplyPoint(Vector3::zero());

		GLuint modelToWorldLocation = glGetUniformLocation(iter.m_material.m_renderProgram, "modelToWorldMatrix");
		float modelToWorldMatrixArray[16];
		iter.m_transform.GetLocalToWorldMatrix().GetMatrixArray(modelToWorldMatrixArray);
		glUniformMatrix4fv(modelToWorldLocation, 1, true, modelToWorldMatrixArray);

		GLuint mvLocation = glGetUniformLocation(iter.m_material.m_renderProgram, "mv_matrix");
		float mvMatrixArray[16];
		mv.GetMatrixArray(mvMatrixArray);
		glUniformMatrix4fv(mvLocation, 1, true, mvMatrixArray);

		GLuint viewLocation = glGetUniformLocation(iter.m_material.m_renderProgram, "view_matrix");
		float viewMatrixArray[16];
		view.GetMatrixArray(viewMatrixArray);
		glUniformMatrix4fv(viewLocation, 1, true, viewMatrixArray);


		GLuint projLocation = glGetUniformLocation(iter.m_material.m_renderProgram, "proj_matrix");
		float projMatrixArray[16];
		project.GetMatrixArray(projMatrixArray);
		glUniformMatrix4fv(projLocation, 1, true, projMatrixArray);

		iter.RenderObj();
	}
}
