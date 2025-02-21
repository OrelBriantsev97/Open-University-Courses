#include "Post.h"
#include <iostream>


Post::Post(std::string text)
    :text(text),media(nullptr) {}

Post::Post(std::string text,Media* media)
{
    if(text.empty() && media == nullptr)
        throw std::invalid_argument("post cannot be empty,post contain text with or without media ");
    this->text=text;
    this->media=media;
}

std::string Post::getText()
{
    return this->text;
}
    

Media* Post::getMedia()
{
    return this->media;
}
