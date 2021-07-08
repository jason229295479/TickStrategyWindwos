#include "FileUtil.h"

#include <fstream>
#include <string>

#include "boost/algorithm/string.hpp"

bool FileUtil::IsFileExist(const std::string &filepath)
{
	boost::filesystem::path pathfile(filepath);
	return boost::filesystem::exists(pathfile);
}

bool FileUtil::isDirExist(const std::string &dirpath)
{
	return IsFileExist(dirpath);
}

bool FileUtil::CreateDir(const std::string &dirpath)
{
	boost::filesystem::path pathfile(dirpath);
	if (!isDirExist(dirpath))
	{
		return boost::filesystem::create_directories(pathfile);
	}
	return false;
}

bool FileUtil::Remove(const std::string &path)
{
	boost::filesystem::path pathfile(path);
	return boost::filesystem::remove(pathfile);
}

bool FileUtil::WriteFile(const std::string &strFile, const std::string &strContext)
{
	std::fstream out;
	out.open(strFile,  std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	if (out.is_open())
	{
		out << strContext << std::endl;
		out.close();
		return true;
	}
	return false;
}

bool FileUtil::WriteFile(const std::string &strFile, const std::list<std::string> &listContext)
{
	std::fstream out;
	out.open(strFile, std::ios_base::out);
	if (out.is_open())
	{
		for (auto &item : listContext)
		{
			out << item << std::endl;
		}		
		out.close();
		return true;
	}
	return false;
}

bool FileUtil::ReadFile(const std::string &strFile, std::string &strContext)
{
	std::fstream In;
	In.open(strFile, std::ios_base::in | std::ios_base::binary);
	if (In.is_open())
	{
		std::string strLine;
		while (std::getline(In, strLine))
		{
			strContext += strLine;
		} 
		In.close();
		return true;
	}
	return false;
}

bool FileUtil::WriteFileApp(const std::string &strFile, const std::string &strContext)
{
	std::fstream out;
	out.open(strFile, std::ios_base::out | std::ios_base::app | std::ios_base::binary);
	if (out.is_open())
	{
		out << strContext << std::endl;
		out.close();
		return true;
	}
	return false;
}

bool FileUtil::ReadFileLine(const std::string &strFile, std::vector<std::string> &vectorContext)
{
	std::list<std::string> listData;
	bool bRet = ReadFileLine(strFile, listData);
	vectorContext.assign(listData.begin(), listData.end());
	return bRet;
}

bool FileUtil::ReadFileLine(const std::string &strFile, std::list<std::string> &listContext)
{
	std::fstream In;
	In.open(strFile, std::ios_base::in | std::ios_base::binary);
	if (In.is_open())
	{
		std::string strLine;
		while (std::getline(In, strLine))
		{
			if (strLine.empty())
			{
				continue;
			}
			if (strLine[strLine.size() - 1] == '\r')
			{
				strLine.erase(strLine.size() - 1);
			}
			listContext.emplace_back(strLine);
			strLine.clear();
		}
		In.close();
		return true;
	}
	return false;
}

bool FileUtil::GetFileList(std::string &strDir, std::list<std::string> &listFiles, std::list<std::string> &listDir)
{
	if (!isDirExist(strDir) || !boost::filesystem::is_directory(strDir))
	{
		return true;
	}
	using rd_iterator = boost::filesystem::recursive_directory_iterator;
	rd_iterator DirPos(strDir), end;
	for (; DirPos != end; ++DirPos)
	{
		if (boost::filesystem::is_regular_file(*DirPos))
		{
			listFiles.emplace_back(DirPos->path().generic_string());
		}
		else if (boost::filesystem::is_directory(*DirPos))
		{
			listDir.emplace_back(DirPos->path().generic_string());
		}
	}
	return true;
}

bool FileUtil::GetFilName(std::string &strFullPath, std::string &strFileName)
{

	boost::filesystem::path filePath(strFullPath);
	strFileName = filePath.filename().generic_string();
	return true;
}

bool FileUtil::ParseFilName(std::string &strFileName, std::string &strMarket, std::string &strCode, std::string &strDate, std::string &strFilePre)
{
	std::vector<std::string> vecStr;
	boost::algorithm::split(vecStr, strFileName, boost::is_any_of("_"));
	if (vecStr.empty())
	{
		return false;
	}

	strFilePre = vecStr[0];
	strMarket = vecStr[1];
	strCode = vecStr[2];
	strDate = vecStr[3];
	return true;
}

