/*
 * ParticleGeneratorBase.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_

#include "../Definitions.hpp"
#include "../IO/Options.hpp"
#include "../datastructures/DatastructureBase.hpp"
class ParticleGeneratorBase {
  protected:
    s_options&  m_options;
    std::string m_stucture_name;

  public:
    virtual void generate (DatastructureBase* p_particles);
    ParticleGeneratorBase (s_options& p_options);
    virtual ~ParticleGeneratorBase ();
    const std::string& get_stucture_name () const;
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_ */
