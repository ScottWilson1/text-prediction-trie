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

class trie {
public:
    trie();
    ~trie();
    void insert_word(string word);
    void print_trie();
    void print_trie_recur(trie_node* node);
    void print_suggestions(string word);

private:
    trie_node* root;
    trie_node* init_node(string data);
    trie_node* check_for_matching_nodes(trie_node* node, string word, string &remaining_letters, bool &word_in_trie);
    void add_nodes(trie_node*, string word, string remaining_letters);
    trie_node* find_current_node(trie_node* node, string word);
    void find_words(trie_node* root, string word = "");
    void find_words_recur(trie_node* node, string word);
};

#endif // trie_h__