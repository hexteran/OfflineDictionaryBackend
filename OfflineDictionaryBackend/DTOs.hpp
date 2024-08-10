#include "definitions.hpp"

namespace offline_dictionary_backend
{
	struct persistable
	{
		const type_persistable type = type_persistable::none;
		persistable()
		{}
	};

	struct persistable_vector : persistable
	{
		const type_persistable type = type_persistable::translations;
		std::vector<std::string> values;
		persistable_vector(std::vector<std::string>&& values) : values(values)
		{}
	};

	struct persistable_string : persistable
	{
		const type_persistable type = type_persistable::description;
		std::string value;
		persistable_string(const std::string&& value) : value(value)
		{}
	};

	struct persistable_str_map : persistable
	{
		const type_persistable type = type_persistable::description;
		std::map<std::string, std::vector<std::string>> value;
		persistable_str_map(std::map<std::string, std::vector<std::string>>&& value) : value(value)
		{}
	};
	
	using persistable_ptr = std::shared_ptr<persistable>;
	using persistable_vector_ptr = std::shared_ptr<persistable_vector>;
	using persistable_string_ptr = std::shared_ptr<persistable_string>;
	using persistable_str_map_ptr = std::shared_ptr<persistable_str_map>;

}