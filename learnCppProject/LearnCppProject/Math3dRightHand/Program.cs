using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

// namespace Math3d
// {
    class Program
    {
        static Vector3RightHand NormalizeAngles(Vector3RightHand angles)
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
        //UnityEngine.Matrix4x4RightHand.Test();

        //Vector3RightHand euler0 = new Vector3RightHand(-86, 0.000000f, 0.000000f);
        //QuaternionRightHand qua0 = QuaternionRightHand.Euler(euler0);
        //Vector3RightHand euler = new Vector3RightHand(-88, 0.000000f, 0.000000f);
        //QuaternionRightHand qua = QuaternionRightHand.Euler(euler);
        //Vector3RightHand euler4 = qua0.eulerAngles;
        //Vector3RightHand euler3 = qua.eulerAngles;
        //Debug.Log(NormalizeAngles(euler3));

        //Matrix4x4RightHand trs = Matrix4x4RightHand.TRS();

        Matrix4x4RightHand mat = new Matrix4x4RightHand();
        mat.m00 = 10.121946f;
        mat.m01 = -0.070887f;
        mat.m02 = 16.107624f;
        mat.m03 = 16.404133f;

        mat.m10 = 16.107441f;
        mat.m11 = 0.167915f;
        mat.m12 = -10.121094f;
        mat.m13 = -1.901794f;

        mat.m20 = -0.104461f;
        mat.m21 = 19.023176f;
        mat.m22 = 0.149360f;
        mat.m23 = -0.155247f;

        mat.m30 = 0.000000f;
        mat.m31 = 0.000000f;
        mat.m32 = 0.000000f;
        mat.m33 = 1.000000f;

        Vector3RightHand pos = MathHelper.GetPosition(mat);
        Vector3RightHand euler = MathHelper.GetRotation(mat).eulerAngles;
        Vector3RightHand scale = MathHelper.GetScale(mat);

        Console.WriteLine(pos);
        Console.WriteLine(euler);
        Console.WriteLine(scale);

        Console.WriteLine("right hand math end");

            Console.ReadLine();
        }
    }
/*}*/
