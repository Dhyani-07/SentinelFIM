#include "scanner.hpp"

#include <spdlog/spdlog.h>

#include "hasher.hpp"

namespace fs = std::filesystem;

namespace sentinel {

Snapshot scan_directory(const fs::path& root) {
    Snapshot snapshot;

    for (const auto& entry : fs::recursive_directory_iterator(
             root, fs::directory_options::skip_permission_denied)) {
        std::error_code ec;
        if (!entry.is_regular_file(ec) || ec) continue;  // skip folders, links, etc.

        auto hash = sha256_file(entry.path());
        if (!hash) {
            spdlog::warn("Could not read: {}", entry.path().string());
            continue;
        }

        FileRecord rec;
        rec.sha256 = *hash;
        rec.size = entry.file_size(ec);
        rec.mtime = static_cast<std::int64_t>(
            entry.last_write_time(ec).time_since_epoch().count());

        const std::string rel =
            fs::relative(entry.path(), root).generic_u8string();
        snapshot[rel] = rec;
    }
    return snapshot;
}

}  // namespace sentinel