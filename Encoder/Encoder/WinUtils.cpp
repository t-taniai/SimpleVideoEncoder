#include "WinUtils.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <time.h>
#include <atlstr.h>
#include <codecvt>

namespace WinUtil
{
	void CreateDirectories_(const CStringA& path)
	{
		// only create directories that don't exist
		if (::GetFileAttributesA(path) == INVALID_FILE_ATTRIBUTES)
		{
			// check if our parent needs to be created, too...
			int i = max(path.ReverseFind('/'), path.ReverseFind('\\'));
			if (i > 0)
			{
				// ...yes, create the parent (recursively)
				CreateDirectories_(path.Left(i));
			}

			//std::cout << path << std::endl;
			// finally, actually create the directory in p
			::CreateDirectoryA(path, NULL);
		}
	}

	void CreateDirectories(const std::string& dir_Path)
	{
		//auto cmd = "mkdir " + dir_Path;
		//system(cmd.c_str());
		CreateDirectories_(CStringA(dir_Path.c_str()));
	}
	
	bool IsDirectoryExist(const std::string& dir_Path)
	{
		DWORD dwAttrib = GetFileAttributesA(dir_Path.c_str());

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}

	std::vector<std::string> GetFiles(const std::string& dir_path, const std::string& filter)
	{
		WIN32_FIND_DATAA fd;

		std::string ss = dir_path + filter;
		HANDLE hFind = FindFirstFileA(ss.c_str(), &fd);

		std::vector<std::string> fileList;

		if (hFind == INVALID_HANDLE_VALUE)
			return fileList;

		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				fileList.push_back(fd.cFileName);
		} while (FindNextFileA(hFind, &fd));

		FindClose(hFind);

		auto newend = std::remove_if(fileList.begin(), fileList.end(), [](const std::string& str){ return str == "." || str == ".."; });
		fileList.erase(newend, fileList.end());

		return fileList;
	}
	std::vector<std::string> GetDirectries(const std::string& dir_path, const std::string& filter)
	{
		WIN32_FIND_DATAA fd;

		std::string ss = dir_path + filter;
		HANDLE hFind = FindFirstFileA(ss.c_str(), &fd);

		std::vector<std::string> fileList;

		if (hFind == INVALID_HANDLE_VALUE)
			return fileList;
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				fileList.push_back(fd.cFileName);
		} while (FindNextFileA(hFind, &fd));

		FindClose(hFind);

		auto newend = std::remove_if(fileList.begin(), fileList.end(), [](const std::string& str){ return str == "." || str == ".."; });
		fileList.erase(newend, fileList.end());

		return fileList;
	}

	void MySleep(unsigned long int msec)
	{
		//Sleep(msec);
		clock_t st = clock();
		while (1000 * (clock() - st) / CLOCKS_PER_SEC < msec)
			;
	}
}