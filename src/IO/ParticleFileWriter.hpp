/*
 * ParticleFileWriter.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEFILEWRITER_HPP_
#define SRC_PARTICLEFILEWRITER_HPP_
#include "../Definitions.hpp"
class ParticleFileWriter {
	private:
	static int m_timestep;

	public:
	static std::string m_file_name_base;
	static void saveData (std::shared_ptr<ParticlesBase> p_particles);
};

#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
