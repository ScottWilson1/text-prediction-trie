#ifndef trie_h__
#define trie_h__

#include <memory>
#include <string>
#include <vector>

using namespace std;

// trie_node is the trie node structure.
struct trie_node {
  string data;
  int child_count;
  trie_node* children[26];
  bool is_word_end;
};

//trie
//
//The root node contains the string of a space character, " ".
//Off of the root are children nodes that contain letters. The
//children nodes link to other children nodes that also contain letters.
//As you work your way down branches of the trie the letters in the
//nodes spell words.
class trie {
public:

    //The construction initializes the root node, which contains a space
    //character in its data variable.
    trie();

    //deconsructor
    ~trie();

    //Inserts words into the trie. The method takes in a string and adds
    //nodes to the trie for each letter in the string, assuming the letter
    //node doesn't already exist in the trie branch.
    void insert_word(string word);

    //A rudimentary print out of the trie. It lists a node's letter
    //then lists the children of that node. It continues like that through
    //all nodes in the trie. This method uses a depth-first traversal of the
    //trie, so you'll see the print out spelling out whole words before moving on
    //to the next word. This method only sets the initial node to the root node
    //and calls the recursive print trie method.
    void print_trie();

    //This is where most of the logic for the tree print method is. 
    void print_trie_recur(trie_node* node);

    //This method takes in a string navigates down the trie to the last letter
    //node of the word entered by the user. From there, it searches down the nodes
    //stemming off of that node and combines characters to form words and prints
    //them in the console.
    void print_suggestions(string word);

    //sets the word_removed variable to false and calls the remove_word_recur with the previously
    //mentioned variable as well as the trie root passed in.
    void remove_word(string word);

private:
    //The initial node of the trie, always contains a string of the space character, " ".
    trie_node* root;

    //Creates a new node and intializes the node's data value with the string passed in
    trie_node* init_node(string data);

    //Helper method used by insert_word to check the nodes of the trie to see if they match
    //the lettes of the passed in word. If all the nodes for the word already exist in the
    //trie it sets the is_word_end variable on the last node to true. If that node is already
    //a word end then it prints a message in the console that the word already exists in the 
    //trie.
    trie_node* check_for_matching_nodes(trie_node* node, string word, 
        string &remaining_letters, bool &word_in_trie);

    //Helper method used by insert_word. Once the last matching node has been navigated to,
    //this method creates new nodes for each remaining letter of the passed in word
    void add_nodes(trie_node*, string word, string remaining_letters);

    //Helper method used by print_suggestions. Navigates the trie to find the node that
    //corresponds to the last letter of the passed in word. Returns that node as a trie_node
    //pointer.
    trie_node* find_current_node(trie_node* node, string word);

    //Helper method used by print_suggestions. Once the last node of the passed in word is
    //found, it prints to the console all the complete words in the tree that stem off the
    //current node.
    void find_words(trie_node* root, string word = "");

    //This method is almost identical to find_words, but it builds the word string suggestions
    //that are printed in the console.
    void find_words_recur(trie_node* node, string word);

    //Recursively navigates the trie for the word to be removed. If that word is part of another
    //word, then only the is_word_end on the last node of the word is set to false. If the word
    //to be removes has nodes that are not shared by any other words, those nodes are removed.
    void remove_word_recur(trie_node* node, string word, bool &word_removed);

    //When a node is removes from a node's children array, the elements of that array are shifted
    //to the left and the nullpointer value is shifted to the right.
    void children_shift_left(trie_node* &node, int pos);
};

#endif // trie_h__