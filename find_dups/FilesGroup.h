#pragma once
#include <vector>

template <class T>
class CFilesGroup :
	public std::vector<CFileInfo<T>>
{

public:

	void PushFile(const CFileInfo<T>& FileInfo)
	{
		push_back(FileInfo);
	}

	friend std::ostream& operator<< (std::ostream &out, const CFilesGroup &fg)
	{
		for (auto& fi : fg)
		{
			out << fi << std::endl;
		}
		return out;
	}
};

