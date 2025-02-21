#pragma once
#include "User.h"

class BusinessUser : public User
{
public:
        /**
        * send message to another user
        * @param Usr is the user that will receive the message
        * @param msg is the message the will be sent to user 
        */
        virtual void SendMessage(User* usr,Message* msg);
};
