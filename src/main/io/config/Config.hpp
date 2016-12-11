#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "options/Options.hpp"

struct Config {
    friend class boost::serialization::access;
    std::string m_config_name;
    s_options   m_options;

    template <class Archive>
    void serialize (Archive& archive, const unsigned int version) {
        (void) version;
        archive& BOOST_SERIALIZATION_NVP (m_config_name);
        archive& BOOST_SERIALIZATION_NVP (m_options);
    }
};

#endif
