#include <iostream>
#include "trie.h"
using namespace std;

void print_menu(int &selection) {
    cout << endl;
    cout << "Enter one of the following options (1-4):" << endl;
    cout << "1 Add word to trie" << endl;
    cout << "2 Get suggestions" << endl;
    cout << "3 Print trie" << endl;
    cout << "4 Exit" << endl << endl;
    cout << "Selection: ";
    cin >> selection;
    cout << endl;
}

// Credit to Geeksforgeeks, converts uppercase letters in string to lowercase
string to_lower_case(string word) {
    for(auto& x : word) {
        x = tolower(x);
    }
    return word;
}

int main() {
    trie t;
    int selection = 0;

    while(selection != 4) {
        print_menu(selection);

        switch(selection) {
            case 1: {
                cout << "Enter new word (only letters): ";
                string text;
                cin >> text;
                cout << endl;
                t.insert_word(to_lower_case(text));
                break;
            }
            case 2: {
                cout << "Enter text for suggestions: ";
                string text;
                cin >> text;
                cout << endl;
                t.print_suggestions(text);
                cout << endl;
                break;
            }
            case 3:
                cout << "Trie:" << endl;
                t.print_trie();
                cout << endl;
                break;
            case 4:
                break;
            default:
                cout << "Please enter a valid option." << endl;
                break;
        }
    }
    return 0;
}