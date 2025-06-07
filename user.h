#ifndef USER_H
#define USER_H
#include <string>
#include <set>
#include <vector>
#include "post.h"

class User{
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
    std::vector<Post*> messages_;
    int privacy_ = 2;

    //pre: none
    //post: default constructor
public: User();

    //pre: id, name, birth year, zip code, and friends of user (constructor)
    //post: will initialize a new user
    User(int id, std::string name, int year, int zip, const std::set<int>& friends, int privacy = 2);

    //pre: id of the user
    //post: Add new friend for the user
    void addFriend(int id);

    //pre: id of the user
    //post: delete the user's friend
    void deleteFriend(int id);

    //pre: none
    //post: return user id
    int getId();

    //pre: none (Next four methods are getters)
    //post: return user name
    std::string getName();

    //pre: none
    //post: return user birth year
    int getYear();

    //pre: none
    //post: return user zip code
    int getZip();

    //pre: none
    //post: get privacy
    int getPrivacy();

    //pre: an int
    //post: sets Privacy
    void setPrivacy(int p);

    //pre: none
    //post: returns a reference of set of ints of the user's friends
    std::set<int>& getFriends();

    //pre: a post pointer
    //post: adds the post to the user
    void addPost(Post*);

    //pre: none
    //post: gets a vector of all posts from users
    std::vector<Post*> getPosts();

    //pre: howMany, and publicity
    //post: prints the most recent posts fpr the user depending on publicity
    std::string getPostsString(int howMany, bool showOnlyPublic);
};

#endif
