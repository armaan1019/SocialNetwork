#include "network.h"
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

struct Record { //In order to read a file
    int id, year, zip;
    std::string name;
    std::set<int> friends;
};

Network::Network() {} //Default constructor

//pre: a user object
//post: add to the users_ vector
void Network::addUser(User* User) {
    users_.push_back(User);
}

//pre: two strings which are the names of two users
//Post: will create a connection between the two users
int Network::addConnection(std::string s1, std::string s2) {
    User* user1 = nullptr;
    User* user2 = nullptr;

    if(s1 == s2) { //Make sure the two names aren't the same
        std::cout << "You cannot add yourself" << std::endl;
        return -1;
    }

    for(User* user: users_) {
        //std::cout << user->getName() << std::endl << s1 << std::endl << s2 << std::endl;
        if(s1 == user->getName()) { //Get user 1
            user1 = user;
        }
        if(s2 == user->getName()) { //Get user 2
            user2 = user;
        } 
    }
    if(user1 != nullptr && user2 != nullptr) { // Make sure they exist
        user1->addFriend(user2->getId());
        user2->addFriend(user1->getId());
        std::cout << "You have successfully added " << s2 << std::endl; //print success message
        return 0;
    } else {
        std::cout << "Connection failed" << std::endl;
    }
    return -1;
}

//pre: Two strings which are the name of two different users
//post: Will delete the connection between these two users
int Network::deleteConnection(std::string s1, std::string s2) {
    User* user1 = nullptr;
    User* user2 = nullptr;

    if(s1 == s2) { //Make sure the names aren't the same
        std::cout << "You cannot delete yourself" << std::endl;
        return -1;
    }

    for(User* user: users_) {
        //std::cout << user->getName() << std::endl << s1 << std::endl << s2 << std::endl;
        if(s1 == user->getName()) { //Assign user 1 and user 2
            user1 = user;
        }
        if(s2 == user->getName()) {
            user2 = user;
        } 
    }
    if(user1 != nullptr && user2 != nullptr) { // As long as the two users exist and have a connection, the connection will be deleted
        user1->deleteFriend(user2->getId());
        user2->deleteFriend(user1->getId());
        return 0;
    } else {
        std::cout << "Deletion failed" << std::endl;
    }
    return -1;
}

//pre: string name of the user
//post: will return the id of the user
int Network::getId(std::string name) {
    for(User* user: users_) {
        if(user->getName() == name) {
            return user->getId();
        }
    }

    std::cout << name << " is not a user" << std::endl;
    return -1;
}

//pre: char* of the filename
//post: Will read and initialize users from the file
int Network::readUsers(char* fname) {
    std::vector<Record> records;
    std::ifstream file(fname);
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {  
        Record record;

        // Line 1: ID
        record.id = std::stoi(line);

        // Line 2: Name
        std::getline(file, record.name);
        auto start = std::find_if(record.name.begin(), record.name.end(),
                          [](unsigned char ch) { return !std::isspace(ch); });

        record.name = std::string(start, record.name.end());

        // Line 3: Year
        std::getline(file, line);
        record.year = std::stoi(line);

        // Line 4: Zip
        std::getline(file, line);
        record.zip = std::stoi(line);

        // Line 5: Friend Id's
        std::getline(file, line);
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            record.friends.insert(value);
        }

        User* user = new User(record.id, record.name, record.year, record.zip, record.friends); //Initialize user
        users_.push_back(user); //Add to the users_ vector
        records.push_back(record);
    }

    return 0;
}

//pre: char* of the filename to write to
//post: Will write the network of users to a file
int Network::writeUsers(char* fname) {
    std::ofstream file(fname); //open the file

    file << users_.size() << "\n";

    for (User* user: users_) { // write each user to file
        file << user->getId() << "\n";
        file << "\t" << user->getName() << "\n";
        file << "\t" << user->getYear() << "\n";
        file << "\t" << user->getZip() << "\n" << "\t";

        for (int i: user->getFriends()) { //This is for the friends of the user
            file << i << " ";
        }
        file << "\n";
    }

    return 0;
}

//pre: none
//post: returns the number of users in the network
int Network::numUsers() {
    return users_.size();
}

//pre: id of a user
//post: Will return the pointer to the user with that id
User* Network::getUser(int id) {
    for(User* user: users_) {
        if(user->getId() == id) {
            return user;
        }
    }
    std::cout << "There is no user with that id" << std::endl;
    return NULL;
}

//pre: Ids from and to
//post: Finds the shortest distance away from the user to another user
std::vector<int> Network::shortestPath(int from, int to) {
    std::queue<int> q; //Initialize vectors and queue
    std::vector<bool> visited (numUsers(), 0);
    std::vector<int> previous(numUsers(), -1);

    visited[from] = true;
    q.push(from);

    while(q.size() > 0) { 
        int current = q.front();
        q.pop(); //Iterate through queue looking at friends of different users
        for(auto neighbor : getUser(current)->getFriends()) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
                previous[neighbor] = current;
            }
        }
    }

    std::vector<int> path;
    int current = to;
    while(current != -1) { //Establish a path
        path.push_back(current);
        current = previous[current];
    }

    if(path.back() != from) { //If no path exists
        return {};
    }

    std::reverse(path.begin(), path.end()); //Reverse and return path
    return path;
}

//pre: Ids from, to, and distance
//post: finds users the select number of distance away from the user. 
std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    std::queue<int> q; //This method is the same as above apart from the level variable
    std::vector<bool> visited (numUsers(), 0);
    std::vector<int> previous(numUsers(), -1);
    std::vector<int> level(numUsers(), 0);

    visited[from] = true;
    q.push(from);

    while(q.size() > 0) {
        int current = q.front();
        q.pop();

        if(level[current] == distance && current != from) { //If a user is found at the specific distance
            to = current;

            std::vector<int> path; //Establish the path using cur
            int cur = to;
            while(cur != -1) {
                path.push_back(cur);
                cur = previous[cur];
            }

            std::reverse(path.begin(), path.end());
            return path;
        }
        for(auto neighbor : getUser(current)->getFriends()) {
            if(!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
                previous[neighbor] = current;
                level[neighbor] = level[current] + 1; //Increment level of the neighbor
            }
        }
    }

    to = -1; //If there is no user found
    return {};
}

//pre: Id of a user, and a score
//post: This method finds friends with the most amount of mutual friends with the user given. Returns a list of friends found.
std::vector<int> Network::suggestFriends(int who, int& score) {
    std::set<int> directFriends = getUser(who)->getFriends();
    std::map<int, int> scores; //map of scores
    score = 0;

    for(int buddy: directFriends) { //buddy is direct friend
        User* friendUser = getUser(buddy);
        if(!friendUser) continue;

        for(int buddysFriend: friendUser->getFriends()) { //Look through buddys friends (friends of friends)
            if(buddysFriend == who) continue;
            if(directFriends.count(buddysFriend)) continue;

            scores[buddysFriend]++;
            if(scores[buddysFriend] > score) {
                score = scores[buddysFriend];
            }
        }
    }

    std::vector<int> suggestions;
    for(auto& pair: scores) { //Create our suggestions based on scores
        if(pair.second == score) {
            suggestions.push_back(pair.first);
        }
    }

    return suggestions;
}

//pre: none
//post: This method counts how many groups of users we have. Groups are users who are connected to each other, but aren't connected
//to another group of users
std::vector<std::vector<int> > Network::groups() {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(users_.size(), false);

    for(int source = 0; source < users_.size(); ++source) {
        if(visited[source]) continue;

        std::stack<int> stak;
        std::vector<int> component;

        visited[source] = true;
        stak.push(source);

        while(!stak.empty()) { //Using stack, go until its empty
            int current = stak.top();
            stak.pop();
            component.push_back(current);

            for(int neighbor: users_[current]->getFriends()) { //Iterate through neighbors
                if(!visited[neighbor]) {
                    visited[neighbor] = true;
                    stak.push(neighbor);
                }
            }
        }

        components.push_back(component); //components holds the group we just looked at
    }

    return components;
}

//pre: owner ID, message, likes, isIncoming, author's name, and the publicity.
//post: adds a post to the user in the network.
void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic) {
    int count = 0;
    for(User* user: users_) {
        count += user->getPosts().size(); //Get amount of posts in database to assign next ID
    }

    if(!isIncoming) { //Based on isIncoming, add the post
        Post* post = new Post(count, ownerId, message, likes);
        getUser(ownerId)->addPost(post);
    } else {
        IncomingPost* post = new IncomingPost(count, ownerId, message, likes, isPublic, authorName);
        getUser(ownerId)->addPost(post);
    }
}

//pre: owner ID, howMany posts, publicity
//post: returns a string of the most recent posts of the user depending on publicity
std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic) {
    User* user = getUser(ownerId);
    if(user == nullptr) {
        return ""; //Make sure user exists
    }
    return user->getPostsString(howMany, showOnlyPublic); //Call user function
}

//pre: file name
//post: reads post from a file
int Network::readPosts(char* fname) {
    std::ifstream file(fname);
    if(!file.is_open()) {
        return -1;
    }

    int numPosts;
    file >> numPosts;
    file.ignore(); //Go to next line

    for(int i = 0; i < numPosts; i++) {
        int messageId, ownerId, likes;
        std::string message, line, visibility, author;

        file >> messageId; //Get each line from file in order
        file.ignore();

        std::getline(file, message);
        message = message.substr(1);

        std::getline(file, line);
        ownerId = stoi(line.substr(1));

        std::getline(file, line);
        likes = stoi(line.substr(1));

        std::getline(file, visibility);
        if(!visibility.empty()) {
            visibility = visibility.substr(1);
        }

        std::getline(file, author);
        if(!author.empty()) {
            author = author.substr(1);
        }

        if(visibility.empty() && author.empty()) { //Ordinary post
            Post* post = new Post(messageId, ownerId, message, likes);
            getUser(ownerId)->addPost(post);
        } else { //Incoming Post
            bool isPublic = (visibility == "public");
            IncomingPost* post = new IncomingPost(messageId, ownerId, message, likes, isPublic, author);
            getUser(ownerId)->addPost(post);
        }
    }

    return 0;
}

//pre: file name
//post: writes post to a file
int Network::writePosts(char* fname) {
    std::ofstream file(fname);
    if(!file.is_open()) {
        return -1;
    }

    std::vector<Post*> allPosts;
    for(User* user: users_) { //Put allposts into the a vector
        std::vector<Post*> posts = user->getPosts();
        allPosts.insert(allPosts.end(), posts.begin(), posts.end());
    }

    std::sort(allPosts.begin(), allPosts.end(), [](Post* a, Post* b) { //Sort all posts by message ID
        return a->getMessageId() < b->getMessageId();
    });

    file << allPosts.size() << std::endl; //Print the amount of posts we have to file

    for(Post* post: allPosts) { //Put all of these posts into the file
        file << post->getMessageId() << std::endl;
        file << "\t" << post->getMessage() << std::endl;
        file << "\t" << post->getOwnerId() << std::endl;
        file << "\t" << post->getLikes() << std::endl;

        std::string visibility = post->getIsPublic() ? "public" : "private";
        std::string author = post->getAuthor();

        if(author.empty()) {
            file << "\t\n\t\n";
        } else {
            file << "\t" << visibility << std::endl;
            file << "\t" << author << std::endl;
        }
    }

    file.close();
    return 0;
}