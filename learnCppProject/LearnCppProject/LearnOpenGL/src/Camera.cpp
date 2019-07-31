#include "./Camera.h"

#include "./ApplicationBase.h"

void Camera::Init(GLFWwindow* window)
{
	//m_lastX = (float)application::app->info.windowWidth / 2.0;
	//m_lastY = (float)application::app->info.windowHeight / 2.0;
	m_window = window;
}
