# file-transfer

Example project for file uploading and downloading.

## Installation

```bash
cd file-transfer
pip install .
```

> For Python 2, use the version `6.0.2` of`minio`, a.k.a, `python2 -m pip install minio==6.0.2`

## Example

- `example/example_minio.py`:
  - connect to MinIO server
  - upload file to MinIO server
  - download file from MinIO server
  - remove file on MinIO server
