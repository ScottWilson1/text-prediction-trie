#include "trie.h"
#include <iostream>
using namespace std;

trie::trie() {
    root = new trie_node;
    root->data = " ";
    root->child_count = 0;
    root->is_word_end = false;
    for(int i = 0; i < 26; i++) {
        root->children[i] = nullptr;
    }
}

trie::~trie() {
}

trie_node* trie::init_node(string data) {
    trie_node* ret(new trie_node);
    ret->data = data;
    ret->child_count = 0;
    for(int i = 0; i < sizeof(ret->children); i++) {
        ret->children[i] = nullptr;
    }
    ret->is_word_end = false;
    return ret;
}

void trie::insert_word(string word) {
    bool word_in_trie = false;
    string remaining_letters = word;
    trie_node* current_node = check_for_matching_nodes(root, word, remaining_letters, word_in_trie);
    if(word_in_trie == false) {
        add_nodes(current_node, word, remaining_letters);
    }
}

trie_node* trie::check_for_matching_nodes(trie_node* node, string word, string &remaining_letters, bool &word_in_trie) {
    if(node->child_count > 0) {

        //creates string variable of the first letter from remaining letters
        string letter(1, remaining_letters[0]);

        //loops through children in node and compares their data values to the letter variable
        for(int i = 0; i < node->child_count; i++) {
            if(node->children[i]->data == letter) {

                //dermines if the node of the last letter of the passed in word is already a word end
                if(remaining_letters.length() == 1) {
                    if(node->children[i]->is_word_end == true) {
                        cout << word <<" already exists in trie" << endl;
                    }
                    //sets is_word_end on last node of word to true
                    else {
                        node->children[i]->is_word_end = true;
                        cout << word << " added" << endl;
                    }
                    //setting word_in_trie to true avoids running the add_nodes method because
                    //the word has already been added to the trie
                    word_in_trie = true;
                    return node->children[i];
                }

                //if there is more than one letter in remaining_letters, the first letter is removed and it is
                //passed in to this method to run again recursively
                remaining_letters = remaining_letters.substr(1);
                return check_for_matching_nodes(node->children[i], word, remaining_letters, word_in_trie);
            }
        }
        return node;
    }
    return node;
}

void trie::add_nodes(trie_node* node, string word, string remaining_letters) {
    trie_node* current_node = node;
    for(int j = 0; j < remaining_letters.length(); j++) {
        string letter(1, remaining_letters[j]);
        trie_node* child_node = init_node(letter);
        if(j == remaining_letters.length() - 1) {
            child_node->is_word_end = true;
        }
        current_node->children[current_node->child_count] = child_node;
        current_node->child_count += 1;
        current_node = child_node;
    }
    cout << word << " added" << endl;
}

void trie::print_trie() {
    print_trie_recur(root);
}

void trie::print_trie_recur(trie_node* node) {
    cout << "node value: ";
    if(node->data == " ") {
        cout << "\" \"" << endl;
    } else {
        cout <<node->data << endl;
    }
    if(node->child_count > 0) {
        cout << "children: ";
        for(int i = 0; i < node->child_count; i++) {
            cout << node->children[i]->data << " ";
        }
        cout << endl;
        for(int j = 0 ; j < node->child_count; j++) {
            print_trie_recur(node->children[j]);
        }
    }
}

void trie::print_suggestions(string word) {
    trie_node* node = find_current_node(root, word);
    if(node != nullptr) {
        find_words(node, word);
    }
    else {
        cout << word << " is misspelled or doesn't exist in trie" << endl;
    }
}

trie_node* trie::find_current_node(trie_node* node, string word) {
    string letter(1, word[0]);
    if(node->child_count > 0) {
        for(int i = 0; i < node->child_count; i++) {
            if(node->children[i]->data == letter) {
                if(word.length() == 1) {
                    return node->children[i];
                }
                string remaining_letters = word.substr(1);
                return find_current_node(node->children[i], remaining_letters);
            }
        }
        return nullptr;
    } else {
        return nullptr;
    }
}

void trie::find_words(trie_node* node, string word) {
    if(node->is_word_end == true) {
        cout << word << endl;
    }
    if(node->child_count > 0) {
        for(int i = 0; i < node->child_count; i++) {
            find_words_recur(node->children[i], word);
        }
    }
}

void trie::find_words_recur(trie_node* node, string word) {
    word += node->data;
    if(node->is_word_end == true) {
        cout << word << endl;
    }
    if(node->child_count > 0) {
        for(int i = 0; i < node->child_count; i++) {
            find_words_recur(node->children[i], word);
        }
    }
}

void trie::remove_word(string word) {
    bool word_removed = false;
    remove_word_recur(root, word, word_removed);
}

void trie::remove_word_recur(trie_node* node, string word, bool &word_removed) {
    if(word_removed == true) {
        return;
    }
    string letter(1, word[0]);
    if(node->child_count > 0) {
        if(word.length()==1) {
            node->is_word_end = false;
            word_removed = true;
            return;
        }
    }
    if(node->child_count > 0) {
        for(int i = 0; i < node->child_count; i++) {
            if(node->children[i]->data == letter) {
                string remaining_letters = word.substr(1);
                remove_word_recur(node->children[i], remaining_letters, word_removed);
                if(node->children[i]->child_count == 0) {
                    delete node->children[i];
                    node->children[i] = nullptr;
                    node->child_count -= 1;
                    if(node->child_count > 0) {
                        children_shift_left(node, i);
                    }
                    break;
                } else {
                    node->children[i]->is_word_end = false;
                }
            } else {
                cout << word << "does not exist in trie" << endl;
            }
        }
    }
}

void trie::children_shift_left(trie_node* &node, int pos) {
    for(int i = pos; i < node->child_count; i++) {
        trie_node* temp = node->children[i + 1];
        node->children[i + 1] = node->children[i];
        node->children[i] = temp;
    }
}