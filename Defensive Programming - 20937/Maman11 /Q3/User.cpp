#include "User.h"
#include "USocial.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <list>


User::User() {}

User::~User()
{

}

unsigned long  User::getId()
{
    return this->id;
}

std::string User::getName()
{
    return this->name;

}

void User::addFriend(User * new_friend)
{
    if(new_friend ==nullptr)
        throw std::invalid_argument("please provide a user to add as a friend for this user");
    int uid=new_friend->getId();
    friends.push_back(uid);

}

void User::removeFriend(User* old_friend)
{
    
    if(old_friend == nullptr)
        throw std::invalid_argument("please provide a user to unfriend");
    auto check_friendship=std::find(friends.begin(),friends.end(),old_friend->id);
    if(check_friendship == friends.end())
        throw std::invalid_argument("the given user is not a friend ot this user");
    
    friends.erase(check_friendship);
}

void User::post(std::string text)
{
    if(text.empty())
        throw std::invalid_argument("Canoot post empty post");
    posts.push_back(new Post(text));
}

void User::post(std::string text ,Media* media)
{
    if(text.empty())
        throw std::invalid_argument("Canoot post empty post");
    if(media ==nullptr)
        post(text);
    posts.push_back(new Post(text,media));
}

std::list<Post*> User::getPosts()
{
    return posts;
}

void User::viewFriendsPosts()
{
    for(auto friendid : friends)
        {
            User* fuser=us->getUserById(friendid);
            fuser->getPosts();
        }

}

void User::receiveMessage(Message* msg)
{
    if(msg ==nullptr)
        throw std::invalid_argument("cannot receive empty message");
    receivedMsgs.push_back(msg);

}
void User::sendMessage(User* usr ,Message* msg)
{
    if(usr ==nullptr)
           throw std::invalid_argument("please provide recepient to the message");
    if(msg ==nullptr)
           throw std::invalid_argument("cannot send empty message");
    usr->receivedMsgs.push_back(msg);

}
void User::viewReceivedMessages()
{
    for(auto msg : receivedMsgs)
    {
        std::cout << msg->getText() << std::endl;
    }
}
