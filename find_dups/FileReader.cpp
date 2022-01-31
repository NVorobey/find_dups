#include "FileReader.h"

bool CFileReader::Open(const std::string& sourcePath)
{
	m_fi.open(sourcePath, std::ios::in | std::ios::binary);
	m_uBiteReaded = 0;
	return m_fi.is_open();
}

bool CFileReader::Read(char *_Str, std::streamsize  _Count)
{
	if (m_fi.good())
	{
		m_fi.read(_Str, _Count);
		m_uBiteReaded += m_fi.gcount();
		return true;
	}
	else
	{
		return false;
	}
}

std::streamsize CFileReader::GetReadedCount() const
{
	return m_fi.gcount();
}

IReader* CFileReader::Duplicate() const
{
	return new CFileReader(*this);
}