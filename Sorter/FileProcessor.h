#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Constants.h"
#include "WindowsConfig.h"

namespace FileProcessor {
	std::string SaveFileDialog(const std::string&);
	std::string OpenFileDialog(const std::string&);
	bool WriteToFile(const std::vector<double>*, const std::string&);
	std::vector<double> ReadFormFile(const std::string&);
};
