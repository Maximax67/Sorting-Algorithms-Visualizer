#pragma once

#include <string>
#include <vector>
#include <thread>
#include <atomic>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "Statistic.h"
#include "../Constants.h"
#include "../Random.h"

class Algorithm {
protected:
	sf::Clock clock;
	Statistic st;

	std::thread thread;

	inline static std::vector<double> array;
	inline static unsigned int arraySize = Constants::STARTUP_ARRAY_SIZE;
	inline static double rangeMin = Constants::STARTUP_RANGE_MIN;
	inline static double rangeMax = Constants::STARTUP_RANGE_MAX;
	inline static float delay = Constants::STARTUP_DELAY;
	
	inline static std::vector<unsigned int> pointers;

	std::atomic<bool> pointersVisible = false,
		paused = false,
		sorting = false,
		shuffling = false,
		makestep = false;

	sf::Time calculateDelay(const float) const;
	void makeDelay() const;

	bool checkSorting();
	void sortingFinished();

	virtual void sort() = 0;
public:
	void start();
	void stop();
	void pause();
	void step();
	void shuffle();
	void reset();

	Statistic getStats() const;

	void setArraySize(const unsigned int);
	void setRange(const double, const double);
	void setDelay(const float);

	unsigned int getSize() const;
	double getMinRange() const;
	double getMaxRange() const;
	float getDelay() const;

	bool isPaused() const;
	bool isSorting() const;
	bool isShuffling() const;
	bool showPointers() const;

	const std::vector<unsigned int>& getPointers() const;

	const std::vector<double>* getNumbers() const;
	void setNumbers(const std::vector<double>&, const double, const double);

	virtual ~Algorithm() = default;
};
