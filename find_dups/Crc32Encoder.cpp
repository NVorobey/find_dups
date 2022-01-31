#include <boost/crc.hpp>
#include <vector>
#include "IReader.h"
#include "Crc32Encoder.h"

bool CCrc32Encoder::Encode(IReader* pIReader, std::uint32_t& Result)
{

	std::vector<char>   buffer(4096);
	boost::crc_32_type result;

	while (pIReader->Read(&buffer[0], buffer.size()))
	{
		std::streamsize count = pIReader->GetReadedCount();
		result.process_bytes(&buffer[0], (size_t)count);
	}

	return result.checksum();
}

IEncoder<std::uint32_t>* CCrc32Encoder::Duplicate() const
{
	return new CCrc32Encoder(*this);
}