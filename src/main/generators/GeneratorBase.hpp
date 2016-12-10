/*
 * ParticleGeneratorBase.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_

#include "../Definitions.hpp"
#include "../datastructures/DatastructureBase.hpp"
#include "../options/Options.hpp"
class GeneratorBase {
  protected:
    s_options&  m_options;
    std::string m_stucture_name;

  public:
    virtual void generate (DatastructureBase* p_particles) = 0;
    GeneratorBase (s_options& p_options);
    virtual ~GeneratorBase ();
    const std::string& get_stucture_name () const;
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_ */
