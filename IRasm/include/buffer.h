#pragma once

#include <string>

class Buffer
{
public:
	void write(const char* const data, size_t dataSize) noexcept
	{
		this->data.append(data, dataSize);
	}

	std::string readAll() const noexcept { return data; }
	std::string& readAll() noexcept { return data; }

	size_t size() const noexcept { return data.size(); }

private:
	std::string data;
};