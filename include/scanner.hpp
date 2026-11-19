#pragma once
#include <cstdint>
#include <filesystem>
#include <map>
#include <string>

namespace sentinel {

struct FileRecord {
    std::string sha256;
    std::uintmax_t size = 0;
    std::int64_t mtime = 0;  // last-write time (raw clock ticks, used for comparison)
};

// relative path -> record. std::map keeps keys sorted, so output is stable.
using Snapshot = std::map<std::string, FileRecord>;

Snapshot scan_directory(const std::filesystem::path& root);

}  // namespace sentinel