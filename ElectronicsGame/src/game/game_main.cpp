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
}

void game_update() {

}

void game_draw(SDL_GLContext context) {
	//Need to figure out a way to draw player using OpenGL
}
void game_end() {
	uninstall_drag_extension();
}