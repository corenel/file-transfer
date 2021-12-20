#include "client/aws_client.h"

namespace ftrans {

AwsClient::AwsClient(const ClientConfig& config, const bool& secure)
    : BaseClient(config), secure_(secure) {}

AwsClient::~AwsClient() {}

void AwsClient::Connect() {}

void AwsClient::Disconnect() {}

bool AwsClient::CreateDirectory(const std::string& remote_dir) { return false; }

bool AwsClient::RemoveDirectory(const std::string& remote_dir) { return false; }

std::vector<std::string> AwsClient::ListDirectory(
    const std::string& remote_dir) {
  return {};
}

bool AwsClient::UploadFile(const std::string& local_filepath,
                           const std::string& remote_dir,
                           const std::string& remote_filename) {
  return false;
}

bool AwsClient::DownloadFile(const std::string& remote_dir,
                             const std::string& remote_filename,
                             const std::string& local_filepath) {
  return false;
}

bool AwsClient::RemoveFile(const std::string& remote_dir,
                           const std::string& remote_filename) {
  return false;
}

bool AwsClient::Exists(const std::string& remote_dir,
                       const std::string& remote_filename) {
  return false;
}

bool AwsClient::Exists(const std::string& remote_dir) { return false; }

}  // namespace ftrans