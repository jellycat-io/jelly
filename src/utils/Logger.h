//
// Created by Maxime Blanc on 05/09/2021.
//

#pragma once

#include <string>

namespace Jelly {
	class Logger {
	public:
		static void Error(const std::string& message, bool writeToFile = true);
		static void Warn(const std::string& message, bool writeToFile = true);
		static void Trace(const std::string& message);
		static void ClearLogs();

	private:
		static std::string getTime();
	};
}
