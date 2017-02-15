/*
 * GeneratorGridDistribution.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "GeneratorGridDistribution.hpp"
GeneratorGridDistribution::GeneratorGridDistribution (s_options& p_options, DatastructureBase& p_datastructure) : InputBase (p_options, p_datastructure) {
    m_stucture_name = "GeneratorGridDistribution";
    std::cout << "GeneratorGridDistribution::a" << std::endl;
}
GeneratorGridDistribution::~GeneratorGridDistribution () {
}
void GeneratorGridDistribution::initialize_datastructure () {
    Vec3f particle_free_Border_size = m_options.m_bounds * 0.001;
    Benchmark::begin ("ParticleGeneratorGridDistribution");
    data_type     temp  = pow (m_options.m_particle_count, 1.0f / 3.0f);
    Vec3f         delta = (m_options.m_bounds - particle_free_Border_size * 2) / (temp);
    unsigned int  x, y, z;
    unsigned int  tempInt = temp;
    unsigned long count   = 0;
    for (x = 0; x < tempInt; x++) {
        for (y = 0; y < tempInt; y++) {
            for (z = 0; z < tempInt; z++) {
                m_datastructure.add_particle (particle_free_Border_size + delta * 0.5 + Vec3f (x, y, z) * delta,
                                              Vec3f (m_options.m_initial_speed, 0, 0).rotateX (rand () % 360).rotateY (rand () % 360).rotateZ (rand () % 360));
                count++;
            }
        }
    }
    if (m_options.m_particle_count != tempInt) {
        for (x = 0; x < tempInt; x++) {
            for (y = 0; y < tempInt; y++) {
                for (z = 0; z < tempInt; z++) {
                    if (count++ < m_options.m_particle_count) {
                        m_datastructure.add_particle (particle_free_Border_size + delta * 0.5 + Vec3f (temp / 2.0 + x, y, z) * delta,
                                                      Vec3f (m_options.m_initial_speed, 0, 0).rotateX (rand () % 360).rotateY (rand () % 360).rotateZ (rand () % 360));
                    }
                }
            }
        }
    }
    Benchmark::end ();
}
