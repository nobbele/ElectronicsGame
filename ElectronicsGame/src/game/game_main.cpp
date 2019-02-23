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

void game_start() {
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
		for (GameObject &obj : GameObject::all) {
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
}

void game_update() {

}

void game_draw(SDL_GLContext context) {

}

void game_end() {
	delete player;
}

/*#include <Graphics/Shader.h>
#include <Graphics/ShaderProgram.h>
#include <Graphics/Texture.h>
#include <IO/eg_io.h>
#include <IO/eg_error.h>

Texture *texture;
ShaderProgram *shaderProgram;

unsigned int VBO, VAO, EBO;

GLint posOffsetLocation;

void game_start() {
	texture = new Texture("assets/apple.png");

	char *vertex_source = readFile("shaders/apple.vs");
	char *fragment_source = readFile("shaders/apple.fs");
	Shader shader(vertex_source, fragment_source);
	delete vertex_source;
	delete fragment_source;

	shaderProgram = new ShaderProgram(&shader);

	posOffsetLocation = shaderProgram->GetUniformLocation("posOffset");
	if(posOffsetLocation == -1) {
		EG_ERROR(
			fprintf(stderr, "Couldn't get posOffset uniform location")
		);
	}

	float vertices[] = {
        // positions    // colors           // texture coords
         0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void game_update() {

}

void game_draw(SDL_GLContext context) {
	texture->Bind();

	shaderProgram->Use();

	glUniform2f(posOffsetLocation, 0, 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void game_end() {
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete texture;
	delete shaderProgram;
	uninstall_drag_extension();
}*/