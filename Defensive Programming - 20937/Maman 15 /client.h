#ifndef CLIENT_H
#define CLIENT_H

#include "RSAWrapper.h"
#include "protocol.h"
#include "files.h"
#include "EncFile.h"

#include <boost/asio.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>

extern unsigned int MAX_CLIENT_NAME;
extern unsigned int CLIENT_VERSION;
extern  unsigned char clientID_bytes[16];
using boost::asio::ip::tcp;


class Client {
private:
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::socket socket;
	RSAPrivateWrapper rsa;
	RSAPublicWrapper rsapub;
	std::string pubkey;
	std::string base64privkey;
	std::string base64pubkey;
public:
	Client(const std::string& address, int port);
	void register_client(std::string& client_name);
	template <typename T>
	void send_request(const T& request);
	void reconnect();
	std::string get_clientID();
	std::string get_priv_key();
	std::string decodeID(const unsigned char* clientid);
	void send_public_key(std::string name,std::string id);
	template <typename T>
	void build_header(T& req, std::vector<uint8_t> clientId, ClientRequestCode code, size_t payloadsize);
	void generate_keys();
	void register_req(std::string name, ClientRequestCode code);
	std::vector<uint8_t> encodeID(const std::string& uuid_str);
	std::string getAes();
	std::string dectyptKey(const std::string& AESKey);
	void sendFile(std::string de_key, std::string file_path, std::string id);
};


#endif 

