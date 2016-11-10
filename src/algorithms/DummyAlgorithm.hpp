#ifndef DUMMY_ALGORITHM_HPP
#define DUMMY_ALGORITHM_HPP

#include <memory>

#include "../datastructures/ParticlesBase.hpp"

bool dummy_algo (glm::vec3 &position1,
                 glm::vec3 &velocity1,
                 glm::vec3 &acceleration1,
                 glm::vec3 &position2,
                 glm::vec3 &velocity2,
                 glm::vec3 &acceleration2) {
    std::cout << "calculating interation" << std::endl;

    if (true) {
        std::cout << "Error:  iteration could not be finished" << std::endl;
        return false;
    }
    return true;
}
#endif
