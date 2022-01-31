// find_dups.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <map>
#include <boost/log/core.hpp> 
#include <boost/log/trivial.hpp> 
#include <boost/log/expressions.hpp> 

#include <filesystem>
#include "FileReader.h"
#include "FileInfo.h"
#include "MapOfFileGroup.h"
#include "Crc32Encoder.h"

namespace fs = std::filesystem;
namespace logging = boost::log;

typedef std::map<uintmax_t, CMapOfFileGroup<std::uint32_t> > CFileGroupBySize;
typedef CFileInfo<std::uint32_t> CFileInfoWithCrc32;

void ParseDirectory(const std::string& strDirectoryPath, CFileGroupBySize& m)
{
	try
	{
		for (const auto & entry : fs::directory_iterator(strDirectoryPath))
		{
			if (entry.is_regular_file())
			{
				try
				{
					std::string strPath(entry.path().string());
					m[entry.file_size()].Push(CFileInfoWithCrc32(strPath, entry.file_size(),
						new CFileReader(entry.file_size()), new CCrc32Encoder()));
				}
				catch (std::system_error&e)
				{
					BOOST_LOG_TRIVIAL(error) << e.what();
				}
				catch(...)
				{
					BOOST_LOG_TRIVIAL(error) << "Unknown Error";
				}
			}
			else
				if (entry.is_directory())
				{
					ParseDirectory(entry.path().string(), m);
				}
		}
	}
	catch (fs::filesystem_error &e)
	{
		BOOST_LOG_TRIVIAL(error) << e.what();
	}

}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << std::endl << "Please specify path to the folder";
		return 0;
	}

	CFileGroupBySize  m;

	ParseDirectory(argv[1], m);

	for (const auto&[key, value] : m) {

		std::cout << value;
	}
}
