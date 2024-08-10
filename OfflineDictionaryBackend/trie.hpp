#pragma once
#include "DTOs.hpp"

namespace offline_dictionary_backend
{
	template<class T>
	concept element_iterable = requires(std::ranges::range_value_t<T> val)
	{
		val.begin();
		val.end();
	};

	template<class R, class V, class PL>
	//requires element_iterable<R>
	class trie
	{
		struct trie_node
		{
			V value;
			std::map <V, std::shared_ptr<trie_node>> children;
			PL payload;
			bool is_full_word = false;
		};
		using trie_node_ptr = std::shared_ptr<trie_node>;

		std::shared_ptr<trie_node> _root{ std::make_shared<trie_node>() };

	public:
		void insert(const R& word, const PL& payload)
		{
			if (word.size() == 0)
				return;

			std::shared_ptr<trie_node> cursor = _root;
			for (auto symbol : word)
			{
				auto iter = cursor->children.find(symbol);
				if (iter == cursor->children.end())
				{
					auto new_element = std::make_shared<trie_node>(trie_node{ .value = symbol });
					cursor->children.insert({ symbol, new_element });
					cursor = new_element;
				}
				else
					cursor = iter->second;
			}

			cursor->is_full_word = true;
			cursor->payload = payload;
		};

		bool find_exact(const R& word, PL& payload) const
		{
			std::shared_ptr<trie_node> cursor = _root;
			for (auto& symbol : word)
			{
				auto iter = cursor->children.find(symbol);
				if (iter == cursor->children.end())
					return false;
				cursor = iter->second;
			}
			if (!cursor->is_full_word)
				return false;

			payload = cursor->payload;
			return true;
		}

		std::vector<std::pair<R, PL>> find_template(const R& word) const
		{
			std::vector<std::pair<R, PL>> result;
			std::vector<V> current_word;
			std::function<void(trie_node_ptr)> dfs;
			dfs = [&result, &dfs, &current_word](trie_node_ptr cursor)
			{
				current_word.push_back(cursor->value);
				if (cursor->is_full_word)
				{
					R new_word{ ++current_word.begin(), current_word.end() };
					result.push_back(std::make_pair(new_word, cursor->payload));
				}
				for (auto& [symbol, child_ptr] : cursor->children)
					dfs(child_ptr);
				current_word.pop_back();
			};
			auto cursor = _root;
			for (auto symbol : word)
			{
				current_word.push_back(cursor->value);
				auto iter = cursor->children.find(symbol);
				if (iter == cursor->children.end())
					return result;
				cursor = iter->second;
			}
			dfs(cursor);
			return result;
		}
	};
}