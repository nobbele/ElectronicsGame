#include "extensions.h"
#include <SDL.h>
#include "eg_events.h"
#include "game_main.h"

bool drag_installed = false;
bool mdown = false;
bool dragging = false;

Uint32 drag_timer_callback(Uint32 interval, void* param) {
	if (mdown && !dragging) {
		dragging = true;
		SDL_Event *event = static_cast<SDL_Event*>(param);
		event->type = EG_EVENT_DRAG_BEGIN;
		SDL_PushEvent(event);
		delete event;
	}
	return 0;
}
SDL_TimerID drag_timer_id;

void install_drag_extension() {
	if (!drag_installed) {
		drag_installed = true;
		eg_events::subscribe_event(SDL_EventType::SDL_MOUSEBUTTONDOWN, [&](const SDL_Event& event) {
			SDL_Event *event_param = new SDL_Event(event);
			drag_timer_id = SDL_AddTimer(1000 / 10, drag_timer_callback, static_cast<SDL_Event*>(event_param));
			mdown = true;
		});
		eg_events::subscribe_event(SDL_EventType::SDL_MOUSEBUTTONUP, [&](const SDL_Event& event) {
			mdown = false;
			if (dragging) {
				SDL_RemoveTimer(drag_timer_id);
				dragging = false;
				SDL_Event new_event(event);
				new_event.type = EG_EVENT_DRAG_END;
				SDL_PushEvent(&new_event);
			}
		});
		eg_events::subscribe_event(SDL_EventType::SDL_MOUSEMOTION, [&](const SDL_Event& event) {
			if (mdown) {
				if (dragging) {
					SDL_Event new_event(event);
					new_event.type = EG_EVENT_DRAG;
					SDL_PushEvent(&new_event);
				}
			}
		});
	}
}
void uninstall_drag_extension() {
	if (drag_installed) {
		drag_installed = false;
	}
}