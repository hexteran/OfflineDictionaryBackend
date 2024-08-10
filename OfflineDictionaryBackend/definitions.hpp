#pragma once
#include <memory>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <utility>
#include <vector>
#include <ranges>
#include <functional>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <filesystem>

namespace offline_dictionary_backend
{
	constexpr char entity_delim = 0x1;
	constexpr char section_delim = 0x2;
	constexpr char record_delim = 0x3;

	enum class type_persistable
	{
		none,
		word,
		examples,
		description,
		translations,
	};

	enum class languages
	{
		none, 
		dutch,
		english
	};
}