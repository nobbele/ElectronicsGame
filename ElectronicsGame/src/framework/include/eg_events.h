#pragma once

#include <functional>
#include <vector>
#include <SDL.h>
extern "C" {
	#include "lua.h"
}

//For future use
enum EG_EVENT_TYPE {
	EG_EVENT_DRAG_BEGIN = 0x8001,
	EG_EVENT_DRAG = 0x8002,
	EG_EVENT_DRAG_END = 0x8003
};

#define EG_EVENT(event) ((SDL_EventType)event)

struct EG_MOUSE_POSITION_CHANGE_EVENT {
	int new_x, new_y, old_x, old_y;
};

namespace eg_events {
	typedef void(EVENT_SUBSCRIPTION_CALLBACK_TYPE)(const SDL_Event&);
	typedef std::function<EVENT_SUBSCRIPTION_CALLBACK_TYPE> EVENT_SUBSCRIPTION_CALLBACK;

	struct Subscription {
		SDL_EventType type = (SDL_EventType)0;
		EVENT_SUBSCRIPTION_CALLBACK callback;
	};

	extern std::vector<Subscription> event_subscriptions;

	void subscribe_event(const SDL_EventType event_type, const EVENT_SUBSCRIPTION_CALLBACK& callback);
	void unsubscribe_event(const EVENT_SUBSCRIPTION_CALLBACK& callback);
}

int lua_SubscribeEvent(lua_State *L);