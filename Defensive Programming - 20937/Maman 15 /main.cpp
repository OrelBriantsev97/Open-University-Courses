#include <iostream>
#include <fstream>
#include <string>
#include "files.h"
#include "client.h"
#include <stdexcept>



int main()
{
	std::string transfer_file = "transfer.info";
	std::string me_file = "me.info";
	std::string client_name;
	std::string client_id;
	std::string priv_key;
	std::string encryptedAES;
	File tfile(transfer_file);
	if (!tfile.is_opened())
	{
		throw std::runtime_error("Failed to open the file: " + transfer_file);
	}
	std::string ipAdd = tfile.getIPAddress();
	std::string host = tfile.getHost();
	std::cout << "Client connecting to server ..." << std::endl;
	File mfile(me_file);
	if (!mfile.is_opened())
	{
		client_name = tfile.getSecondLine();
		Client client(ipAdd, std::stoi(host));
		std::cout << "Client connected to server " << std::endl;
		client.register_client(client_name);

		std::cout << "Client registered suceccfully " << std::endl;
		
		//genrate RSA pair and send public key
		client_id = client.get_clientID();
		std::cout << "client id is : " << client_id << std::endl;
		client.generate_keys();
		priv_key = client.get_priv_key();
		
		//save in file me.info the name and UUID from server 
		mfile.update(client_name, client_id,priv_key);
		std::cout << "Exchanging keys between client and server "; // check the thins with prev.key
		client.send_public_key(client_name,client_id);
		std::cout << "Keys exchanged successfully." << std::endl;
		encryptedAES = client.getAes();
		std::string de_key = client.dectyptKey(encryptedAES);
		std::string file_path = tfile.getThirdLine();
		client.sendFile(de_key ,file_path,client_id);
		

	}
	else
	{
		File file(me_file);
		client_name = mfile.getFirstLine();
		Client client(ipAdd, std::stoi(host));
		client.reconnect();
		//dont send RSA key to server - use old one from priv.key and dont register again

	}
	
	



	

}
