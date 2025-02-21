#ifndef ENCFILE_H
#define ENCFILE_H

#include <filesystem>
#include <fstream>
#include "RSAWrapper.h"

class EncFile {
private:
	std::string aes_key;
	std::string file_path;
	size_t encrypted_size;

public:
	EncFile(std::string key, std::string path);
	void EncrFile(RSAPublicWrapper rsapub);
	size_t enSize();
};

#endif
