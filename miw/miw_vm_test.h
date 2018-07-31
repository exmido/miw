#ifndef MIW_VM_TEST_H
#define MIW_VM_TEST_H

#include <ctime>
#include <iostream>

#include "miw_node.h"

//miw_vm_test
class miw_vm_test
{
public:
	static void run()
	{
		std::cout << "miw_vm_test" << std::endl;

		miw_vm<miw_node> vm(256, 4096);

		miw_vm_variable<miw_node>* ptr = NULL;

		//
		for(int i = 0; i < 10; ++i)
		{
			ptr = vm.write(128);
			((int*)ptr->value)[0] = i;
		}

		for(int i = 0; i < 10; ++i)
		{
			ptr = vm.read();
			std::cout << ((int*)ptr->value)[0] << std::endl;
		}

		std::cout << std::endl;

		//clock
		clock_t begin, end;

		//
		begin = clock();
		for(int i = 0; i < 1000000; ++i)
		{
			vm.write(128);
			vm.read();
		}
		end = clock();

		std::cout << "time : " << double(end - begin) / CLOCKS_PER_SEC << std::endl;

		std::cout << std::endl;
	}
};

#endif
