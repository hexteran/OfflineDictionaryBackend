// OfflineDictionaryBackend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include "trie.hpp"
#include "dictionary.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
using namespace offline_dictionary_backend;
using namespace std;

dictionary* dict;

vector<string> split(string& str, char sep = ' ')
{
	stringstream ss(str);
	string line;
	vector<string> result;
	while (getline(ss, line, sep))
	{
		stringstream ss_no_space(line);
		string line_no_space;
		while (getline(ss_no_space, line_no_space, '\t'))
		{
			if (line_no_space != "")
				result.push_back(line_no_space);
		}
	}
	return result;
}

void eraseLines(int count) {
	if (count > 0) {
		std::cout << "\x1b[2K"; // Delete current line
		// i=1 because we included the first line
		for (int i = 1; i < count; i++) {
			std::cout
				<< "\x1b[1A" // Move cursor up one
				<< "\x1b[2K"; // Delete the entire line
		}
		std::cout << "\r"; // Resume the cursor at beginning of line
	}
}

void show_word_information(word_ptr w)
{
	system("CLS");
	cout << w->stored_word << "\n\n";
	dict->load_word_details(w);
	if (w->description != nullptr)
	{
		auto& descr_val = w->description->value;
		for (int i = 0; i < descr_val["type"].size(); ++i)
		{
			std::cout << i + 1 << ")\n";
			if (descr_val["article"][i] != "")
				std::cout << "article: " << descr_val["article"][i] << "\n";
			std::cout << "type: " << descr_val["type"][i] << "\n\n";
		}
	}

	int i = 1;
	if (w->translations != nullptr)
	{
		cout << "Translation:\n\n";
		for (auto& t : w->translations->values)
		{
			cout << "\t" << i << ". " << t << "\n";
			++i;
		}
	}

	i = 0;
	if (w->examples != nullptr)
	{
		cout << "\nExamples:\n\n";
		for (auto& e : w->examples->values)
		{
			cout << "\t" << i << ". " << e << "\n";
			++i;
		}
	}
	cout << "\n\n";
}

void process_list_command(string word)
{
	auto result = dict->find_words(word);//tr.find_template(word);
	if (result.size() == 0)
	{
		std::cout << "\nNo matching words found\n";
		return;
	}
	system("CLS");
	cout << flush << "List of words starting from: " + word + "\n\n";
	for (auto& res : result)
	{
		cout << res->stored_word << "\n";
	}
	std::cout << "\nCheck: ";
	
	int i = 0;
	char c;
	string w = "";
	while ((c = _getche()) != '\r')
	{
		if (c == '\t')
		{
			eraseLines(1);
			cout <<"Check: " << result[i%result.size()]->stored_word;
			w = result[i % result.size()]->stored_word;
			++i;
		}
		else
		{
			i = 0;
			w += c;
		}
	}
	auto iter = find_if(result.begin(), result.end(), [&w](decltype(result[0]) e) {return e->stored_word == w; });
	if (iter != result.end())
		show_word_information(*iter);
	cout << "\n";
}

void process_find_command(string word)
{
	auto result = dict->load_word_details(word);//tr.find_template(word);
	if (result == nullptr)
	{
		std::cout << "\n\nNot found\n\n";
		return;
	}
	system("CLS");
	
	show_word_information(result);
	cout << "\n";
}

void process_save_command(std::vector<string> command)
{
	string theme = "default";
	int descr = 1;
	set<int> transl_indices = {};
	set<int> exampl_indices = {};

	auto result = dict->load_word_details(command[1]);

	if (result == nullptr)
	{
		std::cout << "\n\nNot found\n\n";
		return;
	}

	try
	{
		for (int i = 1; i < command.size(); ++i)
		{
			if (command[i] == "--theme")
			{
				theme = command[i + 1];
				++i;
				continue;
			}

			if (command[i] == "--translations")
			{
				auto digits = split(command[i + 1], ',');

				for (auto& e : digits)
				{
					transl_indices.insert(std::stoi(e));
				}
				i += 1;
				continue;
			}

			if (command[i] == "--examples")
			{
				auto digits = split(command[i + 1], ',');
				for (auto& e : digits)
				{
					exampl_indices.insert(std::stoi(e));
				}
				i += 1;
				continue;
			}

			if (command[i] == "--description")
			{
				descr = std::stoi(command[i + 1]);
				i += 1;
				continue;
			}
		}
	}
	catch (...)
	{
		std::cout << "\nCan't parse command\n";
	}
	dict->save_word_in_file(theme, result, descr, transl_indices, exampl_indices);
	cout << "\n";
}
//*/
int main(int argc, const char* argv[])
{
	if (argc <= 1)
		dict = new dictionary("C:\\Job\\StockSharp\\OfflineDictionaryBackend\\OfflineDictionaryBackend\\data", languages::dutch);
	else
		dict = new dictionary(argv[1], languages::dutch);

	while (true)
	{
		std::cout << "\nEnter: ";
		string command;
		getline(cin, command, '\n');
	
		auto tokens = split(command);
		
		if (tokens.size() > 0 && tokens[0] == "--list")
		{
			if (tokens.size() == 2)
			{
				process_list_command(tokens[1]);
			}
			else
			{
				cout << "\nWrong syntax\n";
			}
		}
		else if (tokens[0] == "--save")
		{
			process_save_command(tokens);
		}
		else
		{
			process_find_command(command);
		}
		
	}//*/
	return 0;
}
