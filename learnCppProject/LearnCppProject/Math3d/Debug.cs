using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace UnityEngine
{
    public class Debug
    {
        static bool s_hasInit = false;
        public static void Init()
        {
            if (!s_hasInit)
            {
                s_hasInit = true;
                //Console.SetWindowSize(1280, 720);
            }
        }

        public static void Log(string str)
        {
            Init();

            Console.WriteLine(str);
        }

        public static void Log(Object obj)
        {
            Init();

            string str = obj.ToString();

            Console.WriteLine(str);
        }

        public static void LogWarning(string str)
        {
            Init();

            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine(str);
            Console.ForegroundColor = ConsoleColor.White;
        }

        public static void LogError(string str)
        {
            Init();

            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(str);
            Console.ForegroundColor = ConsoleColor.White;
        }

        public static void LogException(System.Exception ex)
        {
            Init();

            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.WriteLine(ex.Message + "\n" + GetStackFrame());
            Console.ForegroundColor = ConsoleColor.White;
        }

        public static string GetStackFrame()
        {
            string info = "";
            StackTrace st = new StackTrace(true);
            //得到当前的所以堆栈  
            StackFrame[] sf = st.GetFrames();
            for (int i = 0; i < sf.Length; ++i)
            {
                info += sf[i].ToString();
            }
            return info;
        }

        public static string GetTime()
        {
            string month = DateTime.Now.Month < 10 ? "0" + DateTime.Now.Month.ToString() : DateTime.Now.Month.ToString();
            string day = DateTime.Now.Day < 10 ? "0" + DateTime.Now.Day.ToString() : DateTime.Now.Day.ToString();
            string hour = DateTime.Now.Hour < 10 ? "0" + DateTime.Now.Hour.ToString() : DateTime.Now.Hour.ToString();
            string minute = DateTime.Now.Minute < 10 ? "0" + DateTime.Now.Minute.ToString() : DateTime.Now.Minute.ToString();
            string second = DateTime.Now.Second < 10 ? "0" + DateTime.Now.Second.ToString() : DateTime.Now.Second.ToString();
            //DateTime curTime = DateTime.Now;
            string time = DateTime.Now.Year + "_" +
                month + "_" +
                day + "_" +
                hour + "_" +
                minute + "_" +
                second;

            return time;
        }
    }
}



