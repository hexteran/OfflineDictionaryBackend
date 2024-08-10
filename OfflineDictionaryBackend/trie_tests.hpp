#pragma once
#include <string>
#include "trie.hpp"

using namespace offline_dictionary_backend;

void test_add_one()
{
    std::string str = "testogramm";
    trie<std::string, char, int> l;
    l.insert(str, 5);
    std::cout << l.find_template(str).size();
}