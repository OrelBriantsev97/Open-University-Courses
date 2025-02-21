
#include "files.h"


File::File(const std::string& new_file) : opened(false)
{
	file.open(new_file);
	if (file.is_open())
	{
		std::getline(file, first_line);
		std::getline(file, second_line);
		std::getline(file, third_line);
		opened = true;
	}


}
std::string File::getFirstLine()
{
	return first_line;
}

std::string File::getSecondLine()
{
	return second_line;
}

std::string File::getThirdLine()
{
	return third_line;
}


std::string File::getIPAddress()
{
	std::string IPAddress;
	size_t colonPos = first_line.find(':');

	if (colonPos != std::string::npos) {
		IPAddress = first_line.substr(0, colonPos);
	}
	else {
		std::cerr << "Error: Unable to find ':' in first_line." << std::endl;
	}

	return IPAddress;

}

std::string File::getHost()
{
	std::string host;
	size_t colonPos = first_line.find(':');

	if (colonPos != std::string::npos && colonPos + 1 < first_line.length()) {
		host = first_line.substr(colonPos + 1);
	}
	else {
		std::cerr << "Error: Unable to find ':' or invalid host format in first_line." << std::endl;
	}

	return host;
}

bool File::is_opened()
{
	return opened;
}

void File::update(std::string name, std::string cid, std::string key)
{
	//change name to me file and check why public key not saved correctly
	std::ofstream file("file.txt", std::ios::app);
	file << "Name: " << name << std::endl;
	file << "Client ID: " << cid << std::endl;
	file << "Public Key: " << key << std::endl;

}


