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

#ifndef MIW_CPP_NATIVE
#define MIW_CPP_NATIVE

#include "miw_cpp_compiler.h"

namespace miw_cpp
{
	//reg_var
	static miw_node_var* reg_var(std::string decl, void* value = NULL, std::string name = "")
	{
		//parser decl
		miw_cpp::compiler compiler = miw_cpp::compiler((void*)decl.c_str(), decl.length(), NULL);

		std::list<miw_node_var*> fun;
		compiler.parser_decl_list(fun);

		if(fun.size() <= 0)
			return NULL;

		//create node
		miw_node_var* ret = *fun.begin();
		ret->data_isnative = true;
		ret->cache_var.value = value;

		//replace name
		if(name.compare(""))
			ret->data_name = name;

		miw_node_scope* scope = miw_node::cast<miw_node_scope>(ret->info_scope);
		if(scope)
		{
			miw_node_class* cls = scope->find_class(miw_node::root());
			if(cls && cls->reg_variable(ret))
				return ret;
		}
		else if(ret->info_scope == NULL && miw_node::root()->reg_variable(ret)) //is root
		{
			return ret;
		}

		delete ret;
		return NULL;
	}

	//reg_fun
	static miw_node_var* reg_fun(std::string decl, void(*fp)(), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v0* exp = new miw_node_native_global_v0(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v1<typename P0>* exp = new miw_node_native_global_v1<typename P0>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v2<typename P0, typename P1>* exp = new miw_node_native_global_v2<typename P0, typename P1>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v3<typename P0, typename P1, typename P2>* exp = new miw_node_native_global_v3<typename P0, typename P1, typename P2>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2, typename P3>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2, P3), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v4<typename P0, typename P1, typename P2, typename P3>* exp = new miw_node_native_global_v4<typename P0, typename P1, typename P2, typename P3>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2, typename P3, typename P4>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2, P3, P4), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v5<typename P0, typename P1, typename P2, typename P3, typename P4>* exp = new miw_node_native_global_v5<typename P0, typename P1, typename P2, typename P3, typename P4>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2, P3, P4, P5), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v6<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>* exp = new miw_node_native_global_v6<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2, P3, P4, P5, P6), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v7<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>* exp = new miw_node_native_global_v7<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2, P3, P4, P5, P6, P7), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v8<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>* exp = new miw_node_native_global_v8<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v9<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>* exp = new miw_node_native_global_v9<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	static miw_node_var* reg_fun(std::string decl, void(*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_v10<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>* exp = new miw_node_native_global_v10<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_0<typename R>* exp = new miw_node_native_global_0<typename R>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_1<typename R, typename P0>* exp = new miw_node_native_global_1<typename R, typename P0>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_2<typename R, typename P0, typename P1>* exp = new miw_node_native_global_2<typename R, typename P0, typename P1>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_3<typename R, typename P0, typename P1, typename P2>* exp = new miw_node_native_global_3<typename R, typename P0, typename P1, typename P2>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2, typename P3>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2, P3), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_4<typename R, typename P0, typename P1, typename P2, typename P3>* exp = new miw_node_native_global_4<typename R, typename P0, typename P1, typename P2, typename P3>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2, P3, P4), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_5<typename R, typename P0, typename P1, typename P2, typename P3, typename P4>* exp = new miw_node_native_global_5<typename R, typename P0, typename P1, typename P2, typename P3, typename P4>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2, P3, P4, P5), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_6<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>* exp = new miw_node_native_global_6<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2, P3, P4, P5, P6), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_7<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>* exp = new miw_node_native_global_7<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2, P3, P4, P5, P6, P7), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_8<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>* exp = new miw_node_native_global_8<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_9<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>* exp = new miw_node_native_global_9<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	static miw_node_var* reg_fun(std::string decl, R(*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_global_10<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>* exp = new miw_node_native_global_10<typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v0<typename T>* exp = new miw_node_native_local_v0<typename T>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v1<typename T, typename P0>* exp = new miw_node_native_local_v1<typename T, typename P0>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v2<typename T, typename P0, typename P1>* exp = new miw_node_native_local_v2<typename T, typename P0, typename P1>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v3<typename T, typename P0, typename P1, typename P2>* exp = new miw_node_native_local_v3<typename T, typename P0, typename P1, typename P2>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2, typename P3>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2, P3), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v4<typename T, typename P0, typename P1, typename P2, typename P3>* exp = new miw_node_native_local_v4<typename T, typename P0, typename P1, typename P2, typename P3>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2, P3, P4), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v5<typename T, typename P0, typename P1, typename P2, typename P3, typename P4>* exp = new miw_node_native_local_v5<typename T, typename P0, typename P1, typename P2, typename P3, typename P4>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2, P3, P4, P5), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v6<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>* exp = new miw_node_native_local_v6<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2, P3, P4, P5, P6), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v7<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>* exp = new miw_node_native_local_v7<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2, P3, P4, P5, P6, P7), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v8<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>* exp = new miw_node_native_local_v8<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v9<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>* exp = new miw_node_native_local_v9<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	static miw_node_var* reg_fun(std::string decl, void(T::*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_v10<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>* exp = new miw_node_native_local_v10<typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_0<typename R, typename T>* exp = new miw_node_native_local_0<typename R, typename T>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_1<typename R, typename T, typename P0>* exp = new miw_node_native_local_1<typename R, typename T, typename P0>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_2<typename R, typename T, typename P0, typename P1>* exp = new miw_node_native_local_2<typename R, typename T, typename P0, typename P1>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_3<typename R, typename T, typename P0, typename P1, typename P2>* exp = new miw_node_native_local_3<typename R, typename T, typename P0, typename P1, typename P2>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2, typename P3>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2, P3), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_4<typename R, typename T, typename P0, typename P1, typename P2, typename P3>* exp = new miw_node_native_local_4<typename R, typename T, typename P0, typename P1, typename P2, typename P3>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2, P3, P4), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_5<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4>* exp = new miw_node_native_local_5<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2, P3, P4, P5), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_6<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>* exp = new miw_node_native_local_6<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2, P3, P4, P5, P6), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_7<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>* exp = new miw_node_native_local_7<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2, P3, P4, P5, P6, P7), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_8<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>* exp = new miw_node_native_local_8<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_9<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>* exp = new miw_node_native_local_9<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}

	template <typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	static miw_node_var* reg_fun(std::string decl, R(T::*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9), std::string name = "")
	{
		miw_node_var* ret = reg_var(decl, NULL, name);
		if(ret)
		{
			miw_node_native_local_10<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>* exp = new miw_node_native_local_10<typename R, typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>(__LINE__, __FILE__);
			ret->data_exp = exp;
			exp->data_fp = fp;
		}

		return ret;
	}
};

#endif
