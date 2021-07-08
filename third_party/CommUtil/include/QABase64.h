#ifndef _QABASE64_H
#define _QABASE64_H

#include <iostream>


class QABase64
{
public:

	static std::string EncodeBase64(const std::string &bytes_to_encode, size_t in_len);
	

	static std::string EncodeBase64(const char *bytes_to_encode, unsigned int in_len);
	

	static std::string DecodeBase64(std::string const& encoded_string);
	

private:
	static inline bool is_base64(unsigned char c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}


private:
	static const std::string QABase64::Base64_char;

	
};

#endif // _QABASE64_H
