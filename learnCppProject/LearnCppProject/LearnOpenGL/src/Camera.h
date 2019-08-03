#pragma once

#include "./Learn3D/Transform.h"
#include "./Learn3D/Matrix4x4.h"
#include "./GLHelper.h"
#include "GLFW/glfw3.h"
#include "./GUtil.h"

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

	bool m_pressDownMouseBtn = false;

	bool m_firstMouse = true;
	float m_lastX = 0;
	float m_lastY = 0;

	Matrix4x4 GetViewMatrix()
	{
		return GLHelper::worldToCameraMatrix(m_transform.GetLocalToWorldMatrix());
	}

	void onMouseMove(int xpos, int ypos)
	{
		if (!m_pressDownMouseBtn)
		{
			return;
		}

		if (m_firstMouse)
		{
			m_lastX = xpos;
			m_lastY = ypos;
			m_firstMouse = false;
		}

		float xoffset = xpos - m_lastX;
		float yoffset = m_lastY - ypos; // reversed since y-coordinates go from bottom to top

		m_lastX = xpos;
		m_lastY = ypos;

		ProcessMouseMovement(xoffset, yoffset);
	}

	void OnMouseDown()
	{
		m_pressDownMouseBtn = true;
	}

	void OnMouseUp()
	{
		m_pressDownMouseBtn = false;
		m_firstMouse = true;
	}

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		Vector3 euler = NormalizeAngles(m_transform.GetLocalEulerAngles());
		euler.y += xoffset;
		euler.x -= yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (euler.x > 89.0f)
				euler.x = 89.0f;
			if (euler.x < -89.0f)
				euler.x = -89.0f;
		}
		m_transform.SetLocalEulerAngles(euler);

		// Update Front, Right and Up Vectors using the updated Euler angles
		//updateCameraVectors();
	}

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

	Vector3 NormalizeAngles(Vector3 angles)
	{
		angles.x = NormalizeAngle(angles.x);
		angles.y = NormalizeAngle(angles.y);
		angles.z = NormalizeAngle(angles.z);
		return angles;
	}

	float NormalizeAngle(float angle)
	{
		while (angle > 180)
			angle -= 360;
		while (angle < -180)
			angle += 360;
		return angle;
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

		
		Vector3 euler = m_transform.GetEulerAngles();
		Vector3 normalEuler = NormalizeAngles(euler);
		if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			normalEuler.y -= m_rotateSpeed * deltaTime;

			GUtil::Log("normalEuler " + normalEuler.toString());
			m_transform.SetEulerAngles(normalEuler);
		}
		if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			//Vector3 euler = m_transform.GetEulerAngles();
			normalEuler.y += m_rotateSpeed * deltaTime;

			//m_transform.SetEulerAngles(euler);
			GUtil::Log("normalEuler " + normalEuler.toString());
			m_transform.SetEulerAngles(normalEuler);
		}
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			//Vector3 euler = m_transform.GetEulerAngles();
			normalEuler.x -= m_rotateSpeed * deltaTime;
			//m_transform.SetEulerAngles(euler);
			if (normalEuler.x < -89)
			{
				normalEuler.x = -89;
			}
			GUtil::Log("normalEuler1 " + normalEuler.toString());
			m_transform.SetEulerAngles(normalEuler);
			GUtil::Log("normalEuler2 " + NormalizeAngles(m_transform.GetEulerAngles()).toString());
		}
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			//Vector3 euler = m_transform.GetEulerAngles();
			normalEuler.x += m_rotateSpeed * deltaTime;
			//m_transform.SetEulerAngles(euler);
			if (normalEuler.x > 89)
			{
				normalEuler.x = 89;
			}
			GUtil::Log("normalEuler " + normalEuler.toString());
			m_transform.SetEulerAngles(normalEuler);
		}

	}

	void onMouseWheel(int pos)
	{
		//GUtil::Log("onMouseWheel " + std::to_string(pos));
		if (pos == 1) 
		{
			// 向前滚 拉远
			ProcessKeyboard(BACKWARD, 0.1f);
		}
		else if (pos == -1)
		{
			// 向后滚 拉近
			ProcessKeyboard(FORWARD, 0.1f);
		}
	}
};