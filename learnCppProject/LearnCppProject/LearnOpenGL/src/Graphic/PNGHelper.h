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
	// 默认不应该rotatey
	static GLubyte * ReadPngFile(const char * filename, bool rotateY, int & width, int & height, bool & isAlpha)
	{
		unsigned char header[8];     //8
		int k;   //用于循环
		GLuint textureID; //贴图名字
		//int width, height; //记录图片到宽和高
		png_byte color_type; //图片到类型（可能会用在是否是开启来通道）
		png_byte bit_depth; //字节深度

		png_structp png_ptr; //图片
		png_infop info_ptr; //图片的信息
		int number_of_passes; //隔行扫描
		png_bytep * row_pointers;//图片的数据内容
		int row, col, pos;  //用于改变png像素排列的问题。
		GLubyte *rgba;

		FILE *fp = fopen(filename, "rb");//以只读形式打开文件名为file_name的文件
		if (!fp)//做出相应可能的错误处理
		{
			fclose(fp);//关闭打开的文件！给出默认贴图
			return 0;//此处应该调用一个生成默认贴图返回ID的函数
		}
		//读取文件头判断是否所png图片.不是则做出相应处理
		fread(header, 1, 8, fp);
		if (png_sig_cmp(header, 0, 8))
		{
			fclose(fp);
			return 0; //每个错误处理都是一样的！这样报错之后锁定就要花点小时间来！
		}

		//根据libpng的libpng-manual.txt的说明使用文档 接下来必须初始化png_structp 和 png_infop
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); //后三个是绑定错误以及警告的函数这里设置为空
		if (!png_ptr)//做出相应到初始化失败的处理
		{
			fclose(fp);
			return 0;
		}
		//根据初始化的png_ptr初始化png_infop
		info_ptr = png_create_info_struct(png_ptr);

		if (!info_ptr)
		{
			//初始化失败以后销毁png_structp
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			fclose(fp);
			return 0;
		}


		//老老实实按照libpng给到的说明稳定步骤来  错误处理！
		if (setjmp(png_jmpbuf(png_ptr)))

		{
			//释放占用的内存！然后关闭文件返回一个贴图ID此处应该调用一个生成默认贴图返回ID的函数

			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);

			fclose(fp);

			return 0;

		}
		//你需要确保是通过2进制打开的文件。通过i/o定制函数png_init_io
		png_init_io(png_ptr, fp);
		//似乎是说要告诉libpng文件从第几个开始missing
		png_set_sig_bytes(png_ptr, 8);
		//如果你只想简单的操作你现在可以实际读取图片信息了！
		png_read_info(png_ptr, info_ptr);
		//获得图片到信息 width height 颜色类型  字节深度
		width = png_get_image_width(png_ptr, info_ptr);
		height = png_get_image_height(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);
		isAlpha = (color_type == PNG_COLOR_TYPE_RGBA);
		//如果图片带有alpha通道就需要
	   // if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)

			   // png_set_swap_alpha(png_ptr);
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		//隔行扫描图片  这个必须要调用才能进行
		number_of_passes = png_set_interlace_handling(png_ptr);
		//将读取到的信息更新到info_ptr
		png_read_update_info(png_ptr, info_ptr);

		//读文件
		if (setjmp(png_jmpbuf(png_ptr))) {
			fclose(fp);
			return 0;
		}

		int size = isAlpha ? 4 : 3;

		rgba = (GLubyte*)malloc(width * height * size);
		//使用动态数组  设置长度
		row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

		for (k = 0; k < height; k++)
			row_pointers[k] = NULL;

		//通过扫描流里面的每一行将得到的数据赋值给动态数组       
		for (k = 0; k < height; k++)
			//row_pointers[k] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
			row_pointers[k] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr,
				info_ptr));
		//由于png他的像素是由 左-右-从顶到底 而贴图需要的像素都是从左-右-底到顶的所以在这里需要把像素内容进行一个从新排列
		//读图片
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
		std::string str = std::string("加载纹理成功") + std::string(filename);
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
			// 不知道这里为什么必须翻转下图片y才行
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