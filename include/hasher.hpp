#pragma once
#include <filesystem>
#include <optional>
#include <string>

namespace sentinel {

// Returns the SHA-256 of a file as a 64-char hex string,
// or std::nullopt if the file cannot be read.
std::optional<std::string> sha256_file(const std::filesystem::path& path);

}  // namespace sentinel