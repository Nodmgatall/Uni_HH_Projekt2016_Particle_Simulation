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
class GeneratorInvalidException : public std::exception {
    private:
    int m_generator_mode;

    public:
    GeneratorInvalidException () : m_generator_mode (-1) {
    }
    GeneratorInvalidException (int p_generator_mode) : m_generator_mode (p_generator_mode) {
    }
    virtual const char *what () const throw () {
        return (std::string ("generator mode ( ") + std::to_string (m_generator_mode) +
                " ) is undefined")
            .c_str ();
    }
};
class GeneratorNotImplementedException : public std::exception {
    private:
    int m_generator_mode;

    public:
    GeneratorNotImplementedException (int p_generator_mode) : m_generator_mode (p_generator_mode) {
    }
    virtual const char *what () const throw () {
        return (std::string ("generator mode ( ") + std::to_string (m_generator_mode) +
                " ) is not (fully) implemented")
            .c_str ();
    }
};
class ParticleGeneratorFactory {
    public:
    static std::unique_ptr<ParticleGeneratorBase> build (s_options &p_options);
};

#endif /* SRC_PARTICLEGENERATOR_HPP_ */
