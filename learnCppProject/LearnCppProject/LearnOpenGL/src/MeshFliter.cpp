#include "./MeshFliter.h"
#include "./ApplicationBase.h"

void MeshFliter::UnInit()
{
	application::app->m_resourceMgr.ReleaseMeshFilter(this);
}