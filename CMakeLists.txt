cmake_minimum_required(VERSION 3.10)
project(text-prediction-trie)
set(CMAKE_CXX_STANDARD 17)
add_executable(text-prediction-trie main.cpp trie.cpp)