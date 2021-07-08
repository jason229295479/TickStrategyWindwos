#ifndef _FILEUTIL_H_
#define _FILEUTIL_H_

#include "boost/filesystem.hpp"

#include <string>

class FileUtil
{
public:

	static bool IsFileExist(const std::string &filepath);

	static bool isDirExist(const std::string &dirpath);

	static bool CreateDir(const std::string &dirpath);

	static bool Remove(const std::string &path);

	//写二进制文件 
	static bool WriteFile(const std::string &strFile,const std::string &strContext);

	//写二进制文件 
	static bool WriteFile(const std::string &strFile, const std::list<std::string> &listContext);

	//读二进制文件
	static bool ReadFile(const std::string &strFile, std::string &strContext);
	//写二进制文件 
	static bool WriteFileApp(const std::string &strFile, const std::string &strContext);
	//读二进制文件
	static bool ReadFileLine(const std::string &strFile, std::vector<std::string> &vectorContext);

	static bool ReadFileLine(const std::string &strFile, std::list<std::string> &listContext);

	static bool GetFileList(std::string &strDir, std::list<std::string> &listFiles, std::list<std::string> &listDir);

	static bool GetFilName(std::string &strFullPath, std::string &strFileName);

	static bool ParseFilName(std::string &strFileName,std::string &strMarket, std::string &strCode, std::string &strDate, std::string &strFilePre);
};




#endif // _FILEUTIL_H_
