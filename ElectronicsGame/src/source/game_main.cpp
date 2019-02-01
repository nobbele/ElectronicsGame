#include "game_main.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <SDL.h>
#include <GL/gl3w.h>
#include "eg_events.h"
#include "GameObject.h"
#include "Component.h"
#include "extensions.h"
#include "globals.h"

GameObject *player;
int speed = 15;
 
GameObject *drag_object = nullptr;
Vector2<float> offset;

/*void game_start() {
	player = GameObject::Create();
	player->AddNewScriptComponent("Scripts/Player/Test.lua", "ScriptTest", player);
	player->AddNewNativeComponent(
		[](GameObject* parent) {
			printf("Start from C++!\n");
			GetScriptComponent(parent, "ScriptTest")->Call("Hello");
		},
		static_cast<NativeComponentFunction*>(0),
		static_cast<NativeComponentFunction*>(0),
		OtherFunctionCollection
		{
			{
				"Hello",
				[](GameObject *parent) {
					printf("Hello from C++\n");
				}
			}
		},
		"NativeTest",
		player
	);

	eg_events::subscribe_event(SDL_EventType::SDL_KEYDOWN, [](const SDL_Event& event) {
		if (event.key.keysym.sym == SDLK_RIGHT) {
			player->position.x += speed;
		} else if (event.key.keysym.sym == SDLK_LEFT) {
			player->position.x -= speed;
		}
		else if (event.key.keysym.sym == SDLK_UP) {
			player->position.y -= speed;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			player->position.y += speed;
		}
	});
	install_drag_extension();
	eg_events::subscribe_event(EG_EVENT(EG_EVENT_DRAG_BEGIN), [&](const SDL_Event& event) {
		for (GameObject &obj : GameObject::GetAll()) {
			if (within_rectangle((float)event.motion.x, (float)event.motion.y, obj.position.x, obj.position.y, obj.position.x + 100, obj.position.y + 20)) {
				drag_object = &obj;
				offset = { obj.position.x - event.motion.x, obj.position.y - event.motion.y };
			}
		}
	});
	eg_events::subscribe_event(EG_EVENT(EG_EVENT_DRAG), [&](const SDL_Event& event) {
		
		if (drag_object) {
			drag_object->position.x = event.motion.x + offset.x;
			drag_object->position.y = event.motion.y + offset.y;
		}
	});
	eg_events::subscribe_event(EG_EVENT(EG_EVENT_DRAG_END), [&](const SDL_Event& event) {
		drag_object = nullptr;
	});
}*/

bool check_shader_compile_status(GLuint obj)
{
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(obj, length, &length, &log[0]);
		std::cerr << &log[0];
		return false;
	}
	return true;
}

bool check_program_link_status(GLuint obj)
{
	GLint status;
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetProgramInfoLog(obj, length, &length, &log[0]);
		std::cerr << &log[0];
		return false;
	}
	return true;
}

// data for a fullscreen quad
GLfloat rectangleVertexData[] = {
	//  X     Y          R     G     B
	   1.0f, 1.0f,      1.0f, 0.0f, 0.0f, // vertex 0
	  -1.0f, 1.0f,	    0.0f, 1.0f, 0.0f, // vertex 1
	   1.0f,-1.0f,    	0.0f, 0.0f, 1.0f, // vertex 2
	   1.0f,-1.0f,   	0.0f, 0.0f, 1.0f, // vertex 3
	  -1.0f, 1.0f,  	0.0f, 1.0f, 0.0f, // vertex 4
	  -1.0f,-1.0f,  	1.0f, 0.0f, 0.0f, // vertex 5
}; // 6 vertices with 6 components (floats) each
const unsigned int rectangleVertexCount = 6;
const size_t rectangleVertexFloatCount = sizeof_array(rectangleVertexData);
const size_t rectangleVertexSize = rectangleVertexFloatCount * sizeof(GLfloat);

std::string vertex_source =
"#version 330\n"
"layout(location = 0) in vec4 vposition;\n"
"layout(location = 1) in vec4 vcolor;\n"
"out vec4 fcolor;\n"
"void main() {\n"
"   fcolor = vcolor;\n"
"   gl_Position = vposition;\n"
"}\n";

std::string fragment_source =
"#version 330\n"
"in vec4 fcolor;\n"
"layout(location = 0) out vec4 FragColor;\n"
"void main() {\n"
"   FragColor = fcolor;\n"
"}\n";

GLuint compile_string_shader(const char *str, GLenum type)
{
	int length = (int)strlen(str);

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &str, &length);

	glCompileShader(shader);
	if (!check_shader_compile_status(shader)) {
		getchar();
		exit(-1);
	}

	return shader;
}

struct GraphicsObject
{
	GLuint shader_program;
	GLuint vertex_shader, fragment_shader;
	GLuint vao, vbo;
	unsigned int vertex_count;
};
GraphicsObject graph_rect;

GraphicsObject graphicsrect_create()
{
	GLuint vertex_shader = compile_string_shader(vertex_source.c_str(), GL_VERTEX_SHADER);

	GLuint fragment_shader = compile_string_shader(fragment_source.c_str(), GL_FRAGMENT_SHADER);

	// create program
	GLuint shader_program = glCreateProgram();

	// attach shaders
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	// link the program and check for errors
	glLinkProgram(shader_program);
	if (!check_program_link_status(shader_program)) {
		getchar();
		exit(-1);
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// fill with data
	glBufferData(GL_ARRAY_BUFFER, rectangleVertexSize, rectangleVertexData, GL_STATIC_DRAW);

	// set up generic attrib pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (char*)0 + 0 * sizeof(GLfloat));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (char*)0 + 2 * sizeof(GLfloat));

	GLuint offset_location = glGetUniformLocation(shader_program, "offset");

	return GraphicsObject{ shader_program, vertex_shader, fragment_shader, vao, vbo, rectangleVertexCount };
}
void graphicsrect_destroy(GraphicsObject &rect)
{
	glDeleteVertexArrays(1, &rect.vao);
	glDeleteBuffers(1, &rect.vbo);

	glDetachShader(rect.shader_program, rect.vertex_shader);
	glDetachShader(rect.shader_program, rect.fragment_shader);
	glDeleteShader(rect.vertex_shader);
	glDeleteShader(rect.fragment_shader);
	glDeleteProgram(rect.shader_program);
}

struct EG_Rect
{
	float x, y, scalex, scaley;
};

GLfloat *draw_verts;
size_t draw_verts_size = 0;

void game_start()
{
	graph_rect = graphicsrect_create();
	const int n = 50000;
	GameObject::Reserve_set(n);
	for (int i = 0; i < n; i++) {
		GameObject::Create();
	}
	draw_verts = new GLfloat[draw_verts_size = GameObject::GetAll().size() * rectangleVertexFloatCount];
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*draw_verts_size, draw_verts, GL_STATIC_DRAW);
}

void game_update() {

}

void game_draw(SDL_GLContext context)
{
	int k = 0;
	for (const GameObject &obj : GameObject::GetAll()) {
		EG_Rect rect = { obj.position.x, obj.position.y, 0.5f, 0.5f };

		for (int i = 0; i < rectangleVertexFloatCount; i++) {
			GLfloat f = rectangleVertexData[i];
			if ((i % 5) == 0) f *= rect.scalex;
			else if ((i % 5) == 1) f *= rect.scaley;
			draw_verts[k] = f;
			k++;
		}
	}
	glUseProgram(graph_rect.shader_program);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*draw_verts_size, draw_verts);
	glDrawArrays(GL_TRIANGLES, 0, rectangleVertexCount);
}
void game_end() {
	uninstall_drag_extension();
	graphicsrect_destroy(graph_rect);
}