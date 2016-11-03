#ifndef DUMMY_ALGORITHM_HPP
#define DUMMY_ALGORTIHM_HPP

#include <memory>

#include "Particles.hpp"

bool dummy_algo (std::shared_ptr<Particles>) {
	std::cout << "calculating interation" << std::endl;

	if (true) {
		std::cout << "Error:  iteration could not be finished" << std::endl;
		return false;
	}
	return true;
}
#endif
