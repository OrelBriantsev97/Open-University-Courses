#include "client.h"
#include <sstream>
#include <filesystem>
#include "files.h"
bool registered = false;
unsigned int MAX_CLIENT_NAME = 255;
unsigned int CLIENT_VERSION = 3;
unsigned int UUID_SIZE = 16;
unsigned char clientID_bytes[16];
unsigned char aes_key[128];
std::string cid;
std::string pkey;
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>



Client::Client(const std::string& address, int port) : io_context(), socket(io_context)
{
	//set up socket and connect 
	const std::string& cadd = address;
	int cport = port;

	tcp::resolver resolver(io_context);

	boost::asio::connect(socket, resolver.resolve(cadd, std::to_string(cport)));
}


void Client::register_client(std::string& client_name)
{
	ClientRequestCode code = ClientRequestCode::Register;
	unsigned char tmp_buffer[USER_ID_SIZE_BYTES];
	if (registered == true)
		throw std::runtime_error("Registration Error : client already registered");

	register_req(client_name, code);


	ServerRequestCode res_type;
	ServerHeader res_header;
	boost::asio::read(socket, boost::asio::buffer(&res_header, sizeof(res_header)));
	res_type = static_cast<ServerRequestCode>(res_header.code);
	if (res_type == ServerRequestCode::SuccessfulRegister)
	{
		SuccessfulRegister res_payload;
		boost::asio::read(socket, boost::asio::buffer(&res_payload.client_id, sizeof(res_payload.client_id)));
		cid = decodeID(res_payload.client_id);

		registered = true;
	}
	else if (res_type == ServerRequestCode::FailedRegister)
	{
		throw std::runtime_error("Registration Error : registration failed");
	}
	else
		throw std::runtime_error("Registration Error : unexpected server response");




};

template <typename T>
void Client::build_header(T& req, std::vector<uint8_t> clientId, ClientRequestCode code, size_t payloadsize)
{
	if (clientId.empty())
		std::memset(reinterpret_cast<void*>(req.clientID), 0, sizeof(req.clientID));
	else
		std::memcpy(req.clientID, clientId.data(), std::min(clientId.size(), sizeof(req.clientID)));

	req.version = CLIENT_VERSION;
	req.code = static_cast<uint16_t>(code);
	req.payloadSize = payloadsize;
}

template <typename T>
void Client::send_request(const T& req)
{
	boost::asio::write(socket, boost::asio::buffer(&req, sizeof(req)));
};

void Client::reconnect()
{
	Reconnect req;
	//req.clientID
	send_request(req);
	//print sucess register
};

std::string Client::get_clientID()
{
	return cid;
};

std::string Client::get_priv_key()
{
	return base64privkey;
}

std::string Client::decodeID(const unsigned char* clientid)
{
	std::stringstream ss;
	for (size_t i = 0; i < USER_ID_SIZE_BYTES; ++i)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(clientid[i]);
		if (i == 3 || i == 5 || i == 7 || i == 9)
		{
			ss << "-";
		}
	}
	return ss.str();
};

std::vector<uint8_t> Client::encodeID(const std::string& uuid_str)
{
	// Convert string to UUID
	try {
		boost::uuids::uuid uuid = boost::uuids::string_generator()(uuid_str);

		// Create a vector to store the binary representation of the UUID
		std::vector<uint8_t> encoded_uuid(boost::uuids::uuid::static_size());

		// Copy the binary UUID to the vector
		std::memcpy(encoded_uuid.data(), uuid.data, boost::uuids::uuid::static_size());

		return encoded_uuid;
	}
	catch (const std::exception& e) {
		std::cerr << "Error converting UUID to binary: " << e.what() << std::endl;
		// You may want to handle this error appropriately (e.g., throw an exception).
		// For now, return an empty vector.
		return {};
	}
}

void Client::register_req(std::string name, ClientRequestCode code)
{
	RegistrationRequest req;

	build_header<ClientHeader>(req, std::vector<uint8_t>(), code, MAX_CLIENT_NAME);
	strncpy_s(req.clientName, name.c_str(), sizeof(req.clientName));;
	send_request(req);

}

void Client::send_public_key(std::string name, std::string id)
{
	SendPublicKey req;
	ClientRequestCode code = ClientRequestCode::SendPublicKey;
	
	size_t payloadSize = sizeof(req.clientName) + sizeof(req.publicKey);
	std::string public_key = rsa.getPublicKey();
	std::vector<uint8_t> en_id = encodeID(id);
	std::size_t key_size;

	build_header<ClientHeader>(req, en_id, code, payloadSize);
	strncpy_s(req.clientName, name.c_str(), sizeof(req.clientName));;
	std::memcpy(req.publicKey, public_key.data(), std::min(public_key.size(), sizeof(req.publicKey)));
	//strncpy_s(req.publicKey, sizeof(req.publicKey), public_key.c_str(), _TRUNCATE);
	send_request(req);


	ServerRequestCode res_type;
	ServerHeader res_header;
	boost::asio::read(socket, boost::asio::buffer(&res_header, sizeof(res_header)));
	res_type = static_cast<ServerRequestCode>(res_header.code);
	if (res_type == ServerRequestCode::SendAES)
	{
		SendAES res_payload;

		boost::asio::read(socket, boost::asio::buffer(&res_payload.client_id, sizeof(res_payload.client_id)));;
		cid = decodeID(res_payload.client_id);

		size_t size = sizeof(res_header.payloadSize - sizeof(res_payload.client_id));
		size_t sizecheck = sizeof(res_payload.client_id);
		size_t payloadSize = res_header.payloadSize - sizecheck;
		boost::asio::read(socket, boost::asio::buffer(&res_payload.s_key, 128));
		std::memcpy(aes_key, res_payload.s_key, sizeof(res_payload.s_key));
		

		registered = true;
	}
	else
		throw std::runtime_error("Registration Error : unexpected server response");

	
}


void Client::generate_keys()
{
	RSAPrivateWrapper rsa;
	pubkey = rsa.getPublicKey();

	char pubkeybuff[RSAPublicWrapper::KEYSIZE];
	rsa.getPublicKey(pubkeybuff, RSAPublicWrapper::KEYSIZE);
	RSAPublicWrapper rsapub(pubkey);

	base64privkey = Base64Wrapper::encode(rsa.getPrivateKey());

}

std::string Client::getAes()
{
	std::string aes_key_str(reinterpret_cast<char*>(aes_key), sizeof(aes_key));
	return  aes_key_str;
}

std::string Client::dectyptKey(const std::string& AESKey)
{
	const std::string& key = rsa.decrypt(AESKey);
	return key;
}

void Client::sendFile(std::string de_key, std::string file_path, std::string id)

{


}
