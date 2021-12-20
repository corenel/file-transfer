#pragma once

#include <aws/s3/S3Client.h>

#include "interface/base_client.h"

namespace ftrans {

class AwsClient : protected BaseClient {
 public:
  AwsClient(const ClientConfig& config, const bool& secure = true);
  ~AwsClient();

 public:
  void Connect() override;
  void Disconnect() override;

  bool CreateDirectory(const std::string& remote_dir) override;
  bool RemoveDirectory(const std::string& remote_dir) override;
  std::vector<std::string> ListDirectory(
      const std::string& remote_dir) override;

  bool UploadFile(const std::string& local_filepath,
                  const std::string& remote_dir,
                  const std::string& remote_filename) override;
  bool DownloadFile(const std::string& remote_dir,
                    const std::string& remote_filename,
                    const std::string& local_filepath) override;
  bool RemoveFile(const std::string& remote_dir,
                  const std::string& remote_filename) override;

  bool Exists(const std::string& remote_dir,
              const std::string& remote_filename) override;
  bool Exists(const std::string& remote_dir) override;

 private:
  bool secure_;
  std::shared_ptr<Aws::S3::S3Client> s3_;
};

}  // namespace ftrans