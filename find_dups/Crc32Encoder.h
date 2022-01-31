#pragma once
#include "IEncoder.h"

class CCrc32Encoder :
	public IEncoder<std::uint32_t>
{
public:
	virtual bool Encode(IReader* pIReader, std::uint32_t& Result) override;
	virtual IEncoder* Duplicate() const override;
};

