using System;
using System.Collections.Generic;

using System.Text;
//using UnityEngine;

namespace UnityEngine
{
    /// <summary>
    /// 坐标系与unity保持一致 为左手坐标系
    /// </summary>
    [System.Serializable]
    public struct Vector3
    {
        public static void Test()
        {
            Vector3 src = new Vector3(1, 2, 3);
            Vector3 des = new Vector3(40, 50, 60);
            Debug.Log("测试vecotr3.slerp" + Vector3.Slerp(src, des, 0.7f));

            //Console.ReadLine();
        }

        public const float kEpsilon = 1e-005f;

        public float x;
        public float y;
        public float z;

        public Vector3(float x, float y)
        {
            this.x = x;
            this.y = y;
            this.z = 0;
        }

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }


        public static Vector3 operator -(Vector3 a)
        {
            Vector3 ret = new Vector3();
            ret.x = -a.x;
            ret.y = -a.y;
            ret.z = -a.z;
            return ret;
        }

        public static Vector3 operator -(Vector3 a, Vector3 b)
        {
            Vector3 ret = new Vector3();
            ret.x = a.x - b.x;
            ret.y = a.y - b.y;
            ret.z = a.z - b.z;
            return ret;
        }

        public static bool operator !=(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
        }

        public static Vector3 operator *(float d, Vector3 a)
        {
            Vector3 ret = new Vector3();
            ret.x = a.x * d;
            ret.y = a.y * d;
            ret.z = a.z * d;
            return ret;
        }

        public static Vector3 operator *(Vector3 a, float d)
        {
            Vector3 ret = new Vector3();
            ret.x = a.x * d;
            ret.y = a.y * d;
            ret.z = a.z * d;
            return ret;
        }

        public static Vector3 operator /(Vector3 a, float d)
        {
            Vector3 ret = new Vector3();
            ret.x = a.x / d;
            ret.y = a.y / d;
            ret.z = a.z / d;
            return ret;
        }

        public static Vector3 operator +(Vector3 a, Vector3 b)
        {
            Vector3 ret = new Vector3();
            ret.x = a.x + b.x;
            ret.y = a.y + b.y;
            ret.z = a.z + b.z;
            return ret;
        }

        public static bool operator ==(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
        }

        public static Vector3 back
        {
            get { return new Vector3(0, 0, -1); }
        }

        public static Vector3 forward
        {
            get { return new Vector3(0, 0, 1); }
        }

        public static Vector3 up
        {
            get { return new Vector3(0, 1, 0); }
        }

        public static Vector3 down
        {
            get { return new Vector3(0, -1, 0); }
        }

        public static Vector3 right
        {
            get { return new Vector3(1, 0, 0); }
        }

        public static Vector3 left
        {
            get { return new Vector3(-1, 0, 0); }
        }

        public static Vector3 zero
        {
            get { return new Vector3(0, 0, 0); }
        }

        public static Vector3 one
        {
            get { return new Vector3(1, 1, 1); }
        }

        public float magnitude
        {
            get
            {
                return (float)Mathf.Sqrt(sqrMagnitude);
            }
        }

        public float sqrMagnitude
        {
            get
            {
                return this.x * this.x + this.y * this.y + this.z * this.z;
            }
        }

        public Vector3 normalized
        {
            get
            {
                return Vector3.Normalize(this);
            }
        }

        public float this[int index]
        {
            get
            {
                switch (index)
                {
                    case 0:
                        return this.x;
                    case 1:
                        return this.y;
                    case 2:
                        return this.z;
                    default:
                        throw new IndexOutOfRangeException("Invalid Vector3 index!");
                }
            }
            set
            {
                switch (index)
                {
                    case 0:
                        this.x = value;
                        break;
                    case 1:
                        this.y = value;
                        break;
                    case 2:
                        this.z = value;
                        break;
                    default:
                        throw new IndexOutOfRangeException("Invalid Vector3 index!");
                }
            }
        }

        public static float Angle(Vector3 from, Vector3 to)
        {
            return (float)Mathf.Acos(Mathf.Clamp(Vector3.Dot(from.normalized, to.normalized), -1f, 1f)) * 57.29578f;
        }

        public static Vector3 ClampMagnitude(Vector3 vector, float maxLength)
        {
            if (vector.sqrMagnitude > maxLength * maxLength)
            {
                return vector.normalized * maxLength;
            }
            return vector;
        }

        public static Vector3 Cross(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
        }

        public static float Distance(Vector3 a, Vector3 b)
        {
            Vector3 vector = new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
            return (float)Mathf.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        }

        public static float Dot(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
        }

        public static Vector3 Lerp(Vector3 from, Vector3 to, float t)
        {
            t = Mathf.Clamp01(t);
            return new Vector3(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t);
        }

        public static float Magnitude(Vector3 a)
        {
            return (float)Mathf.Sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        }

        public static Vector3 Max(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(Mathf.Max(lhs.x, rhs.x), Mathf.Max(lhs.y, rhs.y), Mathf.Max(lhs.z, rhs.z));
        }

        public static Vector3 Min(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(Mathf.Min(lhs.x, rhs.x), Mathf.Min(lhs.y, rhs.y), Mathf.Min(lhs.z, rhs.z));
        }

        public static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
        {
            Vector3 a = target - current;
            float magnitude = a.magnitude;
            if (magnitude <= maxDistanceDelta || magnitude == 0f)
            {
                return target;
            }
            return current + a / magnitude * maxDistanceDelta;
        }

        public void Normalize()
        {
            float num = Vector3.Magnitude(this);
            if (num > 1E-05f)
            {
                this /= num;
            }
            else
            {
                this = Vector3.zero;
            }
        }

        public static Vector3 Normalize(Vector3 value)
        {
            float num = Vector3.Magnitude(value);
            if (num > 1E-05f)
            {
                return value / num;
            }
            return Vector3.zero;
        }

        public static Vector3 Project(Vector3 vector, Vector3 onNormal)
        {
            float num = Vector3.Dot(onNormal, onNormal);
            if (num < 1.401298E-45f)
            {
                return Vector3.zero;
            }
            return onNormal * Vector3.Dot(vector, onNormal) / num;
        }

        public static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
        {
            return vector - Vector3.Project(vector, planeNormal);
        }

        public static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal)
        {
            return -2f * Vector3.Dot(inNormal, inDirection) * inNormal + inDirection;
        }

        public void Scale(Vector3 scale)
        {
            this.x *= scale.x;
            this.y *= scale.y;
            this.z *= scale.z;
        }

        public static Vector3 Scale(Vector3 a, Vector3 b)
        {
            return new Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        public void Set(float new_x, float new_y, float new_z)
        {
            x = new_x;
            y = new_y;
            z = new_z;
        }

        public static float SqrMagnitude(Vector3 a)
        {
            return a.x * a.x + a.y * a.y + a.z * a.z;
        }

        /// <summary>
        /// 两个向量的球形插值
        /// </summary>
        /// <param name="a">向量a</param>
        /// <param name="b">向量b</param>
        /// <param name="t">t的值在[0..1]</param>
        /// <returns></returns>
        public static Vector3 Slerp(Vector3 a, Vector3 b, float t)
        {
            //         Quaternion fromQua = Quaternion.LookRotation(from, Vector3.up);
            //         Quaternion toQua = Quaternion.LookRotation(to, Vector3.up);
            //         Quaternion endQua = Quaternion.Slerp(fromQua, toQua, t);
            // 
            //         Vector3 endDir = endQua * Vector3.forward;
            //         endDir.Normalize();
            // 
            //         float length = Mathf3d.Lerp(from.magnitude, to.magnitude, t);
            //         return endDir.normalized * length;
            if (t <= 0)
            {
                return a;
            }
            else if (t >= 1)
            {
                return b;
            }

            Vector3 v = RotateTo(a, b, Vector3.Angle(a, b) * t);

            //向量的长度，跟线性插值一样计算
            float length = b.magnitude * t + a.magnitude * (1 - t);
            return v.normalized * length;
        }

        /// <summary>
        /// 将向量from向向量to旋转角度angle
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        /// <param name="angle"></param>
        /// <returns></returns>
        static Vector3 RotateTo(Vector3 from, Vector3 to, float angle)
        {
            //如果两向量角度为0
            if (Vector3.Angle(from, to) == 0)
            {
                return from;
            }

            //旋转轴
            Vector3 n = Vector3.Cross(from, to);

            //旋转轴规范化
            n.Normalize();

            //旋转矩阵
            Matrix4x4 rotateMatrix = new Matrix4x4();

            //旋转的弧度
            double radian = angle * Mathf.PI / 180;
            float cosAngle = (float)Mathf.Cos((float)radian);
            float sinAngle = (float)Mathf.Sin((float)radian);

            //矩阵的数据
            //这里看不懂的自行科普矩阵知识
            rotateMatrix.SetRow(0, new Vector4(n.x * n.x * (1 - cosAngle) + cosAngle, n.x * n.y * (1 - cosAngle) + n.z * sinAngle, n.x * n.z * (1 - cosAngle) - n.y * sinAngle, 0));
            rotateMatrix.SetRow(1, new Vector4(n.x * n.y * (1 - cosAngle) - n.z * sinAngle, n.y * n.y * (1 - cosAngle) + cosAngle, n.y * n.z * (1 - cosAngle) + n.x * sinAngle, 0));
            rotateMatrix.SetRow(2, new Vector4(n.x * n.z * (1 - cosAngle) + n.y * sinAngle, n.y * n.z * (1 - cosAngle) - n.x * sinAngle, n.z * n.z * (1 - cosAngle) + cosAngle, 0));
            rotateMatrix.SetRow(3, new Vector4(0, 0, 0, 1));

            Vector4 v = Vector3.ToVector4(from);
            Vector3 vector = new Vector3();
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; j++)
                {
                    vector[i] += v[j] * rotateMatrix[j, i];
                }
            }
            return vector;
        }

        static Vector4 ToVector4(Vector3 v)
        {
            return new Vector4(v.x, v.y, v.z, 0);
        }

        public override string ToString()
        {
            return "(" + x.ToString("f6") + "," + y.ToString("f6") + "," + z.ToString("f6") + ")";
        }

        public override int GetHashCode()
        {
            return this.x.GetHashCode() ^ this.y.GetHashCode() << 2 ^ this.z.GetHashCode() >> 2;
        }

        public override bool Equals(object other)
        {
            if (!(other is Vector3))
            {
                return false;
            }
            Vector3 vector = (Vector3)other;
            return this.x.Equals(vector.x) && this.y.Equals(vector.y) && this.z.Equals(vector.z);
        }

//         public static implicit operator Vector2(UnityEngine.Vector3 vec)
//         {
//             return new Vector2(vec.x, vec.y);
//         }
    }

}