#pragma once

#include <png.h>
#include "../GL/gl3w.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

struct PNGHelper
{
public:
	// Ĭ�ϲ�Ӧ��rotatey
	static GLubyte * ReadPngFile(const char * filename, bool rotateY, int & width, int & height, bool & isAlpha)
	{
		unsigned char header[8];     //8
		int k;   //����ѭ��
		GLuint textureID; //��ͼ����
		//int width, height; //��¼ͼƬ����͸�
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
		isAlpha = (color_type == PNG_COLOR_TYPE_RGBA);
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

		int size = isAlpha ? 4 : 3;

		rgba = (GLubyte*)malloc(width * height * size);
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

		pos = (width * height * size) - (size * width);
		if (rotateY)
		{
			for (row = height - 1; row >= 0; row--)
			{
				for (col = 0; col < (size * width); col += size)
				{
					rgba[pos++] = row_pointers[row][col];        // red
					rgba[pos++] = row_pointers[row][col + 1];    // green
					rgba[pos++] = row_pointers[row][col + 2];    // blue
					if (isAlpha)
					{
						rgba[pos++] = row_pointers[row][col + 3];    // alpha
					}
				}
				pos = (pos - (width * size) * 2);
			}
		}
		else
		{
			for (row = 0; row < height; row++)
			{
				for (col = 0; col < (size * width); col += size)
				{
					rgba[pos++] = row_pointers[row][col];        // red
					rgba[pos++] = row_pointers[row][col + 1];    // green
					rgba[pos++] = row_pointers[row][col + 2];    // blue
					if (isAlpha)
					{
						rgba[pos++] = row_pointers[row][col + 3];    // alpha
					}
				}
				pos = (pos - (width * size) * 2);
			}
		}

		//length = width * height * 4;
		fclose(fp);
		free(row_pointers);
		return rgba;
	}

	static GLuint LoadPngAsGLTexture(const char * filename, bool rotateY = false)
	{
		GLuint texture;
		int width = 0;
		int height = 0;
		bool isAlpha = false;
		GLubyte * data = PNGHelper::ReadPngFile(filename, rotateY, width, height, isAlpha);
		if (data == NULL)
		{
			return 0;
		}
		std::string str = std::string("��������ɹ�") + std::string(filename);
		GUtil::Log(str);
		int size = isAlpha ? 4 : 3;
		int length = width * height * size;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, isAlpha ? GL_RGBA : GL_RGB, width, height, 0, isAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		free(data);
		return texture;
	}

	static GLuint LoadCubemap(std::vector<std::string> faces)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height;
		bool isAlpha = false;
		unsigned char* image;

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		for (GLuint i = 0; i < faces.size(); i++)
		{
			std::string iter = faces[i];
			// ��֪������Ϊʲô���뷭ת��ͼƬy����
			image = ReadPngFile(iter.c_str(), true, width, height, isAlpha);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			free(image);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return textureID;
 	}
	
// 	static bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
// 		png_structp png_ptr;
// 		png_infop info_ptr;
// 		unsigned int sig_read = 0;
// 		int color_type, interlace_type;
// 		FILE *fp;
// 
// 		if ((fp = fopen(name, "rb")) == NULL)
// 			return false;
// 
// 		/* Create and initialize the png_struct
// 		 * with the desired error handler
// 		 * functions.  If you want to use the
// 		 * default stderr and longjump method,
// 		 * you can supply NULL for the last
// 		 * three parameters.  We also supply the
// 		 * the compiler header file version, so
// 		 * that we know if the application
// 		 * was compiled with a compatible version
// 		 * of the library.  REQUIRED
// 		 */
// 		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
// 			NULL, NULL, NULL);
// 
// 		if (png_ptr == NULL) {
// 			fclose(fp);
// 			return false;
// 		}
// 
// 		/* Allocate/initialize the memory
// 		 * for image information.  REQUIRED. */
// 		info_ptr = png_create_info_struct(png_ptr);
// 		if (info_ptr == NULL) {
// 			fclose(fp);
// 			png_destroy_read_struct(&png_ptr, NULL, NULL);
// 			return false;
// 		}
// 
// 		/* Set error handling if you are
// 		 * using the setjmp/longjmp method
// 		 * (this is the normal method of
// 		 * doing things with libpng).
// 		 * REQUIRED unless you  set up
// 		 * your own error handlers in
// 		 * the png_create_read_struct()
// 		 * earlier.
// 		 */
// 		if (setjmp(png_jmpbuf(png_ptr))) {
// 			/* Free all of the memory associated
// 			 * with the png_ptr and info_ptr */
// 			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
// 			fclose(fp);
// 			/* If we get here, we had a
// 			 * problem reading the file */
// 			return false;
// 		}
// 
// 		/* Set up the output control if
// 		 * you are using standard C streams */
// 		png_init_io(png_ptr, fp);
// 
// 		/* If we have already
// 		 * read some of the signature */
// 		png_set_sig_bytes(png_ptr, sig_read);
// 
// 		/*
// 		 * If you have enough memory to read
// 		 * in the entire image at once, and
// 		 * you need to specify only
// 		 * transforms that can be controlled
// 		 * with one of the PNG_TRANSFORM_*
// 		 * bits (this presently excludes
// 		 * dithering, filling, setting
// 		 * background, and doing gamma
// 		 * adjustment), then you can read the
// 		 * entire image (including pixels)
// 		 * into the info structure with this
// 		 * call
// 		 *
// 		 * PNG_TRANSFORM_STRIP_16 |
// 		 * PNG_TRANSFORM_PACKING  forces 8 bit
// 		 * PNG_TRANSFORM_EXPAND forces to
// 		 *  expand a palette into RGB
// 		 */
// 		png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
// 
// 		png_uint_32 width, height;
// 		int bit_depth;
// 		png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
// 			&interlace_type, NULL, NULL);
// 		outWidth = width;
// 		outHeight = height;
// 
// 		unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
// 		*outData = (unsigned char*)malloc(row_bytes * outHeight);
// 
// 		png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
// 
// 		for (int i = 0; i < outHeight; i++) {
// 			// note that png is ordered top to
// 			// bottom, but OpenGL expect it bottom to top
// 			// so the order or swapped
// 			memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);
// 		}
// 
// 		/* Clean up after the read,
// 		 * and free any memory allocated */
// 		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
// 
// 		/* Close the file */
// 		fclose(fp);
// 
// 		/* That's it */
// 		return true;
// 	}


};