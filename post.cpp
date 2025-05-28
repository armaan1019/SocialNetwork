#include "post.h"
#include <string>

//Default constructor
Post::Post() {

}

//pre: message ID, owner ID, message, likes
//post: initializes a new post
Post::Post(int messageId, int ownerId, std::string message, int likes) {
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    likes_ = likes;
}

//pre: none
    //post: prints all of the info
std::string Post::toString() {
    return message_ + " Liked by " + std::to_string(likes_) + " people";
}

//pre: none
//post: returns message ID
int Post::getMessageId() {
    return messageId_;
}

//pre: none
    //post: returns owner ID
int Post::getOwnerId() {
    return ownerId_;
}

//pre: none
//post: get Message
std::string Post::getMessage() {
    return message_;
}

//pre: none
//post: get likes
int Post::getLikes() {
    return likes_;
}

//pre: none
//post: get author name
std::string Post::getAuthor() {
    return "";
}

//pre: none
//post: get publicity
bool Post::getIsPublic() {
    return true;
}

IncomingPost::IncomingPost() {} //Default constructor

//pre: same as post plus isPublic and author
//post: initializes Incoming Post object
IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author): Post(messageId, ownerId, message, likes), isPublic_(isPublic), author_(author) {}

//pre: none
    //post: returns a string of info
std::string IncomingPost::toString() {
    if(isPublic_ == true) {
        return author_ + " wrote: " + Post::toString(); 
    }
    return author_ + " wrote(private): " + Post::toString();
}

//pre: none
//post: gets author name
std::string IncomingPost::getAuthor() {
    return author_;
}

//pre: none
//post: gets publicity
bool IncomingPost::getIsPublic() {
    return isPublic_;
}