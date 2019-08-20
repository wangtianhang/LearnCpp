#include "./DebugMemory.h"

#include "./FileIO.h"

std::string LoadTextFile(const std::string & filePath)
{
	//GLuint result = 0;
	FILE * fp;
	size_t filesize;
	char * data;

	fp = fopen(filePath.c_str(), "rb");

	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	data = new char[filesize + 1];

	fread(data, 1, filesize, fp);
	data[filesize] = 0;
	fclose(fp);

	std::string ret = data;
	delete[] data;

	return ret;
}