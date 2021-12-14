#include <string>
#include <utility>

namespace ftrans {

struct ClientConfig {
 public:
  ClientConfig(std::string in_host_addr, int in_host_port,
               std::string in_access_key, std::string in_secret_key)
      : host_addr(std::move(in_host_addr)),
        host_port(in_host_port),
        access_key(std::move(in_access_key)),
        secret_key(std::move(in_secret_key)){};

 public:
  std::string host_addr;
  int host_port;
  std::string access_key;
  std::string secret_key;
};

}  // namespace ftrans