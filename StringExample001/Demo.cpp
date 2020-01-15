#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <io.h>
#include <direct.h>


void GetFiles(std::string folder_path, std::vector<std::string>& files)
{

	//�ļ����
	intptr_t hFile = 0;//Win10
	//long hFile = 0; // linux C++
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	std::string p;
	try
	{
		if ((hFile = _findfirst(p.assign(folder_path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				//�����Ŀ¼,����֮���������,��ʾ����һ���ļ�,�����б�  (fileinfo.attrib &  _A_SUBDIR) == true ��ʾ����һ���ļ��С�
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					// ��Ϊ�ǻ�ȡ�ļ�����, ��Ҫ�ѵ�ǰĿ¼�͸�Ŀ¼�ų���Ҫ��Ȼ�Ž�ȥ�ľ����ļ��е�������
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					{
						GetFiles(p.assign(folder_path).append("\\").append(fileinfo.name), files);
					}
				}
				else
				{
					files.push_back(p.assign(folder_path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);

			_findclose(hFile);
		}
	}
	catch (std::exception e)
	{
		//�˴����catch �쳣����
	}
}

int main(int argc, char** argv)
{
	std::vector<std::string> fileNameVec;
	const std::string dirPath = "E:\\��������\\2020��\\1��13";
	GetFiles(dirPath, fileNameVec);
	int fileNameCount = fileNameVec.size();
	std::vector<std::string>::iterator pathIterator;
	for (pathIterator = fileNameVec.begin(); pathIterator != fileNameVec.end(); pathIterator++)
	{
		std::string fileName = (*pathIterator).substr((*pathIterator).find_last_of("\\") + 1);
		std::string prefixName = fileName.substr(0, fileName.find_last_of("."));
	}
}