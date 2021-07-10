
#include "json_parser.h"


/******************************************************************************
 * This function outputs the given message to the console and a file called
 * "program_log.txt" in the same directory as the executable. By default,
 * the message is appended to the same file. If the value new_file=true, the
 * "program_log.txt" file will be deleted, and a new "program_log.txt" file
 * will be generated.
 * Params:
 * 		message 	- The message to be outputted
 *		new_file	- Boolean determining if a new log file will be generated
 *****************************************************************************/
bool Json::load (std::string filename, std::string location) 
{
	input_file.open(filename);
	if (!input_file.is_open())
		return false;
	
	std::list<std::string> keys = split_string(location, ":");

	//get_section(input_file, keys);
	values = *get_value();
	input_file.close();
	return true;
}

std::string Json::get_section (std::ifstream &input_file, std::list<std::string> &keys)
{
	std::string section;
	std::string name;
	char input;

	
	
	return section;
}

std::string Json::get_string_representation()
{
	return to_string(values);
}

std::string Json::to_string(struct Value v)
{
	if (!v.s.empty())
		return "\"" + v.s + "\"";
	else if (!v.a.empty())
	{
		std::string array = "[";
		for (auto i : v.a) {
			array.append(to_string(*i));
			array.append(", ");
		}
		array = array.substr(0, array.size()-2);
		array.append("]");
		return array;
	}
	else if (!v.o.empty())
	{
		std::string object = "{";
		for (auto x : v.o)
		{
			object.append("\"").append(x.first).append("\" : ");
			object.append(to_string(*x.second)).append(", \n");
        }
        object = object.substr(0, object.size()-3);
        object.append("}");
        return object;
	}
	else
		return "";
}

std::list<std::string> Json::split_string (std::string s, std::string delimiter)
{
	std::list<std::string> array;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		array.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	array.push_back(s);
	return array;
}

Json::Value* Json::get_value ()
{
	if (!next_nonwhitespace())
		return nullptr;
	else if (next == '"')
		return new Value({.s = get_string()});
	else if (next == '[')
		return new Value({.a = get_array()});
	else if (next == '{')
		return new Value({.o = get_object()});
	else if (next == '-' || (next >= 48 && next <=57) )
		return new Value({.s = get_num()});
	else if (input_file.get(next))
		return get_value();
	else
		return nullptr;
}

std::unordered_map<std::string, Json::Value*> Json::get_object ()
{
	if (next == '{')
	{
		std::unordered_map<std::string, struct Value*> o;
		get_inner_object(o);
		return o;
	}
	else if (input_file.get(next))
	{
		return get_object();
	}
	else
	{
		std::unordered_map<std::string, struct Value*> o;
		return o;
	}
}

void Json::get_inner_object (std::unordered_map<std::string, Json::Value*> &o)
{
	if (next == '}')
		return;
	else if (next == '"')
	{
		o.insert({get_string(), get_value()});
		get_inner_object(o);
	}
	else if (next == ',')
	{
		if (input_file.get(next))
			get_inner_object(o);
		else
			return;
	}
	else
	{
		if (input_file.get(next))
			get_inner_object(o);
		else
			return;
	}
}

std::list<Json::Value*> Json::get_array ()
{
	if (next == '[')
	{
		std::list<struct Value*> a;
		get_inner_array(a);
		return a;
	}
	else if (input_file.get(next))
	{
		return get_array();
	}
	else
	{
		std::list<struct Value*> a;
		return a;
	}
}

void Json::get_inner_array (std::list<Json::Value*> &a)
{
	if (next == ']')
	{
		return;
	}
	else if (next == ',')
	{
		if (input_file.get(next))
		{
			a.push_back(get_value());
			get_inner_array(a);
		}
		else
			return;
	}
	else
	{
		if (input_file.get(next))
			get_inner_array(a);
		else
			return;
	}
}

std::string Json::get_num ()
{
	if (next == '-')
	{
		if (input_file.get(next))
			return "-" + get_num();
		else return "-";
	}
	else if (next >= 48 && next <= 57)
	{
		std::string pre;
		pre += next;
		if (input_file.get(next))
			return pre + get_num();
		else
			return pre;
	}
	else if (next == '.')
	{
		if (input_file.get(next))
			return "." + get_num();
		else 
			return ".";
	}
	else if (next == 'e' || next == 'E')
	{
		if (input_file.get(next))
			return "e" + get_num();
		else 
			return "e";
	}
	else
		return "";
}

std::string Json::get_string ()
{
	if (next == '"')
		if (input_file.get(next))
			return get_inner_string ();
		else
			return "";
	else if (next_nonwhitespace())
		return get_string();
	else 
		return "";
}

std::string Json::get_inner_string ()
{
	if (next == '\\')
	{
		if (input_file.get(next))
		{
			std::string esc = "\\";
			esc += next;
			if (input_file.get(next))
				return esc + get_inner_string();
			else
				return esc;
		}
		else
		{
			return "";
		}
	}
	else if (next == '"')
	{
		return "";
	}
	else
	{
		std::string pre;
		pre += next;
		if (input_file.get(next))
			return pre + get_inner_string();
		else
			return pre;
	}
}

bool Json::next_nonwhitespace ()
{
	if (next == ' ' || next == '\t' || next == '\n' || next == '\r')
		return input_file.get(next) && next_nonwhitespace();
	else
		return true;
}
