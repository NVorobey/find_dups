#pragma once
#include "FilesGroup.h"



template <class T>
class CMapOfFileGroup :
	public std::map<T, CFilesGroup<T> >
{
private:
	CMapOfFileGroup(const CMapOfFileGroup&);
protected:

	CFileInfo<T> * m_pSingleFileInfo = nullptr;

public:
	CMapOfFileGroup()
	{
	}

	~CMapOfFileGroup()
	{
		if (nullptr == m_pSingleFileInfo)
		{
			delete m_pSingleFileInfo;
		}
	}

protected:
	
	void PushFileInfo(CFileInfo<T> fi)
	{
		if(fi.Encode())
		{
			(*this)[*fi.GetEncodeResult()].push_back(fi);
		}
		else
		{
			BOOST_LOG_TRIVIAL(error)<< "Read Faile: " << fi << std::endl;
		}
	}
	
public:

	void Push(const CFileInfo<T>& FileInfo)
	{
		if (0 == std::map<T, CFilesGroup<T> >::size())
		{
			if (nullptr == m_pSingleFileInfo)
			{
				m_pSingleFileInfo = new CFileInfo<T>(FileInfo);
				return;
			}
			else
			{
				PushFileInfo(*m_pSingleFileInfo);
				delete m_pSingleFileInfo;
				m_pSingleFileInfo = nullptr;
			}
		}
		PushFileInfo(FileInfo);
	}


	friend std::ostream& operator<< (std::ostream &out, const CMapOfFileGroup<T> &fg)
	{
		std::cout <<  std::endl;
		if (nullptr == fg.m_pSingleFileInfo)
		{
			for (const auto&[key, value] : fg) {

				std::cout << value << std::endl;
			}
		}
		else
			std::cout << (*fg.m_pSingleFileInfo) << std::endl;
		return out;
	}
};
