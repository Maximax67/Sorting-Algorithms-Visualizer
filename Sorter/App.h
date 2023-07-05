#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Interface.h"

#include "Resources/icon.hpp"

class App {
private:
	inline static sf::Clock clock;
public:
	static int run();
};
