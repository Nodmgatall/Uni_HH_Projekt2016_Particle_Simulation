#ifndef USAGE_HPP
#define USAGE_HPP

#include <iostream>

void print_usage_generation_mode () {
	std::cout << "Usage:" << std::endl;
	std::cout << "-g [generation_mode]" << std::endl;
}

void print_usage_particle_sim () {
	std::cout << "Usage:" << std::endl;
	std::cout << "-g        set generation mode" << std::endl;
	std::cout << "-d        choose simulation algortihm dynamicly" << std::endl;
	std::cout << "-v        verbose " << std::endl;
	std::cout << "-a        set algorithm" << std::endl;
	std::cout << "-d        set dynamic algorithm" << std::endl;
}

#endif
