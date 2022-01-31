#pragma once

class IReader
{
public:
	virtual ~IReader() {}
	virtual bool Open(const std::string& sourcePath) = 0;
	virtual bool Read(char *_Str, std::streamsize  _Count) = 0;
	virtual std::streamsize GetReadedCount() const = 0;
	virtual IReader* Duplicate() const = 0;
};

