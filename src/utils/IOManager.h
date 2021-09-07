//
// Created by Maxime Blanc on 05/09/2021.
//

#pragma once

#include <fstream>
#include <vector>

class IOManager {
public:
	static bool ReadFileToBuffer(const std::string &filename, std::vector<unsigned char> &buffer);
	static std::string ReadFromFile(const std::string &filename);
	static void AppendToFile(const std::string &filename, const std::string &data);
	static bool RemoveFile(const std::string &filename);
};
