#include "FileProcessor.h"

std::string FileProcessor::SaveFileDialog(const std::string& title) {
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		return std::string(ofn.lpstrFile);
	}

	return "";
}

std::string FileProcessor::OpenFileDialog(const std::string& title) {
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return std::string(ofn.lpstrFile);
	}

	return "";
}

bool FileProcessor::WriteToFile(const std::vector<double>* numbers, const std::string& path) {
	if (path.empty()) {
		throw std::exception("Empty path");
	}

	std::ofstream file(path);
	if (!file.is_open()) {
		throw std::exception("Can't open file for writing");
	}

	file << numbers->size() << std::endl;
	for (const double number : *numbers) {
		file << number << std::endl;
	}

	file.close();

	return true;
}

std::vector<double> FileProcessor::ReadFormFile(const std::string& path) {
	if (path.empty()) {
		throw std::exception("Empty path");
	}

	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::exception("Can't open file for reading");
	}

	unsigned int size;
	std::vector<double> numbers;

	if (file >> size) {
		if (size > 0 && size < Constants::ARRAY_RANGE_MAX_LIMIT) {
			numbers.resize(size);
			double number;
			unsigned int count = 0;

			while (file >> number) {
				numbers[count] = number;
				count++;
			}

			file.close();

			if (count != size) {
				throw std::exception("Error: Unexpected number of values in the file");
			}
		}
		else {
			file.close();
			throw std::exception("Error: invalid size of array");
		}
	}
	else {
		file.close();
		throw std::exception("Error: Failed to read the size of the number vector from the file");
	}

	return numbers;
}
