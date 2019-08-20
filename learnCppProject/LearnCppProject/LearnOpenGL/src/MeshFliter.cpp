#include "./DebugMemory.h"

#include "./MeshFliter.h"
#include "./ApplicationBase.h"

void MeshFliter::UnInit()
{
	application::s_app->m_resourceMgr.ReleaseMeshFilter(this);
}