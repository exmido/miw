#ifndef MIW_CPP_TEST_H
#define MIW_CPP_TEST_H

#include <ctime>
#include <iostream>

#include "miw_cpp.h"

#include "mem.h"

#include "test.h"

int add(int a, int b)
{
	return a + b;
}

//miw_cpp_test
class miw_cpp_test
{
public:
	static void run()
	{
		std::cout << "miw_cpp_test" << std::endl;

		//
		miw_cpp::init();

		mem buffer;
		buffer.load("test.h");

		int error = miw_cpp::load(buffer.ptr, buffer.size, "test.h");
		std::cout << "error : " << error << ", reference : " << miw_node::reference() << std::endl;

		if(error)
		{
			miw_cpp::del();
			std::cout << miw_node::reference() << std::endl << std::endl;
			return;
		}

		//
		/*
		test* t = new test;
		t->C::B::ccc = new test;
		t->C::B::ccc->C::B::ccc = new test;
		std::cout << (void*)&t->C::B::ccc << std::endl;
		std::cout << (void*)&t->C::B::ccc->C::B::ccc << std::endl;
		std::cout << (void*)&t->C::B::ccc->C::B::ccc->C::B::ccc << std::endl;
		*/
		test* t = new test;
		((C::B*)t)->ccc = new test;
		((C::B*)((C::B*)t)->ccc)->ccc = new test;
		std::cout << (void*)&((C::B*)t)->ccc << std::endl;
		std::cout << (void*)&((C::B*)((C::B*)t)->ccc)->ccc << std::endl;
		std::cout << (void*)&((C::B*)((C::B*)((C::B*)t)->ccc)->ccc)->ccc << std::endl;

		std::cout << std::endl;

		//test* t
		miw_vm_variable<miw_node> root;
		root.type = miw_node::root();

		miw_vm_variable<miw_node> rt;
		
		miw_vm<miw_node> vm(16, 256);

		rt = root.type->apply(root, &vm, NULL, root.type->find(root, &vm, "test"));
		rt.value = t;

		//
		std::string str = "C::B::ccc";
		miw_cpp::compiler compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		miw_node* node = compiler.parser_scope();

		miw_vm_variable<miw_node> ret = node->invoke(rt, &vm, NULL);
		std::cout << ret.value << std::endl;

		delete node;

		//
		str = "C::B::ccc->C::B::ccc";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		node = compiler.parser_scope();

		ret = node->invoke(rt, &vm, NULL);
		std::cout << ret.value << std::endl;

		delete node;

		//
		str = "C::B::ccc->C::B::ccc->C::B::ccc";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		node = compiler.parser_scope();

		ret = node->invoke(rt, &vm, NULL);
		std::cout << ret.value << std::endl;

		std::cout << std::endl;

		//clock
		clock_t begin, end;

		//
		begin = clock();
		for(int i = 0; i < 10000; ++i)
			ret = node->clear()->invoke(rt, &vm, NULL);
		end = clock();

		std::cout << ret.value << " : " << (void*)ret.type << std::endl;
		std::cout << ret.type->print() << std::endl;
		std::cout << "time : " << double(end - begin) / CLOCKS_PER_SEC << std::endl;

		std::cout << std::endl;

		//
		begin = clock();
		for(int i = 0; i < 10000; ++i)
			ret = node->invoke(rt, &vm, NULL);
		end = clock();

		std::cout << ret.value << " : " << (void*)ret.type << std::endl;
		std::cout << ret.type->print() << std::endl;
		std::cout << "time : " << double(end - begin) / CLOCKS_PER_SEC << std::endl;

		std::cout << std::endl;

		//
		delete node;

		//
		str = "A::B::add";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		node = compiler.parser_scope();

		ret = node->invoke(miw_node::root(), &vm, NULL);
		std::cout << ret.type->print() << std::endl;

		std::cout << std::endl;

		delete node;

		//
		std::list<miw_node_var*> fun;

		str = "static int add(char a, int b)";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		compiler.parser_decl_list(fun);

		str = "static int add(int a, char b)";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		compiler.parser_decl_list(fun);

		str = "static int add(char a, char b)";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		compiler.parser_decl_list(fun);

		for(std::list<miw_node_var*>::iterator it = fun.begin(); it != fun.end(); ++it)
			miw_node::root()->reg_variable(*it);

		miw_cpp::reg_fun("static int add(int& a, int& b)", add);

		miw_node_exp* exp = new miw_node_exp(__LINE__, __FILE__);

		str = "add";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		exp->data_op = compiler.parser_scope();

		str = "1";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		exp->data_value.push_back(compiler.parser_value());

		str = "2";
		compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
		exp->data_value.push_back(compiler.parser_value());

		exp->invoke(miw_vm_variable<miw_node>(miw_node::root(), NULL), NULL, NULL);

		begin = clock();
		miw_vm_variable<miw_node> self = miw_vm_variable<miw_node>(miw_node::root(), NULL);
		for(int i = 0; i < 1000000; ++i)
		{
			exp->invoke(self, &vm, vm.getseek());
			ret = *vm.read();
		}
		end = clock();

		std::cout << "time : " << double(end - begin) / CLOCKS_PER_SEC << std::endl;
		std::cout << ret.type->print() << std::endl;
		std::cout << *(int*)ret.value << std::endl;
		std::cout << std::endl;

		begin = clock();
		int i0 = 0, i1 = 1, i2 = 2;
		for(int i = 0; i < 1000000; ++i)
		{
			i0 = add(i1, i2);
			vm.write();
			vm.read();
		}

		end = clock();
		std::cout << "time : " << double(end - begin) / CLOCKS_PER_SEC << std::endl;

		delete exp;

		//
		miw_cpp::unload("test.h");

		miw_cpp::del();
		std::cout << "reference : " << miw_node::reference() << std::endl << std::endl;
	}
};

#endif
