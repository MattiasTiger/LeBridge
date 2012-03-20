#pragma once

#include <GL\glew.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

namespace dM
{


GLuint loadShaders(const char *vertFileName, const char *fragFileName);


}