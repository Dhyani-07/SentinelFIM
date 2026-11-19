#include "hasher.hpp"

#include <openssl/evp.h>

#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>

namespace sentinel {

namespace {
// RAII: this guarantees EVP_MD_CTX_free() is always called.
struct CtxDeleter {
    void operator()(EVP_MD_CTX* ctx) const { EVP_MD_CTX_free(ctx); }
};
using CtxPtr = std::unique_ptr<EVP_MD_CTX, CtxDeleter>;
}  // namespace

std::optional<std::string> sha256_file(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return std::nullopt;

    CtxPtr ctx(EVP_MD_CTX_new());
    if (!ctx || EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) != 1)
        return std::nullopt;

    std::vector<char> buffer(64 * 1024);  // 64 KB chunk
    while (file) {
        file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        const std::streamsize n = file.gcount();
        if (n > 0 && EVP_DigestUpdate(ctx.get(), buffer.data(),
                                      static_cast<size_t>(n)) != 1)
            return std::nullopt;
    }
    if (file.bad()) return std::nullopt;

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    if (EVP_DigestFinal_ex(ctx.get(), digest, &len) != 1) return std::nullopt;

    std::ostringstream oss;
    for (unsigned int i = 0; i < len; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(digest[i]);
    return oss.str();
}

}  // namespace sentinel