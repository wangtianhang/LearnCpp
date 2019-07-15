using System;
using System.Collections.Generic;

using System.Text;

namespace UnityEngine
{
    /// <summary>
    /// 坐标系与unity保持一致 为左手坐标系
    /// </summary>
public struct Matrix4x4
    {
        public static void Test()
        {
            Vector3 pos = new Vector3(100, 200, 300);
            Quaternion rotate = Quaternion.identity;
            rotate.eulerAngles = new Vector3(40, 50, 60);
            //Console.WriteLine("测试Quaternion " + rotate);

            Vector3 scale = new Vector3(7, 8, 9);
            Matrix4x4 trs = TRS(pos, rotate, scale);
            Console.WriteLine("测试trs\n" + trs.ToString());

            Matrix4x4 transpose = Transpose(trs);
            Console.WriteLine("测试转置矩阵\n" + transpose.ToString());

            Matrix4x4 inverse = Inverse(trs);
            Console.WriteLine("测试逆矩阵\n" + inverse.ToString());

            Matrix4x4 posMatrix = Matrix4x4.identity;
            posMatrix.m03 = pos.x;
            posMatrix.m13 = pos.y;
            posMatrix.m23 = pos.z;
            Vector4 point = new Vector4(0, 0, 0, 1);
            Vector4 newPoint = posMatrix * point;

            float fov = 60;
            float aspect = (float)16 / 9;
            float zNear = 1;
            float zFar = 1000;
            Matrix4x4 perspectiveMat = Matrix4x4.Perspective(fov, aspect, zNear, zFar);
            Console.WriteLine("测试透视矩阵\n" + perspectiveMat.ToString());

            //Console.ReadLine();
        }

        public float m00;

        public float m10;

        public float m20;

        public float m30;

        public float m01;

        public float m11;

        public float m21;

        public float m31;

        public float m02;

        public float m12;

        public float m22;

        public float m32;

        public float m03;

        public float m13;

        public float m23;

        public float m33;


        public override string ToString()
        {
            string ret = m00.ToString("f6") + ",\t" + m01.ToString("f6") + ",\t" + m02.ToString("f6") + ",\t" + m03.ToString("f6") + "\n";
            ret += m10.ToString("f6") + ",\t" + m11.ToString("f6") + ",\t" + m12.ToString("f6") + ",\t" + m13.ToString("f6") + "\n";
            ret += m20.ToString("f6") + ",\t" + m21.ToString("f6") + ",\t" + m22.ToString("f6") + ",\t" + m23.ToString("f6") + "\n";
            ret += m30.ToString("f6") + ",\t" + m31.ToString("f6") + ",\t" + m32.ToString("f6") + ",\t" + m33.ToString("f6") + "\n";
            return ret;
        }

        public static bool operator ==(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            return lhs.GetColumn(0) == rhs.GetColumn(0) && lhs.GetColumn(1) == rhs.GetColumn(1) && lhs.GetColumn(2) == rhs.GetColumn(2) && lhs.GetColumn(3) == rhs.GetColumn(3);
        }

        public static bool operator !=(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            return !(lhs == rhs);
        }

        public static Matrix4x4 operator *(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            return new Matrix4x4
            {
                m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30,
                m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31,
                m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32,
                m03 = lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33,
                m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30,
                m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31,
                m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32,
                m13 = lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33,
                m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30,
                m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31,
                m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32,
                m23 = lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33,
                m30 = lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30,
                m31 = lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31,
                m32 = lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32,
                m33 = lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33
            };
        }

        public static Vector4 operator *(Matrix4x4 lhs, Vector4 v)
        {
            Vector4 result = new Vector4();
            result.x = lhs.m00 * v.x + lhs.m01 * v.y + lhs.m02 * v.z + lhs.m03 * v.w;
            result.y = lhs.m10 * v.x + lhs.m11 * v.y + lhs.m12 * v.z + lhs.m13 * v.w;
            result.z = lhs.m20 * v.x + lhs.m21 * v.y + lhs.m22 * v.z + lhs.m23 * v.w;
            result.w = lhs.m30 * v.x + lhs.m31 * v.y + lhs.m32 * v.z + lhs.m33 * v.w;
            return result;
        }

        public static Matrix4x4 identity
        {
            get
            {
                return new Matrix4x4
                {
                    m00 = 1f,
                    m01 = 0f,
                    m02 = 0f,
                    m03 = 0f,
                    m10 = 0f,
                    m11 = 1f,
                    m12 = 0f,
                    m13 = 0f,
                    m20 = 0f,
                    m21 = 0f,
                    m22 = 1f,
                    m23 = 0f,
                    m30 = 0f,
                    m31 = 0f,
                    m32 = 0f,
                    m33 = 1f
                };
            }
        }

        public static Matrix4x4 zero
        {
            get
            {
                return new Matrix4x4
                {
                    m00 = 0f,
                    m01 = 0f,
                    m02 = 0f,
                    m03 = 0f,
                    m10 = 0f,
                    m11 = 0f,
                    m12 = 0f,
                    m13 = 0f,
                    m20 = 0f,
                    m21 = 0f,
                    m22 = 0f,
                    m23 = 0f,
                    m30 = 0f,
                    m31 = 0f,
                    m32 = 0f,
                    m33 = 0f
                };
            }
        }

        /// <summary>
        /// 逆矩阵
        /// </summary>
        public Matrix4x4 inverse
        {
            get
            {
                return Inverse(this);
            }
        }

        /// <summary>
        /// 转置矩阵
        /// </summary>
        /// <param name="i"></param>
        /// <returns></returns>
        public Matrix4x4 transpose
        {
            get
            {
                return Transpose(this);
            }
        }


        public float this[int row, int column]
        {
            get
            {
                return this[row + column * 4];
            }
            set
            {
                this[row + column * 4] = value;
            }
        }

        public float this[int index]
        {
            get
            {
                switch (index)
                {
                    case 0:
                        return this.m00;
                    case 1:
                        return this.m10;
                    case 2:
                        return this.m20;
                    case 3:
                        return this.m30;
                    case 4:
                        return this.m01;
                    case 5:
                        return this.m11;
                    case 6:
                        return this.m21;
                    case 7:
                        return this.m31;
                    case 8:
                        return this.m02;
                    case 9:
                        return this.m12;
                    case 10:
                        return this.m22;
                    case 11:
                        return this.m32;
                    case 12:
                        return this.m03;
                    case 13:
                        return this.m13;
                    case 14:
                        return this.m23;
                    case 15:
                        return this.m33;
                    default:
                        throw new IndexOutOfRangeException("Invalid matrix index!");
                }
            }
            set
            {
                switch (index)
                {
                    case 0:
                        this.m00 = value;
                        break;
                    case 1:
                        this.m10 = value;
                        break;
                    case 2:
                        this.m20 = value;
                        break;
                    case 3:
                        this.m30 = value;
                        break;
                    case 4:
                        this.m01 = value;
                        break;
                    case 5:
                        this.m11 = value;
                        break;
                    case 6:
                        this.m21 = value;
                        break;
                    case 7:
                        this.m31 = value;
                        break;
                    case 8:
                        this.m02 = value;
                        break;
                    case 9:
                        this.m12 = value;
                        break;
                    case 10:
                        this.m22 = value;
                        break;
                    case 11:
                        this.m32 = value;
                        break;
                    case 12:
                        this.m03 = value;
                        break;
                    case 13:
                        this.m13 = value;
                        break;
                    case 14:
                        this.m23 = value;
                        break;
                    case 15:
                        this.m33 = value;
                        break;
                    default:
                        throw new IndexOutOfRangeException("Invalid matrix index!");
                }
            }
        }

        public Vector4 GetColumn(int i)
        {
            return new Vector4(this[0, i], this[1, i], this[2, i], this[3, i]);
        }

        public Vector4 GetRow(int i)
        {
            return new Vector4(this[i, 0], this[i, 1], this[i, 2], this[i, 3]);
        }

        public void SetColumn(int i, Vector4 v)
        {
            this[0, i] = v.x;
            this[1, i] = v.y;
            this[2, i] = v.z;
            this[3, i] = v.w;
        }

        public void SetRow(int i, Vector4 v)
        {
            this[i, 0] = v.x;
            this[i, 1] = v.y;
            this[i, 2] = v.z;
            this[i, 3] = v.w;
        }

        public static Matrix4x4 Inverse(Matrix4x4 m)
        {
            float[][] mat = new float[4][];
            for (int i = 0; i < 4; ++i)
                mat[i] = new float[4];

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

            float[][] inverseMat = _MatrixInverse(mat);

            Matrix4x4 ret = new Matrix4x4();
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

        public Vector3 MultiplyPoint(Vector3 v)
        {
            Vector3 result;
            result.x = this.m00 * v.x + this.m01 * v.y + this.m02 * v.z + this.m03;
            result.y = this.m10 * v.x + this.m11 * v.y + this.m12 * v.z + this.m13;
            result.z = this.m20 * v.x + this.m21 * v.y + this.m22 * v.z + this.m23;
            float num = this.m30 * v.x + this.m31 * v.y + this.m32 * v.z + this.m33;
            num = 1f / num;
            result.x *= num;
            result.y *= num;
            result.z *= num;
            return result;
        }

        public Vector3 MultiplyVector(Vector3 v)
        {
            Vector3 result;
            result.x = this.m00 * v.x + this.m01 * v.y + this.m02 * v.z;
            result.y = this.m10 * v.x + this.m11 * v.y + this.m12 * v.z;
            result.z = this.m20 * v.x + this.m21 * v.y + this.m22 * v.z;
            return result;
        }
        public static Matrix4x4 Perspective(float fov, float aspect , float zNear, float zFar)
        {
            // 为什么这里用的是opengl的透视矩阵？

            Matrix4x4 ret = Matrix4x4.zero;

            //ret.m00 = 1 / (float)Math.Tan(fov * 0.5f) / aspect;
            //ret.m11 = 1 / (float)Math.Tan(fov * 0.5f);
            //ret.m22 = zFar / (zFar - zNear);
            //ret.m23 = 1;
            //ret.m32 = zFar * zNear / (zNear - zFar);
            float fovRad = Mathf.Deg2Rad * fov;
            // 
            //         float width = (float)Math.Tan(fovRad / 2) * zNear * 2;
            //         float height = width / aspect;
            //         float fovYRad = (float)Math.Atan(height / 2 / zNear) * 2;
            // 
            //         float fovY = Math3d.Rad2Deg * fovYRad;

            ret.m00 = 1 / (float)Mathf.Tan(fovRad * 0.5f) / aspect;
            ret.m11 = 1 / (float)Mathf.Tan(fovRad * 0.5f);

            ret.m22 = -(zFar + zNear) / (zFar - zNear);
            ret.m23 = -2 * zNear * zFar / (zFar - zNear);
            ret.m32 = -1;

            return ret;
        }

        public static Matrix4x4 Scale(Vector3 v)
        {
            return new Matrix4x4
            {
                m00 = v.x,
                m01 = 0f,
                m02 = 0f,
                m03 = 0f,
                m10 = 0f,
                m11 = v.y,
                m12 = 0f,
                m13 = 0f,
                m20 = 0f,
                m21 = 0f,
                m22 = v.z,
                m23 = 0f,
                m30 = 0f,
                m31 = 0f,
                m32 = 0f,
                m33 = 1f
            };
        }

        public static Matrix4x4 Transpose(Matrix4x4 m)
        {
            Matrix4x4 ret = new Matrix4x4();
            ret.m00 = m.m00; ret.m01 = m.m10; ret.m02 = m.m20; ret.m03 = m.m30;
            ret.m10 = m.m01; ret.m11 = m.m11; ret.m12 = m.m21; ret.m13 = m.m31;
            ret.m20 = m.m02; ret.m21 = m.m12; ret.m22 = m.m22; ret.m23 = m.m32;
            ret.m30 = m.m03; ret.m31 = m.m13; ret.m32 = m.m23; ret.m33 = m.m33;
            return ret;
        }

        /// <summary>
        /// 可以用来计算ojbtoworld矩阵
        /// </summary>
        /// <param name="pos"></param>
        /// <param name="q"></param>
        /// <param name="s"></param>
        /// <returns></returns>
        public static Matrix4x4 TRS(Vector3 pos, Quaternion q, Vector3 s)
        {
            Matrix4x4 posMatrix = Matrix4x4.identity;
            posMatrix.m03 = pos.x;
            posMatrix.m13 = pos.y;
            posMatrix.m23 = pos.z;

            Matrix4x4 rotateMatrix = Matrix4x4.identity;
            rotateMatrix.m00 = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
            rotateMatrix.m10 = 2 * q.x * q.y + 2 * q.w * q.z;
            rotateMatrix.m20 = 2 * q.x * q.z - 2 * q.w * q.y;

            rotateMatrix.m01 = 2 * q.x * q.y - 2 * q.w * q.z;
            rotateMatrix.m11 = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
            rotateMatrix.m21 = 2 * q.y * q.z + 2 * q.w * q.x;

            rotateMatrix.m02 = 2 * q.x * q.z + 2 * q.w * q.y;
            rotateMatrix.m12 = 2 * q.y * q.z - 2 * q.w * q.x;
            rotateMatrix.m22 = 1 - 2 * q.x * q.x - 2 * q.y * q.y;

            Matrix4x4 scaleMatrix = Scale(s);

            Matrix4x4 ret = posMatrix * rotateMatrix * scaleMatrix;
            return ret;
        }

        #region 求逆 https://github.com/Phylliida/UnityMatrix/blob/master/Matrix.cs
        static float[][] _MatrixCreate(int rows, int cols)
        {
            float[][] result = new float[rows][];
            for (int i = 0; i < rows; ++i)
                result[i] = new float[cols];
            return result;
        }

        static float[][] _MatrixInverse(float[][] matrix)
        {
            // assumes determinant is not 0
            // that is, the matrix does have an inverse
            int n = matrix.Length;
            float[][] result = _MatrixCreate(n, n); // make a copy of matrix
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    result[i][j] = matrix[i][j];

            float[][] lum; // combined lower & upper
            int[] perm;
            int toggle;
            toggle = _MatrixDecompose(matrix, out lum, out perm);

            float[] b = new float[n];
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                    if (i == perm[j])
                        b[j] = 1.0f;
                    else
                        b[j] = 0.0f;

                float[] x = _Helper(lum, b); // 
                for (int j = 0; j < n; ++j)
                    result[j][i] = x[j];
            }
            return result;
        }

        static int _MatrixDecompose(float[][] m, out float[][] lum, out int[] perm)
        {
            // Crout's LU decomposition for matrix determinant and inverse
            // stores combined lower & upper in lum[][]
            // stores row permuations into perm[]
            // returns +1 or -1 according to even or odd number of row permutations
            // lower gets dummy 1.0s on diagonal (0.0s above)
            // upper gets lum values on diagonal (0.0s below)

            int toggle = +1; // even (+1) or odd (-1) row permutatuions
            int n = m.Length;

            // make a copy of m[][] into result lu[][]
            lum = _MatrixCreate(n, n);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    lum[i][j] = m[i][j];


            // make perm[]
            perm = new int[n];
            for (int i = 0; i < n; ++i)
                perm[i] = i;

            for (int j = 0; j < n - 1; ++j) // process by column. note n-1 
            {
                float max = Mathf.Abs(lum[j][j]);
                int piv = j;

                for (int i = j + 1; i < n; ++i) // find pivot index
                {
                    float xij = Mathf.Abs(lum[i][j]);
                    if (xij > max)
                    {
                        max = xij;
                        piv = i;
                    }
                } // i

                if (piv != j)
                {
                    float[] tmp = lum[piv]; // swap rows j, piv
                    lum[piv] = lum[j];
                    lum[j] = tmp;

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

        static float[] _Helper(float[][] luMatrix, float[] b) // helper
        {
            int n = luMatrix.Length;
            float[] x = new float[n];
            b.CopyTo(x, 0);

            for (int i = 1; i < n; ++i)
            {
                float sum = x[i];
                for (int j = 0; j < i; ++j)
                    sum -= luMatrix[i][j] * x[j];
                x[i] = sum;
            }

            x[n - 1] /= luMatrix[n - 1][n - 1];
            for (int i = n - 2; i >= 0; --i)
            {
                float sum = x[i];
                for (int j = i + 1; j < n; ++j)
                    sum -= luMatrix[i][j] * x[j];
                x[i] = sum / luMatrix[i][i];
            }

            return x;
        }
        #endregion

        public override int GetHashCode()
        {
            return this.GetColumn(0).GetHashCode() ^ this.GetColumn(1).GetHashCode() << 2 ^ this.GetColumn(2).GetHashCode() >> 2 ^ this.GetColumn(3).GetHashCode() >> 1;
        }

        public override bool Equals(object other)
        {
            if (!(other is Matrix4x4))
            {
                return false;
            }
            Matrix4x4 matrix4x = (Matrix4x4)other;
            return this.GetColumn(0).Equals(matrix4x.GetColumn(0)) && this.GetColumn(1).Equals(matrix4x.GetColumn(1)) && this.GetColumn(2).Equals(matrix4x.GetColumn(2)) && this.GetColumn(3).Equals(matrix4x.GetColumn(3));
        }
    }

}