import argparse
import os

from ftrans.client import MinioClient, ClientConfig


def touch(fname, times=None):
    with open(fname, 'a'):
        os.utime(fname, times)


def parse_args():
    parser = argparse.ArgumentParser(description='Minio example')
    parser.add_argument('--host_addr',
                        type=str,
                        help='Minio host address',
                        default='localhost')
    parser.add_argument('--host_port',
                        type=int,
                        help='Minio host port',
                        default=9000)
    parser.add_argument('--access_key',
                        type=str,
                        required=True,
                        help='Minio access key')
    parser.add_argument('--secret_key',
                        type=str,
                        required=True,
                        help='Minio secret key')
    parser.add_argument('--filepath',
                        type=str,
                        default='/tmp/test.txt',
                        help='Filepath to upload')
    parser.add_argument('--bucket',
                        type=str,
                        default='test',
                        help='Bucket name')
    parser.add_argument('--object',
                        type=str,
                        default='test.txt',
                        help='Object name')
    return parser.parse_args()


def main():
    # init
    args = parse_args()
    config = ClientConfig(host_addr=args.host_addr,
                          host_port=args.host_port,
                          access_key=args.access_key,
                          secret_key=args.secret_key)
    client = MinioClient(config)
    touch(args.filepath)

    # create dir
    if not client.exists_dir(args.bucket):
        client.create_dir(args.bucket)
        print('Bucket created: {}'.format(args.bucket))

    # upload file
    result = client.upload_file(args.filepath, args.bucket, args.object)
    print('File uploaded: {}'.format(args.filepath))

    # download file
    download_path = '{}.download'.format(args.filepath)
    if not client.exists(args.bucket, args.object):
        print('Object does not exist')
    else:
        client.download_file(args.bucket, args.object, download_path)
        print('File downloaded: {}'.format(args.filepath))
    os.remove(download_path)

    # remove dir
    client.remove_file(args.bucket, args.object)
    if client.exists(args.bucket, args.object):
        print('Failed to remove object')
    else:
        print('Object removed: {}'.format(args.object))


if __name__ == '__main__':
    main()
