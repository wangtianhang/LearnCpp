#pragma once

#include <png.h>
#include "../GL/gl3w.h"
#include <stdio.h>

struct PNGHelper
{
public:
	static const GLubyte * ReadPngFile(const char * filename)
	{
		unsigned char header[8];     //8
		int k;   //����ѭ��
		GLuint textureID; //��ͼ����
		int width, height; //��¼ͼƬ����͸�
		png_byte color_type; //ͼƬ�����ͣ����ܻ������Ƿ��ǿ�����ͨ����
		png_byte bit_depth; //�ֽ����

		png_structp png_ptr; //ͼƬ
		png_infop info_ptr; //ͼƬ����Ϣ
		int number_of_passes; //����ɨ��
		png_bytep * row_pointers;//ͼƬ����������
		int row, col, pos;  //���ڸı�png�������е����⡣
		GLubyte *rgba;

		FILE *fp = fopen(filename, "rb");//��ֻ����ʽ���ļ���Ϊfile_name���ļ�
		if (!fp)//������Ӧ���ܵĴ�����
		{
			fclose(fp);//�رմ򿪵��ļ�������Ĭ����ͼ
			return 0;//�˴�Ӧ�õ���һ������Ĭ����ͼ����ID�ĺ���
		}
		//��ȡ�ļ�ͷ�ж��Ƿ���pngͼƬ.������������Ӧ����
		fread(header, 1, 8, fp);
		if (png_sig_cmp(header, 0, 8))
		{
			fclose(fp);
			return 0; //ÿ����������һ���ģ���������֮��������Ҫ����Сʱ������
		}

		//����libpng��libpng-manual.txt��˵��ʹ���ĵ� �����������ʼ��png_structp �� png_infop
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); //�������ǰ󶨴����Լ�����ĺ�����������Ϊ��
		if (!png_ptr)//������Ӧ����ʼ��ʧ�ܵĴ���
		{
			fclose(fp);
			return 0;
		}
		//���ݳ�ʼ����png_ptr��ʼ��png_infop
		info_ptr = png_create_info_struct(png_ptr);

		if (!info_ptr)
		{
			//��ʼ��ʧ���Ժ�����png_structp
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			fclose(fp);
			return 0;
		}


		//����ʵʵ����libpng������˵���ȶ�������  ������
		if (setjmp(png_jmpbuf(png_ptr)))

		{
			//�ͷ�ռ�õ��ڴ棡Ȼ��ر��ļ�����һ����ͼID�˴�Ӧ�õ���һ������Ĭ����ͼ����ID�ĺ���

			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);

			fclose(fp);

			return 0;

		}
		//����Ҫȷ����ͨ��2���ƴ򿪵��ļ���ͨ��i/o���ƺ���png_init_io
		png_init_io(png_ptr, fp);
		//�ƺ���˵Ҫ����libpng�ļ��ӵڼ�����ʼmissing
		png_set_sig_bytes(png_ptr, 8);
		//�����ֻ��򵥵Ĳ��������ڿ���ʵ�ʶ�ȡͼƬ��Ϣ�ˣ�
		png_read_info(png_ptr, info_ptr);
		//���ͼƬ����Ϣ width height ��ɫ����  �ֽ����
		width = png_get_image_width(png_ptr, info_ptr);
		height = png_get_image_height(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);
		//���ͼƬ����alphaͨ������Ҫ
	   // if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)

			   // png_set_swap_alpha(png_ptr);
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		//����ɨ��ͼƬ  �������Ҫ���ò��ܽ���
		number_of_passes = png_set_interlace_handling(png_ptr);
		//����ȡ������Ϣ���µ�info_ptr
		png_read_update_info(png_ptr, info_ptr);

		//���ļ�
		if (setjmp(png_jmpbuf(png_ptr))) {
			fclose(fp);
			return 0;
		}
		rgba = (GLubyte*)malloc(width * height * 4);
		//ʹ�ö�̬����  ���ó���
		row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

		for (k = 0; k < height; k++)
			row_pointers[k] = NULL;

		//ͨ��ɨ���������ÿһ�н��õ������ݸ�ֵ����̬����       
		for (k = 0; k < height; k++)
			//row_pointers[k] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
			row_pointers[k] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr,
				info_ptr));
		//����png������������ ��-��-�Ӷ����� ����ͼ��Ҫ�����ض��Ǵ���-��-�׵�����������������Ҫ���������ݽ���һ����������
		//��ͼƬ
		png_read_image(png_ptr, row_pointers);

		pos = (width * height * 4) - (4 * width);
		for (row = 0; row < height; row++)
		{
			for (col = 0; col < (4 * width); col += 4)
			{
				rgba[pos++] = row_pointers[row][col];        // red
				rgba[pos++] = row_pointers[row][col + 1];    // green
				rgba[pos++] = row_pointers[row][col + 2];    // blue
				rgba[pos++] = row_pointers[row][col + 3];    // alpha
			}
			pos = (pos - (width * 4) * 2);
		}

		return rgba;
	}
};