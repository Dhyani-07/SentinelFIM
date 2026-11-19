#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <openssl/opensslv.h>

int main() {
    spdlog::info("SentinelFIM starting up...");

    nlohmann::json info;
    info["project"] = "SentinelFIM";
    info["version"] = "0.1.0";
    spdlog::info("Config test: {}", info.dump());

    spdlog::info("Using {}", OPENSSL_VERSION_TEXT);
    return 0;
}