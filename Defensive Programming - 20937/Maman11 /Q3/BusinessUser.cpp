#include "BusinessUser.h"
#include <stdexcept>

void BusinessUser::SendMessage(User* usr,Message* msg)
{
    if(msg == nullptr)
        throw std::invalid_argument("Message cannot be empty");
    if(usr==nullptr)
        throw std::invalid_argument("Please provide recepient for this message");
    usr->receiveMessage(msg);
    
    
}
