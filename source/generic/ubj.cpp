
#include "ubj.h"

/******************************************************************************
* Default Constructor. Initializes the file f to NULL in order to make sure the
* it has some value.
******************************************************************************/
Ubj::Ubj () 
{
	f = nullptr;
}

/******************************************************************************
* Default Destructor. Currently does nothing.
******************************************************************************/
Ubj::~Ubj ()
{
	
}

/******************************************************************************
* Opens a given file for binary reading and writing. Returns true if successful.
* Params:
*     filepath - Path to the file relative to the executable.
******************************************************************************/
bool Ubj::open (std::string filepath) 
{
	if (f == nullptr)
		f = new std::ifstream();
	if (not f->is_open())
		f->open(filepath, std::ios::out | std::ios::in | std::ios::binary);
	return f->is_open();
}

/******************************************************************************
* Closes the open file.
******************************************************************************/
void Ubj::close () 
{
	if (f->is_open())
		f->close();
	delete f;
}

/******************************************************************************
* Sets the current position of the head to the beginning of the file. Returns
* a Ubj object with the new position.
******************************************************************************/
Ubj Ubj::beginning()
{
	Ubj new_ubj;
	new_ubj.pos = 0;
	f->seekg(0);
	new_ubj.f = f;
	return new_ubj;
}

/******************************************************************************
* Sets the current position of the head to the previously searched for name.
* Returns a Ubj object with the new position.
******************************************************************************/
Ubj Ubj::back()
{
	Ubj new_ubj;
	if (links.empty())
	{
		new_ubj.pos = 0;
		f->seekg(0);
		new_ubj.f = f;
	}
	else
	{
		new_ubj.pos = links.front();
		f->seekg(links.front());
		links.pop_front();
		new_ubj.f = f;
		new_ubj.links = links;
	}
	return new_ubj;
}

/******************************************************************************
* Sets the current position of the head to the next layer of a given name under 
* the current layer. Returns a Ubj object with the new position.
* Params:
*     name - Name of the desired name-key value.
******************************************************************************/
Ubj Ubj::at (std::string name)
{
	links.push_front(pos);
	f->seekg(pos);
	Ubj new_ubj;
	int new_pos = search(name);
	if (new_pos == -1)
		new_ubj.pos = 0;
	else
		new_ubj.pos = new_pos;
	
	new_ubj.f = f;
	new_ubj.links = links;
	return new_ubj;
}

/******************************************************************************
* Sets the current position of the head to the index of the array the current
* array. Returns a Ubj object with the new position.
* Params:
*     index - Index of the array to place the head at.
******************************************************************************/
Ubj Ubj::at (unsigned int index)
{
	links.push_front(pos);
	f->seekg(pos);
	Ubj new_ubj;
	for (unsigned int i = 0; i < index; i++)
		skip();
	new_ubj.pos = f->tellg();
	new_ubj.f = f;
	new_ubj.links = links;
	return new_ubj;
}

/******************************************************************************
* Finds the value with the same name as the given name. Places the head at the
* beginning of the value. Returns the position of the head as an int. Returns
* -1 if the file reaches the end of the file or an error occurs. 
* Params:
*     name - Name of the desired name-key value.
******************************************************************************/
int Ubj::search (std::string &name)
{
	if (f->eof() || f->fail())
	{
		std::cout << "Something went wrong" << std::endl;
		f->clear();
		return -1;
	}
	else if (name == get_name())
	{
		pos = f->tellg();
		f->read((char *) &next, sizeof(char));
		if (next == '{' || next == '[')
			pos = f->tellg();
		else
			f->seekg(pos);
		return pos;
	}
	else
	{
		pos = f->tellg();
		f->read((char *) &next, sizeof(char));
		if (next == '}')
			return -1;
		else if (next != ']')
			f->seekg(pos);
		
		if (skip())
			return search(name);
		else
			return -1;
	}	
}

/******************************************************************************
* Gets the 8-bit signed int at the current position of the head.
******************************************************************************/
int8_t Ubj::get_i ()
{
	int8_t val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(int8_t));
	return val;
}

/******************************************************************************
* Gets the 8-bit unsigned int at the current position of the head.
******************************************************************************/
uint8_t Ubj::get_U ()
{
	uint8_t val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(uint8_t));
	return val;
}

/******************************************************************************
* Gets the 16-bit signed int at the current position of the head.
******************************************************************************/
int16_t Ubj::get_I ()
{
	int16_t val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(int16_t));
	unsigned int x = 1;
	if ( (int) (((char *)&(x))[0]) == 1)	// Using little endian architecture?
		val = __builtin_bswap16(val);		// Switch big -> small endian
	return val;
}

/******************************************************************************
* Gets the 32-bit signed int at the current position of the head.
******************************************************************************/
int32_t Ubj::get_l ()
{
	int32_t val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(int32_t));
	unsigned int x = 1;
	if ( (int) (((char *)&(x))[0]) == 1)	// Using little endian architecture?
		val = __builtin_bswap32(val);		// Switch big -> small endian
	return val;
}

/******************************************************************************
* Gets the 64-bit signed int at the current position of the head.
******************************************************************************/
int64_t Ubj::get_L ()
{
	int64_t val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(int64_t));
	unsigned int x = 1;
	if ( (int) (((char *)&(x))[0]) == 1)	// Using little endian architecture?
		val = __builtin_bswap64(val);		// Switch big -> small endian
	return val;
}

/******************************************************************************
* Gets the float at the current position of the head.
******************************************************************************/
float Ubj::get_f ()
{
	float val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(float));
	return val;
}

/******************************************************************************
* Gets the double at the current position of the head.
******************************************************************************/
double Ubj::get_d ()
{
	double val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(double));
	return val;
}

/******************************************************************************
* Gets the char at the current position of the head.
******************************************************************************/
char Ubj::get_C ()
{
	char val;
	f->read((char *) &next, sizeof(char));
	f->read((char *) &val, sizeof(char));
	return val;
}

/******************************************************************************
* Gets the string at the current position of the head.
******************************************************************************/
std::string Ubj::get_S ()
{
	std::string val;
	f->read((char *) &next, sizeof(char));
	uint8_t size = get_U();
	f->read((char *) &val, size*sizeof(char));
	return val;
}

/******************************************************************************
* Gets the name represented as a string at the current position of the head.
******************************************************************************/
std::string Ubj::get_name () 
{
	pos = f->tellg();
	f->clear();
	f->seekg(pos);
	f->read((char *) &next, sizeof(char));
	pos += sizeof(char);
	char *cname;
	uint8_t size;
	f->read((char *) &size, sizeof(uint8_t));
	pos += sizeof(uint8_t);
	cname = new char[size];
	f->read((char *) cname, size*sizeof(char));
	pos += size*sizeof(char);
	cname[size] = '\0';
	std::string name;
	name = cname;
	delete cname;
	f->seekg(pos);
	return name;
}

/******************************************************************************
* Places the head immediately after the next value. It returns true if the head
* was placed successfully, false if the end of the file was reached or there
* was an error. This function is operational, but it still needs to account for
* more value types before it can be complete.
******************************************************************************/
bool Ubj::skip ()
{
	f->read((char *) &next, sizeof(char));
	if (next == 'Z' || next == 'N' || 
		next == 'T' || next == 'F' || 
		next == '}' || next == ']')
	{
		pos = f->tellg();
		return true;
	}
	else if (next == 'i')
	{
		pos = f->tellg();
		pos += sizeof(int8_t);
		f->seekg(pos);
		return true;
	}
	else if (next == 'U')
	{
		pos = f->tellg();
		pos += sizeof(uint8_t);
		f->seekg(pos);
		return true;
	}
	else if (next == 'I')
	{
		pos = f->tellg();
		pos += sizeof(int16_t);
		f->seekg(pos);
		return true;
	}
	else if (next == 'l')
	{
		pos = f->tellg();
		pos += sizeof(int32_t);
		f->seekg(pos);
		return true;
	}
	else if (next == 'L')
	{
		pos = f->tellg();
		pos += sizeof(int64_t);
		f->seekg(pos);
		return true;
	}
	else if (next == 'd')
	{
		pos = f->tellg();
		pos += sizeof(float);
		f->seekg(pos);
		return true;
	}
	else if (next == 'D')
	{
		pos = f->tellg();
		pos += sizeof(double);
		f->seekg(pos);
		return true;
	}
	else if (next == 'C')
	{
		pos = f->tellg();
		pos += sizeof(char);
		f->seekg(pos);
		return true;
	}
	else if (next == 'S')
	{
		f->read((char *) &next, sizeof(char));
		uint8_t size;
		f->read((char *) &size, sizeof(uint8_t));
		pos = f->tellg();
		pos += size*sizeof(char);
		f->seekg(pos);
		return true;
	}
	else if (next == '{')
	{
		bool fine;
		while (next != '}')
		{
			fine = skip();
		}
		return true && fine;
	}
	else if (next == '[')
	{
		bool fine;
		while (next != ']')
			fine = skip();
		return true && fine;
	}
	else
	{
		return false;
	}
}
