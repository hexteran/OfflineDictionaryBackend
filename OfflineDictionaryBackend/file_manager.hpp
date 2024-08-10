#pragma once
#include "helpers.hpp"
class file_manager
{
	std::string _filename;
public:
	file_manager(std::string filename, std::string header = "") : _filename(filename)
	{
		if (!std::filesystem::exists(filename))
		{
			std::ofstream file(filename); 
			if (header != "")
				file << header;
		}
	}

	bool add_unique_record(std::string record)
	{
		std::ifstream ifile(_filename);
		std::string line;
		while (std::getline(ifile, line))
		{
			if (record == line)
				return false;
		}
		ifile.close();
		std::ofstream ofile(_filename, std::ios_base::app);
		ofile << '\n' << record;
		return true;
	}
};