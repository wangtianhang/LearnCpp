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
            UnityEngine.Matrix4x4.Test();

            Vector3 euler = new Vector3(-88, 0.000000f, 0.000000f);
            Quaternion qua = Quaternion.Euler(euler);
            Vector3 euler3 = qua.eulerAngles;
            Debug.Log(NormalizeAngles(euler3));

            Console.ReadLine();
        }
    }
}
