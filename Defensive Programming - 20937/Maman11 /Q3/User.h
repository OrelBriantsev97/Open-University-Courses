#pragma once
#include "Post.h"
#include "Message.h"
#include <list>

class USocial;
//describe user with all of his attributes in the social network
class User{

    
protected:
    friend class USocial;

    USocial* us;
    unsigned long id;
    std::string name;
    std::list<unsigned long> friends;
    std::list<Post*> posts;
    std::list<Message*> receivedMsgs;
    //constructor for new user
    User();
    //destructor for a user
    ~User();

public:
    //gets user ID
    unsigned long getId();
    //gets user name
    std::string getName();
    /**
     * add user as a friend.
     * @param new_friend is the new friend
    */
    void addFriend(User* new_friend);
     /**
     * unfriend user .
     * @param old_friend is the old friend
    */
    void removeFriend(User*);
    /**
     * posts a post with text only
     * @param std::string is the post content
    */
    void post(std::string text);
    /**
     * posts a post with text and media
     * @param std::string is the post content
    */
    void post(std::string text,Media* media);
    //get user's posts
    std::list<Post*> getPosts();
    //gets posts from users's friends
    void viewFriendsPosts();
    /**
     * receive message from other user
     * @param msg is the message that the user gets
    */
    void receiveMessage(Message* msg);
    /**
     * send message to other user
     * @param usr is the recepient of the message
     * @param msg is the message that will be sent
    */
    virtual void sendMessage(User* usr,Message* msg); 
    //view all message that the user received
    void viewReceivedMessages();


};
