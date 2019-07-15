﻿using System;
using System.Collections.Generic;
using System.Text;
//using UnityEngine;

namespace UnityEngine
{

    public struct Mathf
    {
        public static void Test()
        {
            Debug.Log(IsPowerOfTwo(8).ToString());
            Debug.Log(IsPowerOfTwo(3).ToString());
            Debug.Log(ClosestPowerOfTwo(8).ToString());
            Debug.Log(ClosestPowerOfTwo(3).ToString());
            Debug.Log(ClosestPowerOfTwo(10).ToString());
        }
        public const float Deg2Rad = 0.0174533f;
        public const float Epsilon = 1.4013e-045f;
        public const float Infinity = 1.0f / 0.0f;
        public const float NegativeInfinity = -1.0f / 0.0f;
        public const float PI = 3.14159f;
        public const float Rad2Deg = 57.2958f;


        public static float Abs(float f)
        {
            return Math.Abs(f);
        }
        public static int Abs(int value)
        {
            return Math.Abs(value);
        }

        public static float Acos(float f)
        {
            return (float)Math.Acos((double)f);
        }

        public static bool Approximately(float a, float b)
        {
            return Mathf.Abs(b - a) < Mathf.Max(1E-06f * Mathf.Max(Mathf.Abs(a), Mathf.Abs(b)), 1.121039E-44f);
        }
        public static float Asin(float f)
        {
            return (float)Math.Asin((double)f);
        }

        public static float Atan(float f)
        {
            return (float)Math.Atan((double)f);
        }

        public static float Atan2(float y, float x)
        {
            return (float)Math.Atan2((double)y, (double)x);
        }

        public static float Ceil(float f)
        {
            return (float)Math.Ceiling((double)f);
        }

        public static int CeilToInt(float f)
        {
            return (int)Math.Ceiling((double)f);
        }

        public static float Clamp(float value, float min, float max)
        {
            if (value < min)
            {
                value = min;
            }
            else if (value > max)
            {
                value = max;
            }
            return value;
        }

        public static double Clamp(double value, double min, double max)
        {
            if (value < min)
            {
                value = min;
            }
            else if (value > max)
            {
                value = max;
            }
            return value;
        }

        public static int Clamp(int value, int min, int max)
        {
            if (value < min)
            {
                value = min;
            }
            else if (value > max)
            {
                value = max;
            }
            return value;
        }

        public static float Clamp01(float value)
        {
            if (value < 0f)
            {
                return 0f;
            }
            if (value > 1f)
            {
                return 1f;
            }
            return value;
        }

        public static double Clamp01(double value)
        {
            if (value < 0d)
            {
                return 0d;
            }
            if (value > 1d)
            {
                return 1d;
            }
            return value;
        }

        public static float Cos(float f)
        {
            return (float)Math.Cos((double)f);
        }

        public static float DeltaAngle(float current, float target)
        {
            float num = Mathf.Repeat(target - current, 360f);
            if (num > 180f)
            {
                num -= 360f;
            }
            return num;
        }

        public static float Exp(float power)
        {
            return (float)Math.Exp((double)power);
        }

        public static float Floor(float f)
        {
            return (float)Math.Floor((double)f);
        }

        public static int FloorToInt(float f)
        {
            return (int)Math.Floor((double)f);
        }

        public static float Gamma(float value, float absmax, float gamma)
        {
            bool flag = false;
            if (value < 0f)
            {
                flag = true;
            }
            float num = Mathf.Abs(value);
            if (num > absmax)
            {
                return (!flag) ? num : (-num);
            }
            float num2 = Mathf.Pow(num / absmax, gamma) * absmax;
            return (!flag) ? num2 : (-num2);
        }

        public static float InverseLerp(float from, float to, float value)
        {
            if (from < to)
            {
                if (value < from)
                {
                    return 0f;
                }
                if (value > to)
                {
                    return 1f;
                }
                value -= from;
                value /= to - from;
                return value;
            }
            else
            {
                if (from <= to)
                {
                    return 0f;
                }
                if (value < to)
                {
                    return 1f;
                }
                if (value > from)
                {
                    return 0f;
                }
                return 1f - (value - to) / (from - to);
            }
        }


        public static float Lerp(float from, float to, float t)
        {
            return from + (to - from) * Mathf.Clamp01(t);
        }

        public static float LerpAngle(float a, float b, float t)
        {
            float num = Mathf.Repeat(b - a, 360f);
            if (num > 180f)
            {
                num -= 360f;
            }
            return a + num * Mathf.Clamp01(t);
        }

        public static float Log(float f)
        {
            return (float)Math.Log((double)f);
        }

        public static float Log(float f, float p)
        {
            return (float)Math.Log((double)f, (double)p);
        }

        public static float Log10(float f)
        {
            return (float)Math.Log10((double)f);
        }

        public static float Max(float a, float b)
        {
            return (a <= b) ? b : a;
        }

        public static float Max(params float[] values)
        {
            int num = values.Length;
            if (num == 0)
            {
                return 0f;
            }
            float num2 = values[0];
            for (int i = 1; i < num; i++)
            {
                if (values[i] > num2)
                {
                    num2 = values[i];
                }
            }
            return num2;
        }

        public static int Max(int a, int b)
        {
            return (a <= b) ? b : a;
        }

        public static int Max(params int[] values)
        {
            int num = values.Length;
            if (num == 0)
            {
                return 0;
            }
            int num2 = values[0];
            for (int i = 1; i < num; i++)
            {
                if (values[i] > num2)
                {
                    num2 = values[i];
                }
            }
            return num2;
        }

        public static float Min(float a, float b)
        {
            return (a >= b) ? b : a;
        }

        public static float Min(params float[] values)
        {
            int num = values.Length;
            if (num == 0)
            {
                return 0f;
            }
            float num2 = values[0];
            for (int i = 1; i < num; i++)
            {
                if (values[i] < num2)
                {
                    num2 = values[i];
                }
            }
            return num2;
        }

        public static int Min(int a, int b)
        {
            return (a >= b) ? b : a;
        }

        public static int Min(params int[] values)
        {
            int num = values.Length;
            if (num == 0)
            {
                return 0;
            }
            int num2 = values[0];
            for (int i = 1; i < num; i++)
            {
                if (values[i] < num2)
                {
                    num2 = values[i];
                }
            }
            return num2;
        }

        public static float MoveTowards(float current, float target, float maxDelta)
        {
            if (Mathf.Abs(target - current) <= maxDelta)
            {
                return target;
            }
            return current + Mathf.Sign(target - current) * maxDelta;
        }

        public static float MoveTowardsAngle(float current, float target, float maxDelta)
        {
            target = current + Mathf.DeltaAngle(current, target);
            return Mathf.MoveTowards(current, target, maxDelta);
        }

        public static float PingPong(float t, float length)
        {
            t = Mathf.Repeat(t, length * 2f);
            return length - Mathf.Abs(t - length);
        }

        public static float Pow(float f, float p)
        {
            return (float)Math.Pow((double)f, (double)p);
        }

        public static float Repeat(float t, float length)
        {
            return t - Mathf.Floor(t / length) * length;
        }

        public static float Round(float f)
        {
            return (float)Math.Round((double)f);
        }

        public static int RoundToInt(float f)
        {
            return (int)Math.Round((double)f);
        }

        public static float Sign(float f)
        {
            return (f < 0f) ? -1f : 1f;
        }

        public static float Sin(float f)
        {
            return (float)Math.Sin((double)f);
        }

        public static float SmoothDamp(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
        {
            smoothTime = Mathf.Max(0.0001f, smoothTime);
            float num = 2f / smoothTime;
            float num2 = num * deltaTime;
            float num3 = 1f / (1f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
            float num4 = current - target;
            float num5 = target;
            float num6 = maxSpeed * smoothTime;
            num4 = Mathf.Clamp(num4, -num6, num6);
            target = current - num4;
            float num7 = (currentVelocity + num * num4) * deltaTime;
            currentVelocity = (currentVelocity - num * num7) * num3;
            float num8 = target + (num4 + num7) * num3;
            if (num5 - current > 0f == num8 > num5)
            {
                num8 = num5;
                currentVelocity = (num8 - num5) / deltaTime;
            }
            return num8;
        }

        public static float SmoothDampAngle(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
        {
            target = current + Mathf.DeltaAngle(current, target);
            return Mathf.SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
        }

        public static float SmoothStep(float from, float to, float t)
        {
            t = Mathf.Clamp01(t);
            t = -2f * t * t * t + 3f * t * t;
            return to * t + from * (1f - t);
        }

        public static float Sqrt(float f)
        {
            return (float)Math.Sqrt((double)f);
        }

        public static float Tan(float f)
        {
            return (float)Math.Tan((double)f);
        }

        public static int ClosestPowerOfTwo(int n)
        {
            int v = n;
            v--;
            v |= v >> 1;
            v |= v >> 2;
            v |= v >> 4;
            v |= v >> 8;
            v |= v >> 16;
            v++;

            int x = v >> 1;
            return (v - n) > (n - x) ? x : v;
        }

        public static bool IsPowerOfTwo(int n)
        {
            if (n <= 0)
            {
                return false;
            }
            else
            {
                return (n & (n - 1)) == 0;
            }
        }
    }

}