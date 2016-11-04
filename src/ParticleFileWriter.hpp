/*
 * ParticleFileWriter.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: benjamin
 */

#ifndef SRC_PARTICLEFILEWRITER_HPP_
#define SRC_PARTICLEFILEWRITER_HPP_
#include "Definitions.hpp"
class ParticleFileWriter {
	private:
	int m_timestep;

	public:
	ParticleFileWriter ();
	void saveData (std::shared_ptr<ParticlesBase> p_particles);
};

#endif /* SRC_PARTICLEFILEWRITER_HPP_ */
