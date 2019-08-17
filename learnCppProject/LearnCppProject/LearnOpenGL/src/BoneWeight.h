#pragma once

struct BoneWeight
{
public:
	int m_index0 = -1;
	int m_index1 = -1;
	int m_index2 = -1;
	int m_index3 = -1;
	float m_weight0 = 0;
	float m_weight1 = 0;
	float m_weight2 = 0;
	float m_weight3 = 0;

	void AddWeight(int boneIndex, float weight)
	{
		if (m_index0 == -1)
		{
			m_index0 = boneIndex;
			m_weight0 = weight;
			return;
		}
		if (m_index1 == -1)
		{
			m_index1 = boneIndex;
			m_weight1 = weight;
			return;
		}
		if (m_index2 == -1)
		{
			m_index2 = boneIndex;
			m_weight2 = weight;
			return;
		}
		if (m_index3 == -1)
		{
			m_index3 = boneIndex;
			m_weight3 = weight;
			return;
		}
	}
};