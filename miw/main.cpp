#include <stdlib.h>

#include "miw_cpp_test.h"
#include "miw_vm_test.h"

class F
{
public:
	int f()
	{
		return 0;
	}

	int (F::* tf())();

	static int (F::* (*ptf)())();
};

int (F::* F::tf())()
{
	return &F::f;
}

int (F::* (*F::ptf)())();

int main()
{
	miw_cpp_test::run();
	miw_vm_test::run();
/*
	miw_cpp::init();

	std::string str = "int (F::* (*F::ptf)())()";
	miw_cpp::compiler compiler = miw_cpp::compiler((void*)str.c_str(), str.length(), NULL);
	std::list<miw_node_var*> nodes;
	compiler.parser_decl_list(nodes);

	miw_node* node = *nodes.begin();
	std::cout << node->print() << std::endl;
	delete node;

	miw_cpp::del();

	std::cout << "reference : " << miw_node::reference() << std::endl << std::endl;
*/
	system("pause");
	return 0;
}
