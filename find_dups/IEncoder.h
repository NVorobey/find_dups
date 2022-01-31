#pragma once
class IReader;

template <class T>
class IEncoder
{
public:
	virtual ~IEncoder()	{}
	virtual bool Encode(IReader* pIReader, T& Result) = 0;
	virtual IEncoder* Duplicate() const = 0;
};

