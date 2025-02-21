#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint> 
#include <string>
#include <sstream>
#include <iomanip>


const int USER_NAME = 255;
const int PUBLIC_KEY = 160;
const int CONTENT_SIZE = 4;
const int USER_ID_SIZE_BYTES = 16;

#pragma pack(push, 1)
class ClientHeader {
public:
    unsigned char clientID[16];
    unsigned char version;
    uint16_t code;
    unsigned int payloadSize;
};
#pragma pack(pop)   


enum class ClientRequestCode : uint16_t {
    Register = 1025,
    SendPublicKey = 1026,
    Reconnect = 1027,
    SendFile = 1028,
    ValidCRC = 1029,
    UnvalidCRC_Resend = 1030,
    UnvalidCRC_Done = 1031
};

//represents request #1025
class RegistrationRequest : public ClientHeader {
public:
    char clientName[USER_NAME];

};
//represents request #1026
class SendPublicKey : public ClientHeader {
public:
    char clientName[USER_NAME];
    char publicKey[PUBLIC_KEY];
};

//represents request #1027
class Reconnect : public  ClientHeader {
public:
    char clientName[USER_NAME];
};

//represents request #1028 
class SendFile : public  ClientHeader {
public:
    int contentSize[CONTENT_SIZE];
    char fileName[USER_NAME];
   
};

//represents request #1029
class ValidCRC : public ClientHeader {
public:
    char fileName[USER_NAME];
};

//represents request 1030
class inValidCRC : public  ClientHeader {
public:
    char fileName[USER_NAME];
};
//represents request 1031
class Done : public  ClientHeader {
public:
    char fileName[USER_NAME];
};


class ServerHeader {
public:
    unsigned char version;
    uint16_t code;
    unsigned int payloadSize;

};



enum class ServerRequestCode : uint16_t {
    SuccessfulRegister = 2100,
    FailedRegister = 2101,
    SendAES = 2102,
    ValidFileCRC = 2103,
    ValidMsg = 2104,
    sReconnect = 2105,
    Declined = 2106,
    General = 2107,
};

class SuccessfulRegister : public ServerHeader {
public:
    unsigned char client_id[USER_ID_SIZE_BYTES];;
};


//represents request 2101
class FailedRegister : public ServerHeader {
public:

};

//represents request 2102
class SendAES : public ServerHeader {
public:
    unsigned char client_id[USER_ID_SIZE_BYTES];
    unsigned char s_key[USER_NAME];
};

//represents request 2103
class ValidFileCRC : public ServerHeader {
public:
    unsigned int client_id[USER_ID_SIZE_BYTES];
    unsigned int content_size[CONTENT_SIZE];
    unsigned char file_name[USER_NAME];
    unsigned int cksum[CONTENT_SIZE];
};

//represents request 2104
class ValidMsg : public ServerHeader {
public:
    unsigned int client_id[USER_ID_SIZE_BYTES];
};

//represents request 2105
class sReconnect : public ServerHeader {
public:
    unsigned int client_id[USER_ID_SIZE_BYTES];
    unsigned int s_key;
};

//represents request 2106
class Declined : public ServerHeader {
public:
    unsigned int client_id[USER_ID_SIZE_BYTES];
};

//represents request 2107
class General : public ServerHeader {
public:

};
// Other classes and enums...

std::string decodeID(const unsigned char* clientid);

#endif
