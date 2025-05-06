# Trie Data Structure for Text Prediction
This code implements a trie data structure. You can add words to a trie, then you can use the trie to get suggestions based on the words you've already added to it. If a word does not exist in the trie you will receive a message that the word you entered is either misspelled or does not exist in the trie.

A trie stores words by assigning each letter in the word to a node. The root node of the trie is a space character, " ". The root node then has children nodes for the first letters in words. And those nodes each have children nodes for the next letter in the word. Each node has a child node containing the word's letters until the word is complete. As you look down a branch in a trie you will spell words.

<u>Example:</u>
Suppose you want to add the word "bit" to a trie. The root node contains a space character, but it will have a child node that contains the letter "b". That child node will itself have a child node that contains the letter "i". And that child node will its own child node that contains the letter "t".

## How to run code
Run the following commands in your terminal to build the project and run the code. If it's successful you should see a list of options printed out in the terminal.

mkdir build
cd build
cmake ..
make
./text-prediction-trie

Once the code runs you will be prompted in the console to enter a number from 1 to 4 to perform actions with the trie.

## Link to Video Demo of Trie
https://o365coloradoedu-my.sharepoint.com/:v:/g/personal/scwi7689_colorado_edu/ES8EbYP91lxLhLsPm_WiHlwBB-_xSzeMs4vN_ssPY07SdQ?e=hItLUv
