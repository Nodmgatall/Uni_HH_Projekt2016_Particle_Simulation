#include <iostream>
#define EXTERN
#define MAIN_CPP
#include "definitions.hpp"
#include "debug.hpp"
#include "particles.hpp"

int main() {
	int x = 1234;
	int y = 2345;
	int z = 3456;
	debug_var(x, y, z);
	std::cout << "Hello World" << std::endl;
}
