#include <getopt.h>
#include <miniocpp/s3.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
  S3Client s3("https://play.min.io:9000", "minioadmin", "minioadmin");
  Minio::S3ClientIO io;
  s3.MakeBucket("newbucket", io);
  if (io.Failure()) {
    std::cerr << "ERROR: failed to create bucket" << std::endl;
    std::cerr << "response:\n" << io << std::endl;
    std::cerr << "response body:\n" << io.response.str() << std::endl;
    return -1;
  }
  return 0;
}