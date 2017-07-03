#ifndef OGL_UTIL_H
#define OGL_UTIL_H
#include<string>
#include "ogl_types.h"
using namespace std;

bool ReadFile(const char* fileName, string& outFile);

void OglError(const char* pFileName, uint line, const char* msg, ...);

long long GetCurrentTimeMillis();

#define OGLDEV_FILE_ERROR(FileError)\
 OglError(__FILE__, __LINE__, FileError);

#define OGL_ERROR0(msg) OglError(__FILE__, __FILE__, msg)

#define OGL_ERROR(msg, ...)\
 OglError(__FILE__, __LINE__, msg, __VA_ARGS__)

#define VSNPRINTF vsnprintf_s

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SNPRINTF _snprintf_s

#define GLCheckError() (glGetError() == GL_NO_ERROR)

#define INVALID_UNIFORM_LOCATION 0xffffffff

#define INVALID_OGL_VALUE 0XFFFFFFFF

#define SAFE_DELETE(p) if (p) {delete p; p = NULL; }

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)


#endif // !OGL_UTIL_H
