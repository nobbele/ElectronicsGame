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
#include <Graphics/Shader.h>
#include <Graphics/ShaderProgram.h>
#include <Graphics/Texture.h>
#include <Graphics/BufferObject.h>
#include <IO/eg_io.h>
#include <IO/eg_error.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Sprite.h>

Vector2<float> offset(0,0);
float speed = 0.00005;
 
Sprite *drag_object = nullptr;

Texture *apple_texture, *banana_texture;
ShaderProgram *shaderProgram;

Sprite *sprite;

void game_start() {
	apple_texture = new Texture("assets/apple.png");
	banana_texture = new Texture("assets/banana.png");

	shaderProgram = ShaderProgram::NewFromFile("shaders/normal_sprite.vs", "shaders/normal_sprite.fs");

	sprite = new Sprite(*shaderProgram, *banana_texture, {0, 0}, { 0.0f, 0.0f });

	eg_events::subscribe_event(SDL_EventType::SDL_KEYDOWN, [](const SDL_Event& event) {
		if (event.key.keysym.sym == SDLK_RIGHT) {
			sprite->position.x += speed;
		} else if (event.key.keysym.sym == SDLK_LEFT) {
			sprite->position.x -= speed;
		}
		else if (event.key.keysym.sym == SDLK_UP) {
			sprite->position.y -= speed;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			sprite->position.y += speed;
		}
	});

	install_drag_extension();
	eg_events::subscribe_event(EG_EVENT(EG_EVENT_DRAG_BEGIN), [&](const SDL_Event& event) {
		printf("dragging %dx%d target: %fx%f\n", event.motion.x, event.motion.y, sprite->position.x, sprite->position.y);
		if (within_rectangle((float)event.motion.x, (float)event.motion.y, sprite->position.x, sprite->position.y, sprite->position.x + 100, sprite->position.y + 20)) {

			drag_object = sprite;
			offset = { sprite->position.x - event.motion.x, sprite->position.y - event.motion.y };
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
	
	//printf("x: %f, y: %f\n", sprite->position.x, sprite->position.y);
}

void game_draw(SDL_GLContext context) {
	sprite->Draw();
}
void game_end() {
	delete banana_texture;
	delete apple_texture;
	delete shaderProgram;
	delete sprite;
	uninstall_drag_extension();
}