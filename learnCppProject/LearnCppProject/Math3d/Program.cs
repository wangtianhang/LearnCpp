using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Math3d
{
    class Program
    {
        static Vector3 NormalizeAngles(Vector3 angles)
        {
            angles.x = NormalizeAngle(angles.x);
            angles.y = NormalizeAngle(angles.y);
            angles.z = NormalizeAngle(angles.z);
            return angles;
        }

        static float NormalizeAngle(float angle)
        {
            while (angle > 180)
                angle -= 360;
            while (angle < -180)
                angle += 360;
            return angle;
        }

        static void Main(string[] args)
        {
            //             UnityEngine.Matrix4x4.Test();
            // 
            //             Vector3 euler0 = new Vector3(-86, 0.000000f, 0.000000f);
            //             Quaternion qua0 = Quaternion.Euler(euler0);
            //             Vector3 euler = new Vector3(-88, 0.000000f, 0.000000f);
            //             Quaternion qua = Quaternion.Euler(euler);
            //             Vector3 euler4 = qua0.eulerAngles;
            //             Vector3 euler3 = qua.eulerAngles;
            //             Debug.Log(NormalizeAngles(euler3));

            Matrix4x4 mat = new Matrix4x4();
            mat.m00 = 10.121946f;
            mat.m01 = -0.070887f;
            mat.m02 = -16.107624f;
            mat.m03 = 16.404133f;

            mat.m10 = 16.107441f;
            mat.m11 = 0.167915f;
            mat.m12 = 10.121094f;
            mat.m13 = -1.901794f;

            mat.m20 = 0.104461f;
            mat.m21 = -19.023176f;
            mat.m22 = 0.149360f;
            mat.m23 = 0.155247f;

            mat.m30 = 0.000000f;
            mat.m31 = 0.000000f;
            mat.m32 = 0.000000f;
            mat.m33 = 1.000000f;

            Vector3 pos = MathHelper.GetPosition(mat);
            Quaternion qua = MathHelper.GetRotation(mat);
            Vector3 euler = qua.eulerAngles;
            Vector3 scale = MathHelper.GetScale(mat);

            Console.WriteLine(pos);
            Console.WriteLine(euler);
            Console.WriteLine(scale);

            Console.ReadLine();
        }
    }
}
