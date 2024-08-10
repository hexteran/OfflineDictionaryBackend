#pragma once
#include "persistence.hpp"
#include "file_manager.hpp"

namespace offline_dictionary_backend
{
	class dictionary
	{
	private:
		std::string _data_path;
		std::vector<std::string> _words;
		
		languages _language;

		word_trie _trie;
		str_map_persistance _descr_pers;
		vector_persistance _exam_pers;
		vector_persistance _trans_pers;

	public:
		dictionary(const dictionary&) = delete;
		dictionary(const dictionary&&) = delete;
		dictionary(std::string_view data_path, languages language): 
			_data_path(data_path), _language(language)
		{
			std::string filename = std::string(data_path) + std::string("\\words.txt");
			std::ifstream file(filename);
			std::string line;
			while (std::getline(file, line))
			{
				register_word(line);
			}
		}

		void register_word(const std::string& new_word)
		{
			auto w = std::make_shared<word>(new_word, int(_words.size()), _language);
			_trie.insert(new_word, w);
		}

		void load_word_details(word_ptr word)
		{
			word->examples = std::static_pointer_cast<persistable_vector>(_exam_pers.load(_data_path + "\\examples\\", word->stored_word));
			word->translations = std::static_pointer_cast<persistable_vector>(_exam_pers.load(_data_path + "\\translations\\", word->stored_word));
			word->description = std::static_pointer_cast<persistable_str_map>(_descr_pers.load(_data_path + "\\descriptions\\", word->stored_word));
		}

		const word_ptr load_word_details(const std::string& word)
		{
			word_ptr result;
			if (!_trie.find_exact(word, result))
			{
				return nullptr;
			}

			result->examples = std::static_pointer_cast<persistable_vector>(_exam_pers.load(_data_path + "\\examples\\", word));
			result->translations = std::static_pointer_cast<persistable_vector>(_exam_pers.load(_data_path + "\\translations\\", word));
			result->description = std::static_pointer_cast<persistable_str_map>(_descr_pers.load(_data_path + "\\descriptions\\", word));
			return result;
		}

		void remove_word_details(word_ptr word)
		{
			word->examples = nullptr;
			word->translations = nullptr;
			word->description = nullptr;
		}

		void save_word_in_file(std::string theme, word_ptr w, int descr_index, std::set<int> transl_indices, std::set<int> exampl_indices)
		{
			file_manager manager(_data_path + "\\saved\\" + theme + ".csv", "Theme;Word;Translation;Image;Definition");
			load_word_details(w);
			std::string record = theme + ';';
			if (w->description != nullptr)
			{
				auto& descr_val = w->description->value;
				for (int i = 0; i < descr_val["type"].size(); ++i)
				{
					if (descr_index == i + 1)
					{
						if (descr_val["article"][i] != "")
							record += descr_val["article"][i] + " ";
						record += w->stored_word + ';';
					}
				}
			}
			if (w->translations != nullptr)
			{
				auto& trans_val = w->translations->values;
				for (int i = 0; i < trans_val.size(); ++i)
				{
					if (transl_indices.empty() || transl_indices.contains(i + 1))
					{		
						if (i != trans_val.size() - 1)
							record += trans_val[i] + ", ";
						else
							record += trans_val[i];
					}
				}
			}
			record += ";";
			if (w->examples != nullptr)
			{
				auto& exam_val = w->examples->values;
				for (int i = 0; i < exam_val.size(); ++i)
				{
					if (exampl_indices.empty() || exampl_indices.contains(i + 1))
					{
						record += exam_val[i] + " | ";
					}
				}
			}
			if (!manager.add_unique_record(record))
				std::cout << "\nThis word is already included\n";
		}

		std::vector<word_ptr> find_words(const std::string& word)
		{
			auto words = _trie.find_template(word);
			std::vector<word_ptr> result;
			for (auto& word : words)
				result.push_back(word.second);
			
			return result;
		}

	};
};