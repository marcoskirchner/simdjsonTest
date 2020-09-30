#include "simdjson.h"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[], char* envp[]) {

	if (argc < 2) {
		std::cout << "simdjson v" << STRINGIFY(SIMDJSON_VERSION) << std::endl;
		std::cout << "Detected the best implementation for your machine: " << simdjson::active_implementation->name();
		std::cout << "(" << simdjson::active_implementation->description() << ")" << std::endl << std::endl;

		std::cout << "Available implementations:" << std::endl;
		for (auto implementation : simdjson::available_implementations) {
			std::cout << implementation->name() << ": " << implementation->description() << std::endl;
		}
		std::cout << std::endl;

		std::cout << "Usage:" << std::endl << argv[0] << " <directory> [simdjson implementation]" << std::endl;
	}
	else {
		std::string path = argv[1];
		if (argc >= 3) {
			std::string impl = argv[2];
			simdjson::active_implementation = simdjson::available_implementations[impl];
		}

		std::cout << "Reading json files from: " << path << std::endl;
		std::cout << "Using simdjson implementation: " << simdjson::active_implementation->name() << std::endl;




		auto t1 = std::chrono::high_resolution_clock::now();
		simdjson::dom::parser parser;
		int fileCount = 0;

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.path().extension() == ".json") {
				std::cout << entry.path() << " - ";

				simdjson::dom::element data = parser.load(entry.path().string());
				std::cout << data["count"] << std::endl;
				fileCount++;
			}
		}

		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

		std::cout << std::endl << "Processed " << fileCount << " file(s) in " << fp_ms.count() << " second(s)" << std::endl;
	}
}
