#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <miniocpp/s3.h>

#include <iostream>

#include "client/minio_client.h"

ABSL_FLAG(std::string, host_addr, "play.min.io", "Minio host address");
ABSL_FLAG(int, host_port, 9000, "Minio host port");
ABSL_FLAG(std::string, access_key, "minioadmin", "Minio access key");
ABSL_FLAG(std::string, secret_key, "minioadmin", "Minio secret key");
ABSL_FLAG(bool, disable_tls, false, "Whether or not to disable TLS (HTTPS)");

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  std::string host_addr = absl::GetFlag(FLAGS_host_addr);
  int host_port = absl::GetFlag(FLAGS_host_port);
  std::string access_key = absl::GetFlag(FLAGS_access_key);
  std::string secret_key = absl::GetFlag(FLAGS_secret_key);
  bool enable_tls = !absl::GetFlag(FLAGS_disable_tls);

  ftrans::ClientConfig config(host_addr, host_port, access_key, secret_key);
  ftrans::MinioClient client(config, enable_tls);

  // create bucket
  std::cout << "create bucket" << std::endl;
  if (!client.CreateDirectory("newbucket")) {
    return -1;
  }

  // upload file
  std::cout << "upload file" << std::endl;
  if (!client.UploadFile("/tmp/test.txt", "newbucket", "test.txt")) {
    return -1;
  }

  // check file
  std::cout << "list objects" << std::endl;
  if (!client.Exists("newbucket", "test.txt")) {
    return -1;
  }

  // download file (not implemented)
  std::cout << "download file (not implemented)" << std::endl;
  // client.DownloadFile("newbucket", "test.txt", "/tmp/test.txt.download");

  // remove file
  std::cout << "remove file" << std::endl;
  if (!client.RemoveFile("newbucket", "test.txt")) {
    return -1;
  }

  return 0;
}