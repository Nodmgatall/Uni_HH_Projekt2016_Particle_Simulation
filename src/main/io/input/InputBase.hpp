/*
 * ParticleGeneratorBase.h
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */

#ifndef SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_
#define SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_

#include "Definitions.hpp"
#include "datastructures/DatastructureBase.hpp"
#include "options/Options.hpp"

class InputBase {
  protected:
    s_options&         m_options;
    DatastructureBase& m_datastructure;
    std::string        m_stucture_name;

  public:
    InputBase (s_options& p_options, DatastructureBase& p_datastructure)
    : m_options (p_options), m_datastructure (p_datastructure) {
    }
    virtual ~InputBase () {
    }
    /**
     *
     * @return the string representation of the class name. uses to verify, that the correct class is used
     */
    std::string get_structure_name () {
        return m_stucture_name;
    }
    /**
     * creates particles and put them directly into the datastructure given to the constructor
     */
    virtual void initialize_datastructure () = 0;
};

#endif /* SRC_GENERATORS_PARTICLEGENERATORBASE_HPP_ */
