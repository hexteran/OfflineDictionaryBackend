#pragma once
#include "definitions.hpp"

namespace offline_dictionary_backend
{
	
	class helpers
	{
	public:
		class cache
		{
			const int _size;
			std::list<std::pair<std::string, const std::shared_ptr<std::vector<std::string>>>> _storage;
		public:
			cache(const int size) : _size(size) {}

			void swap(decltype(_storage.begin()) a, decltype(_storage.begin()) b)
			{
				auto temp = b;
				b = a;
				a = temp;
			}

			const decltype(_storage.begin()) begin()
			{
				return _storage.begin();
			}

			const decltype(_storage.end()) end()
			{
				return _storage.end();
			}

			const decltype(_storage.begin()) find(const std::string& to_find)
			{
				auto pred = [&to_find](decltype(_storage.back())& elem) {return elem.first == to_find; };
				auto iter = std::find_if(_storage.begin(), _storage.end(), pred);
				return iter;
			}

			void push_element(const std::string& to_push, std::vector<std::string>& result)
			{
				auto iter = find(to_push);
				if (iter != end())
				{
					swap(_storage.begin(), iter);
					return;
				}

				if (_storage.size() == _size)
					_storage.pop_front();

				_storage.push_back(std::make_pair(to_push, std::make_shared<std::vector<std::string>>(result)));
			}
		};

		static std::vector<std::string> split(std::string& str, char delim)
		{
			std::stringstream ss(str);
			std::string line;
			std::vector<std::string> result;
			while (std::getline(ss, line, delim))
			{
				result.push_back(line);
			}
			return result;
		}

		static void to_lower(std::string& str)
		{
			for (int i = 0; i < str.size(); ++i)
				str[i] = std::tolower(str[i]);
		}
	};

};
