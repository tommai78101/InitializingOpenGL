
#pragma once

#ifndef __PCH_H___
#	define __PCH_H___

//Defines
#	define NOMINMAX

//Exceptional rules
#	include <algorithm>
using std::max;
using std::min;

//Common standard headers
#	include <iostream>
#	include <fstream>
#	include <sstream>
#	include <thread>
#	include <utility>
#	include <memory>
#	include <functional>
#	include <cstdio>
#	include <strsafe.h>
#	include <initializer_list>

//Data structures
#	include <string>
#	include <stack>
#	include <deque>
#	include <array>
#	include <vector>
#	include <set>
#	include <map>
#	include <unordered_map>
#	include <unordered_set>

//Massive headers
#	include <Windows.h>
#	include <gl/GL.h>
#	include "gl/glext.h"
#	include "gl/wglext.h"

//OpenGL function declarations
//Declare them only when we are to use them.
//Function pointers are to be declared only once.

//ARB functions
extern PFNGLCREATEPROGRAMOBJECTARBPROC      glCreateProgramObjectARB;
extern PFNGLDELETEOBJECTARBPROC             glDeleteObjectARB;
extern PFNGLUSEPROGRAMOBJECTARBPROC         glUseProgramObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC       glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC             glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC            glCompileShaderARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC     glGetObjectParameterivARB;
extern PFNGLATTACHOBJECTARBPROC             glAttachObjectARB;
extern PFNGLGETINFOLOGARBPROC               glGetInfoLogARB;
extern PFNGLLINKPROGRAMARBPROC              glLinkProgramARB;
extern PFNGLGETUNIFORMLOCATIONARBPROC       glGetUniformLocationARB;
extern PFNGLUNIFORM4FARBPROC                glUniform4fARB;
extern PFNGLUNIFORM3FARBPROC                glUniform3fARB;
extern PFNGLUNIFORM1FARBPROC                glUniform1fARB;
extern PFNGLUNIFORM1IARBPROC                glUniform1iARB;
extern PFNGLUNIFORM2FVARBPROC               glUniform2fvARB;
extern PFNGLGETATTRIBLOCATIONARBPROC        glGetAttribLocationARB;
extern PFNGLVERTEXATTRIB3FARBPROC           glVertexAttrib3fARB;
extern PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointerARB;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
extern PFNGLGENBUFFERSARBPROC               glGenBuffersARB;
extern PFNGLBINDBUFFERARBPROC               glBindBufferARB;
extern PFNGLBUFFERDATAARBPROC               glBufferDataARB;

//Non-ARB functions
extern PFNGLGENVERTEXARRAYSPROC             glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC             glBindVertexArray;
extern PFNGLGENBUFFERSPROC                  glGenBuffers;
extern PFNGLCREATESHADERPROC                glCreateShader;
extern PFNGLDETACHSHADERPROC                glDetachShader;
extern PFNGLDELETESHADERPROC                glDeleteShader;
extern PFNGLDELETEPROGRAMPROC               glDeleteProgram;
extern PFNGLDELETEBUFFERSPROC               glDeleteBuffers;
extern PFNGLDELETEVERTEXARRAYSPROC          glDeleteVertexArrays;
extern PFNGLGETSHADERIVPROC                 glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog;
extern PFNGLGETPROGRAMIVPROC                glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC           glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC                  glUseProgram;


#endif