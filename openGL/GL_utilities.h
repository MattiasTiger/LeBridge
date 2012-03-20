#ifndef _GL_UTILITIES_
#define _GL_UTILITIES_

#include <GL/glew.h>


void printError(const char *functionName);
GLuint loadShaders(const char *vertFileName, const char *fragFileName);
void dumpInfo(void);

void initKeymapManager();
char keyIsDown(unsigned char c);


#endif
