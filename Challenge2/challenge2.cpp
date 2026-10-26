
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    vector<string> jokes;
    string line;

    // Open the file containing the jokes
    
ifstream file("Challenge2/randomJokes.txt");


    if (!file.is_open()) {
        cout << "Could not open randomJokes.txt" << endl;
        return 1;
    }

    // Read all the jokes from the file
    while (getline(file, line)) {
        if (!line.empty()) {
            jokes.push_back(line);
        }
    }

    file.close();

    // Check if the file contains jokes
    if (jokes.empty()) {
        cout << "No jokes found in the file." << endl;
        return 1;
    }

    // Make the jokes appear in random order
    srand(time(0));

    string command;

    cout << "Welcome to Alexa Joke Generator!" << endl;
    cout << "Type: Alexa, tell me a joke" << endl;
    cout << "Type quit to exit." << endl;

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, command);

        if (command == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }
        else if (command == "Alexa, tell me a joke") {

            // Pick a random joke
            int randomNumber = rand() % jokes.size();
            string joke = jokes[randomNumber];

            // Find where the question ends
            size_t position = joke.find('?');

            if (position != string::npos) {
                string question = joke.substr(0, position + 1);
                string answer = joke.substr(position + 1);

                cout << "\n" << question << endl;
                cout << "Press Enter to see the answer...";
                string wait;
                getline(cin, wait);

                cout << answer << endl;
            }
            else {
                cout << joke << endl;
            }
        }
        else {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}
