#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <io.h>
#include <direct.h>


void GetFiles(std::string folder_path, std::vector<std::string>& files)
{

	//文件句柄
	intptr_t hFile = 0;//Win10
	//long hFile = 0; // linux C++
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	try
	{
		if ((hFile = _findfirst(p.assign(folder_path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				//如果是目录,迭代之，如果不是,表示他是一个文件,加入列表  (fileinfo.attrib &  _A_SUBDIR) == true 表示这是一个文件夹。
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					// 因为是获取文件名字, 需要把当前目录和父目录排除，要不然放进去的就是文件夹的名字了
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
		//此处添加catch 异常处理
	}
}

int main(int argc, char** argv)
{
	std::vector<std::string> fileNameVec;
	const std::string dirPath = "E:\\创迹工作\\2020年\\1月13";
	GetFiles(dirPath, fileNameVec);
	int fileNameCount = fileNameVec.size();
	std::vector<std::string>::iterator pathIterator;
	for (pathIterator = fileNameVec.begin(); pathIterator != fileNameVec.end(); pathIterator++)
	{
		std::string fileName = (*pathIterator).substr((*pathIterator).find_last_of("\\") + 1);
		std::string prefixName = fileName.substr(0, fileName.find_last_of("."));
	}
}