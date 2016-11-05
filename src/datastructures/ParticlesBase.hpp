#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <glm/glm.hpp>
#include <vector>
class ParticlesBase {
	public:
	std::vector<unsigned long> m_ids;
	std::vector<glm::vec3>	 m_positions;
	std::vector<glm::vec3>	 m_velocities;
	std::vector<glm::vec3>	 m_accelerations;

	virtual glm::vec3 get_velocity (int p_particle_id)		 = 0;
	virtual std::vector<glm::vec3> *	get_velocities ()	= 0;
	virtual std::vector<glm::vec3> *	get_positions ()	 = 0;
	virtual std::vector<glm::vec3> *	get_accelerations () = 0;
	virtual std::vector<unsigned long> *get_ids ()			 = 0;
	virtual void add_particle (glm::vec3 p_position, glm::vec3 p_velocity, glm::vec3 p_acceleration) = 0;
	virtual unsigned long get_particle_count () = 0;
	virtual ~ParticlesBase () {
	}
};
#endif
