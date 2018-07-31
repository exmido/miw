#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <string.h>

typedef unsigned char BYTE;

//filelength
inline unsigned int filelength(const char* filename)
{
	//load file
	FILE *fp = fopen(filename, "rb");
	if(fp == NULL)
		return 0;

	//get file length
	fseek(fp, 0, SEEK_END);
	unsigned int length = ftell(fp);

	fclose(fp);
	return length;
}

//mem
class mem
{
public:
	union
	{
		BYTE*			ptr;

		//
		void*			pvoid;

		char*			ps8;
		unsigned char*	pu8;

		short*			ps16;
		unsigned short*	pu16;

		int*			ps32;
		unsigned int*	pu32;

		float*			pf32;
		double*			pf64;
	};

	unsigned int size;

	//mem
	mem(void* objptr = NULL, unsigned int objsize = 0)
	{
		set(objptr, objsize);
	}

	mem(const mem& m)
	{
		*this = m;
	}

	//init
	void init(unsigned int objsize) //need del()
	{
		size = objsize;
		ptr = new BYTE[size];
	}

	void init(const mem* m) //need del()
	{
		if(m && m->size > 0)
		{
			init(m->size);
			memcpy(ptr, m->ptr, m->size);
		}
		else
		{
			set(NULL, 0);
		}
	}

	//del
	void del()
	{
		if(ptr != NULL)
			delete[] ptr;

		ptr = NULL;
		size = 0;
	}

	//set
	void set(void* objptr, unsigned int objsize)
	{
		pvoid = objptr;
		size = objsize;
	}

	//read
	void* read(unsigned int objsize) //can not del()
	{
		if(objsize == 0 || objsize > size)
			return NULL;

		void* ret = ptr;

		size -= objsize;
		ptr += objsize;

		return ret;
	}

	//write
	bool write(void* objptr, unsigned int objsize) //can not del()
	{
		if(objsize == 0 || objsize > size)
			return false;

		memcpy(ptr, objptr, objsize);

		size -= objsize;
		ptr += objsize;

		return true;
	}

	//save
	//if size == 0. it save data use mem size
	bool save(const char* filename, const char* control = "wb", unsigned int offset = 0, unsigned int objsize = 0)
	{
		FILE *fp = fopen(filename, control);
		if(fp == NULL)
			return false;

		if(offset && !fseek(fp, offset, SEEK_SET))
			return false;

		fwrite(ptr, objsize ? objsize : size, 1, fp);

		fclose(fp);
		return true;
	}

	//load
	//if size == 0. it load data until file EOF.
	//return size of load.
	unsigned int load(const char* filename, unsigned int offset = 0, unsigned int objsize = 0,
		const char* control = "rb") //need del()
	{
		FILE *fp = fopen(filename, control);
		if(fp == NULL)
			return 0;

		//get file length.
		fseek(fp, 0, SEEK_END);
		unsigned int ret = ftell(fp);

		//checking and setting size.
		if(objsize == 0 && offset <= ret)
			ret -= offset;
		else if(offset + objsize <= ret)
			ret = objsize;
		else
		{
			fclose(fp);
			return 0;
		}

		if(ptr == NULL)
		{
			size = ret;
			ptr = new BYTE[size];
		}
		else if(ret > size) //out of buffer.
		{
			fclose(fp);
			return 0;
		}

		fseek(fp, offset, SEEK_SET);
		fread(ptr, ret, 1, fp);

		fclose(fp);
		return ret;
	}

	// =
	// mem = mem
	inline mem& operator = (const mem& m)
	{
		ptr = m.ptr;
		size = m.size;

		return *this;
	}
};

#endif
