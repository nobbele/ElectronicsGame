#pragma once

#include <GL/gl3w.h>
#include <SDL.h>
#include <stdio.h>

struct gl_version { int major; int minor; };

inline gl_version getOpenGLVersion()
{
	gl_version version;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &version.major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &version.minor);
	return version;
}

inline void checkOpenGLVersionSupport()
{
	if (!gl3wIsSupported(3, 3)) {
		fprintf(stderr, "OpenGL 3.3 not supported\n");
		getchar();
		exit(-1);
	}
}

inline void SetGLAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
inline SDL_GLContext CreateGLContext(SDL_Window *window)
{
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		fprintf(stderr, "Error Creating GLContext %s\n", SDL_GetError());
		getchar();
		exit(-1);
	}
	return context;
}