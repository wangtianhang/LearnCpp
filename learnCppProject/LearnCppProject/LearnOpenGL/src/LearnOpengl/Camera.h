#pragma once

#include "../Learn3D/Transform.h"
#include "../Learn3D/Matrix4x4.h"
#include "../GL/GLUtil.h"
#include "GLFW/glfw3.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Transform m_transform;
	float m_MovementSpeed = 5;
	float m_MouseSensitivity = 0.1;
	//float m_lastX = 0;
	//float m_lastY = 0;
	
	float m_rotateSpeed = 45;
	GLFWwindow* m_window = NULL;
	void Init(GLFWwindow* window);

	Matrix4x4 GetViewMatrix()
	{
		return GLUtil::worldToCameraMatrix(m_transform.GetLocalToWorldMatrix());
	}

//	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//	{
// 		xoffset *= m_MouseSensitivity;
// 		yoffset *= m_MouseSensitivity;
// 
// 		Vector3 euler = m_transform.GetLocalEulerAngles();
// 		euler.y += xoffset;
// 		euler.x += yoffset;
// 		
// 		// Make sure that when pitch is out of bounds, screen doesn't get flipped
// 		if (constrainPitch)
// 		{
// 			if (euler.x > 89.0f)
// 				euler.x = 89.0f;
// 			if (euler.x < -89.0f)
// 				euler.x = -89.0f;
// 		}
// 		m_transform.SetLocalEulerAngles(euler);

		// Update Front, Right and Up Vectors using the updated Euler angles
		//updateCameraVectors();
//	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = m_MovementSpeed * deltaTime;
		if (direction == FORWARD)
			m_transform.SetPosition(m_transform.GetPosition() + m_transform.GetForward() * velocity);
		if (direction == BACKWARD)
			m_transform.SetPosition(m_transform.GetPosition() - m_transform.GetForward() * velocity);
		if (direction == LEFT)
			m_transform.SetPosition(m_transform.GetPosition() - m_transform.GetRight() * velocity);
		if (direction == RIGHT)
			m_transform.SetPosition(m_transform.GetPosition() + m_transform.GetRight() * velocity);
	}

	void Update(float deltaTime)
	{
		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
			ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
			ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
			ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
			ProcessKeyboard(RIGHT, deltaTime);

		
		if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			Vector3 euler = m_transform.GetEulerAngles();
			euler.y -= m_rotateSpeed * deltaTime;
			m_transform.SetEulerAngles(euler);
		}
		if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			Vector3 euler = m_transform.GetEulerAngles();
			euler.y += m_rotateSpeed * deltaTime;
			m_transform.SetEulerAngles(euler);
		}
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			Vector3 euler = m_transform.GetEulerAngles();
			euler.x -= m_rotateSpeed * deltaTime;
			m_transform.SetEulerAngles(euler);
		}
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			Vector3 euler = m_transform.GetEulerAngles();
			euler.x += m_rotateSpeed * deltaTime;
			m_transform.SetEulerAngles(euler);
		}
	}
};