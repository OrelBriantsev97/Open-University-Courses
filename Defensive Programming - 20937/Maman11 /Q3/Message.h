#pragma once
#include <string>

// represents message that one user sent to another
class Message{
    std::string text;
public:
    /**
     *constractor for new message
     @param msg is the message content
    */
    Message(std::string msg);
   
    //returns message content
    std::string getText(); 
};
