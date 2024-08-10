#pragma once
#include "trie.hpp"

namespace offline_dictionary_backend
{
	class word
	{
	public:
		const int id;
		const std::string stored_word;
		const languages language; 
		persistable_vector_ptr translations;
		persistable_vector_ptr examples;
		persistable_str_map_ptr description;

	public:
		word(std::string_view w, int id, languages lang) :
			stored_word(w), id(id), language(lang)
		{

		}
	};

	using word_ptr = std::shared_ptr<word>;
	using word_trie = trie<std::string, char, word_ptr>;
}