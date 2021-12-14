#include <vector>

#include "common/config.h"

namespace ftrans {

class BaseClient {
 public:
  BaseClient(const ClientConfig& config) : config_(config) {}

 public:
  virtual void Connect() = 0;
  virtual void Disconnect() = 0;

  virtual bool CreateDirectory(const std::string& remote_dir) = 0;
  virtual bool RemoveDirectory(const std::string& remote_dir) = 0;
  virtual std::vector<std::string> ListDirectory(
      const std::string& remote_dir) = 0;

  virtual bool UploadFile(const std::string& local_filepath,
                          const std::string& remote_dir,
                          const std::string& remote_filename) = 0;
  virtual bool DownloadFile(const std::string& remote_dir,
                            const std::string& remote_filename,
                            const std::string& local_filepath) = 0;
  virtual bool RemoveFile(const std::string& remote_dir,
                          const std::string& remote_filename) = 0;

  virtual bool Exists(const std::string& remote_dir,
                      const std::string& remote_filename) = 0;
  virtual bool Exists(const std::string& remote_dir) = 0;

 protected:
  ClientConfig config_;
};

}  // namespace ftrans