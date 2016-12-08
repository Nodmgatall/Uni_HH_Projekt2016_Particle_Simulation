/*
 * ParticleGenerator.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEGENERATORFACTORY_HPP_
#define SRC_PARTICLEGENERATORFACTORY_HPP_

#include "../Definitions.hpp"
#include "../IO/Options.hpp"
#include "../datastructures/ParticlesBase.hpp"
#include "ParticleGeneratorBase.hpp"
#include "ParticleGeneratorGridDistribution.hpp"
#include "ParticleGeneratorRandom.hpp"
#include "ParticleGeneratorSingleObjectMiddle.hpp"

#include <memory>
#include <unistd.h>

class ParticleGeneratorFactory {

    public:
    static std::unique_ptr<ParticleGeneratorBase> build (s_options &p_options);
};

#endif /* SRC_PARTICLEGENERATOR_HPP_ */
