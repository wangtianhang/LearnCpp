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
    public struct Vector3RightHand
    {
        public static void Test()
        {
            Vector3RightHand src = new Vector3RightHand(1, 2, 3);
            Vector3RightHand des = new Vector3RightHand(40, 50, 60);
            Debug.Log("测试vecotr3.slerp" + Vector3RightHand.Slerp(src, des, 0.7f));

            //Console.ReadLine();
        }

        public const float kEpsilon = 1e-005f;

        public float x;
        public float y;
        public float z;

        public Vector3RightHand(float x, float y)
        {
            this.x = x;
            this.y = y;
            this.z = 0;
        }

        public Vector3RightHand(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }


        public static Vector3RightHand operator -(Vector3RightHand a)
        {
            Vector3RightHand ret = new Vector3RightHand();
            ret.x = -a.x;
            ret.y = -a.y;
            ret.z = -a.z;
            return ret;
        }

        public static Vector3RightHand operator -(Vector3RightHand a, Vector3RightHand b)
        {
            Vector3RightHand ret = new Vector3RightHand();
            ret.x = a.x - b.x;
            ret.y = a.y - b.y;
            ret.z = a.z - b.z;
            return ret;
        }

        public static bool operator !=(Vector3RightHand lhs, Vector3RightHand rhs)
        {
            return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
        }

        public static Vector3RightHand operator *(float d, Vector3RightHand a)
        {
            Vector3RightHand ret = new Vector3RightHand();
            ret.x = a.x * d;
            ret.y = a.y * d;
            ret.z = a.z * d;
            return ret;
        }

        public static Vector3RightHand operator *(Vector3RightHand a, float d)
        {
            Vector3RightHand ret = new Vector3RightHand();
            ret.x = a.x * d;
            ret.y = a.y * d;
            ret.z = a.z * d;
            return ret;
        }

        public static Vector3RightHand operator /(Vector3RightHand a, float d)
        {
            Vector3RightHand ret = new Vector3RightHand();
            ret.x = a.x / d;
            ret.y = a.y / d;
            ret.z = a.z / d;
            return ret;
        }

        public static Vector3RightHand operator +(Vector3RightHand a, Vector3RightHand b)
        {
            Vector3RightHand ret = new Vector3RightHand();
            ret.x = a.x + b.x;
            ret.y = a.y + b.y;
            ret.z = a.z + b.z;
            return ret;
        }

        public static bool operator ==(Vector3RightHand lhs, Vector3RightHand rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
        }

        public static Vector3RightHand back
        {
            get { return new Vector3RightHand(0, 0, -1); }
        }

        public static Vector3RightHand forward
        {
            get { return new Vector3RightHand(0, 0, 1); }
        }

        public static Vector3RightHand up
        {
            get { return new Vector3RightHand(0, 1, 0); }
        }

        public static Vector3RightHand down
        {
            get { return new Vector3RightHand(0, -1, 0); }
        }

        public static Vector3RightHand right
        {
            get { return new Vector3RightHand(1, 0, 0); }
        }

        public static Vector3RightHand left
        {
            get { return new Vector3RightHand(-1, 0, 0); }
        }

        public static Vector3RightHand zero
        {
            get { return new Vector3RightHand(0, 0, 0); }
        }

        public static Vector3RightHand one
        {
            get { return new Vector3RightHand(1, 1, 1); }
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

        public Vector3RightHand normalized
        {
            get
            {
                return Vector3RightHand.Normalize(this);
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

        public static float Angle(Vector3RightHand from, Vector3RightHand to)
        {
            return (float)Mathf.Acos(Mathf.Clamp(Vector3RightHand.Dot(from.normalized, to.normalized), -1f, 1f)) * 57.29578f;
        }

        public static Vector3RightHand ClampMagnitude(Vector3RightHand vector, float maxLength)
        {
            if (vector.sqrMagnitude > maxLength * maxLength)
            {
                return vector.normalized * maxLength;
            }
            return vector;
        }

        public static Vector3RightHand Cross(Vector3RightHand lhs, Vector3RightHand rhs)
        {
            //return new Vector3RightHand(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
            return new Vector3RightHand(
                  lhs.y * rhs.z - rhs.y * lhs.z,
                  lhs.z * rhs.x - rhs.z * lhs.x,
                  lhs.x * rhs.y - rhs.x * lhs.y);
        }

        public static float Distance(Vector3RightHand a, Vector3RightHand b)
        {
            Vector3RightHand vector = new Vector3RightHand(a.x - b.x, a.y - b.y, a.z - b.z);
            return (float)Mathf.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        }

        public static float Dot(Vector3RightHand lhs, Vector3RightHand rhs)
        {
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
        }

        public static Vector3RightHand Lerp(Vector3RightHand from, Vector3RightHand to, float t)
        {
            t = Mathf.Clamp01(t);
            return new Vector3RightHand(from.x + (to.x - from.x) * t, from.y + (to.y - from.y) * t, from.z + (to.z - from.z) * t);
        }

        public static float Magnitude(Vector3RightHand a)
        {
            return (float)Mathf.Sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        }

        public static Vector3RightHand Max(Vector3RightHand lhs, Vector3RightHand rhs)
        {
            return new Vector3RightHand(Mathf.Max(lhs.x, rhs.x), Mathf.Max(lhs.y, rhs.y), Mathf.Max(lhs.z, rhs.z));
        }

        public static Vector3RightHand Min(Vector3RightHand lhs, Vector3RightHand rhs)
        {
            return new Vector3RightHand(Mathf.Min(lhs.x, rhs.x), Mathf.Min(lhs.y, rhs.y), Mathf.Min(lhs.z, rhs.z));
        }

        public static Vector3RightHand MoveTowards(Vector3RightHand current, Vector3RightHand target, float maxDistanceDelta)
        {
            Vector3RightHand a = target - current;
            float magnitude = a.magnitude;
            if (magnitude <= maxDistanceDelta || magnitude == 0f)
            {
                return target;
            }
            return current + a / magnitude * maxDistanceDelta;
        }

        public void Normalize()
        {
            float num = Vector3RightHand.Magnitude(this);
            if (num > 1E-05f)
            {
                this /= num;
            }
            else
            {
                this = Vector3RightHand.zero;
            }
        }

        public static Vector3RightHand Normalize(Vector3RightHand value)
        {
            float num = Vector3RightHand.Magnitude(value);
            if (num > 1E-05f)
            {
                return value / num;
            }
            return Vector3RightHand.zero;
        }

        public static Vector3RightHand Project(Vector3RightHand vector, Vector3RightHand onNormal)
        {
            float num = Vector3RightHand.Dot(onNormal, onNormal);
            if (num < 1.401298E-45f)
            {
                return Vector3RightHand.zero;
            }
            return onNormal * Vector3RightHand.Dot(vector, onNormal) / num;
        }

        public static Vector3RightHand ProjectOnPlane(Vector3RightHand vector, Vector3RightHand planeNormal)
        {
            return vector - Vector3RightHand.Project(vector, planeNormal);
        }

        public static Vector3RightHand Reflect(Vector3RightHand inDirection, Vector3RightHand inNormal)
        {
            return -2f * Vector3RightHand.Dot(inNormal, inDirection) * inNormal + inDirection;
        }

        public void Scale(Vector3RightHand scale)
        {
            this.x *= scale.x;
            this.y *= scale.y;
            this.z *= scale.z;
        }

        public static Vector3RightHand Scale(Vector3RightHand a, Vector3RightHand b)
        {
            return new Vector3RightHand(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        public void Set(float new_x, float new_y, float new_z)
        {
            x = new_x;
            y = new_y;
            z = new_z;
        }

        public static float SqrMagnitude(Vector3RightHand a)
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
        public static Vector3RightHand Slerp(Vector3RightHand a, Vector3RightHand b, float t)
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

            Vector3RightHand v = RotateTo(a, b, Vector3RightHand.Angle(a, b) * t);

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
        static Vector3RightHand RotateTo(Vector3RightHand from, Vector3RightHand to, float angle)
        {
            //如果两向量角度为0
            if (Vector3RightHand.Angle(from, to) == 0)
            {
                return from;
            }

            //旋转轴
            Vector3RightHand n = Vector3RightHand.Cross(from, to);

            //旋转轴规范化
            n.Normalize();

            //旋转矩阵
            Matrix4x4RightHand rotateMatrix = new Matrix4x4RightHand();

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

            Vector4 v = Vector3RightHand.ToVector4(from);
            Vector3RightHand vector = new Vector3RightHand();
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; j++)
                {
                    vector[i] += v[j] * rotateMatrix[j, i];
                }
            }
            return vector;
        }

        static Vector4 ToVector4(Vector3RightHand v)
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
            if (!(other is Vector3RightHand))
            {
                return false;
            }
            Vector3RightHand vector = (Vector3RightHand)other;
            return this.x.Equals(vector.x) && this.y.Equals(vector.y) && this.z.Equals(vector.z);
        }

//         public static implicit operator Vector2(UnityEngine.Vector3 vec)
//         {
//             return new Vector2(vec.x, vec.y);
//         }
    }

}