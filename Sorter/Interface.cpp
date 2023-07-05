#include "Interface.h"

void Interface::init(sf::RenderWindow& window) {
	ImGui::SFML::Init(window, false);

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;

	ImFontConfig config;
	config.MergeMode = true;
	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

	io.Fonts->AddFontFromMemoryCompressedBase85TTF(ubuntu_font, Constants::MAIN_FONT_SIZE);
	io.Fonts->AddFontFromMemoryCompressedBase85TTF(icons_font, Constants::ICONS_FONT_SIZE, &config, icon_ranges);
	
	ImGui::SFML::UpdateFontTexture();

	ImPlot::CreateContext();
}

void Interface::draw(sf::RenderWindow& window) {
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::SetNextWindowSizeConstraints(ImVec2(600, -1), ImVec2(FLT_MAX, -1));


	ImGui::Begin("Sorting program", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize);

	bool isSorting = Controller::isSorting();
	bool isPaused = Controller::isPaused();
	bool isShuffling = Controller::isShuffling();

	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y + Constants::CONTROL_BUTTONS_SIZE.y / 2 - 11);

	ImGui::PushItemWidth(Constants::INPUT_ELEMENTS_WIDTH);
	ImGui::BeginDisabled(isSorting || isShuffling);
	if (ImGui::Combo("##Algorithm", &algorithm,
		Controller::getAlgorithms(), Controller::getAlgorithmsNumber())) {
		Controller::changeAlgorithm(algorithm);
	} ImGui::SameLine();
	ImGui::EndDisabled();

	ImGui::Text("Algorithm");
	ImGui::SameLine();

	float startX = ImGui::GetWindowSize().x / 2 - Constants::CONTROL_BUTTONS_SIZE.x * 3 - ImGui::GetStyle().ItemSpacing.x * 2;

	ImGui::SetCursorPosX(startX);
	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y);

	ImGui::BeginDisabled(isShuffling);
	if (ImGui::Button(isSorting ? ICON_FA_STOP : ICON_FA_PLAY, Constants::CONTROL_BUTTONS_SIZE)) {
		if (isSorting) {
			Controller::stop();
		}
		else {
			Controller::start();
		}
	}
	ImGui::EndDisabled();
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y);
	ImGui::BeginDisabled(!isSorting);
	if (ImGui::Button(isPaused ? ICON_FA_PLAY : ICON_FA_PAUSE, Constants::CONTROL_BUTTONS_SIZE)) {
		Controller::pause();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y);
	ImGui::BeginDisabled(!isSorting || !isPaused);
	if (ImGui::Button(ICON_FA_STEP_FORWARD, Constants::CONTROL_BUTTONS_SIZE)) {
		Controller::step();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y);
	ImGui::BeginDisabled(isSorting || isShuffling);
	if (ImGui::Button(ICON_FA_RANDOM, Constants::CONTROL_BUTTONS_SIZE)) {
		Controller::shuffle();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y);
	ImGui::BeginDisabled(isSorting || isShuffling);
	if (ImGui::Button(ICON_FA_FLOPPY_O, Constants::CONTROL_BUTTONS_SIZE))
	{
		std::string savePath = FileProcessor::SaveFileDialog("Save numbers array");
		if (!savePath.empty()) {
			try {
				FileProcessor::WriteToFile(Controller::getNumbers(), savePath);
			}
			catch (std::exception& e) {
				errorMessage = e.what();
			}
		}
	}
	ImGui::EndDisabled();
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y);
	ImGui::BeginDisabled(isSorting || isShuffling);
	if (ImGui::Button(ICON_FA_DOWNLOAD, Constants::CONTROL_BUTTONS_SIZE))
	{
		std::string loadPath = FileProcessor::OpenFileDialog("Load numbers array");
		if (!loadPath.empty()) {
			try {
				std::vector<double> numbers = FileProcessor::ReadFormFile(loadPath);
				Controller::setNumbers(numbers);
			}
			catch (std::exception& e) {
				errorMessage = e.what();
			}
		}
	}
	ImGui::EndDisabled();
	ImGui::SameLine();

	startX = ImGui::GetWindowSize().x - (Constants::INPUT_ELEMENTS_WIDTH + Constants::DELAY_BUTTON_SIZE.x + ImGui::GetStyle().ItemSpacing.x * 2);
	ImGui::SetCursorPosX(startX);
	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y + Constants::CONTROL_BUTTONS_SIZE.y / 2 - 11);

	if (ImGui::Button(ICON_FA_CLOCK_O, Constants::DELAY_BUTTON_SIZE)) {
		doDelay = !doDelay;
		if (doDelay) {
			Controller::setDelay(delay);
		}
		else {
			Controller::setDelay(0.0);
		}
	} ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y + Constants::CONTROL_BUTTONS_SIZE.y / 2 - 11);
	ImGui::BeginDisabled(!doDelay);
	if (ImGui::SliderFloat("##Delay", &delay, Constants::DELAY_RANGE_MIN, Constants::DELAY_RANGE_MAX, "%.2f ms", ImGuiSliderFlags_Logarithmic)) {
		Controller::setDelay(delay);
	}
	ImGui::SameLine();
	ImGui::Text("Delay");
	ImGui::EndDisabled();


	if (ImGui::InputScalar("Size of array", ImGuiDataType_U32, &arraySize, nullptr, nullptr, "%u", ImGuiInputTextFlags_CharsDecimal)) {
		if (arraySize > Constants::ARRAY_SIZE_LIMIT) {
			arraySize = Constants::ARRAY_SIZE_LIMIT;
		}
		else if (arraySize == 0) {
			arraySize = 1;
		}
	}

	if (ImGui::InputDouble("Range Min", &rangeMin, 1, 10, "%.12g")) {
		if (rangeMin > Constants::ARRAY_RANGE_MAX_LIMIT) {
			rangeMin = Constants::ARRAY_RANGE_MAX_LIMIT;
		}
		else if (rangeMin < Constants::ARRAY_RANGE_MIN_LIMIT) {
			rangeMin = Constants::ARRAY_RANGE_MIN_LIMIT;
		}
		if (rangeMax < rangeMin) {
			rangeMax = rangeMin;
		}
	}

	if (ImGui::InputDouble("Range Max", &rangeMax, 1, 10, "%.12g")) {
		if (rangeMax > Constants::ARRAY_RANGE_MAX_LIMIT) {
			rangeMax = Constants::ARRAY_RANGE_MAX_LIMIT;
		}
		else if (rangeMax < Constants::ARRAY_RANGE_MIN_LIMIT) {
			rangeMax = Constants::ARRAY_RANGE_MIN_LIMIT;
		}
		if (rangeMax < rangeMin) {
			rangeMax = rangeMin;
		}
	}

	ImGui::BeginDisabled(isSorting || isShuffling);
	if (ImGui::Button("Generate array", Constants::APPLY_BUTTON_SIZE))
	{
		Controller::setArraySize(arraySize);
		Controller::setRange(rangeMin, rangeMax);
		Controller::shuffle();
	}
	ImGui::EndDisabled();

	if (!errorMessage.empty()) {
		ImGui::OpenPopup("ERROR");
	}

	if (ImGui::BeginPopupModal("ERROR", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text(errorMessage.c_str());
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
			errorMessage.clear();
		}
		ImGui::EndPopup();
	}

	ImGui::Separator();

	Statistic stat = Controller::getStatistic();
	Controller::updateTime();
	sf::Time visualTime = Controller::getTime();

	double minr = Controller::getMinRange();
	double maxr = Controller::getMaxRange();

	if (ImGui::BeginTable("table", 6, ImGuiTableFlags_BordersInnerV)) {
		ImGui::TableNextColumn();
		ImGui::Text("Comparisons: %llu", stat.getComparisons());
		ImGui::SameLine();

		ImGui::TableNextColumn();
		ImGui::Text("Swaps: %llu", stat.getSwaps());

		ImGui::TableNextColumn();
		ImGui::Text("Recursive Depth: %llu", stat.getRecursiveDepth());

		ImGui::TableNextColumn();
		ImGui::Text("Max Depth: %llu", stat.getMaxRecursiveDepth());

		ImGui::TableNextColumn();
		ImGui::Text("Time: %.4f s", visualTime.asSeconds());
		ImGui::SameLine();

		ImGui::TableNextColumn();
		ImGui::Text("%u: %.6g - %.6g", Controller::getSize(), minr, maxr);
		ImGui::SameLine();

		ImGui::EndTable();
	}

	ImGui::Separator();

	float graphHeight = ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() * 6 - Constants::CONTROL_BUTTONS_SIZE.y - 25;
	const double* values = Controller::getNumbers()->data();

	ImPlotAxisFlags axisFlags = ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoSideSwitch | ImPlotAxisFlags_NoHighlight | ImPlotAxisFlags_NoTickLabels;

	if (ImPlot::BeginPlot("##Visualization", { -1, graphHeight }, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText)) {
		ImPlot::SetupAxes(NULL, NULL, axisFlags, axisFlags);
		ImPlot::SetupAxesLimits(-0.5, Controller::getSize() - 0.5, minr == maxr ? minr < 0 ? -1 : 1 : minr, Controller::getMaxRange(), ImPlotCond_Always);

		ImPlot::PushStyleColor(ImPlotCol_Fill, Constants::BAR_COLOR);
		ImPlot::PlotBars("##Numbers", &values[0], Controller::getSize(), Constants::BAR_WIDTH);
		ImPlot::PopStyleColor();


		if (Controller::showPointers()) {
			const std::vector<unsigned int> pointers = Controller::getPointers();
			ImPlot::PushStyleColor(ImPlotCol_Fill, Constants::POINTER_COLOR);
			for (unsigned int pointer : pointers) {
				double pointerX = (double)pointer;
				double pointerY = values[pointer];
				ImPlot::PlotBars("##Cursor", &pointerX, &pointerY, 1, Constants::POINTER_WIDTH);
			}
			ImPlot::PopStyleColor();
		}

		ImPlot::EndPlot();
	}


	ImGui::End();
	ImGui::SFML::Render(window);
}

void Interface::update(sf::RenderWindow& window, sf::Time diff) {
	ImGui::SFML::Update(window, diff);
}

void Interface::destroy() {
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}

void Interface::processEvent(sf::Event& newEvent) {
	ImGui::SFML::ProcessEvent(newEvent);
}
