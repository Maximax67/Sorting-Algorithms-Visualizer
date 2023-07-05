#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Algorithms/Algorithm.h"
#include "Constants.h"

class Controller {
private:
	inline static const char* algorithms = "Quick Sort\0Heap sort\0Smooth sort";
	inline static const int algorithmsSize = 3;

	inline static int selectedAlgorithm = Constants::STARTUP_ALGORITHM;

	inline static sf::Clock clock;
	inline static sf::Time time;

	inline static Algorithm* sorter = nullptr;
public:
	static void init();

	static bool isPaused();
	static bool isSorting();
	static bool isShuffling();
	static int curAlgorithm();

	static void setArraySize(const unsigned int);
	static void setRange(const double, const double);
	static void setDelay(const float);

	static unsigned int getSize();
	static double getMinRange();
	static double getMaxRange();
	static float getDelay();

	static void changeAlgorithm(const int);
	static char* getAlgorithms();
	static int getAlgorithmsNumber();

	static void start();
	static void stop();
	static void step();
	static void pause();
	
	static void shuffle();

	static sf::Time getTime();
	static void updateTime();

	static Statistic getStatistic();

	static const std::vector<double>* getNumbers();
	static void setNumbers(const std::vector<double>&);

	static const std::vector<unsigned int>& getPointers();

	static bool showPointers();

	~Controller();
};
