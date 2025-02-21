#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

class File {
private:
	std::ifstream file;
	std::string first_line;
	std::string second_line;
	std::string third_line;
	bool opened;
public:
	File(const std::string& file);
	std::string getIPAddress();
	std::string getHost();
	std::string getName(); //need to check it 
	std::string getPath(); //need to check it
	std::string getFirstLine();
	std::string getSecondLine();
	std::string getThirdLine();
	bool is_opened();
	void update(std::string, std::string,std::string);

};



#endif 
