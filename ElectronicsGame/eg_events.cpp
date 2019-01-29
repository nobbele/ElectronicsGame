#include "eg_events.h"

namespace eg_events {
	std::vector<Subscription> event_subscriptions;

	void subscribe_event(const SDL_EventType event_type, const EVENT_SUBSCRIPTION_CALLBACK& callback) {
		event_subscriptions.push_back({ event_type, callback });
	}
	void unsubscribe_event(const EVENT_SUBSCRIPTION_CALLBACK& callback) {
		for (size_t i = 0; i < event_subscriptions.size(); i++) {
			const Subscription& sub = event_subscriptions[i];
			auto sub_ccallback = sub.callback.target<EVENT_SUBSCRIPTION_CALLBACK_TYPE*>();
			auto ccallback = callback.target<EVENT_SUBSCRIPTION_CALLBACK_TYPE*>();
			if (sub_ccallback == ccallback) {
				event_subscriptions.erase(event_subscriptions.begin() + i);
			}
		}
	}
}

int lua_SubscribeEvent(lua_State *L)
{
	const SDL_EventType type = (SDL_EventType)lua_tointeger(L, 1);
	return 0;
}
