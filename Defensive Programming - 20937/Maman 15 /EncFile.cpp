#include "EncFile.h"

EncFile::EncFile(std::string key,  std::string filepath)
{
	std::string aes_key = key;
	 std::string fpath = filepath;
}

void EncFile::EncrypFile(RSAPublicWrapper rsapub)
{
	std::ifstream File(fpath, std::ios::binary);
	if (!File.is_open()) {
		throw std::runtime_error("File '" + fpath + "': client already registered");
		return;
	}
    std::vector<char> file_content((std::istreambuf_iterator<char>(fpath)), std::istreambuf_iterator<char>());
    std::string cipher = rsapub.encrypt(file_content.data(), file_content.size());
  


}
