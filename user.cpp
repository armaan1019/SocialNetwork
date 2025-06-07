#include "user.h"
#include <string>
#include <set>
#include <iostream>
#include <vector>

User::User() {} //Default constructor

//pre: id, name, birth year, zip code, and friends of user (constructor)
//post: will initialize a new user
User::User(int id, std::string name, int year, int zip, const std::set<int>& friends, int privacy) {
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
    privacy_ = privacy;
}


//pre: none
//post: return user id
int User::getId() {
    return id_;
}

//pre: none (Next four methods are getters)
//post: return user name
std::string User::getName() {
    return name_;
}

//pre: none
//post: return user birth year
int User::getYear() {
    return year_;
}

//pre: none
//post: return user zip code
int User::getZip() {
    return zip_;
}

//pre: none
//post: returns a reference of set of ints of the user's friends
std::set<int>& User::getFriends() {
    return friends_;
}

int User::getPrivacy() {
    return privacy_;
}

//pre: id of the user
//post: Add new friend for the user
void User::addFriend(int id) {
    friends_.insert(id);
}

//pre: id of the user
//post: delete the user's friend
void User::deleteFriend(int id) {
    for(int x: friends_) {
        //std::cout << x << std::endl;
        if(id == x) { //If it finds the id, it will delete the person.
            friends_.erase(id); // If two people do not have a connection and you attempt to delete, it will simply do nothing
            std::cout << "Deletion Successful" << std::endl;
            break;
        }
    }
}

//pre: a post pointer
//post: adds the post to the user
void User::addPost(Post* post) {
    messages_.push_back(post);
}

//pre: none
//post: gets a vector of all posts from users
std::vector<Post*> User::getPosts() {
    return messages_;
}

//pre: howMany, and publicity
//post: prints the most recent posts for the user depending on publicity
std::string User::getPostsString(int howMany, bool showOnlyPublic) {
    std::string result;
    int count = 0; //Will track how many posts we grabbed

    if(messages_.empty()) { //If empty
        return "";
    }

    for(int i = messages_.size() - 1; i >= 0 && count < howMany; i--) {
        Post* post = messages_[i];

        if(showOnlyPublic && post->getPrivacy() != 2) {
            continue;
        }

        if(!result.empty()){ //Two new lines everytime past the first name
            result += "\n\n";
        }
        result += post->toString();
        count++;
    }

    return result;
}

void User::setPrivacy(int p) {
    privacy_ = p;
}
