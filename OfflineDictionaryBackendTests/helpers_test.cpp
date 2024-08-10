#include "pch.h"
#include "../OfflineDictionaryBackend/dictionary.hpp"
using namespace offline_dictionary_backend;
using namespace std;
TEST(HelpersTest, Test_1)
{
	helpers::cache cache(2);
	std::string test_string_1;
	vector<string> vt1{"1a", "2a", "3a"};
	vector<string> vt2{ "1b", "2b", "3b" };
	vector<string> vt3{ "1c", "2c", "3c" };
	cache.push_element("a", vt1);
	cache.push_element("b", vt1);
	cache.push_element("c", vt1);
	auto iter = cache.find("a");
	EXPECT_EQ(cache.end(), iter);
	iter = cache.find("b");
	EXPECT_EQ("b", iter->first);
	iter = cache.find("c");
	EXPECT_EQ("c", iter->first);
}
