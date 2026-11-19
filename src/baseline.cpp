#include "baseline.hpp"

#include <nlohmann/json.hpp>

#include <chrono>
#include <fstream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace sentinel {

void save_baseline(const Snapshot& snap, const fs::path& root,
                   const fs::path& out_file) {
    nlohmann::json j;
    j["version"] = 1;
    j["root"] = fs::absolute(root).generic_u8string();
    j["created_unix"] = std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch())
                            .count();

    nlohmann::json files = nlohmann::json::object();
    for (const auto& [path, rec] : snap) {
        files[path] = {{"sha256", rec.sha256},
                       {"size", rec.size},
                       {"mtime", rec.mtime}};
    }
    j["files"] = files;

    std::ofstream out(out_file);
    if (!out) throw std::runtime_error("Cannot write " + out_file.string());
    out << j.dump(2);
}

}  // namespace sentinel