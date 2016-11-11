#ifndef OPTIONS_GENERATOR_HPP
#define OPTIONS_GENERATOR_HPP

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "../Definitions.hpp"

struct s_generator_options {
    friend class boost::serialization::access;
    e_generator_mode m_mode = GRID_DISTRIBUTION;
    unsigned int     m_seed = 123456789;

    template <class Archive>
    void serialize (Archive &archive, const unsigned int version) {
        (void) version;
        archive &BOOST_SERIALIZATION_NVP (m_mode);
        archive &BOOST_SERIALIZATION_NVP (m_seed);
    }
};
#endif
