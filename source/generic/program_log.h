
#ifndef PROGRAM_LOG_H
#define PROGRAM_LOG_H

#include <stdio.h>
#include <string>
#include "../../glm/glm.hpp"

void program_log(const char*, bool = false);
void program_log(std::string, bool = false);
void program_log(glm::vec3, bool = false);
void program_log(std::string,glm::vec3,std::string, bool = false);

#endif
