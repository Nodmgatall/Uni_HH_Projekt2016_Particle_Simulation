#include <iostream>
#define EXTERN
#define MAIN_CPP
#include "debug.hpp"
#include "definitions.hpp"
#include "particles.hpp"
int main () {
	int x = 1234;
	int y = 2345;
	int z = 3457;
	debug_var (x, y, z);
	std::cout << "Hello World" << std::endl;
}
