#pragma once
#include <string>
#include <map>
#include "User.h"

//describes the social network
class USocial{

    std::map<unsigned long,User*> users;
    unsigned int next_id=1;

public:
    //register new user by using registerUser(name,false)
   // User* registerUser(std::string name);
    /**
     * register a new user is the social network
     * @param text is the user name
     * @param businessUser represnts if the user is a bussines user or not
    */
    User* registerUser(std::string name ,bool businessUser = false);
      /**
     * removes exising user
     * @param usr is the user that will be removed
    */
    void removeUser(User* old_user);
    /**
     * get user according to given ID
     * @param uid is the user ID that we need to find
    */
    User* getUserById(unsigned long uid);
};
