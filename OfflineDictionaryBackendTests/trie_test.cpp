#include "pch.h"
#include "../OfflineDictionaryBackend/trie.hpp"
using namespace offline_dictionary_backend;

TEST(TrieTest, Test_1)
{ 
  std::string str = "testogramm";
  trie<std::string, char, int> l;
  l.insert(str, 5);
  auto result = l.find_template("testogramm");
  EXPECT_EQ(result.size(), 1);
}

TEST(TrieTest, Test_2)
{
	trie<std::string, char, int> l;
	l.insert("testogram", 1);
	l.insert("palaroid", 2);
	l.insert("testo", 3);
	l.insert("murmur", 4);
	auto result = l.find_template("testo");
	EXPECT_EQ(result.size(), 2);
	EXPECT_EQ(result[0].first, "testo");
	EXPECT_EQ(result[1].first, "testogram");

	result = l.find_template("mur");
	EXPECT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].first, "murmur");

	result = l.find_template("r");
	EXPECT_EQ(result.size(), 0);
}

TEST(TrieTest, Test_3)
{
	trie<std::string, char, int> l;
	l.insert("testogram", 1);
	l.insert("palaroid", 2);
	l.insert("testo", 3);
	l.insert("murmur", 4);
	int res = 0;
	auto result = l.find_exact("testo", res);
	EXPECT_EQ(result, true);
	EXPECT_EQ(res, 3);
	result = l.find_exact("testogr", res);
	EXPECT_EQ(result, false);

	result = l.find_exact("testogram", res);
	EXPECT_EQ(result, true);
	EXPECT_EQ(res, 1);
}