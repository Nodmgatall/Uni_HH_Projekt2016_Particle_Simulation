/*
 * ParticleWriterBase.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: benjamin
 */
#ifndef SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_
#define SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_
#include "Definitions.hpp"
#include "options/Options.hpp"
class WriterBase {
  protected:
    /**
     * the name of the child-class to verify which subclass is used at runtime
     */
    std::string m_stucture_name;

  public:
    /**
     * constructor
     */
    WriterBase () {
    }
    /**
     * destructor
     */
    virtual ~WriterBase () {
    }
    /**
     *
     * @return the string representation of the class name used for verification, that the
     * class-type is correct
     */
    std::string get_structure_name () {
        return m_stucture_name;
    }
    /**
     * save an individual particle
     * @param p_positions_x
     * @param p_positions_y
     * @param p_positions_z
     * @param p_ids
     */
    virtual void saveData (std::vector<data_type>& p_positions_x, std::vector<data_type>& p_positions_y, std::vector<data_type>& p_positions_z, std::vector<unsigned long>& p_ids) = 0;
    /**
     * begin writing
     */
    virtual void start () = 0;
    /**
     * stop writing
     */
    virtual void end () = 0;
    /**
     * called after the last timestep
     */
    virtual void finalize () = 0;
};
#endif /* SRC_MAIN_IO_PARTICLEWRITERBASE_HPP_ */
