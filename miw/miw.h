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

#ifndef MIW_H
#define MIW_H

#include "miw_node_native.h"

//miw
namespace miw
{
	//object_new
	template <typename T>
	inline static void* object_new(void* ptr)
	{
		return ptr ? new T(*(T*)ptr) : new T;
	}

	//object_delete
	template <typename T>
	inline static void object_delete(void* ptr)
	{
		delete (T*)ptr;
	}

	//object_clear
	inline static void object_clear(void* ptr)
	{
	}

	//object_fp
	class object_fp
	{
	public:
		void* (*new_fp)(void*);
		void(*delete_fp)(void*);
		void(*clear_fp)(void*);

		//object_fp
		object_fp(void* (*_new_fp)(void*) = NULL, void(*_delete_fp)(void*) = NULL)
		{
			new_fp = _new_fp;
			delete_fp = _delete_fp;
			clear_fp = object_clear;
		}
	};

	//object_fun
	template <typename T>
	inline static object_fp* object_fun()
	{
		static object_fp* ret = new object_fp(object_new<typename T>, object_delete<typename T>);
		return ret;
	}

	//object_map
	inline static std::map<void*, size_t>& object_map()
	{
		static std::map<void*, size_t>* ret = new std::map<void*, size_t>();
		return *ret;
	}

	//object
	template <typename TT>
	class object
	{
	protected:
		//add
		void* add(void* _ptr)
		{
			std::map<void*, size_t>::iterator it = object_map().find(_ptr);
			if(it == object_map().end())
				it = object_map().insert(std::pair<void*, size_t>(fp->new_fp(_ptr), 0)).first;

			++it->second;
			return it->first;
		}

		//remove
		void remove()
		{
			std::map<void*, size_t>::iterator it = object_map().find(ptr);
			if(it != object_map().end())
			{
				--it->second;

				if(it->second <= 0)
				{
					fp->delete_fp(ptr);
					object_map().erase(it);
				}
			}
		}

	public:
		void* ptr;
		object_fp* fp;

		//object
		object()
		{
			ptr = NULL;
			fp = NULL;
		}

		object(const object& r)
		{
			fp = NULL;
			*this = r;
		}

		template <typename T>
		object(const object<T>& r)
		{
			fp = NULL;
			*this = r;
		}

		object(char r)
		{
			fp = NULL;
			*this = r;
		}

		object(short r)
		{
			fp = NULL;
			*this = r;
		}

		object(int r)
		{
			fp = NULL;
			*this = r;
		}

		object(long long r)
		{
			fp = NULL;
			*this = r;
		}

		object(unsigned char r)
		{
			fp = NULL;
			*this = r;
		}

		object(unsigned short r)
		{
			fp = NULL;
			*this = r;
		}

		object(unsigned int r)
		{
			fp = NULL;
			*this = r;
		}

		object(unsigned long long r)
		{
			fp = NULL;
			*this = r;
		}

		object(float r)
		{
			fp = NULL;
			*this = r;
		}

		object(double r)
		{
			*this = r;
		}

		template <typename T>
		object(const T* r)
		{
			fp = NULL;
			*this = r;
		}

		template <typename T>
		object(const T& r)
		{
			fp = NULL;
			*this = r;
		}

		//~object
		~object()
		{
			if(fp)
			{
				fp->clear_fp(ptr);
				remove();
			}
		}

		// *@
		TT& operator * () const
		{
			return fp ? *((TT*)ptr) : *((TT*)&ptr);
		}

		// @->
		TT* operator -> () const
		{
			return fp ? ((TT*)ptr) : ((TT*)&ptr);
		}

		// @=
		object& operator = (const object& r)
		{
			if(fp)
				remove();

			fp = r.fp;
			ptr = fp ? add(r.ptr) : r.ptr;
			return *this;
		}

		template <typename T>
		object& operator = (const object<typename T>& r)
		{
			if(fp)
				remove();

			fp = r.fp;
			ptr = fp ? add(r.ptr) : r.ptr;
			return *this;
		}

		object& operator = (char r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((char*)&ptr) = r;
			return *this;
		}

		object& operator = (short r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((short*)&ptr) = r;
			return *this;
		}

		object& operator = (int r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((int*)&ptr) = r;
			return *this;
		}

		object& operator = (long long r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((long long*)&ptr) = r;
			return *this;
		}

		object& operator = (unsigned char r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((unsigned char*)&ptr) = r;
			return *this;
		}

		object& operator = (unsigned short r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((unsigned short*)&ptr) = r;
			return *this;
		}

		object& operator = (unsigned int r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((int*)&ptr) = r;
			return *this;
		}

		object& operator = (unsigned long long r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((unsigned long long*)&ptr) = r;
			return *this;
		}

		object& operator = (float r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((float*)&ptr) = r;
			return *this;
		}

		object& operator = (double r)
		{
			if(fp)
				remove();

			fp = NULL;
			*((double*)&ptr) = r;
			return *this;
		}

		template <typename T>
		object& operator = (const T* r)
		{
			if(fp)
				remove();

			fp = NULL;
			ptr = (void*)r;
			return *this;
		}

		template <typename T>
		object& operator = (const T& r)
		{
			if(fp)
				remove();

			fp = object_fun<T>();
			ptr = add((void*)&r);
			return *this;
		}

		// @==
		template <typename T>
		bool operator == (const object<T>& r)
		{
			return ptr == r.ptr;
		}

		bool operator == (char r)
		{
			return *((char*)&ptr) == r;
		}

		bool operator == (short r)
		{
			return *((short*)&ptr) == r;
		}

		bool operator == (int r)
		{
			return *((int*)&ptr) == r;
		}

		bool operator == (long long r)
		{
			return *((long long*)&ptr) == r;
		}

		bool operator == (unsigned char r)
		{
			return *((unsigned char*)&ptr) == r;
		}

		bool operator == (unsigned short r)
		{
			return *((unsigned short*)&ptr) == r;
		}

		bool operator == (unsigned int r)
		{
			return *((unsigned int*)&ptr) == r;
		}

		bool operator == (unsigned long long r)
		{
			return *((unsigned long long*)&ptr) == r;
		}

		bool operator == (float r)
		{
			return *((float*)&ptr) == r;
		}

		bool operator == (double r)
		{
			return *((double*)&ptr) == r;
		}
	};

	//object_less
	template <typename T>
	class object_less
	{
	public:
		bool operator() (const object<typename T>& left, const object<typename T>& right) const
		{
			return left.ptr < right.ptr;
		}
	};
}

#endif
