#pragma once

#include "../INC/main.hpp"


class Events
{
private:
	std::map<int, bool> keys;
	void	keyEvents(const int key, bool& quit, const bool type);
public:
	Events();
	~Events();
	void	eventHandler(const SDL_Event& event, bool& quit);
	std::map<int, bool>	getKeys() const { return keys; };
};

Events::Events()
{
	keys[SDLK_w] = false;
	keys[SDLK_LCTRL] = false;
}

Events::~Events()
{
}

void	Events::eventHandler(const SDL_Event& event, bool& quit) {
	if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		bool type = event.type == 768 ? true : false;
		keyEvents(event.key.keysym.sym, quit, type);
	}
	if(event.type == SDL_QUIT) {
		quit = true;
	}
}

void	Events::keyEvents(const int key, bool& quit, const bool type) {
	if(keys.find(key) == keys.end())
		return;
	keys[key] = type;
	if(keys[SDLK_LCTRL] == true && keys[SDLK_w] == true)
		quit = true;
}

std::ostream& operator<<(std::ostream& os, const Events& events) {
	std::map<int, bool> temp = events.getKeys();
	for(auto it = temp.begin(); it != temp.end(); it++) {
		os << it->first << ": " << it->second << std::endl;
	}
	return os;
}