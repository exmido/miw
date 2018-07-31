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

#ifndef MIW_VM_H
#define MIW_VM_H

#include "stdlib.h"

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

//miw_vm_variable
template <class T>
class miw_vm_variable
{
public:
	T * type;
	void* value;

	//reset
	void reset(T* _type = NULL, void* _value = NULL)
	{
		type = _type;
		value = _value;
	}

	//miw_vm_variable
	miw_vm_variable(T* _type = NULL, void* _value = NULL)
	{
		reset(_type, _value);
	}

	//seek
	void* seek(size_t _value)
	{
		return value = (unsigned char*)value + _value;
	}

	void* seek(void* _value)
	{
		return value = (unsigned char*)value + (size_t)_value;
	}
};

//miw_vm_register
template <class T>
class miw_vm_register : public miw_vm_variable<typename T>
{
public:
	unsigned char* mem;
};

//miw_vm
template <class T>
class miw_vm
{
protected:
	miw_vm_register<typename T>* var;
	miw_vm_register<typename T>* var_seek;

	unsigned char* mem;
	unsigned char* mem_seek;

public:
	//miw_vm
	miw_vm(size_t var_size, size_t mem_size)
	{
		var = new miw_vm_register<typename T>[var_size];
		mem = new unsigned char[mem_size];

		//
		reset();
	}

	//~miw_vm
	~miw_vm()
	{
		delete[] var;
		delete[] mem;
	}

	//reset
	void reset()
	{
		var_seek = var;
		mem_seek = var_seek->mem = mem;
	}

	//read
	miw_vm_variable<typename T>* read()
	{
		miw_vm_variable<typename T>* ret = (miw_vm_variable<typename T>*)var_seek;
		--var_seek;
		mem_seek = var_seek->mem;
		return ret;
	}

	//write
	miw_vm_variable<typename T>* write()
	{
		++var_seek;
		var_seek->mem = mem_seek;
		return (miw_vm_variable<typename T>*)var_seek;
	}

	miw_vm_variable<typename T>* write(size_t size)
	{
		++var_seek;

		var_seek->value = mem_seek;
		mem_seek += size;

		var_seek->mem = mem_seek;
		return (miw_vm_variable<typename T>*)var_seek;
	}

	//reserve
	miw_vm_variable<typename T>* reserve(size_t size)
	{
		var_seek->value = mem_seek;
		mem_seek += size;

		var_seek->mem = mem_seek;
		return (miw_vm_variable<typename T>*)var_seek;
	}

	//base
	miw_vm_variable<typename T>* base()const
	{
		return (miw_vm_variable<typename T>*)var;
	}

	//offset
	size_t offset(miw_vm_variable<typename T>* end, miw_vm_variable<typename T>* start)
	{
		return (miw_vm_register<typename T>*)end - (miw_vm_register<typename T>*)start;
	}

	//getseek
	miw_vm_variable<typename T>* getseek()const
	{
		return (miw_vm_variable<typename T>*)var_seek;
	}

	miw_vm_variable<typename T>* getseek(miw_vm_variable<typename T>* seek, size_t offset)const
	{
		return (miw_vm_register<typename T>*)seek + offset;
	}

	//setseek
	miw_vm_variable<typename T>* setseek(miw_vm_variable<typename T>* seek)
	{
		var_seek = (miw_vm_register<typename T>*)seek;
		mem_seek = var_seek->mem;
		return seek;
	}

	miw_vm_variable<typename T>* setseek(miw_vm_variable<typename T>* seek, size_t offset)
	{
		var_seek = (miw_vm_register<typename T>*)seek + offset;
		mem_seek = var_seek->mem;
		return (miw_vm_variable<typename T>*)var_seek;
	}
};

#endif
