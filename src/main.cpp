#include <iostream>
#define EXTERN
#define MAIN_CPP
#include "definitions.hpp"
#include "debug.hpp"
int main() {
	int x = 1234;
	int y = 2345;
	int z = 3456;
	DEBUG_VAR(x, y, z);
	std::cout << "Hello World" << std::endl;
}
