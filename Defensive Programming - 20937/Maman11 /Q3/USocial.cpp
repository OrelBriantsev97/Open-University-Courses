#include "USocial.h"
#include "User.h"
#include "BusinessUser.h"
#include <stdexcept>


//User* USocial::registerUser(std::string name)
//{
  //  return registerUser(name,false);
//}

User* USocial::registerUser(std::string name,bool businessUser)
{
    if(name.empty())
          throw std::invalid_argument("user name cannotbe empty");
    User* usr;
    if(businessUser)
    {
        usr=new BusinessUser();
    }
    else 
        usr = new User();
    next_id++;
    usr->id=next_id;
    usr->name=name;
    usr->us= this;
    users[usr->id]=usr;
    return usr;
}

void USocial::removeUser(User* old_user)
{
    if(old_user ==nullptr)
        throw std::invalid_argument("Please provide user to remove");
    if(users.find(old_user->id)==users.end())
        throw std::invalid_argument("Please provide exising user to remove");
    users.erase(old_user->id);
    delete old_user;
}

User* USocial::getUserById(unsigned long uid)
{
     if(users.find(uid)==users.end())
        throw std::invalid_argument("Please provide exising user to remove");
    return users.at(uid);
}

