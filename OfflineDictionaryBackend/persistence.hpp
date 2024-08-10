#pragma once
#include "word.hpp"
#include "helpers.hpp"

namespace offline_dictionary_backend
{
	class monolith_persistence
	{
	public:
		virtual void load(std::string path, trie<std::string, char, std::shared_ptr<word>>& trie_to_store)
		{
			std::ifstream input(path);
			std::string line;
			/*while (std::getline(input, line, entity_delim))
			{
				auto sections = helpers::split(line, section_delim);
				helpers:: to_lower(sections[0]);
				auto new_word = std::make_shared<word>(sections[0], trie_to_store);
				trie_to_store.insert(new_word->stored_word, new_word);

				new_word->translations = helpers::split(sections[1], record_delim);
				new_word->examples = helpers::split(sections[2], record_delim);
				auto related_words = helpers::split(sections[3], record_delim);
				for (int i = 0; i < related_words.size(); ++i)
				{
					helpers::to_lower(related_words[i]);
					auto related_word = std::make_shared<word>(related_words[i], trie_to_store);
					if (!trie_to_store.find_exact(related_words[i], related_word))
					{
						trie_to_store.insert(related_words[i], related_word);
					}
					new_word->related_words.push_back(related_word);
				}
			}*/
		}
	};

	class partitioned_persistance
	{	
	protected:
		virtual persistable_ptr parse(std::ifstream& input, std::string_view w) = 0;

	public:
		virtual persistable_ptr load(std::string_view path, std::string_view w)
		{
			std::string filename{w[0]};
			if (w.size() >= 2)
				filename += w[1];
			if (path.back() == '\\' || path.back() == '//')
				filename = path.data() + filename;

			std::ifstream file(filename);
			return parse(file, w);
		}
	};

	class vector_persistance: public partitioned_persistance
	{
	protected:
		persistable_ptr parse(std::ifstream& input, std::string_view w) override
		{
			std::string line;
			while (std::getline(input, line, entity_delim))
			{
				auto sections = helpers::split(line, section_delim);
				helpers::to_lower(sections[0]);
				if (sections[0] != w)
					continue;

				return std::make_shared<persistable_vector>(helpers::split(sections[1], record_delim));
			}
			return nullptr;
		}
	};

	class str_map_persistance : public partitioned_persistance
	{
	protected:
		persistable_ptr parse(std::ifstream& input, std::string_view w) override
		{
			std::string line;
			std::map<std::string, std::vector<std::string>> result;
			while (std::getline(input, line, entity_delim))
			{
				auto sections = helpers::split(line, section_delim);
				helpers::to_lower(sections[0]);
				if (sections[0] != w)
					continue;
				for (int i = 1; i < sections.size(); ++i)
				{
					auto record = helpers::split(sections[i], record_delim);
					for (int j = 0; j < record.size(); j += 2)
					{
						if (!result.contains(record[j]))
							result[record[j]] = std::vector<std::string>();
						result[record[j]].push_back(record[j + 1]);
					}
				}
				//return result;
				return std::make_shared<persistable_str_map>(std::move(result));
			}
			return nullptr;
		}
	};

	class string_persistance: public partitioned_persistance
	{
	protected:
		persistable_ptr parse(std::ifstream& input, std::string_view w) override
		{
			std::string line;
			while (std::getline(input, line, entity_delim))
			{
				auto sections = helpers::split(line, section_delim);
				helpers::to_lower(sections[0]);
				if (sections[0] != w)
					continue;

				return std::make_shared<persistable_string>(std::move(sections[1]));
			}
			return nullptr;
		}
	};

}