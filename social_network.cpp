#include "user.h"
#include "network.h"
#include <set>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//pre: none
//post: will display the menu of options
void displayMenu() {
    cout << "Menu options:" << endl;
    cout << "Option 1: Add a user:" << endl;
    cout << "Option 2: Create a connection" << endl; 
    cout << "Option 3: Delete a connection" << endl; 
    cout << "Option 4: Write to file" << endl;
    cout << "Option 5: Get most recent posts from a user" << endl;
    cout << "Option 6: Quit the program" << endl;
}

//pre:none
//post: will get the user input separate by spaces and return a vector of the words
vector<string> getInput() {
    string line;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Include to ignore any active current line so getline can properly wait for input
    getline(cin, line);

    istringstream iss(line);

    vector<string> info;
    string word;

    while(iss >> word) { // Push back user input into vector
        //cout << word << endl;
        info.push_back(word);
    }

    return info;
}

int main(int argc, char *argv[]) {
    Network network;
    bool isFinished = false; //While loop condition in order to terminate the program
    if(argc != 3) { //Arg must be 2 since we are running this program with an initial file
        cout << "Users and posts files are required" << endl;
        return 0;
    } else { //read from the files given
        network.readUsers(argv[1]);
        network.readPosts(argv[2]);
        cout << network.numUsers() << endl; //Debugging purposes
    }

    while(!isFinished) {
        displayMenu();
        cout << "Enter any option number:" << endl;
        int option;
        cin >> option; //Get option number
        if(option == 1) {
            cout << "Enter your first and last name, birth year, and zip code all on the same line separated by spaces: " << endl;
            vector<string> info = getInput();

            if(info.size() != 4) {
                cout << "Invalid entry. Returning to menu." << endl;
            } else {
                try {
                    string name = info[0] + " " + info[1]; // We accept only first and last name so info[0] and info[1] must be first and last name
                    int year = stoi(info[2]); // num -2 and num -1 must be birth year and zip code
                    int zip = stoi(info[3]);

                    User* user = new User(network.numUsers(), name, year, zip, set<int> ()); //Initialize new user
                    network.addUser(user);
                    cout << user->getId() << endl;
                    
                } catch(...) {
                    cout << "Year and zip must be a numbers. Name must be letters. Returning to menu." << endl;
                }
            }
        } else if(option == 2) {
            cout << "Enter your name and the person you want to add:" << endl;
            vector<string> info = getInput();

            string name1 = info[0] + " " + info[1]; //We only accept two first and last names 
            string name2 = info[2] + " " + info[3];

            network.addConnection(name1, name2);
            for(int x: network.getUser(0)->getFriends()) {
                //cout << x << " "; //Debugging purposes
            }
            cout << endl;
        } else if(option == 3) {
            cout << "Enter your name and the person you want to delete:" << endl;
            vector<string> info = getInput();

            string name1 = info[0] + " " + info[1]; // Same concept as above
            string name2 = info[2] + " " + info[3];

            network.deleteConnection(name1, name2);
        } else if(option == 4) {
            cout << "Enter the name of the file you want to write to: ";
            char name[100]; //Allocate memory to the amount of chars a file name can have
            cin >> name;

            network.writeUsers(name);
        } else if(option == 5) {
            cout << "Enter the name and the number of posts you want to get from this user: ";
            try {
                vector<string> info = getInput();
                string name = info[0] + " " + info[1];
                cout << network.getPostsString(network.getId(name), stoi(info[2]), true) << endl;
            } catch(...) {
                cout << "First and last name followed by a number please. Returning to menu" << endl;
            }
        } else { //Any other option number = quit program
            cout << "Quitting Program" << endl;
            isFinished = true;
        }
    }

    return 0;
}