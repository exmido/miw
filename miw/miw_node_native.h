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

#ifndef MIW_NODE_NATIVE_H
#define MIW_NODE_NATIVE_H

#include "miw_node.h"

//miw_node_native
class miw_node_native : public miw_node
{
public:
	//miw_node_native
	miw_node_native(int _line, const char* _file)
		: miw_node(_line, _file)
	{
	}

	//rtti
	virtual bool rtti(unsigned int t)
	{
		return t == miw_node::rttype<miw_node_native>() || miw_node::rtti(t);
	}
};

//miw_node_native_local_v0
template <typename T>
class miw_node_native_local_v0 : public miw_node_native
{
public:
	void(T::*data_fp)();

	//miw_node_native_local_v0
	miw_node_native_local_v0(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)();
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v1
template <typename T, typename P0>
class miw_node_native_local_v1 : public miw_node_native
{
public:
	void(T::*data_fp)(P0);

	//miw_node_native_local_v1
	miw_node_native_local_v1(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v2
template <typename T, typename P0, typename P1>
class miw_node_native_local_v2 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1);

	//miw_node_native_local_v2
	miw_node_native_local_v2(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v3
template <typename T, typename P0, typename P1, typename P2>
class miw_node_native_local_v3 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2);

	//miw_node_native_local_v3
	miw_node_native_local_v3(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v4
template <typename T, typename P0, typename P1, typename P2, typename P3>
class miw_node_native_local_v4 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2, P3);

	//miw_node_native_local_v4
	miw_node_native_local_v4(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2, *p3);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v5
template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4>
class miw_node_native_local_v5 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2, P3, P4);

	//miw_node_native_local_v5
	miw_node_native_local_v5(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2, *p3, *p4);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v6
template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
class miw_node_native_local_v6 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2, P3, P4, P5);

	//miw_node_native_local_v6
	miw_node_native_local_v6(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v7
template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class miw_node_native_local_v7 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6);

	//miw_node_native_local_v7
	miw_node_native_local_v7(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v8
template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class miw_node_native_local_v8 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7);

	//miw_node_native_local_v8
	miw_node_native_local_v8(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p7 = (typename P7*)vm->read()->value;
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v9
template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class miw_node_native_local_v9 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8);

	//miw_node_native_local_v9
	miw_node_native_local_v9(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p8 = (typename P8*)vm->read()->value;
		typename P0* p7 = (typename P7*)vm->read()->value;
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_v10
template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
class miw_node_native_local_v10 : public miw_node_native
{
public:
	void(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);

	//miw_node_native_local_v10
	miw_node_native_local_v10(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p9 = (typename P9*)vm->read()->value;
		typename P0* p8 = (typename P8*)vm->read()->value;
		typename P0* p7 = (typename P7*)vm->read()->value;
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9);
		ret->value = NULL;
		return *ret;
	}
};


//miw_node_native_global_0
template <typename R>
class miw_node_native_global_0 : public miw_node_native
{
public:
	R(*data_fp)();

	//miw_node_native_global_0
	miw_node_native_global_0(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)();
		return *ret;
	}
};

//miw_node_native_global_1
template <typename R, typename P0>
class miw_node_native_global_1 : public miw_node_native
{
public:
	R(*data_fp)(P0);

	//miw_node_native_global_1
	miw_node_native_global_1(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0);
		return *ret;
	}
};

//miw_node_native_global_2
template <typename R, typename P0, typename P1>
class miw_node_native_global_2 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1);

	//miw_node_native_global_2
	miw_node_native_global_2(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1);
		return *ret;
	}
};

//miw_node_native_global_3
template <typename R, typename P0, typename P1, typename P2>
class miw_node_native_global_3 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2);

	//miw_node_native_global_3
	miw_node_native_global_3(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2);
		return *ret;
	}
};

//miw_node_native_global_4
template <typename R, typename P0, typename P1, typename P2, typename P3>
class miw_node_native_global_4 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2, P3);

	//miw_node_native_global_4
	miw_node_native_global_4(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2, *p3);
		return *ret;
	}
};

//miw_node_native_global_5
template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4>
class miw_node_native_global_5 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2, P3, P4);

	//miw_node_native_global_5
	miw_node_native_global_5(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2, *p3, *p4);
		return *ret;
	}
};

//miw_node_native_global_6
template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
class miw_node_native_global_6 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2, P3, P4, P5);

	//miw_node_native_global_6
	miw_node_native_global_6(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5);
		return *ret;
	}
};

//miw_node_native_global_7
template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class miw_node_native_global_7 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2, P3, P4, P5, P6);

	//miw_node_native_global_7
	miw_node_native_global_7(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6);
		return *ret;
	}
};

//miw_node_native_global_8
template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class miw_node_native_global_8 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7);

	//miw_node_native_global_8
	miw_node_native_global_8(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P7* p7 = (typename P7*)vm->read()->value;
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7);
		return *ret;
	}
};

//miw_node_native_global_9
template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class miw_node_native_global_9 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8);

	//miw_node_native_global_9
	miw_node_native_global_9(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P8* p8 = (typename P8*)vm->read()->value;
		typename P7* p7 = (typename P7*)vm->read()->value;
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8);
		return *ret;
	}
};

//miw_node_native_global_10
template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
class miw_node_native_global_10 : public miw_node_native
{
public:
	R(*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);

	//miw_node_native_global_10
	miw_node_native_global_10(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P9* p9 = (typename P9*)vm->read()->value;
		typename P8* p8 = (typename P8*)vm->read()->value;
		typename P7* p7 = (typename P7*)vm->read()->value;
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9);
		return *ret;
	}
};

//miw_node_native_global_v0
class miw_node_native_global_v0 : public miw_node_native
{
public:
	void(*data_fp)();

	//miw_node_native_global_v0
	miw_node_native_global_v0(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)();
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v1
template <typename P0>
class miw_node_native_global_v1 : public miw_node_native
{
public:
	void(*data_fp)(P0);

	//miw_node_native_global_v1
	miw_node_native_global_v1(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v2
template <typename P0, typename P1>
class miw_node_native_global_v2 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1);

	//miw_node_native_global_v2
	miw_node_native_global_v2(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v3
template <typename P0, typename P1, typename P2>
class miw_node_native_global_v3 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2);

	//miw_node_native_global_v3
	miw_node_native_global_v3(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v4
template <typename P0, typename P1, typename P2, typename P3>
class miw_node_native_global_v4 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2, P3);

	//miw_node_native_global_v4
	miw_node_native_global_v4(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2, *p3);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v5
template <typename P0, typename P1, typename P2, typename P3, typename P4>
class miw_node_native_global_v5 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2, P3, P4);

	//miw_node_native_global_v5
	miw_node_native_global_v5(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2, *p3, *p4);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v6
template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
class miw_node_native_global_v6 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2, P3, P4, P5);

	//miw_node_native_global_v6
	miw_node_native_global_v6(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v7
template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class miw_node_native_global_v7 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2, P3, P4, P5, P6);

	//miw_node_native_global_v7
	miw_node_native_global_v7(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v8
template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class miw_node_native_global_v8 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7);

	//miw_node_native_global_v8
	miw_node_native_global_v8(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P7* p7 = (typename P7*)vm->read()->value;
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v9
template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class miw_node_native_global_v9 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8);

	//miw_node_native_global_v9
	miw_node_native_global_v9(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P8* p8 = (typename P8*)vm->read()->value;
		typename P7* p7 = (typename P7*)vm->read()->value;
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_global_v10
template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
class miw_node_native_global_v10 : public miw_node_native
{
public:
	void(*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);

	//miw_node_native_global_v10
	miw_node_native_global_v10(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P9* p9 = (typename P9*)vm->read()->value;
		typename P8* p8 = (typename P8*)vm->read()->value;
		typename P7* p7 = (typename P7*)vm->read()->value;
		typename P6* p6 = (typename P6*)vm->read()->value;
		typename P5* p5 = (typename P5*)vm->read()->value;
		typename P4* p4 = (typename P4*)vm->read()->value;
		typename P3* p3 = (typename P3*)vm->read()->value;
		typename P2* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		(*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9);
		ret->value = NULL;
		return *ret;
	}
};

//miw_node_native_local_0
template <typename R, typename T>
class miw_node_native_local_0 : public miw_node_native
{
public:
	R(T::*data_fp)();

	//miw_node_native_local_0
	miw_node_native_local_0(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)();
		return *ret;
	}
};

//miw_node_native_local_1
template <typename R, typename T, typename P0>
class miw_node_native_local_1 : public miw_node_native
{
public:
	R(T::*data_fp)(P0);

	//miw_node_native_local_1
	miw_node_native_local_1(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0);
		return *ret;
	}
};

//miw_node_native_local_2
template <typename R, typename T, typename P0, typename P1>
class miw_node_native_local_2 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1);

	//miw_node_native_local_2
	miw_node_native_local_2(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1);
		return *ret;
	}
};

//miw_node_native_local_3
template <typename R, typename T, typename P0, typename P1, typename P2>
class miw_node_native_local_3 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2);

	//miw_node_native_local_3
	miw_node_native_local_3(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2);
		return *ret;
	}
};

//miw_node_native_local_4
template <typename R, typename T, typename P0, typename P1, typename P2, typename P3>
class miw_node_native_local_4 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2, P3);

	//miw_node_native_local_4
	miw_node_native_local_4(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2, *p3);
		return *ret;
	}
};

//miw_node_native_local_5
template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4>
class miw_node_native_local_5 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2, P3, P4);

	//miw_node_native_local_5
	miw_node_native_local_5(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2, *p3, *p4);
		return *ret;
	}
};

//miw_node_native_local_6
template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
class miw_node_native_local_6 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2, P3, P4, P5);

	//miw_node_native_local_6
	miw_node_native_local_6(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5);
		return *ret;
	}
};

//miw_node_native_local_7
template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class miw_node_native_local_7 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6);

	//miw_node_native_local_7
	miw_node_native_local_7(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6);
		return *ret;
	}
};

//miw_node_native_local_8
template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class miw_node_native_local_8 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7);

	//miw_node_native_local_8
	miw_node_native_local_8(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p7 = (typename P7*)vm->read()->value;
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9);
		return *ret;
	}
};

//miw_node_native_local_9
template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class miw_node_native_local_9 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8);

	//miw_node_native_local_9
	miw_node_native_local_9(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p8 = (typename P8*)vm->read()->value;
		typename P0* p7 = (typename P7*)vm->read()->value;
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9);
		return *ret;
	}
};

//miw_node_native_local_10
template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
class miw_node_native_local_10 : public miw_node_native
{
public:
	R(T::*data_fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);

	//miw_node_native_local_10
	miw_node_native_local_10(int _line, const char* _file)
		: miw_node_native(_line, _file)
	{
		data_fp = NULL;
	}

	//invoke
	virtual miw_vm_variable<miw_node> invoke(miw_vm_variable<miw_node> self, miw_vm<miw_node>* vm, miw_vm_variable<miw_node>* seek)
	{
		typename P0* p9 = (typename P9*)vm->read()->value;
		typename P0* p8 = (typename P8*)vm->read()->value;
		typename P0* p7 = (typename P7*)vm->read()->value;
		typename P0* p6 = (typename P6*)vm->read()->value;
		typename P0* p5 = (typename P5*)vm->read()->value;
		typename P0* p4 = (typename P4*)vm->read()->value;
		typename P0* p3 = (typename P3*)vm->read()->value;
		typename P0* p2 = (typename P2*)vm->read()->value;
		typename P1* p1 = (typename P1*)vm->read()->value;
		typename P0* p0 = (typename P0*)vm->read()->value;
		typename T* t = *(typename T**)vm->read()->value;

		miw_vm_variable<miw_node>* ret = vm->getseek();
		*(typename R*)ret->value = (t->*data_fp)(*p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9);
		return *ret;
	}
};

#endif
