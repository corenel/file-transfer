#include "client/minio_client.h"

#include <fmt/format.h>

namespace ftrans {

MinioClient::MinioClient(const ClientConfig& config, const bool& secure)
    : BaseClient(config), secure_(secure) {
  Connect();
}

MinioClient::~MinioClient() { Disconnect(); }

void MinioClient::Connect() {
  s3_ = std::make_shared<S3Client>(GetEndpoint(), config_.access_key,
                                   config_.secret_key);
}

void MinioClient::Disconnect() { s3_.reset(); }

bool MinioClient::CreateDirectory(const std::string& remote_dir) {
  if (Exists(remote_dir)) {
    return true;
  }
  Minio::S3ClientIO io;
  s3_->MakeBucket(remote_dir, io);
  if (io.Failure()) {
    std::cerr << "ERROR: failed to create bucket" << std::endl;
    std::cerr << "response:\n" << io << std::endl;
    std::cerr << "response body:\n" << io.response.str() << std::endl;
    return false;
  } else {
    return true;
  }
}

bool MinioClient::RemoveDirectory(const std::string& remote_dir) {
  Minio::S3ClientIO io;
  s3_->RemoveBucket(remote_dir, io);
  if (io.Failure()) {
    std::cerr << "ERROR: failed to remove bucket" << std::endl;
    std::cerr << "response:\n" << io << std::endl;
    std::cerr << "response body:\n" << io.response.str() << std::endl;
    return false;
  } else {
    return true;
  }
}

std::vector<std::string> MinioClient::ListDirectory(
    const std::string& remote_dir) {
  Minio::S3ClientIO io;
  s3_->ListObjects(remote_dir, io);
  // TODO: list objects into a vector
  std::cerr << "ERROR: not implemented" << std::endl;
  std::cerr << "response:\n" << io << std::endl;
  std::cerr << "response body:\n" << io.response.str() << std::endl;
  return {};
}

bool MinioClient::UploadFile(const std::string& local_filepath,
                             const std::string& remote_dir,
                             const std::string& remote_filename) {
  Minio::S3ClientIO io;
  s3_->PutObject(remote_dir, remote_filename, local_filepath, io);
  if (io.Failure()) {
    std::cerr << "ERROR: failed to upload file" << std::endl;
    std::cerr << "response:\n" << io << std::endl;
    std::cerr << "response body:\n" << io.response.str() << std::endl;
    return false;
  } else {
    return true;
  }
}

bool MinioClient::DownloadFile(const std::string& remote_dir,
                               const std::string& remote_filename,
                               const std::string& local_filepath) {
  Minio::S3ClientIO io;
  s3_->GetObject(remote_dir, remote_filename, io);
  // TODO: save objects into local file
  std::cerr << "ERROR: not implemented" << std::endl;
  std::cerr << "response:\n" << io << std::endl;
  std::cerr << "response body:\n" << io.response.str() << std::endl;
  return false;
}

bool MinioClient::RemoveFile(const std::string& remote_dir,
                             const std::string& remote_filename) {
  Minio::S3ClientIO io;
  s3_->DeleteObject(remote_dir, remote_filename, io);
  if (io.Failure()) {
    std::cerr << "ERROR: failed to remove file" << std::endl;
    std::cerr << "response:\n" << io << std::endl;
    std::cerr << "response body:\n" << io.response.str() << std::endl;
    return false;
  } else {
    return true;
  }
}

bool MinioClient::Exists(const std::string& remote_dir,
                         const std::string& remote_filename) {
  Minio::S3ClientIO io;
  s3_->ListObjects(remote_dir, io);
  if (io.response.str().find(remote_filename) != std::string::npos) {
    return true;
  } else {
    return false;
  }
}

bool MinioClient::Exists(const std::string& remote_dir) {
  Minio::S3ClientIO io;
  s3_->ListBuckets(io);
  if (io.response.str().find(remote_dir) != std::string::npos) {
    return true;
  } else {
    return false;
  }
}

std::string MinioClient::GetEndpoint() {
  if (secure_) {
    return fmt::format("https://{}:{}", config_.host_addr, config_.host_port);
  } else {
    return fmt::format("http://{}:{}", config_.host_addr, config_.host_port);
  }
}

}  // namespace ftrans