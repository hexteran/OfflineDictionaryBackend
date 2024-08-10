#pragma once
#include "pch.h"
using namespace offline_dictionary_backend;

/*TEST(PersistenceTest, Test_1)
{
	std::string str = "testogramm";
	trie<std::string, char, std::shared_ptr<word>> l;
	persistence pers;
	pers.load("C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackendTests\\resources\\persistence_test_1.txt", l);
	std::shared_ptr<word> word_to_check;
	EXPECT_EQ(l.find_exact("testword", word_to_check), true);
	EXPECT_EQ(word_to_check->examples.size(), 3);
	EXPECT_EQ(word_to_check->related_words.size(), 2);
	EXPECT_EQ(l.find_exact("testwordtwo", word_to_check), true);
	EXPECT_EQ(word_to_check->examples.size(), 2);
	EXPECT_EQ(word_to_check->related_words.size(), 1);
	EXPECT_EQ(l.find_exact("testwordthree", word_to_check), true);
	EXPECT_EQ(l.find_exact("testwordfive", word_to_check), false);
}

TEST(PersistenceTest, Test_2)
{
	std::string str = "testogramm";
	trie<std::string, char, std::shared_ptr<word>> l;
	monolith_persistence pers;
	pers.load("C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackendTests\\resources\\persistence_test_2.txt", l);
	std::shared_ptr<word> word_to_check;
	EXPECT_EQ(l.find_exact("in", word_to_check), true);
	EXPECT_EQ(l.find_exact("ineens", word_to_check), false);
	EXPECT_EQ(l.find_exact("informatie", word_to_check), true);
	EXPECT_EQ(l.find_exact("hieronder", word_to_check), true);
}

TEST(PersistenceTest, Test_3)
{
	std::string str = "testogramm";
	trie<std::string, char, std::shared_ptr<word>> l;
	monolith_persistence pers;
	pers.load("C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackendTests\\resources\\persistence_test_3.txt", l);
	std::shared_ptr<word> word_to_check;
	EXPECT_EQ(l.find_exact("in", word_to_check), true);
	EXPECT_EQ(l.find_exact("ineens", word_to_check), false);
	EXPECT_EQ(l.find_exact("informatie", word_to_check), true);
}

TEST(PersistenceTest, Test_4)
{
	std::string str = "testogramm";
	trie<std::string, char, std::shared_ptr<word>> l;
	monolith_persistence pers;
	pers.load("C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackendTests\\resources\\persistence_test_4.txt", l);
	std::shared_ptr<word> word_to_check;
	EXPECT_EQ(l.find_exact("in", word_to_check), true);
	EXPECT_EQ(l.find_exact("beschaafde", word_to_check), true);
	EXPECT_EQ(l.find_exact("informatie", word_to_check), true);
}

TEST(PersistenceTest, Test_5)
{
	std::string str = "testogramm";
	trie<std::string, char, std::shared_ptr<word>> l;
	monolith_persistence pers;
	pers.load("C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackendTests\\resources\\persistence_test_5.txt", l);
	std::shared_ptr<word> word_to_check;
	EXPECT_EQ(l.find_exact("in", word_to_check), true);
	EXPECT_EQ(l.find_exact("beschaafde", word_to_check), true);
	EXPECT_EQ(l.find_exact("informatie", word_to_check), true);
}*/