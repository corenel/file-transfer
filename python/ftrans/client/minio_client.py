from ftrans.client.base import BaseClient
from minio import Minio


class MinioClient(BaseClient):

    def __init__(self, config, secure=False):
        """
        MinIO Client

        :param config: client config
        :type config: BaseConfig
        :param secure: Flag to indicate to use secure (TLS) connection to S3 service or not. Defaults to False
        :type secure: bool, optional
        """
        self.config = config
        self.secure = secure
        self.client = None
        self.connect()

    def connect(self):
        self.client = Minio('{}:{}'.format(self.config.host_addr,
                                           self.config.host_port),
                            access_key=self.config.access_key,
                            secret_key=self.config.secret_key,
                            secure=self.secure)

    def disconnect(self):
        del self.client
        self.client = None

    def create_dir(self, remote_dir):
        found = self.client.bucket_exists(remote_dir)
        if not found:
            self.client.make_bucket(remote_dir)
        else:
            print("Bucket '{}' already exists".format(remote_dir))

    def list_dir(self, remote_dir):
        objects = self.client.list_objects(bucket_name=remote_dir,)
        return objects

    def upload_file(self,
                    local_filepath,
                    remote_dir,
                    remote_filename,
                    metadata=None):
        result = self.client.fput_object(remote_dir,
                                         remote_filename,
                                         local_filepath,
                                         metadata=metadata)
        return result

    def download_file(self, remote_dir, remote_filename, local_filepath):
        response = self.client.fget_object(remote_dir, remote_filename,
                                           local_filepath)
        return response

    def remove_file(self, remote_dir, remote_filename):
        self.client.remove_object(remote_dir, remote_filename)

    def exists_dir(self, remote_dir):
        return self.client.bucket_exists(remote_dir)

    def exists(self, remote_dir, remote_filename):
        try:
            return self.client.bucket_exists(remote_dir) and \
                self.client.stat_object(remote_dir, remote_filename)
        except Exception as e:
            return False
