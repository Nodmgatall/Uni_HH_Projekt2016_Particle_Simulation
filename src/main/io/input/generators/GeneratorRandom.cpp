/*
 * GeneratorRandom.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Oliver Heidmann <oliverheidmann@hotmail.de>
 *      Author: Benjamin Warnke <4bwarnke@informatik.uni-hamburg.de>
 */
#include "GeneratorRandom.hpp"
#include "../../../datastructures/DatastructureBase.hpp"
#include <iostream>
#include <random>
GeneratorRandom::GeneratorRandom (s_options& p_options, DatastructureBase& p_datastructure) : InputBase (p_options, p_datastructure) {
    m_stucture_name = "GeneratorRandom";
}
GeneratorRandom::~GeneratorRandom () {
}
/*
 void GeneratorRandom::initialize_datastructure () {
 Benchmark::begin ("ParticleGeneratorRandom");
 std::srand (m_options.m_seed);
 for (unsigned long id = 0; id < m_options.m_particle_count; id++) {
 m_datastructure.add_particle (Vec3f ((data_type) std::rand (), (data_type) std::rand (), (data_type) std::rand ()) / (data_type) RAND_MAX * m_options.m_bounds, Vec3f ());
 }
 Benchmark::end ();
 }
 */
void GeneratorRandom::initialize_datastructure () {
    unsigned long tmp = std::pow (m_options.m_particle_count, 1.f / 3.f);
    while (tmp * tmp * tmp < m_options.m_particle_count) {
        tmp++;
    };
    std::cout << "start " << tmp << std::endl;
    data_type dist_x = m_options.m_bounds.x / tmp;
    data_type dist_z = m_options.m_bounds.z / tmp;
    data_type dist_y = m_options.m_bounds.y / tmp;

    Vec3f                            current_vector = Vec3f (dist_x / 2, dist_y / 2, dist_z / 2);
    Vec3f                            random_velocity;
    std::random_device               random_div;
    std::mt19937                     gen (random_div ());
    std::uniform_real_distribution<> rg_x (-dist_x * 0.4f, dist_x * 0.4f);
    std::uniform_real_distribution<> rg_y (-dist_y * 0.4f, dist_y * 0.4f);
    std::uniform_real_distribution<> rg_z (-dist_z * 0.4f, dist_z * 0.4f);
    unsigned long                    x, y, z;
    for (x = 0; x < tmp; x++) {
        current_vector.y = dist_y / 2;
        for (y = 0; y < tmp; y++) {
            current_vector.z = dist_z / 2;
            for (z = 0; z < tmp; z++) {
                random_velocity = Vec3f (rg_x (gen), rg_y (gen), rg_z (gen));
                std::cout << "cv: " << current_vector << std::endl;
                std::cout << "rv: " << random_velocity << std::endl;
                std::cout << "add: " << current_vector + random_velocity << std::endl;
                m_datastructure.add_particle (current_vector + random_velocity, Vec3f ());
                current_vector.z += dist_z;
            }
            current_vector.y += dist_y;
        }
        current_vector.x += dist_x;
    }
    std::cout << "end" << std::endl;
}
