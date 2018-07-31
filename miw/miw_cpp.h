/*
Copyright (c) <year> Mido

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MIW_CPP_H
#define MIW_CPP_H

#include "miw_cpp_native.h"

//miw_cpp
namespace miw_cpp
{
	//static
	struct cmp_str
	{
		bool operator()(char const* a, char const* b)const
		{
			return std::strcmp(a, b) < 0;
		}
	};

	static std::set<const char*, cmp_str> files;

	//init
	static bool init()
	{
		miw_node::root() = new miw_node_class(0, NULL);

		//default value type
		miw_node_class* node;

		node = new miw_node_class(0, NULL);
		node->data_name = "@void";
		node->data_size = node->data_align = 0;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@s8";
		node->data_size = node->data_align = 1;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@s16";
		node->data_size = node->data_align = 2;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@s32";
		node->data_size = node->data_align = 4;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@s64";
		node->data_size = node->data_align = 8;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@u8";
		node->data_size = node->data_align = 1;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@u16";
		node->data_size = node->data_align = 2;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@u32";
		node->data_size = node->data_align = 4;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@u64";
		node->data_size = node->data_align = 8;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@f32";
		node->data_size = node->data_align = 4;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@f64";
		node->data_size = node->data_align = 8;
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@bool";
		node->data_size = node->data_align = sizeof(bool);
		miw_node::root()->reg_class(node);

		node = new miw_node_class(0, NULL);
		node->data_name = "@wchar_t";
		node->data_size = node->data_align = sizeof(wchar_t);
		miw_node::root()->reg_class(node);

		//mido auto type...
		node = new miw_node_class(0, NULL);
		node->data_name = "@auto";
		node->data_size = node->data_align = 0;
		miw_node::root()->reg_class(node);

		return true;
	}

	//del
	static void del()
	{
		if(miw_node::root() != NULL)
			delete miw_node::root();
	}

	//load
	static inline int load(void* _ptr, int _size, const char* _file = NULL)
	{
		char* file = (char*)_file;

		if(file != NULL)
		{
			std::set<const char*, cmp_str>::iterator it = files.find(file);
			if(it != files.end())
			{
				file = (char*)*it;
			}
			else
			{
				file = new char[strlen(_file) + 1];
				wstrcpy(file, _file);

				files.insert(file);
			}
		}

		miw_cpp::compiler compiler(_ptr, _size, file);

		//
		while(compiler.parser_decl(miw_node::root()) != NULL)
			;

		return compiler.iserror(compiler.isbuffer() != 0); //check eof
	}

	//unload
	static inline void unload(const char* _file = NULL)
	{
		if(_file == NULL) //clear all
		{
			del();
			init();
		}
		else
		{
			for(std::map<std::string, miw_node_class*>::iterator it = miw_node::root()->data_class.begin(); it != miw_node::root()->data_class.end();)
			{
				if(it->second->file != NULL && !strcmp(_file, it->second->file))
				{
					delete it->second;
					miw_node::root()->data_class.erase(it++);
				}
				else
				{
					++it;
				}
			}
		}

		std::set<const char*, cmp_str>::iterator it = files.find(_file);
		if(it != files.end())
		{
			delete[] * it;
			files.erase(it);
		}
	}
};

#endif
