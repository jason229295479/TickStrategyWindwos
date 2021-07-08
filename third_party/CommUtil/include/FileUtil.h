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

	//д�������ļ� 
	static bool WriteFile(const std::string &strFile,const std::string &strContext);

	//д�������ļ� 
	static bool WriteFile(const std::string &strFile, const std::list<std::string> &listContext);

	//���������ļ�
	static bool ReadFile(const std::string &strFile, std::string &strContext);
	//д�������ļ� 
	static bool WriteFileApp(const std::string &strFile, const std::string &strContext);
	//���������ļ�
	static bool ReadFileLine(const std::string &strFile, std::vector<std::string> &vectorContext);

	static bool ReadFileLine(const std::string &strFile, std::list<std::string> &listContext);

	static bool GetFileList(std::string &strDir, std::list<std::string> &listFiles, std::list<std::string> &listDir);

	static bool GetFilName(std::string &strFullPath, std::string &strFileName);

	static bool ParseFilName(std::string &strFileName,std::string &strMarket, std::string &strCode, std::string &strDate, std::string &strFilePre);
};




#endif // _FILEUTIL_H_
