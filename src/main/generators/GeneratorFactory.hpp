/*
 * Generator.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORFACTORY_HPP_
#define SRC_GENERATORFACTORY_HPP_

#include "../Definitions.hpp"
#include "../options/Options.hpp"
#include "GeneratorBase.hpp"
#include "GeneratorGridDistribution.hpp"
#include "GeneratorMultipleObjects.hpp"
#include "GeneratorRandom.hpp"
#include "GeneratorRandomUniform.hpp"
#include "GeneratorSingleObjectMiddle.hpp"
#include <cstdio>
#include <memory>
#include <unistd.h>

#include "../datastructures/DatastructureBase.hpp"
class GeneratorInvalidException : public std::exception {
  private:
    int m_generator_mode;

  public:
    GeneratorInvalidException () : m_generator_mode (-1) {
    }
    GeneratorInvalidException (int p_generator_mode) : m_generator_mode (p_generator_mode) {
    }
    virtual const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "generator mode ( %d ) is undefined", m_generator_mode);
        return text;
    }
};
class GeneratorNotImplementedException : public std::exception {
  private:
    int m_generator_mode;

  public:
    GeneratorNotImplementedException (int p_generator_mode) : m_generator_mode (p_generator_mode) {
    }
    virtual const char* what () const throw () {
        char* text = (char*) malloc (100);
        sprintf (text, "generator mode ( %d ) is not (fully) implemented", m_generator_mode);
        return text;
    }
};
class GeneratorFactory {
  public:
    static GeneratorBase build (s_options& p_options);
};

#endif /* SRC_GENERATOR_HPP_ */
