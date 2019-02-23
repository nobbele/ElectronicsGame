#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <vector>
#include <thread>
#include <unordered_set>
#include <SDL.h>
#include <SDL_ttf.h>
#include <random>
#include <GL/gl3w.h>
#include "eg_events.h"
#include "eg_containers.h"
#include "GameObject.h"
#include "NativeComponent.h"
#include "ScriptComponent.h"
#include "globals.h"
#include "misc.h"
#include "eg_lua.h"
#include "internal_eg_glfunctions.h"
#include "internal_eg_inits.h"
#include "game_main.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

extern std::vector<std::function<void()>> after_frame_queue;

lua_State* _L;

Uint32 fps_timer(Uint32 interval, void* param) {
	return interval;
}

SDL_Window *CreateSDLWindow() {
	SDL_Window *window = SDL_CreateWindow("ElectronicsGame",
										  SDL_WINDOWPOS_UNDEFINED,
										  SDL_WINDOWPOS_UNDEFINED,
										  window_size.x, window_size.y,
										  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!window) {
		fprintf(stderr, "Error Initializing Window %s\n", SDL_GetError());
		getchar();
		exit(-1);
	}
	return window;
}

void end(SDL_GLContext context, SDL_Window *window) {
	game_end();

	lua_close(_L);

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void glMessageCallback( GLenum source,
                 	    GLenum type,
               	 	    GLuint id,
             	        GLenum severity,
					    GLsizei length,
					    const GLchar* message,
					    const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

#undef main
int main(int argc, char* argv[]) {
	initSDL();

	setOpenGLVersion(3, 3);
	printf("OpenGL Version 3.3\n");

	window = CreateSDLWindow();

	SetGLAttributes();
	context = CreateGLContext(window);
	
	initGl3w();

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glMessageCallback, 0);

	glViewport(0, 0, 800, 600);

	checkOpenGLVersionSupport(3,3);

	SDL_AddTimer(1, fps_timer, nullptr);

	initLua();

	game_start();

	Uint32 lastframe = SDL_GetTicks();
	double last_current_time = 0;

	running = true;
	while (running) {
		/*Events*/
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EventType::SDL_QUIT)
					running = false;
				for (eg_events::Subscription sub : eg_events::event_subscriptions) {
					if (sub.type == event.type) {
						sub.callback(event);
					}
				}
			}
		}

		/*After Frame Dispatcher*/
		{
			for (auto it = after_frame_queue.begin(); it != after_frame_queue.end();) {
				(*it)();
				it = after_frame_queue.erase(it);
			}
		}

		/*Misc*/
		{
			Uint32 current_time = SDL_GetTicks();

			delta_time = (current_time - last_current_time) / 1000;
			fps = (unsigned int)(1.0 / delta_time);

			frame_count++;
			last_current_time = current_time;

			for (GameObject &obj : GameObject::all) {
				for(ComponentVariant compVariant : obj.GetComponentIterator()) {
					std::visit([](auto &&comp) {
						comp->Update();
					}, compVariant);
					if(std::holds_alternative<ScriptComponent*>(compVariant)) {
						std::get<ScriptComponent*>(compVariant)->UpdateWatch();
					}
				}
			}
		}

		/*Game logic*/
		{
			game_update();
		}

		/*Drawing*/
		{
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			game_draw(context);

			//std::cout << "FPS: " << fps << " Dt: " << delta_time << std::endl;

			SDL_GL_SwapWindow(window);
		}
	}

	end(context, window);

	return 0;
}