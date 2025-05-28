#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <set>
#include <vector>
#include "user.h"

class Network {
    std::vector<User*> users_;

    public: 
    Network(); //Default constructor
    //pre: a user object
    //post: add to the users_ vector
    void addUser(User* User);

    //pre: two strings which are the names of two users
    //Post: will create a connection between the two users
    int addConnection(std::string s1, std::string s2);

    //pre: Two strings which are the name of two different users
    //post: Will delete the connection between these two users
    int deleteConnection(std::string s1, std::string s2);

    //pre: string name of the user
    //post: will return the id of the user
    int getId(std::string name);

    //pre: char* of the filename
    //post: Will read and initialize users from the file
    int readUsers(char* fname);

    //pre: char* of the filename to write to
    //post: Will write the network of users to a file
    int writeUsers(char *fname);

    //pre: none
    //post: returns the number of users in the network
    int numUsers();

    //pre: id of a user
    //post: Will return the pointer to the user with that id
    User* getUser(int id);

    //pre: Ids from and to
    //post: Finds the shortest distance away from the user to another user
    std::vector<int> shortestPath(int from, int to);

    //pre: Ids from, to, and distance
    //post: finds users the select number of distance away from the user. 
    std::vector<int> distanceUser(int from, int& to, int distance);

    //pre: Id of a user, and a score
    //post: This method finds friends with the most amount of mutual friends with the user given. Returns a list of friends found.
    std::vector<int> suggestFriends(int who, int& score);

    //pre: none
    //post: This method counts how many groups of users we have. Groups are users who are connected to each other, but aren't connected
    //to another group of users
    std::vector<std::vector<int>> groups();

    //pre: owner ID, message, likes, isIncoming, author's name, and the publicity.
    //post: adds a post to the user in the network.
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);

    //pre: owner ID, howMany posts, publicity
    //post: returns a string of the most recent posts of the user depending on publicity
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    //pre: file name
    //post: reads post from a file
    int readPosts(char* fname);

    //pre: file name
    //post: writes post to a file
    int writePosts(char* fname);
};

#endif