//
// Created by Maxime Blanc on 05/09/2021.
//
#include "Logger.h"
#include "IOManager.h"
#include <iostream>
#include <fmt/core.h>
#include <ctime>
#include <chrono>

void Jelly::Logger::Error(const std::string& message, bool writeToFile) {

	std::cout << "\033[1;35m" << getTime() << " \033[0;1;37;45m[ERROR]\033[0m \033[0;1;35m>> \033[0;35m" << message << "\033[0m" << std::endl;

	if (writeToFile) {
		IOManager::AppendToFile("error-log.txt", fmt::format("{} [Error]: {}\n", getTime(), message));
	}
}

void Jelly::Logger::Warn(const std::string& message, bool writeToFile) {
	std::cout << "\033[1;32m" << getTime() << " \033[0;1;37;42m[WARNING]\033[0m \033[0;1;32m>> \033[0;32m" << message << "\033[0m" << std::endl;

	if (writeToFile) {
		IOManager::AppendToFile("error-log.txt", fmt::format("{}[Warning]: {}\n", getTime(), message));
	}
}

void Jelly::Logger::Trace(const std::string& message) {
	std::cout << "\033[1;34m" << getTime() << " \033[0;1;37;44m[TRACE]\033[0m \033[0;1;34m>> \033[0;34m" << message << "\033[0m" << std::endl;
}

std::string Jelly::Logger::getTime() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string s(19, ' ');
	std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

	return s;
}

void Jelly::Logger::ClearLogs() {
	if (IOManager::RemoveFile("error-log.txt")) {
		Logger::Warn("Cleared logs", false);
	}
}
