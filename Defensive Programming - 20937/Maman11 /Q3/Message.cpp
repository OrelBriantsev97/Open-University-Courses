#include "Message.h"
#include <stdexcept>


    Message::Message(std::string text)
    {
        if(text.empty())
            throw std::invalid_argument("Messgae cannot be empty");
        this->text=text;
    }

    std::string Message::getText()
    {
        return this->text;
    }
