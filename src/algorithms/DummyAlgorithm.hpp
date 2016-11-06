#ifndef DUMMY_ALGORITHM_HPP
#define DUMMY_ALGORTIHM_HPP

#include <memory>

#include "../datastructures/ParticlesBase.hpp"

bool dummy_algo (std::shared_ptr<ParticlesBase>) {
    std::cout << "calculating interation" << std::endl;

    if (true) {
        std::cout << "Error:  iteration could not be finished" << std::endl;
        return false;
    }
    return true;
}
#endif
