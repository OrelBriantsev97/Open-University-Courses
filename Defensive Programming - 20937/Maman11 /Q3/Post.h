#pragma once
#include <string>
#include "Media.h"

//represnt a post in the social network
class Post{
    std::string text;
    Media *media;
    
public:
    /**
     * constractor for new post with text only, uses the post(text,media constracor with media =null)
     * @param text is the content of the post
    */
    Post(std::string text);
    /**
     * constractor for new post with text and media  
     * @param text is the content of the post
     * @param media is the media (audio,photo or video) of the post
    */
    Post(std::string text, Media* media);
    //get the text of the post
    std::string getText();
    //get the media of the post
    Media *getMedia();
};
