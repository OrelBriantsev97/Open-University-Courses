#ifndef RSA_H
#define RSA_H

#include <string>
#include <osrng.h>
#include <rsa.h>
#include <base64.h>

#define RSA_KEY_LENGTH_BITS (1024)


class RSAPublicWrapper
{
public:
	static const unsigned int KEYSIZE = 160;
	static const unsigned int BITS = 1024;

private:
	CryptoPP::AutoSeededRandomPool _rng;
	CryptoPP::RSA::PublicKey _publicKey;

	RSAPublicWrapper(const RSAPublicWrapper& rsapublic);
	RSAPublicWrapper& operator=(const RSAPublicWrapper& rsapublic);
public:

	RSAPublicWrapper(const char* key, unsigned int length);
	RSAPublicWrapper(const std::string& key);
	~RSAPublicWrapper();



	std::string encrypt(const std::string& plain);
	std::string encrypt(const char* plain, unsigned int length);
};


class RSAPrivateWrapper
{
private:
	CryptoPP::AutoSeededRandomPool _rng;
	CryptoPP::RSA::PrivateKey _privateKey;
public:
	static const unsigned int BITS = 1024;
	RSAPrivateWrapper();
	RSAPrivateWrapper(const char* key, unsigned int length);
	RSAPrivateWrapper(const std::string& key);
	~RSAPrivateWrapper();

	
	std::string getPrivateKey() const;
	char* getPrivateKey(char* keyout, unsigned int length) const;

	std::string getPublicKey() const;
	char* getPublicKey(char* keyout, unsigned int length) const;

	std::string decrypt(const std::string& cipher);
	std::string decrypt(const char* cipher, unsigned int length);


};


class Base64Wrapper
{
public:
	static std::string encode(const std::string& str);
	static std::string decode(const std::string& str);

#endif

