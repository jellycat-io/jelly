//
// Created by Maxime Blanc on 05/09/2021.
//

#include "IOManager.h"
#include "Logger.h"
#include <fmt/core.h>

bool Jelly::IOManager::ReadFileToBuffer(const std::string &filename, std::vector<unsigned char> &buffer) {
	std::ifstream file(filename, std::ios::binary);
	if (file.fail()) {
		Logger::Error(fmt::format("Failed to open {}", filename), false);
		return false;
	}

	// Seek to eof
	file.seekg(0, std::ios::end);

	// Get file size
	std::streamoff size = file.tellg();
	file.seekg(0, std::ios::beg);

	// Reduce file size by any present header bytes
	size -= file.tellg();

	buffer.resize(size);
	file.read((char *)&(buffer[0]), size);

	file.close();

	return true;
}

void Jelly::IOManager::AppendToFile(const std::string &filename, const std::string &data) {
	std::ofstream file(filename, std::ios_base::app);

	if(file.fail()) {
		Logger::Error(fmt::format("File {} not found", filename), false);
		exit(1);
	}

	file << data;

	file.close();
}

std::string Jelly::IOManager::ReadFromFile(const std::string &filename) {
	std::ifstream file(filename);

	if (file.fail()) {
		Logger::Error(fmt::format("Failed to open file {}", filename));
		exit(1);
	}

	std::string data;
	std::string line;

	while(std::getline(file, line)) {
		data += line + "\n";
	}

	file.close();

	return data;
}

bool Jelly::IOManager::RemoveFile(const std::string &filename) {
	if (!std::filesystem::exists(filename)) return false;

	if(remove(filename.c_str()) != 0) {
		Logger::Error(fmt::format("Error deleting {}", filename), false);
		return false;
	}

	return true;
}
