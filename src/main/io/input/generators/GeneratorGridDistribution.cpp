/*
 * ParticleGeneratorGridDistribution.cpp
 *
 *  Created on: 11.11.2016
 *      Author: benjamin
 */
#include "GeneratorGridDistribution.hpp"
GeneratorGridDistribution::GeneratorGridDistribution (s_options& p_options, DatastructureBase& p_datastructure) : InputBase (p_options, p_datastructure) {
    m_stucture_name = "GeneratorGridDistribution";
    std::cout << "GeneratorGridDistribution::a" << std::endl;
}
GeneratorGridDistribution::~GeneratorGridDistribution () {
}
void GeneratorGridDistribution::initialize_datastructure () {
    std::cout << "GeneratorGridDistribution::b" << std::endl;
    Vec3f particle_free_Border_size = m_options.m_bounds * 0.001;
    Benchmark::begin ("ParticleGeneratorGridDistribution");
    data_type temp  = pow (m_options.m_particle_count, 1.0f / 3.0f);
    Vec3f     delta = (m_options.m_bounds - particle_free_Border_size * 2) / (temp);
    std::cout << "GeneratorGridDistribution::c" << std::endl;
    unsigned int  x, y, z;
    unsigned int  tempInt = temp;
    unsigned long count   = 0;
    std::cout << "GeneratorGridDistribution::d" << std::endl;
    for (x = 0; x < tempInt; x++) {
        for (y = 0; y < tempInt; y++) {
            for (z = 0; z < tempInt; z++) {
                std::cout << "GeneratorGridDistribution::f" << std::endl;
                m_datastructure.add_particle (particle_free_Border_size + delta * 0.5 + Vec3f (x, y, z) * delta, Vec3f ());
                std::cout << "GeneratorGridDistribution::g" << std::endl;
                count++;
            }
        }
    }
    std::cout << "GeneratorGridDistribution::e" << std::endl;
    if (m_options.m_particle_count != tempInt) {
        for (x = 0; x < tempInt; x++) {
            for (y = 0; y < tempInt; y++) {
                for (z = 0; z < tempInt; z++) {
                    if (count++ < m_options.m_particle_count) {
                        m_datastructure.add_particle (particle_free_Border_size + delta * 0.5 + Vec3f (temp / 2.0 + x, y, z) * delta, Vec3f ());
                    }
                }
            }
        }
    }
    Benchmark::end ();
}
