#ifndef POST_H
#define POST_H
#include <string>

class Post {
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;

    public:
    Post(); //Default constructor

    //pre: message ID, owner ID, message, likes
//post: initializes a new post
    Post(int messageId, int ownerId, std::string message, int likes);

    //pre: none
    //post: prints all of the info
    virtual std::string toString();

    //pre: none
//post: returns message ID
    int getMessageId();

    //pre: none
    //post: returns owner ID
    int getOwnerId();

    //pre: none
//post: get Message
    std::string getMessage();

    //pre: none
//post: get likes
    int getLikes();

    //pre: none
//post: get author name
    virtual std::string getAuthor();

    //pre: none
//post: get publicity
    virtual bool getIsPublic();
};

class IncomingPost: public Post {
    std::string author_;
    bool isPublic_;

    public:
    IncomingPost(); //Default constructor

    //pre: same as post plus isPublic and author
//post: initialized Incoming Post object
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    //pre: none
    //post: returns a string of info
    std::string toString();

    //pre: none
//post: gets author name
    std::string getAuthor();

    //pre: none
//post: gets publicity
    bool getIsPublic();
};

#endif