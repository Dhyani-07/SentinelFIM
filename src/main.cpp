#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "baseline.hpp"
#include "scanner.hpp"

namespace fs = std::filesystem;

static void print_usage() {
    std::cout << "SentinelFIM\n"
                 "Usage:\n"
                 "  sentinel baseline <folder> [output.json]\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3 || std::string(argv[1]) != "baseline") {
        print_usage();
        return 1;
    }

    const fs::path folder = argv[2];
    const fs::path out = (argc >= 4) ? fs::path(argv[3]) : fs::path("baseline.json");

    std::error_code ec;
    if (!fs::is_directory(folder, ec)) {
        spdlog::error("Not a folder: {}", folder.string());
        return 1;
    }

    try {
        spdlog::info("Scanning {} ...", folder.string());
        const auto snapshot = sentinel::scan_directory(folder);
        sentinel::save_baseline(snapshot, folder, out);
        spdlog::info("Hashed {} files -> {}", snapshot.size(), out.string());
    } catch (const std::exception& e) {
        spdlog::error("Fatal: {}", e.what());
        return 2;
    }
    return 0;
}