#pragma once
#include <filesystem>

#include "scanner.hpp"

namespace sentinel {

void save_baseline(const Snapshot& snap, const std::filesystem::path& root,
                   const std::filesystem::path& out_file);

}  // namespace sentinel