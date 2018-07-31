#ifndef TEST_H
#define TEST_H

class A
{
public:
	A()
	{
	}

	~A()
	{
	}

	class B
	{
	public:
		int aaa;
		A::B* ccc;

		int(*add)(int a, int* b);
		char(*(*(A::* arr)(int))(double));

		void a()
		{
		}
	};
};

class test;
class C
{
public:
	class E
	{
	public:
		int aaa;
	};

	class B : public E
	{
	public:
		test * ccc;
		char ddd;
	};
};

class D : public A::B, public C::B
{
public:
	short d;
};

//test
class test : public D
{
public:
};

#endif
