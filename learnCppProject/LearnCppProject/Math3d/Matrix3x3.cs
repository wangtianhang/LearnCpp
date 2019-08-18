using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public struct Matrix3x3
{
    public float m00;

    public float m10;

    public float m20;

    public float m01;

    public float m11;

    public float m21;

    public float m02;

    public float m12;

    public float m22;

    public float Get(int row, int column)
    {
        return this[row, column];
    }

    public float this[int row, int column]
    {
        get
        {
            return this[row + column * 3];
        }
        set
        {
            this[row + column * 3] = value;
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
                    return this.m01;
                case 4:
                    return this.m11;
                case 5:
                    return this.m21;
                case 6:
                    return this.m02;
                case 7:
                    return this.m12;
                case 8:
                    return this.m22;
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
                    this.m01 = value;
                    break;
                case 4:
                    this.m11 = value;
                    break;
                case 5:
                    this.m21 = value;
                    break;
                case 6:
                    this.m02 = value;
                    break;
                case 7:
                    this.m12 = value;
                    break;
                case 8:
                    this.m22 = value;
                    break;
                default:
                    throw new IndexOutOfRangeException("Invalid matrix index!");
            }
        }
    }
}

