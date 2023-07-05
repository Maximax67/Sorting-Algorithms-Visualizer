#pragma once

#include "imgui-SFML.h"
#include "imgui.h"
#include "implot.h"

#include "Controller.h"
#include "FileProcessor.h"
#include "Constants.h"

#include "Resources/icons.h"
#include "Resources/icons.hpp"
#include "Resources/Ubuntu-M.hpp"

class Interface {
private:
	inline static int algorithm = Constants::STARTUP_ALGORITHM;
	inline static unsigned int arraySize = Constants::STARTUP_ARRAY_SIZE;
	inline static double rangeMin = Constants::STARTUP_RANGE_MIN;
	inline static double rangeMax = Constants::STARTUP_RANGE_MAX;
	inline static float delay = Constants::STARTUP_DELAY;
	inline static bool doDelay = Constants::STARTUP_DO_DELAY;
	inline static std::string errorMessage;
public:
	static void init(sf::RenderWindow&);
	static void draw(sf::RenderWindow&);
	static void update(sf::RenderWindow&, sf::Time);
	static void destroy();
	static void processEvent(sf::Event&);
};
