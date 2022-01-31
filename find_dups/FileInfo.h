#pragma once
#include <ostream>
#include "IEncoder.h"

template <class T>
class CFileInfo
{
	std::string m_strSourcePath;
	uintmax_t	m_uFileSize;
	IReader * m_pReader;
	IEncoder <T> * m_pEncoder;
	T * m_pEncodeResult = nullptr;
	bool m_bReadFail = false;

public:
	CFileInfo(const std::string& sourcePath, const uintmax_t& uFileSize,
		IReader * pReader, IEncoder<T> * pEncoder)
		:m_strSourcePath(sourcePath), m_uFileSize(uFileSize),
		m_pReader(pReader), m_pEncoder(pEncoder), m_bReadFail(false)
	{
	}

	CFileInfo(const CFileInfo& cp)
	{
		m_strSourcePath = cp.m_strSourcePath;
		m_uFileSize = cp.m_uFileSize;
		m_pReader = cp.m_pReader->Duplicate();
		m_pEncoder = cp.m_pEncoder->Duplicate();
		if (nullptr != cp.m_pEncodeResult)
		{
			m_pEncodeResult = new T(*cp.m_pEncodeResult);
		}
		else
		{
			m_pEncodeResult = nullptr;
		}
		m_bReadFail = cp.m_bReadFail;
	}

	CFileInfo(CFileInfo&& other)
	{
		m_strSourcePath = other.m_strSourcePath;
		m_uFileSize = other.m_uFileSize;
		m_pReader = other.m_pReader;
		m_pEncoder = other.m_pEncoder;
		m_pEncodeResult = other.m_pEncodeResult;
		m_bReadFail = other.m_bReadFail;

		other.m_pReader = nullptr;
		other.m_pEncoder = nullptr;
		other.m_pEncodeResult = nullptr;
		other.m_uFileSize = 0;
		other.m_strSourcePath.clear();
		other.m_bReadFail = false;
	}

	~CFileInfo()
	{
		if (nullptr != m_pEncodeResult)
			delete m_pEncodeResult;
		if (nullptr != m_pReader)
			delete m_pReader;
		if (nullptr != m_pEncoder)
			delete m_pEncoder;

	}

	const std::string& GetSourcePath() const
	{
		return m_strSourcePath;
	}

	bool IsReadedSuccessfully() const
	{
		return !m_bReadFail;
	}

	virtual bool Encode()
	{
		if (nullptr == m_pEncodeResult)
		{
			m_pReader->Open(m_strSourcePath);
			m_pEncodeResult = new T;
			if (!m_pEncoder->Encode(m_pReader, *m_pEncodeResult))
			{
				delete m_pEncodeResult;
				m_pEncodeResult = nullptr;
				m_bReadFail = true;
			}
			else
			{
				m_bReadFail = false;
			}
		}
		return (nullptr != m_pEncodeResult);
	}
	virtual const T * GetEncodeResult() const
	{
		return m_pEncodeResult;
	}

	friend std::ostream& operator << (std::ostream &out, const CFileInfo<T> &fi)
	{
		if (!fi.IsReadedSuccessfully())
		{
			out << "Read Failed: ";
		}
		out << fi.GetSourcePath();
		return out;
	}

};

