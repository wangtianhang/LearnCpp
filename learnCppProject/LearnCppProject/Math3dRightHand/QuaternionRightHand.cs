using System;
using System.Collections.Generic;

using System.Text;

using System.Xml.Serialization;
//using UnityEngine;

namespace UnityEngine
{
    /// <summary>
    /// 坐标系与unity保持一致 为左手坐标系
    /// </summary>
    public struct QuaternionRightHand
    {
        public static void Test()
        {
            QuaternionRightHand rotate = QuaternionRightHand.identity;
            rotate.eulerAngles = new Vector3RightHand(40, 50, 60);
            Debug.Log("测试euler to Quaternion \n" + rotate);

            Vector3RightHand euler = rotate.eulerAngles;
            Debug.Log("测试quaternion to euler \n" + euler);

            Vector3RightHand dir = new Vector3RightHand(0.3f, 0.4f, 0.5f);
            dir.Normalize();
            QuaternionRightHand lookRotation = QuaternionRightHand.LookRotation(dir, Vector3RightHand.up);
            Debug.Log("测试look rotation \n" + lookRotation);

            QuaternionRightHand rotate2 = QuaternionRightHand.identity;
            rotate2.eulerAngles = new Vector3RightHand(70, 80, 90);

            QuaternionRightHand slerp = QuaternionRightHand.Slerp(rotate, rotate2, 0.5f);
            Debug.Log("测试slerp \n" + slerp);

            //Console.ReadLine();

            float angle = Angle(rotate, rotate2);
            Debug.Log("测试angle " + angle);

            QuaternionRightHand angleAxis = AngleAxis(10, dir);
            Debug.Log("测试angleAxis " + angleAxis);

            Vector3RightHand dir2 = new Vector3RightHand(0.6f, 0.7f, 0.8f);
            dir2.Normalize();

            QuaternionRightHand rotateTowards = QuaternionRightHand.RotateTowards(QuaternionRightHand.LookRotation(dir), QuaternionRightHand.LookRotation(dir2), float.MaxValue);
            Debug.Log("测试RotateTowards " + rotateTowards);

            Vector3RightHand dir3 = new Vector3RightHand(1, 0, 0);
            Vector3RightHand dir4 = new Vector3RightHand(0, 0, 1);
            QuaternionRightHand fromToRotation = FromToRotation(dir, dir2);
            //Quaternion fromToRotation = FromToRotation(dir4, dir3);
            Debug.Log("测试FromToRotation " + fromToRotation);

            QuaternionRightHand inverstQua = QuaternionRightHand.Inverse(fromToRotation);
            Debug.Log("测试inverst " + inverstQua);

            QuaternionRightHand lerpQua = QuaternionRightHand.Lerp(rotate, rotate2, 0.5f);
            Debug.Log("测试lerp " + lerpQua);

            float angle2 = 0;
            Vector3RightHand axis = Vector3RightHand.zero;
            lerpQua.ToAngleAxis(out angle2, out axis);
            Debug.Log("测试ToAngleAxis " + angle2 + " " + axis);

            //Console.ReadLine();
        }

        public const float kEpsilon = 1e-006f;

        public float x;
        public float y;
        public float z;
        public float w;

        public override string ToString()
        {
            return x.ToString("f6") + ",\t" + y.ToString("f6") + ",\t" + z.ToString("f6") + ",\t" + w.ToString("f6");
        }

        public QuaternionRightHand(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }



        public static bool operator ==(QuaternionRightHand lhs, QuaternionRightHand rhs)
        {
            return QuaternionRightHand.Dot(lhs, rhs) > 0.999999f;
        }

        public static bool operator !=(QuaternionRightHand lhs, QuaternionRightHand rhs)
        {
            return QuaternionRightHand.Dot(lhs, rhs) <= 0.999999f;
        }

        public static QuaternionRightHand operator *(QuaternionRightHand lhs, QuaternionRightHand rhs)
        {
            return new QuaternionRightHand(lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y, lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z, lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x, lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
        }

        public static Vector3RightHand operator *(QuaternionRightHand rotation, Vector3RightHand point)
        {
            float num = rotation.x * 2f;
            float num2 = rotation.y * 2f;
            float num3 = rotation.z * 2f;
            float num4 = rotation.x * num;
            float num5 = rotation.y * num2;
            float num6 = rotation.z * num3;
            float num7 = rotation.x * num2;
            float num8 = rotation.x * num3;
            float num9 = rotation.y * num3;
            float num10 = rotation.w * num;
            float num11 = rotation.w * num2;
            float num12 = rotation.w * num3;
            Vector3RightHand result;
            result.x = (1f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
            result.y = (num7 + num12) * point.x + (1f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
            result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1f - (num4 + num5)) * point.z;
            return result;
        }

        public static QuaternionRightHand identity
        {
            get
            {
                return new QuaternionRightHand(0, 0, 0, 1);
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
                    case 3:
                        return this.w;
                    default:
                        throw new IndexOutOfRangeException("Invalid Quaternion index!");
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
                    case 3:
                        this.w = value;
                        break;
                    default:
                        throw new IndexOutOfRangeException("Invalid Quaternion index!");
                }
            }
        }

        public static float Angle(QuaternionRightHand a, QuaternionRightHand b)
        {
            float f = QuaternionRightHand.Dot(a, b);
            return (float)Mathf.Acos(Mathf.Min(Mathf.Abs(f), 1f)) * 2f * 57.29578f;
        }

        public static QuaternionRightHand AngleAxis(float degress, Vector3RightHand axis)
        {
            if (axis.sqrMagnitude == 0.0f)
                return identity;

            QuaternionRightHand result = identity;
            var radians = degress * Mathf.Deg2Rad;
            radians *= 0.5f;
            axis.Normalize();
            axis = axis * (float)Mathf.Sin(radians);
            result.x = axis.x;
            result.y = axis.y;
            result.z = axis.z;
            result.w = (float)Mathf.Cos(radians);

            return Normalize(result);
        }

        public Vector3RightHand eulerAngles
        {
            get
            {

                return QuaternionRightHand.ToEulerRad(this) * 57.29578f;
            }
            set
            {

                this = QuaternionRightHand.FromEulerRad(value * 0.0174532924f);
            }
        }

        public static float Dot(QuaternionRightHand a, QuaternionRightHand b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }

        public static QuaternionRightHand Euler(Vector3RightHand euler)
        {
            Vector3RightHand eulerRad = euler * Mathf.Deg2Rad;
            return FromEulerRad(eulerRad);
        }

        public static QuaternionRightHand Euler(float x, float y, float z)
        {
            return Euler(new Vector3RightHand(x, y, z));
        }

        //static Quaternion FromToRotation(Vector3 fromDiection, Vector3 toDirection)
    //根据两个向量计算出旋转量，计算出来的旋转量为从fromDiection,旋转到toDirection的旋转量。
    //这句话意思很明显了。就是计算旋转量。
    //那么LookRotation(Vector3 forward)计算的是，Z轴旋转到forward的旋转量。
    //推出：Quaternion.LookRotation(new Vector3(1,0,0)) == Quaternion.FromToRotation(Vector3.forward, new Vector3(1,0,0));
    //因为前者就是计算向前向量到当前向量（1,0,0）的旋转量的，其实现过程就是后者喽。
         
        public static QuaternionRightHand FromToRotation(Vector3RightHand v1, Vector3RightHand v2)
        {
            //         fromDirection.Normalize();
            //         toDirection.Normalize();
            //         Quaternion fromQua = LookRotation(fromDirection);
            //         Quaternion toQua = LookRotation(toDirection);
            //         fromQua = Normalize(fromQua);
            //         toQua = Normalize(toQua);

            //Vector3 fromDir = fromQua * Vector3.forward;
            //Vector3 toDir = toQua * Vector3.forward;

            //Quaternion ret = RotateTowards(fromQua, toQua, float.MaxValue);
            //return ret;
            return QuaternionRightHand.AngleAxis(Vector3RightHand.Angle(v1, v2), Vector3RightHand.Cross(v1, v2));
        }

        public static QuaternionRightHand Inverse(QuaternionRightHand rotation)
        {
            float lengthSq = rotation.LengthSquared;
            if (lengthSq != 0.0)
            {
                float i = 1.0f / lengthSq;
                return new QuaternionRightHand(rotation.xyz * -i, rotation.w * i);
            }
            return rotation;
        }

        public static QuaternionRightHand Lerp(QuaternionRightHand from, QuaternionRightHand to, float t)
        {
            if (t > 1) t = 1;
            if (t < 0) t = 0;
            return Slerp(from, to, t);
        }

        // 四元数转欧拉角
        static Vector3RightHand ToEulerRad(QuaternionRightHand q)
        {
            //             float sqw = rotation.w * rotation.w;
            //             float sqx = rotation.x * rotation.x;
            //             float sqy = rotation.y * rotation.y;
            //             float sqz = rotation.z * rotation.z;
            //             float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
            //             float test = rotation.x * rotation.w - rotation.y * rotation.z;
            //             Vector3 v;
            // 
            //             if (test > 0.4995f * unit)
            //             { // singularity at north pole
            //                 v.y = 2f * (float)Mathf.Atan2(rotation.y, rotation.x);
            //                 v.x = (float)Mathf.PI / 2;
            //                 v.z = 0;
            //                 return NormalizeAngles(v * Mathf.Rad2Deg);
            //             }
            //             if (test < -0.4995f * unit)
            //             { // singularity at south pole
            //                 v.y = -2f * (float)Mathf.Atan2(rotation.y, rotation.x);
            //                 v.x = -(float)Mathf.PI / 2;
            //                 v.z = 0;
            //                 return NormalizeAngles(v * Mathf.Rad2Deg);
            //             }
            //             Quaternion q = new Quaternion(rotation.w, rotation.z, rotation.x, rotation.y);
            //             v.y = (float)Mathf.Atan2(2f * q.x * q.w + 2f * q.y * q.z, 1 - 2f * (q.z * q.z + q.w * q.w));     // Yaw
            //             v.x = (float)Mathf.Asin(2f * (q.x * q.z - q.w * q.y));                             // Pitch
            //             v.z = (float)Mathf.Atan2(2f * q.x * q.y + 2f * q.z * q.w, 1 - 2f * (q.y * q.y + q.z * q.z));      // Roll
            //             return NormalizeAngles(v * Mathf.Rad2Deg) * Mathf.Deg2Rad;
            float sqw = q.w * q.w;
            float sqx = q.x * q.x;
            float sqy = q.y * q.y;
            float sqz = q.z * q.z;

            float unit = sqx + sqy + sqz + sqw;
            float test = q.x * q.y + q.z * q.w;

            float yaw = 0.0f;
            float pitch = 0.0f;
            float roll = 0.0f;

            // North pole singularity
            if (test > 0.499f * unit)
            {
                yaw = 2.0f * Mathf.Atan2(q.x, q.w);
                pitch = Mathf.PI * 0.5f;
                roll = 0.0f;
            }

            // South pole singularity
            else if (test < -0.499f * unit)
            {
                yaw = -2.0f * Mathf.Atan2(q.x, q.w);
                pitch = -Mathf.PI * 0.5f;
                roll = 0.0f;
            }

            else
            {
                yaw = Mathf.Atan2(2.0f * q.y * q.w - 2.0f * q.x * q.z, sqx - sqy - sqz + sqw);
                pitch = Mathf.Asin(2.0f * test / unit);
                roll = Mathf.Atan2(2.0f * q.x * q.w - 2.0f * q.y * q.z, -sqx + sqy - sqz + sqw);
            }

            // Keep angles [0..360].
            if (Mathf.Sign(yaw) < 0)
                yaw = Mathf.Deg2Rad * (360)  + yaw;
            if (Mathf.Sign(pitch) < 0)
                pitch = Mathf.Deg2Rad * (360) + pitch;
            if (Mathf.Sign(roll) < 0)
                roll = Mathf.Deg2Rad * (360) + roll;

            return new Vector3RightHand(roll, yaw, pitch);
        }

        static Vector3RightHand NormalizeAngles(Vector3RightHand angles)
        {
            angles.x = NormalizeAngle(angles.x);
            angles.y = NormalizeAngle(angles.y);
            angles.z = NormalizeAngle(angles.z);
            return angles;
        }

        static float NormalizeAngle(float angle)
        {
            while (angle > 360)
                angle -= 360;
            while (angle < 0)
                angle += 360;
            return angle;
        }

        // 欧拉角转四元数
        static QuaternionRightHand FromEulerRad(Vector3RightHand euler)
        {
            var yaw = euler.z;
            var pitch = euler.x;
            var roll = euler.y;

            float yawOver2 = yaw * 0.5f;
            float sinYawOver2 = (float)Mathf.Sin((float)yawOver2);
            float cosYawOver2 = (float)Mathf.Cos((float)yawOver2);

            float pitchOver2 = pitch * 0.5f;
            float sinPitchOver2 = (float)Mathf.Sin((float)pitchOver2);
            float cosPitchOver2 = (float)Mathf.Cos((float)pitchOver2);

            float rollOver2 = roll * 0.5f;
            float sinRollOver2 = (float)Mathf.Sin((float)rollOver2);
            float cosRollOver2 = (float)Mathf.Cos((float)rollOver2);

            QuaternionRightHand result;
            result.w = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
            result.x = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
            result.y = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
            result.z = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
            return result;
        }

        public static QuaternionRightHand LookRotation(Vector3RightHand forward)
        {
            return LookRotation(forward, Vector3RightHand.up);
        }

        public static QuaternionRightHand LookRotation(Vector3RightHand forward, Vector3RightHand up)
        {
            forward = Vector3RightHand.Normalize(forward);
            Vector3RightHand right = Vector3RightHand.Normalize(Vector3RightHand.Cross(up, forward));
            up = Vector3RightHand.Cross(forward, right);
            var m00 = right.x;
            var m01 = right.y;
            var m02 = right.z;
            var m10 = up.x;
            var m11 = up.y;
            var m12 = up.z;
            var m20 = forward.x;
            var m21 = forward.y;
            var m22 = forward.z;


            float num8 = (m00 + m11) + m22;
            var quaternion = new QuaternionRightHand();
            if (num8 > 0f)
            {
                var num = (float)Mathf.Sqrt(num8 + 1f);
                quaternion.w = num * 0.5f;
                num = 0.5f / num;
                quaternion.x = (m12 - m21) * num;
                quaternion.y = (m20 - m02) * num;
                quaternion.z = (m01 - m10) * num;
                return quaternion;
            }
            if ((m00 >= m11) && (m00 >= m22))
            {
                var num7 = (float)Mathf.Sqrt(((1f + m00) - m11) - m22);
                var num4 = 0.5f / num7;
                quaternion.x = 0.5f * num7;
                quaternion.y = (m01 + m10) * num4;
                quaternion.z = (m02 + m20) * num4;
                quaternion.w = (m12 - m21) * num4;
                return quaternion;
            }
            if (m11 > m22)
            {
                var num6 = (float)Mathf.Sqrt(((1f + m11) - m00) - m22);
                var num3 = 0.5f / num6;
                quaternion.x = (m10 + m01) * num3;
                quaternion.y = 0.5f * num6;
                quaternion.z = (m21 + m12) * num3;
                quaternion.w = (m20 - m02) * num3;
                return quaternion;
            }
            var num5 = (float)Mathf.Sqrt(((1f + m22) - m00) - m11);
            var num2 = 0.5f / num5;
            quaternion.x = (m20 + m02) * num2;
            quaternion.y = (m21 + m12) * num2;
            quaternion.z = 0.5f * num5;
            quaternion.w = (m01 - m10) * num2;
            return quaternion;
        }

        public static QuaternionRightHand RotateTowards(QuaternionRightHand from, QuaternionRightHand to, float maxDegreesDelta)
        {
            float num = QuaternionRightHand.Angle(from, to);
            if (num == 0f)
            {
                return to;
            }
            float t = Mathf.Min(1f, maxDegreesDelta / num);
            return QuaternionRightHand.SlerpUnclamped(from, to, t);
        }

        public void Set(float new_x, float new_y, float new_z, float new_w)
        {
            x = new_x;
            y = new_y;
            z = new_z;
            w = new_w;
        }

        public void SetFromToRotation(Vector3RightHand fromDirection, Vector3RightHand toDirection)
        {
            this = FromToRotation(fromDirection, toDirection);
        }

        public void SetLookRotation(Vector3RightHand view)
        {
            this = LookRotation(view);
        }

        public void SetLookRotation(Vector3RightHand view, Vector3RightHand up)
        {
            this = LookRotation(view, up);
        }

        private static QuaternionRightHand SlerpUnclamped(QuaternionRightHand a, QuaternionRightHand b, float t)
        {
            // if either input is zero, return the other.
            if (a.LengthSquared == 0.0f)
            {
                if (b.LengthSquared == 0.0f)
                {
                    return identity;
                }
                return b;
            }
            else if (b.LengthSquared == 0.0f)
            {
                return a;
            }


            float cosHalfAngle = a.w * b.w + Vector3RightHand.Dot(a.xyz, b.xyz);

            if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
            {
                // angle = 0.0f, so just return one input.
                return a;
            }
            else if (cosHalfAngle < 0.0f)
            {
                b.xyz = -b.xyz;
                b.w = -b.w;
                cosHalfAngle = -cosHalfAngle;
            }

            float blendA;
            float blendB;
            if (cosHalfAngle < 0.99f)
            {
                // do proper slerp for big angles
                float halfAngle = (float)Mathf.Acos(cosHalfAngle);
                float sinHalfAngle = (float)Mathf.Sin(halfAngle);
                float oneOverSinHalfAngle = 1.0f / sinHalfAngle;
                blendA = (float)Mathf.Sin(halfAngle * (1.0f - t)) * oneOverSinHalfAngle;
                blendB = (float)Mathf.Sin(halfAngle * t) * oneOverSinHalfAngle;
            }
            else
            {
                // do lerp if angle is really small.
                blendA = 1.0f - t;
                blendB = t;
            }

            QuaternionRightHand result = new QuaternionRightHand(blendA * a.xyz + blendB * b.xyz, blendA * a.w + blendB * b.w);
            if (result.LengthSquared > 0.0f)
                return Normalize(result);
            else
                return identity;
        }

        /// <summary>
        /// Construct a new MyQuaternion from vector and w components
        /// </summary>
        /// <param name="v">The vector part</param>
        /// <param name="w">The w part</param>
        QuaternionRightHand(Vector3RightHand v, float w)
        {
            this.x = v.x;
            this.y = v.y;
            this.z = v.z;
            this.w = w;
        }

        [XmlIgnore]
        public Vector3RightHand xyz
        {
            set
            {
                x = value.x;
                y = value.y;
                z = value.z;
            }
            get
            {
                return new Vector3RightHand(x, y, z);
            }
        }

        /// <summary>
        /// Gets the square of the quaternion length (magnitude).
        /// </summary>
        [XmlIgnore]
        public float LengthSquared
        {
            get
            {
                return x * x + y * y + z * z + w * w;
            }
        }

        /// <summary>
        /// Gets the length (magnitude) of the quaternion.
        /// </summary>
        /// <seealso cref="LengthSquared"/>
        [XmlIgnore]
        public float Length
        {
            get
            {
                return (float)Mathf.Sqrt(x * x + y * y + z * z + w * w);
            }
        }

        public static QuaternionRightHand Slerp(QuaternionRightHand a, QuaternionRightHand b, float t)
        {
            if (t > 1) t = 1;
            if (t < 0) t = 0;
            return SlerpUnclamped(a, b, t);
        }

        /// <summary>
        /// Scale the given quaternion to unit length
        /// </summary>
        /// <param name="q">The quaternion to normalize</param>
        /// <returns>The normalized quaternion</returns>
        static QuaternionRightHand Normalize(QuaternionRightHand q)
        {
            float scale = 1.0f / q.Length;
            QuaternionRightHand result = new QuaternionRightHand(q.xyz * scale, q.w * scale);
            return result;
        }

        public void ToAngleAxis(out float angle, out Vector3RightHand axis)
        {
            QuaternionRightHand.ToAxisAngleRad(this, out axis, out angle);
            angle *= Mathf.Rad2Deg;
        }

        /// <summary>
        /// Scales the MyQuaternion to unit length.
        /// </summary>
        void Normalize()
        {
            float scale = 1.0f / this.Length;
            xyz *= scale;
            w *= scale;
        }

        static void ToAxisAngleRad(QuaternionRightHand q, out Vector3RightHand axis, out float angle)
        {
            if (Mathf.Abs(q.w) > 1.0f)
                q.Normalize();
            angle = 2.0f * (float)Mathf.Acos(q.w); // angle
            float den = (float)Mathf.Sqrt(1.0f - q.w * q.w);
            if (den > 0.0001f)
            {
                axis = q.xyz / den;
            }
            else
            {
                // This occurs when the angle is zero. 
                // Not a problem: just set an arbitrary normalized axis.
                axis = new Vector3RightHand(1, 0, 0);
            }
        }

        public override int GetHashCode()
        {
            return this.x.GetHashCode() ^ this.y.GetHashCode() << 2 ^ this.z.GetHashCode() >> 2 ^ this.w.GetHashCode() >> 1;
        }

        public override bool Equals(object other)
        {
            if (!(other is QuaternionRightHand))
            {
                return false;
            }
            QuaternionRightHand quaternion = (QuaternionRightHand)other;
            return this.x.Equals(quaternion.x) && this.y.Equals(quaternion.y) && this.z.Equals(quaternion.z) && this.w.Equals(quaternion.w);
        }
    }

}