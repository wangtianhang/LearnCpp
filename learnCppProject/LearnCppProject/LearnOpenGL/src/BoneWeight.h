#pragma once

struct BoneWeight
{
public:
	int m_index0 = 0;
	int m_index1 = 0;
	int m_index2 = 0;
	int m_index3 = 0;
	float m_weight0 = 0;
	float m_weight1 = 0;
	float m_weight2 = 0;
	float m_weight3 = 0;

	void AddWeight(int boneIndex, float weight)
	{
		if (boneIndex >= 34)
		{
			int test = 0;
		}
		if (m_weight0 == 0)
		{
			m_index0 = boneIndex;
			m_weight0 = weight;
			return;
		}
		if (m_weight1 == 0)
		{
			m_index1 = boneIndex;
			m_weight1 = weight;
			return;
		}
		if (m_weight2 == 0)
		{
			m_index2 = boneIndex;
			m_weight2 = weight;
			return;
		}
		if (m_weight3 == 0)
		{
			m_index3 = boneIndex;
			m_weight3 = weight;
			return;
		}
	}
};