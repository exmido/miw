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

#ifndef MIW_NODE_H
#define MIW_NODE_H

#include "miw_vm.h"
#include "utf.h"

class miw_node_class;

//miw_node
class miw_node
{
protected:
	//global
	//generate
	static unsigned int generate()
	{
		static int id = 0;
		return ++id;
	}

public:
	//local
	int line;
	const char* file;

	//global
	//rttype
	template<class T>
	static unsigned int rttype()
	{
		static unsigned int id = generate();
		return id;
	}

	//cast
	template<typename T>
	static T* cast(miw_node* node)
	{
		if(node && node->rtti(miw_node::rttype<T>()))
			return (T*)node;

		return NULL;
	}

	//reference
	static int& reference()
	{
		static int ret = 0;
		return ret;
	}

	//root
	static miw_node_class*& root()
	{
		static miw_node_class* ret = NULL;
		return ret;
	}

	//reseek
	static void reseek(miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		for(miw_vm_variable<miw_node>* p = vm->getseek(); p != seek; p = vm->getseek())
			p->type->revoke(*p, vm, seek);
	}

	//local
	//miw_node
	miw_node(int _line, const char* _file)
	{
		line = _line;
		file = _file;

		++reference();
	}

	//~miw_node
	virtual ~miw_node()
	{
		--reference();
	}

	//clear
	virtual miw_node* clear()
	{
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		if(node == NULL)
			node = new miw_node(line, file);

		return node;
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node>();
	}

	//type
	virtual miw_node* type()
	{
		return this;
	}

	//size
	virtual int size()
	{
		return 0;
	}

	//align
	virtual int align()
	{
		return 0;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return miw_vm_variable<miw_node>();
	}

	//revoke
	virtual bool revoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return false;
	}

	//find
	virtual miw_vm_variable<miw_node> find(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, std::string name = "")
	{
		return this == self.type ? self : miw_vm_variable<miw_node>();
	}

	//apply
	virtual miw_vm_variable<miw_node> apply(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek, miw_vm_variable<miw_node> offset)
	{
		return miw_vm_variable<miw_node>();
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		return this == node ? this : NULL;
	}

	//print
	virtual std::string print(std::string str = "")
	{
		return "";
	}
};

//miw_node_var
class miw_node_var : public miw_node
{
public:
	//data
	std::string		data_name;	//name
	miw_node*		data_type;	//type
	miw_node*		data_exp;	//expression

	bool			data_isstatic;	//is static
	bool			data_isnative;	//is native

	//cache
	miw_node*					cache_type;		//type
	miw_vm_variable<miw_node>	cache_var;		//variable

	//info
	miw_node*		info_scope;	//scope

	//miw_node_var
	miw_node_var(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		data_name = "";
		data_type = NULL;
		data_exp = NULL;

		data_isstatic = false;
		data_isnative = false;

		//
		cache_type = NULL;

		//
		info_scope = NULL;
	}

	//~miw_node_var
	virtual ~miw_node_var()
	{
		if(data_type != NULL)
			delete data_type;

		if(data_exp != NULL)
			delete data_exp;

		//free static memory
		if(data_isstatic && data_isnative == false && cache_var.value != NULL)
			delete (unsigned char*)cache_var.value;

		//
		if (info_scope)
			delete info_scope;
	}

	//clear
	virtual miw_node* clear()
	{
		data_type->clear();
		data_exp->clear();

		//
		cache_type = NULL;
		cache_var.type = NULL;

		//free static memory
		if(data_isstatic)
		{
			if(data_isnative == false && cache_var.value != NULL)
			{
				delete (unsigned char*)cache_var.value;
				cache_var.value = NULL;
			}
		}
		else
		{
			cache_var.value = NULL;
		}
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_var* ret = (miw_node_var*)node;
		if(ret == NULL)
			ret = new miw_node_var(line, file);

		//
		ret->data_name = data_name;

		if(data_type)
			ret->data_type = data_type->clone();

		ret->data_isstatic = data_isstatic;
		ret->data_isnative = data_isnative;

		return miw_node::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_var>() || miw_node::rtti(t);
	}

	//type
	virtual miw_node* type()
	{
		return cache_type;
	}

	//size
	virtual int size()
	{
		return cache_type->size();
	}

	//align
	virtual int align()
	{
		return cache_type->align();
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		if(cache_var.type == NULL)
		{
			cache_var = data_type->invoke(self, vm, seek);
			cache_type = cache_var.type;
			cache_var.type = this;
			
			//alloc static memory
			if(data_isstatic && data_isnative == false)
				cache_var.value = new unsigned char[size()];
		}

		return cache_var;
	}

	//revoke
	virtual bool revoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return cache_type->revoke(self, vm, seek);
	}

	//find
	virtual miw_vm_variable<miw_node> find(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, std::string name = "")
	{
		return cache_type->find(self, vm, name);
	}

	//apply
	virtual miw_vm_variable<miw_node> apply(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek, miw_vm_variable<miw_node> offset)
	{
		return cache_type->apply(self, vm, seek, offset);
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		return cache_type->compare(node->type());
	}

	//print
	virtual std::string print(std::string str = "")
	{
		std::string ret = data_name;
		if (info_scope)
			ret = info_scope->print() + "::" + ret;

		ret = data_type->print(ret);

		if (data_isstatic)
			ret = "static " + ret;

		return ret;
	}
};

//miw_node_modify
class miw_node_modify : public miw_node
{
public:
	//data
	miw_node * data_type;	//variable type

	//cache
	miw_node* cache_type;	//variable type

	//miw_node_modify
	miw_node_modify(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		data_type = NULL;

		cache_type = NULL;
	}

	//~miw_node_modify
	virtual ~miw_node_modify()
	{
		if(data_type != NULL)
			delete data_type;
	}

	//clear
	virtual miw_node* clear()
	{
		data_type->clear();

		cache_type = NULL;
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_modify* ret = (miw_node_modify*)node;
		if(ret == NULL)
			ret = new miw_node_modify(line, file);

		//
		if(data_type)
			ret->data_type = data_type->clone();

		return miw_node::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_modify>() || miw_node::rtti(t);
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		if(cache_type == NULL)
			cache_type = data_type->invoke(self, vm, seek).type;

		self.type = this;
		return self;
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		//is modify
		miw_node_modify* modify = miw_node::cast<miw_node_modify>(node);
		if(modify == NULL)
			return NULL;

		//check type
		return cache_type->compare(modify->cache_type);
	}

	//
	//modify
	virtual miw_node* modify()
	{
		return cache_type;
	}

	virtual miw_node* modify(miw_node* node)
	{
		if (node)
		{
			miw_node_modify* md = miw_node::cast<miw_node_modify>(node);
			if (md && md->data_type == data_type) //insert
			{
				return data_type = node;
			}
			else if (data_type)
			{
				md = miw_node::cast<miw_node_modify>(data_type);
				if (md)
					return md->modify(node);
				else
					delete data_type;
			}
		}

		data_type = node;
		return this;
	}
};

//miw_node_array
class miw_node_array : public miw_node_modify
{
public:
	//data
	miw_node * data_size;	//array size

	//cache
	int			cache_size;	//array size

	//miw_node_array
	miw_node_array(int _line, const char* _file)
		: miw_node_modify(_line, _file)
	{
		data_size = NULL;

		cache_size = 0;
	}

	//~miw_node_array
	virtual ~miw_node_array()
	{
		if(data_size != NULL)
			delete data_size;
	}

	//clear
	virtual miw_node* clear()
	{
		data_size->clear();

		cache_size = 0;
		return miw_node_modify::clear();
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_array* ret = (miw_node_array*)node;
		if(ret == NULL)
			ret = new miw_node_array(line, file);

		//
		if(data_size)
			ret->data_size = data_size->clone();

		return miw_node_modify::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_array>() || miw_node_modify::rtti(t);
	}

	//size
	virtual int size()
	{
		return cache_type->size() * cache_size;
	}

	//align
	virtual int align()
	{
		return size();
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		if (cache_type == NULL)
		{
			cache_type = data_type->invoke(self, vm, seek).type;
			
			//mido size
		}

		self.type = this;
		return self;
	}

	//revoke
	virtual bool revoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		self.reset(cache_type, *(void**)self.value);
		if(cache_type->revoke(self, vm, seek))
		{
			int offset = cache_type->size();
			for(int i = 1; i < cache_size; ++i)
			{
				self.seek(offset);
				cache_type->revoke(self, vm, seek);
			}

			return true;
		}

		return false;
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		//check array size
		miw_node_array* ary = miw_node::cast<miw_node_array>(node);
		if(ary == NULL || size() != ary->size())
			return NULL;

		//check type
		return miw_node_modify::compare(node);
	}
};

//miw_node_pointer
class miw_node_pointer : public miw_node_modify
{
public:
	//miw_node_pointer
	miw_node_pointer(int _line, const char* _file)
		: miw_node_modify(_line, _file)
	{
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_pointer>() || miw_node_modify::rtti(t);
	}

	//size
	virtual int size()
	{
		return sizeof(void*);
	}

	//align
	virtual int align()
	{
		return sizeof(void*);
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_pointer* ret = (miw_node_pointer*)node;
		if(ret == NULL)
			ret = new miw_node_pointer(line, file);

		return miw_node_modify::clone(ret);
	}

	//find
	virtual miw_vm_variable<miw_node> find(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, std::string name = "")
	{
		if(miw_node::cast<miw_node_class>(cache_type))
			return cache_type->find(self, vm, name);

		return miw_vm_variable<miw_node>(); //mido error...
	}

	//apply
	virtual miw_vm_variable<miw_node> apply(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek, miw_vm_variable<miw_node> offset)
	{
		self.value = *(void**)self.value;
		return cache_type->apply(self, vm, seek, offset);
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		//is pointer or array
		if(miw_node::cast<miw_node_pointer>(node) == NULL && miw_node::cast<miw_node_array>(node) == NULL)
			return NULL;

		//check type
		return miw_node_modify::compare(node);
	}

	//print
	virtual std::string print(std::string str = "")
	{
		return data_type->print("(*" + str + ")");
	}
};

//miw_node_reference
class miw_node_reference : public miw_node_modify
{
public:
	//miw_node_reference
	miw_node_reference(int _line, const char* _file)
		: miw_node_modify(_line, _file)
	{
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_reference>() || miw_node_modify::rtti(t);
	}

	//type
	virtual miw_node* type()
	{
		return cache_type;
	}

	//size
	virtual int size()
	{
		return cache_type->size();
	}

	//align
	virtual int align()
	{
		return cache_type->align();
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_reference* ret = (miw_node_reference*)node;
		if(ret == NULL)
			ret = new miw_node_reference(line, file);

		return miw_node_modify::clone(ret);
	}

	//find
	virtual miw_vm_variable<miw_node> find(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, std::string name = "")
	{
		return cache_type->find(self, vm, name);
	}

	//apply
	virtual miw_vm_variable<miw_node> apply(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek, miw_vm_variable<miw_node> offset)
	{
		return cache_type->apply(self, vm, seek, offset);
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		return cache_type->compare(node);
	}

	//print
	virtual std::string print(std::string str = "")
	{
		return data_type->print("&" + str);
	}
};

//miw_node_alias
class miw_node_alias : public miw_node_reference
{
public:
	//data
	std::string	data_name;

	//miw_node_alias
	miw_node_alias(int _line, const char* _file)
		: miw_node_reference(_line, _file)
	{
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_alias* ret = (miw_node_alias*)node;
		if(ret == NULL)
			ret = new miw_node_alias(line, file);

		return miw_node_modify::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_alias>() || miw_node_reference::rtti(t);
	}

	//print
	virtual std::string print(std::string str = "")
	{
		return data_type->print();
	}
};

//miw_node_fun
class miw_node_fun : public miw_node_modify
{
public:
	//data
	miw_node*				data_scope;		//scope
	miw_node*				data_exp;		//exp
	std::list<miw_node*>	data_parameter;	//parameter

	bool					data_isstatic;	//is static

	//cache
	miw_node*				cache_scope;	//scope

	//miw_node_fun
	miw_node_fun(int _line, const char* _file)
		: miw_node_modify(_line, _file)
	{
		data_scope = NULL;
		data_exp = NULL;
		data_isstatic = true;

		cache_scope = NULL;
	}

	//~miw_node_fun
	virtual ~miw_node_fun()
	{
		if(data_scope)
			delete data_scope;

		for(std::list<miw_node*>::iterator it = data_parameter.begin(); it != data_parameter.end(); ++it)
			delete *it;
	}

	//clear
	virtual miw_node* clear()
	{
		if(data_scope)
			data_scope->clear();

		for(std::list<miw_node*>::iterator it = data_parameter.begin(); it != data_parameter.end(); ++it)
			(*it)->clear();

		if(cache_scope)
			cache_scope->clear();

		return miw_node_modify::clear();
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_fun* ret = (miw_node_fun*)node;
		if(ret == NULL)
			ret = new miw_node_fun(line, file);

		//
		if(data_scope)
			ret->data_scope = data_scope->clone();

		ret->data_exp = data_exp;

		for(std::list<miw_node*>::iterator it = data_parameter.begin(); it != data_parameter.end(); ++it)
			ret->data_parameter.push_back((*it)->clone());

		ret->data_isstatic = data_isstatic;

		return miw_node_modify::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_fun>() || miw_node_modify::rtti(t);
	}

	//size
	virtual int size()
	{
		return cache_type->size();
	}

	//align
	virtual int align()
	{
		return cache_type->align();
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		if(cache_type == NULL)
		{
			cache_type = data_type->invoke(self, vm, seek).type;

			if (data_scope)
				cache_scope = data_scope->invoke(self, vm, seek).type;
			else
				cache_scope = (miw_node*)miw_node::root();

			for(std::list<miw_node*>::iterator it = data_parameter.begin(); it != data_parameter.end(); ++it)
				(*it)->invoke(self, vm, seek);
		}

		self.type = this;
		return self;
	}

	//apply
	virtual miw_vm_variable<miw_node> apply(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek, miw_vm_variable<miw_node> offset)
	{
		return cache_type->apply(self, vm, seek, offset);
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		//check function parameter
		miw_node_fun* fun = miw_node::cast<miw_node_fun>(node);
		if(fun == NULL)
			return NULL;

		//chcek scope
		if (fun->cache_scope != NULL && fun->cache_scope != cache_scope)
			return NULL;

		//chcek parameter
		size_t size = fun->data_parameter.size();
		if(size < data_parameter.size())
			size = data_parameter.size();

		std::list<miw_node*>::iterator it_this = data_parameter.begin();
		std::list<miw_node*>::iterator it_node = fun->data_parameter.begin();

		for(unsigned int i = 0; i < size; ++i)
		{
			if((*it_this)->compare(*it_node) == NULL)
				return NULL;

			++it_this;
			++it_node;
		}

		for(; it_this != data_parameter.end(); ++it_this)
		{
			miw_node_var* var = miw_node::cast<miw_node_var>(*it_this);
			if(var == NULL || var->data_exp == NULL)
				return NULL;
		}

		for(; it_node != fun->data_parameter.end(); ++it_node)
		{
			miw_node_var* var = miw_node::cast<miw_node_var>(*it_node);
			if(var == NULL || var->data_exp == NULL)
				return NULL;
		}

		//no check type
		if(fun->cache_type == NULL)
			return this;

		//check type
		return miw_node_modify::compare(node);
	}

	//print
	virtual std::string print(std::string str = "")
	{
		std::list<miw_node*>::iterator it = data_parameter.begin();
		std::string ret = "";

		if(it != data_parameter.end())
		{
			ret = (*it)->print();
			for(++it; it != data_parameter.end(); ++it)
			{
				ret += ",";
				ret += (*it)->print();
			}
		}

		if (data_scope)
			str = data_scope->print() + ":: " + str;

		return data_type->print(str + "(" + ret + ")");
	}
};

//miw_node_vars
class miw_node_vars : public miw_node
{
public:
	//data
	std::list<miw_node_var*> data_vars;

	//cache
	bool cache_invoke;

	//miw_node_vars
	miw_node_vars(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		cache_invoke = false;
	}

	//~miw_node_vars
	virtual ~miw_node_vars()
	{
		for(std::list<miw_node_var*>::iterator it = data_vars.begin(); it != data_vars.end(); ++it)
			delete *it;
	}

	//clear
	virtual miw_node* clear()
	{
		for(std::list<miw_node_var*>::iterator it = data_vars.begin(); it != data_vars.end(); ++it)
			(*it)->clear();

		cache_invoke = false;
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_vars* ret = (miw_node_vars*)node;
		if(ret == NULL)
			ret = new miw_node_vars(line, file);

		//
		return miw_node::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_vars>() || miw_node::rtti(t);
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		if(cache_invoke == false)
		{
			for (std::list<miw_node_var*>::iterator it = data_vars.begin(); it != data_vars.end(); ++it)
			{
				(*it)->invoke(self, vm, seek);

				//reset function data
				miw_node_fun* fun = miw_node::cast<miw_node_fun>((*it)->type());
				if (fun)
				{
					fun->data_exp = (*it)->data_exp;
					fun->data_isstatic = (*it)->data_isstatic;
					fun->cache_scope = self.type;
				}
			}
		}

		return miw_vm_variable<miw_node>(this, self.value);
	}

	//compare
	virtual miw_node* compare(miw_node* node)
	{
		for(std::list<miw_node_var*>::iterator it = data_vars.begin(); it != data_vars.end(); ++it)
		{
			miw_node* ret = (*it)->compare(node);
			if(ret)
				return ret;
		}

		return NULL;
	}
};

//miw_node_class
class miw_node_class : public miw_node
{
public:
	//data
	std::string								data_name;		//class name
	std::map<std::string, miw_node_class*>	data_class;		//local class
	std::map<std::string, miw_node_vars*>	data_funs;		//functions
	std::map<std::string, miw_node_alias*>	data_alias;		//alias
	int										data_offset;	//offset

	std::list<miw_node*>					data_base;		//base class
	std::list<miw_node_var*>				data_var;		//variable
	int										data_size;		//size
	int										data_align;		//align

	//cache
	std::list< miw_vm_variable<miw_node> >				cache_base;			//base class
	std::map< std::string, miw_vm_variable<miw_node> >	cache_var;			//variable
	int													cache_size;			//class size
	int													cache_align;		//align
	miw_node_var*										cache_revoke;		//revoke function

	//info
	std::string info_scope;	//class scope

	//miw_node_class
	miw_node_class(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		data_name = "";
		data_offset = 0;
		data_size = 0;
		data_align = 0;

		cache_align = 0;
		cache_size = -1;
		cache_revoke = NULL;

		info_scope = "";
	}

	//~miw_node_class
	virtual ~miw_node_class()
	{
		for(std::map<std::string, miw_node_class*>::iterator it = data_class.begin(); it != data_class.end(); ++it)
			delete it->second;

		for(std::map<std::string, miw_node_vars*>::iterator it = data_funs.begin(); it != data_funs.end(); ++it)
			delete it->second;

		for(std::map<std::string, miw_node_alias*>::iterator it = data_alias.begin(); it != data_alias.end(); ++it)
			delete it->second;

		for(std::list<miw_node*>::iterator it = data_base.begin(); it != data_base.end(); ++it)
			delete *it;

		for(std::list<miw_node_var*>::iterator it = data_var.begin(); it != data_var.end(); ++it)
			delete *it;
	}

	//clear
	virtual miw_node* clear()
	{
		//data
		for(std::map<std::string, miw_node_class*>::iterator it = data_class.begin(); it != data_class.end(); ++it)
			it->second->clear();

		for(std::map<std::string, miw_node_vars*>::iterator it = data_funs.begin(); it != data_funs.end(); ++it)
			it->second->clear();

		for(std::map<std::string, miw_node_alias*>::iterator it = data_alias.begin(); it != data_alias.end(); ++it)
			it->second->clear();

		for(std::list<miw_node*>::iterator it = data_base.begin(); it != data_base.end(); ++it)
			(*it)->clear();

		for(std::list<miw_node_var*>::iterator it = data_var.begin(); it != data_var.end(); ++it)
			(*it)->clear();

		//cache
		for(std::list< miw_vm_variable<miw_node> >::iterator it = cache_base.begin(); it != cache_base.end(); ++it)
		{
			if(it->type != NULL)
				it->type->clear();
		}
		cache_base.clear();

		for(std::map< std::string, miw_vm_variable<miw_node> >::iterator it = cache_var.begin(); it != cache_var.end(); ++it)
		{
			if(it->second.type != NULL)
				it->second.type->clear();
		}
		cache_var.clear();

		//
		cache_align = 0;
		cache_size = -1;
		cache_revoke = NULL;

		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		//mido
		return NULL;
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_class>() || miw_node::rtti(t);
	}

	//size
	virtual int size()
	{
		return cache_size > 0 ? cache_size : 1;
	}

	//align
	virtual int align()
	{
		return cache_align > 0 ? cache_align : 4;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		if(cache_size < 0)
		{
			cache_align = data_align;
			cache_size = data_offset;

			//base class
			for(std::list<miw_node*>::iterator it = data_base.begin(); it != data_base.end(); ++it)
			{
				miw_vm_variable<miw_node> v = (*it)->invoke(self, vm, seek);
				v.type->invoke(self, vm, seek);

				int a = v.type->align();

				if(data_align)
				{
					a = data_align;
				}
				else if(cache_align < a)
				{
					cache_align = a;
				}

				int offset = (cache_size + a - 1) & ~(a - 1);
				v.value = (void*)(size_t)offset;

				cache_base.push_back(v);

				miw_node_class* cls = miw_node::cast<miw_node_class>(v.type);
				cache_size = offset + (cls ? cls->cache_size : v.type->size()); //cache_size != size()
			}

			//variable
			self.type = this;
			for(std::list<miw_node_var*>::iterator it = data_var.begin(); it != data_var.end(); ++it)
			{
				miw_vm_variable<miw_node> v = (*it)->invoke(self, vm, seek);

				miw_node_var* var = miw_node::cast<miw_node_var>(v.type);
				if(var && var->data_isstatic == false)
				{
					int a = v.type->align();
					if(data_align)
					{
						a = data_align;
					}
					else if(cache_align < a)
					{
						cache_align = a;
					}

					int offset = (cache_size + a - 1) & ~(a - 1);
					v.value = (void*)(size_t)offset;

					miw_node_class* cls = miw_node::cast<miw_node_class>(v.type);
					cache_size = offset + (cls ? cls->cache_size : v.type->size()); //cache_size != size()
				}

				cache_var.erase((*it)->data_name);
				cache_var.insert(std::make_pair((*it)->data_name, v));
			}

			cache_size = (cache_size + cache_align - 1) & ~(cache_align - 1);

			if(cache_size < data_size)
				cache_size = data_size;
		}

		self.type = this;
		return self;
	}

	//revoke
	virtual bool revoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		bool ret = false;

		if(cache_revoke)
		{
			cache_revoke->data_exp->invoke(self, vm, seek);
			vm->read();
			return true;
		}

		vm->read();
		return false;
	}

	//find
	virtual miw_vm_variable<miw_node> find(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, std::string name = "")
	{
		//check and invoke
		if(cache_size < 0)
			invoke(self, vm, NULL);

		miw_vm_variable<miw_node> ret;

		if(name.compare(""))
		{
			//find this
			if(!name.compare(data_name))
			{
				ret.type = this;
				return ret;
			}

			//find in variable
			{
				std::map< std::string, miw_vm_variable<miw_node> >::iterator it = cache_var.find(name);
				if(it != cache_var.end())
				{
					ret = it->second;
					return ret;
				}
			}

			//find in functions
			{
				std::map<std::string, miw_node_vars*>::iterator it = data_funs.find(name);
				if(it != data_funs.end())
				{
					//check and invoke
					if(it->second->cache_invoke == false)
					{
						self.type = this;
						it->second->invoke(self, vm, NULL);
					}

					ret.type = it->second;
					return ret;
				}
			}

			//find in class
			{
				std::map<std::string, miw_node_class*>::iterator it = data_class.find(name);
				if(it != data_class.end())
				{
					//check and invoke
					if(it->second->cache_size < 0)
					{
						self.type = this;
						it->second->invoke(self, vm, NULL);
					}

					ret.type = it->second;
					return ret;
				}
			}

			//find in data_alias
			{
				std::map<std::string, miw_node_alias*>::iterator it = data_alias.find(name);
				if(it != data_alias.end())
				{
					//check and invoke
					if(it->second->cache_type == NULL)
					{
						self.type = this;
						it->second->invoke(self, vm, NULL);
					}

					ret.type = it->second->type();
					return ret;
				}
			}

			//find in base
			{
				for(std::list< miw_vm_variable<miw_node> >::iterator it = cache_base.begin(); it != cache_base.end(); ++it)
				{
					ret = it->type->find(self, vm, name);
					if(ret.type != NULL)
					{
						miw_node_var* var = miw_node::cast<miw_node_var>(ret.type);
						if(var == NULL || var->data_isstatic == false) //not static variable
							ret.seek(it->value);

						return ret;
					}
				}
			}
		}
		else
		{
			if(this == self.type)
			{
				ret.type = this;
				return ret;
			}

			//find base class
			for(std::list< miw_vm_variable<miw_node> >::iterator it = cache_base.begin(); it != cache_base.end(); ++it)
			{
				//find in self
				if(it->type == self.type)
				{
					ret = *it;
					return ret;
				}
				else
				{
					//find in base
					ret = it->type->find(self, vm);
					if(ret.type != NULL)
					{
						ret.seek(it->value);
						return ret;
					}
				}
			}
		}

		return ret;
	}

	//apply
	virtual miw_vm_variable<miw_node> apply(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek, miw_vm_variable<miw_node> offset)
	{
		offset.seek(self.value);
		return offset;
	}

	//print
	virtual std::string print(std::string str = "")
	{
		if(info_scope.compare(""))
			return info_scope + "::" + data_name;

		return data_name;
	}

	//
	//reg_class
	virtual bool reg_class(miw_node_class* cls)
	{
		if(data_class.find(cls->data_name) != data_class.end())
			return false;

		data_class.insert(std::make_pair(cls->data_name, cls));

		cls->info_scope = print();
		return true;
	}

	//reg_variable
	virtual bool reg_variable(miw_node_var* var)
	{
		if (var == NULL)
			return false;

		if(miw_node::cast<miw_node_fun>(var->data_type)) //function
		{
			std::map<std::string, miw_node_vars*>::iterator it = data_funs.find(var->data_name);

			if(it == data_funs.end())
			{
				it = data_funs.insert(std::make_pair(var->data_name, new miw_node_vars(line, file))).first;
			}

			it->second->data_vars.push_back(var);
		}
		else //variable
		{
			if(cache_var.find(var->data_name) != cache_var.end())
				return false;

			data_var.push_back(var);
			cache_var.insert(std::make_pair(var->data_name, miw_vm_variable<miw_node>()));
		}

		return true;
	}

	//reg_alias
	virtual bool reg_alias(miw_node_alias* alias)
	{
		if(data_alias.find(alias->data_name) != data_alias.end())
			return false;

		data_alias.insert(std::make_pair(alias->data_name, alias));
		return true;
	}
};

//miw_node_block
class miw_node_block : public miw_node
{
public:
	//data
	miw_node * data_base;	//base
	std::list<miw_node*>	data_node;	//node

	//cache
	bool												cache_invoke;	//invoke
	miw_node*											cache_type;		//type
	std::map< std::string, miw_vm_variable<miw_node> >	cache_var;		//variable

	//miw_node_block
	miw_node_block(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		//data
		data_base = NULL;

		//cache
		cache_invoke = false;
		cache_type = NULL;
	}

	//~miw_node_block
	virtual ~miw_node_block()
	{
		for (std::list<miw_node*>::iterator it = data_node.begin(); it != data_node.end(); ++it)
			delete *it;
	}

	//clear
	virtual miw_node* clear()
	{
		cache_var.clear();

		//
		cache_invoke = false;
		cache_type = NULL;
		return this;
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_block>() || miw_node::rtti(t);
	}

	//type
	virtual miw_node* type()
	{
		return cache_type;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		//mido
		if (cache_invoke == false)
		{
			size_t seek = 0;

			for (std::list<miw_node*>::iterator it = data_node.begin(); it != data_node.end(); ++it)
			{
				miw_node_var* var = miw_node::cast<miw_node_var>(*it);
				if (var)
				{
					if(var->data_isstatic)
						cache_var.insert(std::make_pair(var->data_name, miw_vm_variable<miw_node>(var, NULL))); //global variable
					else
						cache_var.insert(std::make_pair(var->data_name, miw_vm_variable<miw_node>(var, (void*)++seek))); //local variable
				}
			}
		}

		return miw_vm_variable<miw_node>();
	}

	//find
	virtual miw_vm_variable<miw_node> find(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, std::string name = "")
	{
		if (name.compare(""))
		{
			std::map< std::string, miw_vm_variable<miw_node> >::iterator it = cache_var.find(name);
			if (it != cache_var.end())
			{
				if(it->second.value) //local variable
					return miw_vm_variable<miw_node>(this, it->second.value);

				return it->second; //global variable
			}
		}

		return data_base->find(self, vm, name);
	}

	//apply
	virtual miw_vm_variable<miw_node> apply(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek, miw_vm_variable<miw_node> offset)
	{
		//apply local variable only
		return *vm->getseek(seek, (size_t)offset.value);
	}
};

//miw_node_value
class miw_node_value : public miw_node
{
public:
	//data
	miw_node*	data_type;	//type

	//cache
	miw_node*	cache_type;	//type

	union
	{
		char s8;
		short s16;
		int s32;
		long long s64;

		unsigned char u8;
		unsigned short u16;
		unsigned int u32;
		unsigned long long u64;

		float f32;
		double f64;

		bool b;
		char* ptr;
	};

	//miw_node_value
	miw_node_value(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		data_type = NULL;

		cache_type = NULL;

		ptr = NULL;
	}

	//~miw_node_value
	virtual ~miw_node_value()
	{
		if(miw_node::cast<miw_node_pointer>(data_type))
			delete[] ptr;

		delete data_type;
	}

	//clear
	virtual miw_node* clear()
	{
		data_type->clear();

		cache_type = NULL;
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_value* ret = (miw_node_value*)node;
		if(ret == NULL)
			ret = new miw_node_value(line, file);

		//
		if(data_type)
			ret->data_type = data_type->clone();

		return miw_node::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_value>() || miw_node::rtti(t);
	}

	//type
	virtual miw_node* type()
	{
		return cache_type;
	}

	//size
	virtual int size()
	{
		return cache_type->size();
	}

	//align
	virtual int align()
	{
		return cache_type->align();
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		if(cache_type == NULL)
		{
			cache_type = data_type->invoke(miw_node::root(), vm, seek).type;
			if(cache_type == NULL)
				return miw_vm_variable<miw_node>(); //mido error...
		}

		miw_vm_variable<miw_node> ret = miw_vm_variable<miw_node>(cache_type, &ptr);
		if(seek)
			*vm->write() = ret;

		return ret;
	}
};

//miw_node_name
class miw_node_name : public miw_node
{
protected:
	miw_vm_variable<miw_node>(miw_node_name::* invoke_fp)(miw_vm_variable<miw_node>&, miw_vm<miw_node>*, miw_vm_variable<miw_node>*);

	//invoke_base
	miw_vm_variable<miw_node> invoke_base(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		self.reset(cache_base, NULL);
		return self.type->apply(self, vm, seek, cache_offset); //apply offset
	}

	//invoke_local
	miw_vm_variable<miw_node> invoke_local(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return self.type->apply(self, vm, seek, cache_offset); //apply offset
	}

	//invoke_global
	miw_vm_variable<miw_node> invoke_global(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return cache_offset;
	}

	//invoke_heap
	miw_vm_variable<miw_node> invoke_heap(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return cache_offset.type->apply(self, vm, seek, cache_offset); //apply offset
	}

	//invoke_no_cache
	miw_vm_variable<miw_node> invoke_no_cache(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		cache_offset = self.type->find(self, vm, data_name); //find offset
		if(cache_offset.type == NULL) //not find
			return miw_vm_variable<miw_node>(); //mido error...

		miw_node_var* var = miw_node::cast<miw_node_var>(cache_offset.type);
		if(var && var->data_isstatic) //static variable
			invoke_fp = &miw_node_name::invoke_global; //global

		miw_node_block* block = miw_node::cast<miw_node_block>(cache_offset.type);
		if(block)
			invoke_fp = &miw_node_name::invoke_heap; //heap
		else if(cache_base)
			invoke_fp = &miw_node_name::invoke_base; //base
		else
			invoke_fp = &miw_node_name::invoke_local; //local

		return (this->*invoke_fp)(self, vm, seek);
	}

public:
	//data
	std::string data_name; //name

	//cache
	miw_node* cache_base; //base
	miw_vm_variable<miw_node> cache_offset; //offset

	//miw_node_name
	miw_node_name(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		invoke_fp = &miw_node_name::invoke_no_cache;
		data_name = "";

		cache_base = NULL;
	}

	//~miw_node_name
	virtual ~miw_node_name()
	{
	}

	//clear
	virtual miw_node* clear()
	{
		cache_base = NULL;
		cache_offset.reset();

		//
		invoke_fp = &miw_node_name::invoke_no_cache;
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_name* ret = (miw_node_name*)node;
		if(ret == NULL)
			ret = new miw_node_name(line, file);

		//
		ret->data_name = data_name;

		return miw_node::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_name>() || miw_node::rtti(t);
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return (this->*invoke_fp)(self, vm, seek);
	}

	//print
	virtual std::string print(std::string str = "")
	{
		return data_name;
	}

	//
	//to_root
	virtual void to_root()
	{
		invoke_fp = &miw_node_name::invoke_global;
		cache_offset.reset((miw_node*)miw_node::root(), NULL);
	}
};

//miw_node_scope
class miw_node_scope : public miw_node
{
protected:
	miw_vm_variable<miw_node>(miw_node_scope::* invoke_fp)(miw_vm_variable<miw_node>&, miw_vm<miw_node>*, miw_vm_variable<miw_node>*);

	//invoke_local
	miw_vm_variable<miw_node> invoke_local(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_vm_variable<miw_node> ret = self;

		for(std::list<miw_node_name*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			ret = (*it)->invoke(ret, vm, seek);

		return ret;
	}

	//invoke_global
	miw_vm_variable<miw_node> invoke_global(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return (*(--data_value.end()))->cache_offset;
	}

	//invoke_no_cache
	miw_vm_variable<miw_node> invoke_no_cache(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_vm_variable<miw_node> ret = self;

		for(std::list<miw_node_name*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
		{
			ret = (*it)->invoke(ret, vm, seek);

			if(ret.type == NULL) //check root
			{
				ret = (*it)->invoke(miw_vm_variable<miw_node>(miw_node::root(), NULL), vm, seek);

				if(ret.type != NULL)
					(*it)->cache_base = (miw_node*)&miw_node::root();
				else
					break;
			}

			if(miw_node::cast<miw_node_class>(ret.type)) //check base class
			{
				miw_vm_variable<miw_node> base = self.type->find(ret, vm);
				(*it)->cache_base = NULL;

				if(base.type != NULL)
				{
					(*it)->cache_offset = base;
					ret = (*it)->invoke(self, vm, seek);
				}
			}
			else
			{
				self = ret;
			}
		}

		if(ret.type == NULL) //not find
			return miw_vm_variable<miw_node>(); //mido error...

		miw_node_var* var = miw_node::cast<miw_node_var>(ret.type);
		if(var && var->data_isstatic) //static variable
			invoke_fp = &miw_node_scope::invoke_global; //global
		else
			invoke_fp = &miw_node_scope::invoke_local; //local

		return ret;
	}

public:
	//data
	std::list<miw_node_name*> data_value; //values

	//miw_node_scope
	miw_node_scope(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		invoke_fp = &miw_node_scope::invoke_no_cache;
	}

	//~miw_node_scope
	virtual ~miw_node_scope()
	{
		for(std::list<miw_node_name*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			delete *it;
	}

	//clear
	virtual miw_node* clear()
	{
		for(std::list<miw_node_name*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			(*it)->clear();

		//
		invoke_fp = &miw_node_scope::invoke_no_cache;
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_scope* ret = (miw_node_scope*)node;
		if(ret == NULL)
			ret = new miw_node_scope(line, file);

		//
		for(std::list<miw_node_name*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			ret->data_value.push_back((miw_node_name*)(*it)->clone());

		return miw_node::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_scope>() || miw_node::rtti(t);
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_vm_variable<miw_node> ret = (this->*invoke_fp)(self, vm, seek);
		ret.type = ret.type->type();
		if(seek)
			*vm->write() = ret;

		return ret;
	}

	//print
	virtual std::string print(std::string str = "")
	{
		std::list<miw_node_name*>::iterator it = data_value.begin();

		std::string ret = (*it)->print();
		for(++it; it != data_value.end(); ++it)
		{
			ret += "::";
			ret += (*it)->print();
		}

		if(str.compare(""))
		{
			ret += " ";
			ret += str;
		}

		return ret;
	}

	//
	//find_class
	virtual miw_node_class* find_class(miw_node_class* cls)
	{
		std::list<miw_node_name*>::iterator it_scope = data_value.begin();
		std::map<std::string, miw_node_class*>::iterator it_class_end = cls->data_class.end();

		for(std::map<std::string, miw_node_class*>::iterator it_class = cls->data_class.begin(); it_class != it_class_end;)
		{
			if(!(*it_scope)->data_name.compare(it_class->second->data_name))
			{
				++it_scope;
				if(it_scope == data_value.end())
				{
					return it_class->second;
				}
				else
				{
					cls = it_class->second;

					it_class = cls->data_class.begin();
					it_class_end = cls->data_class.end();
				}
			}
			else
			{
				++it_class;
			}
		}

		return NULL;
	}
};

//miw_node_exp
class miw_node_exp : public miw_node
{
protected:
	miw_vm_variable<miw_node>(miw_node_exp::* invoke_fp)(miw_vm_variable<miw_node>&, miw_vm<miw_node>*, miw_vm_variable<miw_node>*);

	//invoke_local_fun
	miw_vm_variable<miw_node> invoke_local_fun(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_node* modify = cache_op.type->modify();

		if(seek == NULL)
			return miw_vm_variable<miw_node>(modify); //return type only

		//vm -> operator
		miw_vm_variable<miw_node> op = self.type->apply(self, vm, seek, *(miw_vm_variable<miw_node>*)&cache_op);

		//vm -> return
		miw_vm_variable<miw_node>* p = vm->write(modify->size());
		p->type = modify;

		//convert
		std::list<miw_node*>::iterator it_convert = cache_convert.begin();

		//vm -> this
		if (*it_convert) //apply convert
		{
			p = vm->write(sizeof(void*));
			p->type = *it_convert;
			*(void**)p->value = op.value;
		}
		else
		{
			vm->write()->reset(cache_op.type->cache_scope, op.value);
		}

		++it_convert;

		//vm -> parameter
		for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it, ++it_convert)
		{
			miw_vm_variable<miw_node> tmp = (*it)->invoke(self, vm, seek);

			//apply convert
			if (*it_convert)
				(*it_convert)->invoke(tmp, vm, seek);
		}

		return cache_op.type->data_exp->invoke(self, vm, seek);
	}

	//invoke_global_fun
	miw_vm_variable<miw_node> invoke_global_fun(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_node* modify = cache_op.type->modify();

		if(seek == NULL)
			return miw_vm_variable<miw_node>(modify); //return type only

		//vm -> return
		miw_vm_variable<miw_node>* p = vm->write(modify->size());
		p->type = modify;

		//convert
		std::list<miw_node*>::iterator it_convert = cache_convert.begin();

		//vm -> parameter
		for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it, ++it_convert)
		{
			if (*it_convert) //apply convert
				(*it_convert)->invoke((*it)->invoke(self, vm, seek), vm, seek);
			else
				(*it)->invoke(self, vm, seek);
		}

		return cache_op.type->data_exp->invoke(self, vm, seek);
	}

	//invoke_local_var
	miw_vm_variable<miw_node> invoke_local_var(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_node* modify = cache_op.type->modify();

		if(seek == NULL)
			return miw_vm_variable<miw_node>(modify); //return type only

		//vm -> operator
		cache_op.value = data_op->invoke(self, vm, seek).value;

		//vm -> return
		miw_vm_variable<miw_node>* p = vm->reserve(modify->size()); //union space with operator
		p->type = modify;

		//convert
		std::list<miw_node*>::iterator it_convert = cache_convert.begin();

		//vm -> this
		if (*it_convert) //apply convert
		{
			p = vm->write(sizeof(void*));
			p->type = *it_convert;
			*(void**)p->value = cache_op.value;
		}
		else
		{
			vm->write()->reset(cache_op.type->cache_scope, cache_op.value);
		}

		//vm -> parameter
		for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it, ++it_convert)
		{
			if (*it_convert) //apply convert
				(*it_convert)->invoke((*it)->invoke(self, vm, seek), vm, seek);
			else
				(*it)->invoke(self, vm, seek);
		}

		return cache_op.type->data_exp->invoke(self, vm, seek);
	}

	//invoke_global_var
	miw_vm_variable<miw_node> invoke_global_var(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_node* modify = cache_op.type->modify();

		if(seek == NULL)
			return miw_vm_variable<miw_node>(modify); //return type only

		//vm -> operator
		cache_op.value = data_op->invoke(self, vm, seek).value;

		//vm -> return
		miw_vm_variable<miw_node>* p = vm->reserve(modify->size()); //union space with operator
		p->type = modify;

		//convert
		std::list<miw_node*>::iterator it_convert = cache_convert.begin();

		//vm -> parameter
		for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it, ++it_convert)
		{
			if (*it_convert) //apply convert
				(*it_convert)->invoke((*it)->invoke(self, vm, seek), vm, seek);
			else
				(*it)->invoke(self, vm, seek);
		}

		return cache_op.type->data_exp->invoke(self, vm, seek);
	}

	//invoke_no_cache
	miw_vm_variable<miw_node> invoke_no_cache(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		//operator
		miw_vm_variable<miw_node> op = data_op->invoke(self, vm, NULL);

		miw_node_vars* vars = miw_node::cast<miw_node_vars>(op.type);
		if(vars) //is function
		{
			//create a temp function
			miw_node_fun* fun = new miw_node_fun(line, file);
			fun->modify(new miw_node(line, file));

			//add to parameter
			for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
				fun->data_parameter.push_back((*it)->invoke(self, vm, NULL).type);

			fun->invoke(self, vm, NULL);

			//find best match
			cache_op.type = miw_node::cast<miw_node_fun>(vars->compare(fun));
			if (cache_op.type)
			{
				for (size_t i = 0; i < cache_op.type->data_parameter.size(); ++i)
					cache_convert.push_back(NULL);
			}
			else //find convert match
			{
				for (std::list<miw_node_var*>::iterator it = vars->data_vars.begin(); it != vars->data_vars.end(); ++it)
				{
					cache_op.type = miw_node::cast<miw_node_fun>((*it)->type());
					if (fun_convert(self, vm, cache_op.type))
						break;
				}
			}
			
			//clear temp fun
			fun->data_parameter.clear();
			delete fun;

			if(cache_op.type == NULL)
				return miw_vm_variable<miw_node>(); //mido error...

			cache_op.value = self.type->find(miw_vm_variable<miw_node>(cache_op.type->cache_scope), vm).value;

			if (cache_op.type->data_isstatic)
			{
				invoke_fp = &miw_node_exp::invoke_global_fun;
			}
			else
			{
				invoke_fp = &miw_node_exp::invoke_local_fun;

				if (miw_node::cast<miw_node_pointer>(self.type->type()))
				{
					cache_convert.push_front(NULL);
				}
				else //convert to this
				{
					miw_node_pointer* node = new miw_node_pointer(line, file);
					cache_convert.push_front(node->modify(self.type->type()));
				}
			}
		}
		else //is variable
		{
			cache_op.type = miw_node::cast<miw_node_fun>(op.type);
			if (cache_op.type == NULL || fun_convert(self, vm, cache_op.type) == false)	//find convert
				return miw_vm_variable<miw_node>(); //mido error...

			if (cache_op.type->data_isstatic)
			{
				invoke_fp = &miw_node_exp::invoke_global_var;
			}
			else
			{
				invoke_fp = &miw_node_exp::invoke_local_var;

				if (miw_node::cast<miw_node_pointer>(self.type->type()))
				{
					cache_convert.push_front(NULL);
				}
				else //convert to this
				{
					miw_node_pointer* node = new miw_node_pointer(line, file);
					cache_convert.push_front(node->modify(self.type->type()));
				}
			}
		}

		return vm ? (this->*invoke_fp)(self, vm, seek) : miw_vm_variable<miw_node>(cache_op.type->modify());
	}

public:
	//data
	miw_node*				data_op;
	std::list<miw_node*>	data_value;

	//cache
	miw_vm_variable<miw_node_fun>	cache_op;
	std::list<miw_node*>			cache_convert;

	//miw_node_exp
	miw_node_exp(int _line, const char* _file)
		: miw_node(_line, _file)
	{
		invoke_fp = &miw_node_exp::invoke_no_cache;
		data_op = NULL;
	}

	//~miw_node_exp
	virtual ~miw_node_exp()
	{
		delete data_op;

		for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			delete *it;

		for (std::list<miw_node*>::iterator it = cache_convert.begin(); it != cache_convert.end(); ++it)
		{
			if (*it)
			{
				miw_node_pointer* node = miw_node::cast<miw_node_pointer>(*it); //this
				if (node)
					node->modify(NULL);

				delete *it;
			}
		}
	}

	//clear
	virtual miw_node* clear()
	{
		data_op->clear();

		for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			delete (*it)->clear();

		for (std::list<miw_node*>::iterator it = cache_convert.begin(); it != cache_convert.end(); ++it)
		{
			if (*it)
			{
				miw_node_pointer* node = miw_node::cast<miw_node_pointer>(*it); //this
				if (node)
					node->modify(NULL);

				delete *it;
			}
		}

		//
		cache_op.reset();
		return this;
	}

	//clone
	virtual miw_node* clone(miw_node* node = NULL)
	{
		miw_node_exp* ret = (miw_node_exp*)node;
		if(ret == NULL)
			ret = new miw_node_exp(line, file);

		//
		ret->data_op = data_op->clone();

		for(std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			ret->data_value.push_back((*it)->clone());

		return miw_node::clone(ret);
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_exp>() || miw_node::rtti(t);
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		return (this->*invoke_fp)(self, vm, seek);
	}

	//
	//fun_convert
	virtual bool fun_convert(miw_vm_variable<miw_node>& self, miw_vm<miw_node>* vm, miw_node_fun* fun)
	{
		if (fun == NULL)
			return false;

		//create a temp function
		miw_node_fun* tmp = new miw_node_fun(line, file);
		tmp->modify(new miw_node(line, file));

		//add to parameter
		for (std::list<miw_node*>::iterator it = data_value.begin(); it != data_value.end(); ++it)
			tmp->data_parameter.push_back((*it)->invoke(self, vm, NULL).type);

		tmp->invoke(self, vm, NULL);

		//mido

		//clear temp fun
		tmp->data_parameter.clear();
		delete tmp;

		return false;
	}
};

#endif
