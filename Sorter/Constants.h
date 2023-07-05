#pragma once

#include "implot.h"

namespace Constants {
	static const float MAIN_FONT_SIZE = 18.0f;
	static const float ICONS_FONT_SIZE = 16.0f;

	static const unsigned int ARRAY_SIZE_LIMIT = 50000;
	static const int ARRAY_RANGE_MIN_LIMIT = -100000;
	static const int ARRAY_RANGE_MAX_LIMIT = 100000;

	static const float DELAY_RANGE_MIN = 1;
	static const float DELAY_RANGE_MAX = 1000;

	static const int STARTUP_ALGORITHM = 0;
	static const float STARTUP_DELAY = 10;
	static const double STARTUP_RANGE_MIN = 0;
	static const double STARTUP_RANGE_MAX = 100;
	static const unsigned int STARTUP_ARRAY_SIZE = 200;
	static const bool STARTUP_DO_DELAY = STARTUP_DELAY ? true : false;

	static const float INPUT_ELEMENTS_WIDTH = 180.0f;
	static const float BAR_WIDTH = 1;
	static const float POINTER_WIDTH = 1;

	const ImVec4 BAR_COLOR = { 0.2f, 0.41f, 0.69f, 1.f };
	const ImVec4 POINTER_COLOR = { 1.f, 0.f, 0.f, 1.f };
	const ImVec2 CONTROL_BUTTONS_SIZE = { 40, 40 };
	const ImVec2 APPLY_BUTTON_SIZE = { 180, 22 };
	const ImVec2 DELAY_BUTTON_SIZE = { 24, 24 };
};
