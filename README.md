# file-transfer

Example project for file uploading and downloading.

## Installation

### Python

1. Install project as a Python package

   ```bash
   cd file-transfer
   pip install .
   ```

> For Python 2, use the version `6.0.2` of`minio`, a.k.a, `python2 -m pip install minio==6.0.2`

### C++

1. Install [minio-cpp](https://github.com/minio/minio-cpp):

   ```bash
   sudo apt install libpugixml-dev -y
   cd /tmp && \
     git clone https://github.com/minio/minio-cpp && \
     cd minio-cpp && \
     git submodule init && \
     git submodule update && \
     mkdir build && \
     cd build && \
     cmake ../ && \
     make && \
     sudo make install && \
     cd /tmp && rm -rf minio-cpp
   ```

2. Install [abseil-cpp](https://github.com/abseil/abseil-cpp):

   ```bash
   cd /tmp && \
     git clone https://github.com/abseil/abseil-cpp.git && \
     cd abseil-cpp && \
     git checkout lts_2021_11_02 && \
     mkdir build && \
     cd build && \
     cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON .. && \
     make && \
     sudo make install && \
     cd /tmp && rm -rf abseil-cpp
   ```

3. Install [fmt](https://github.com/fmtlib/fmt):

   ```bash
   sudo apt install -y libfmt-dev
   ```

4. Build project

   ```bash
   cd file-transfer
   mkdir build; cd build; cmake ..;
   make
   ```

## Example

- `example/example_python_minio.py`:
  - connect to MinIO server
  - create bucket on MinIO server
  - upload file to MinIO server
  - download file from MinIO server
  - remove file on MinIO server
- `example/example_cpp_minio.cc`:
  - connect to MinIO server
  - create bucket on MinIO server
  - upload file to MinIO server
  - download file from MinIO server (not implemented)
  - remove file on MinIO server
