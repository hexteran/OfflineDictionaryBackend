#pragma once
#include "pch.h"
#include "../OfflineDictionaryBackend/dictionary.hpp"
using namespace offline_dictionary_backend;
using namespace std;
TEST(DictionaryTest, Test_1)
{
	dictionary dict("C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackend\\data", languages::dutch);
	auto ptr = dict.load_word_details("gaan");
	
	EXPECT_EQ(15, ptr->translations->values.size());
	EXPECT_FALSE(nullptr == ptr);
}
