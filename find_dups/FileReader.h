#pragma once
#include <fstream>
#include "IReader.h"

class CFileReader :
	public IReader
{
	std::ifstream m_fi;
	uintmax_t m_uFileSize;
	uintmax_t m_uBiteReaded = 0;
public:

	CFileReader(const uintmax_t& uFileSize) :
		m_uFileSize(uFileSize)
	{
	}

	CFileReader(const CFileReader& other)
	{
		m_uFileSize = other.m_uFileSize;
	}

	virtual bool Open(const std::string& sourcePath) override;
	virtual bool Read(char *_Str, std::streamsize  _Count) override;
	virtual std::streamsize GetReadedCount() const override;
	virtual IReader* Duplicate() const override;
};


