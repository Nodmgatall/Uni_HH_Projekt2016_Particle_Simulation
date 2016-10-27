/*
 * definitions.hpp
 *
 *  Created on: 27.10.2016
 *      Author: benjamin
 */
#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_
#ifndef EXTERN
#define EXTERN extern
#endif
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
EXTERN std::vector<glm::vec3> position;
EXTERN std::vector<glm::vec3> geschwindigkeit;
EXTERN std::vector<glm::vec3> beschleunigung;

#endif /* DEFINITIONS_HPP_ */
