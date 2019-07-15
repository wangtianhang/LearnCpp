#pragma once

#include "./Vector4.h"

struct Matrix4x4
{
public:

	Matrix4x4()
	{
		m00 = 0;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 0;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 0;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 0;
	}

	static void Test()
	{
		// todo Ò»¶¨Òª²âÊÔÄæ¾ØÕó¡£¡£Ì«tm¸´ÔÓÁË
	}

	float m00;

	float m10;

	float m20;

	float m30;

	float m01;

	float m11;

	float m21;

	float m31;

	float m02;

	float m12;

	float m22;

	float m32;

	float m03;

	float m13;

	float m23;

	float m33;

	bool operator == (const Matrix4x4 & rhs) const
	{
		const Matrix4x4 & lhs = *this;
		return lhs.GetColumn(0) == rhs.GetColumn(0) && lhs.GetColumn(1) == rhs.GetColumn(1) && lhs.GetColumn(2) == rhs.GetColumn(2) && lhs.GetColumn(3) == rhs.GetColumn(3);
	}

	bool operator != (const Matrix4x4 & rhs) const
	{
		return !(*this == rhs);
	}

	Matrix4x4 operator*(const Matrix4x4 & rhs) const
	{
		const Matrix4x4 & lhs = *this;
		Matrix4x4 ret = Matrix4x4();
		
		ret.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30;
		ret.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31;
		ret.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32;
		ret.m03 = lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33;
		ret.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30;
		ret.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31;
		ret.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32;
		ret.m13 = lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33;
		ret.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30;
		ret.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31;
		ret.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32;
		ret.m23 = lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33;
		ret.m30 = lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30;
		ret.m31 = lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31;
		ret.m32 = lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32;
		ret.m33 = lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33;

		return ret;
	}

	Vector4 operator*(const Vector4 & v) const
	{
		const Matrix4x4 & lhs = *this;
		Vector4 result = Vector4();
		result.x = lhs.m00 * v.x + lhs.m01 * v.y + lhs.m02 * v.z + lhs.m03 * v.w;
		result.y = lhs.m10 * v.x + lhs.m11 * v.y + lhs.m12 * v.z + lhs.m13 * v.w;
		result.z = lhs.m20 * v.x + lhs.m21 * v.y + lhs.m22 * v.z + lhs.m23 * v.w;
		result.w = lhs.m30 * v.x + lhs.m31 * v.y + lhs.m32 * v.z + lhs.m33 * v.w;
		return result;
	}

	static Matrix4x4 identity()
	{
		Matrix4x4 ret = Matrix4x4();

		ret.m00 = 1;
		ret.m01 = 0;
		ret.m02 = 0;
		ret.m03 = 0;
		ret.m10 = 0;
		ret.m11 = 1;
		ret.m12 = 0;
		ret.m13 = 0;
		ret.m20 = 0;
		ret.m21 = 0;
		ret.m22 = 1;
		ret.m23 = 0;
		ret.m30 = 0;
		ret.m31 = 0;
		ret.m32 = 0;
		ret.m33 = 1;

		return ret;
	}

	static Matrix4x4 zero()
	{
		return Matrix4x4();
	}

	Matrix4x4 inverse()
	{
		return Inverse(*this);
	}

	static Matrix4x4 Inverse(Matrix4x4 m)
	{
		float mat[4][4];

		mat[0][0] = m.m00;
		mat[0][1] = m.m01;
		mat[0][2] = m.m02;
		mat[0][3] = m.m03;

		mat[1][0] = m.m10;
		mat[1][1] = m.m11;
		mat[1][2] = m.m12;
		mat[1][3] = m.m13;

		mat[2][0] = m.m20;
		mat[2][1] = m.m21;
		mat[2][2] = m.m22;
		mat[2][3] = m.m23;

		mat[3][0] = m.m30;
		mat[3][1] = m.m31;
		mat[3][2] = m.m32;
		mat[3][3] = m.m33;

		float inverseMat[4][4];
		_MatrixInverse(mat, inverseMat);

		Matrix4x4 ret = Matrix4x4();
		ret.m00 = inverseMat[0][0];
		ret.m01 = inverseMat[0][1];
		ret.m02 = inverseMat[0][2];
		ret.m03 = inverseMat[0][3];

		ret.m10 = inverseMat[1][0];
		ret.m11 = inverseMat[1][1];
		ret.m12 = inverseMat[1][2];
		ret.m13 = inverseMat[1][3];

		ret.m20 = inverseMat[2][0];
		ret.m21 = inverseMat[2][1];
		ret.m22 = inverseMat[2][2];
		ret.m23 = inverseMat[2][3];

		ret.m30 = inverseMat[3][0];
		ret.m31 = inverseMat[3][1];
		ret.m32 = inverseMat[3][2];
		ret.m33 = inverseMat[3][3];

		return ret;
	}

	//ÇóÄæ https ://github.com/Phylliida/UnityMatrix/blob/master/Matrix.cs
// 	static float[][] _MatrixCreate(int rows, int cols)
// 	{
// 		float[][] result = new float[rows][];
// 		for (int i = 0; i < rows; ++i)
// 			result[i] = new float[cols];
// 		return result;
// 	}

	static void _MatrixInverse(float matrix [4][4], float result[4][4])
	{
		// assumes determinant is not 0
		// that is, the matrix does have an inverse
		int n = 4;
		//float** result = _MatrixCreate(n, n); // make a copy of matrix
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				result[i][j] = matrix[i][j];

		float lum[4][4] ; // combined lower & upper
		int perm[4] ;
		int toggle;
		toggle = _MatrixDecompose(matrix, lum, perm);

		float b[4];
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
				if (i == perm[j])
					b[j] = 1.0f;
				else
					b[j] = 0.0f;

			float x[4];
			_Helper(lum, b, x); // 
			for (int j = 0; j < n; ++j)
				result[j][i] = x[j];
		}
		//return result;
	}

	static int _MatrixDecompose(float m[4][4], float lum[4][4] , int perm[4] )
	{
		// Crout's LU decomposition for matrix determinant and inverse
		// stores combined lower & upper in lum[][]
		// stores row permuations into perm[]
		// returns +1 or -1 according to even or odd number of row permutations
		// lower gets dummy 1.0s on diagonal (0.0s above)
		// upper gets lum values on diagonal (0.0s below)

		int toggle = +1; // even (+1) or odd (-1) row permutatuions
		int n = 4;

		// make a copy of m[][] into result lu[][]
		//lum = _MatrixCreate(n, n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				lum[i][j] = m[i][j];


		// make perm[]
		perm = new int[n];
		for (int i = 0; i < n; ++i)
			perm[i] = i;

		for (int j = 0; j < n - 1; ++j) // process by column. note n-1 
		{
			float max = Mathf::Abs(lum[j][j]);
			int piv = j;

			for (int i = j + 1; i < n; ++i) // find pivot index
			{
				float xij = Mathf::Abs(lum[i][j]);
				if (xij > max)
				{
					max = xij;
					piv = i;
				}
			} // i

			if (piv != j)
			{
				//float[] tmp = lum[piv]; // swap rows j, piv
				//lum[piv] = lum[j];
				//lum[j] = tmp;
				ChangeRow(lum, j, piv);

				int t = perm[piv]; // swap perm elements
				perm[piv] = perm[j];
				perm[j] = t;

				toggle = -toggle;
			}

			float xjj = lum[j][j];
			if (xjj != 0.0)
			{
				for (int i = j + 1; i < n; ++i)
				{
					float xij = lum[i][j] / xjj;
					lum[i][j] = xij;
					for (int k = j + 1; k < n; ++k)
						lum[i][k] -= xij * lum[j][k];
				}
			}

		} // j

		return toggle;
	}
	
	static void ChangeRow(float mat[4][4], int row1, int row2)
	{
		float row10 = mat[row1][0];
		float row11 = mat[row1][1];
		float row12 = mat[row1][2];
		float row13 = mat[row1][3];

		mat[row1][0] = mat[row2][0];
		mat[row1][1] = mat[row2][1];
		mat[row1][2] = mat[row2][2];
		mat[row1][3] = mat[row2][3];

		mat[row2][0] = row10;
		mat[row2][1] = row11;
		mat[row2][2] = row12;
		mat[row2][3] = row13;
	}

	static void _Helper(float luMatrix[4][4] , float b[4], float result[4]) // helper
	{
		int n = 4;
		//float[] x = new float[n];
		//b.CopyTo(x, 0);
		//float x[4];
		for (int i = 0; i < 4; ++i)
		{
			result[i] = b[i];
		}

		for (int i = 1; i < n; ++i)
		{
			float sum = result[i];
			for (int j = 0; j < i; ++j)
				sum -= luMatrix[i][j] * result[j];
			result[i] = sum;
		}

		result[n - 1] /= luMatrix[n - 1][n - 1];
		for (int i = n - 2; i >= 0; --i)
		{
			float sum = result[i];
			for (int j = i + 1; j < n; ++j)
				sum -= luMatrix[i][j] * result[j];
			result[i] = sum / luMatrix[i][i];
		}

		//return x;
	}
	// ==================½áÊøÇóÄæ====================================

	Vector4 GetColumn(int i) const
	{
		return Vector4(Get(0, i), Get(1, i), Get(2, i), Get(3, i));
	}

	float Get(int row, int column) const
	{
		return (*this)._GetValue(row + column * 4);
	}

	void Set(int row, int column, float value)
	{
		(*this)[row + column * 4] = value;
	}

	float _GetValue(int i) const
	{
		switch (i)
		{
		case 0:
			return m00;
		case 1:
			return m10;
		case 2:
			return m20;
		case 3:
			return m30;
		case 4:
			return m01;
		case 5:
			return m11;
		case 6:
			return m21;
		case 7:
			return m31;
		case 8:
			return m02;
		case 9:
			return m12;
		case 10:
			return m22;
		case 11:
			return m32;
		case 12:
			return m03;
		case 13:
			return m13;
		case 14:
			return m23;
		case 15:
			return m33;
		default:
			throw std::exception("Matrix4x4 no index");
			break;
		}
	}

	float& operator[](int i)
	{
		switch (i)
		{
		case 0:
			return m00;
		case 1:
			return m10;
		case 2:
			return m20;
		case 3:
			return m30;
		case 4:
			return m01;
		case 5:
			return m11;
		case 6:
			return m21;
		case 7:
			return m31;
		case 8:
			return m02;
		case 9:
			return m12;
		case 10:
			return m22;
		case 11:
			return m32;
		case 12:
			return m03;
		case 13:
			return m13;
		case 14:
			return m23;
		case 15:
			return m33;
		default:
			throw std::exception("Matrix4x4 no index");
			break;
		}
	}
};