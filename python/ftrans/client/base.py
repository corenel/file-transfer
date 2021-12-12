class ClientConfig:

    def __init__(self, host_addr, host_port, access_key, secret_key):
        """
        Config for base client connection

        :param host_addr: host address
        :type host_addr: str
        :param host_port: host port
        :type host_port: int
        :param access_key: access key
        :type access_key: str
        :param secret_key: secret key
        :type secret_key: str
        """
        self.host_addr = host_addr
        self.host_port = host_port
        self.access_key = access_key
        self.secret_key = secret_key


class BaseClient(object):

    def __init__(self, config):
        """
        Base client class

        :param config: config for base client connection
        :type config: ClientConfig
        """
        self.config = config

    def connect(self):
        raise NotImplementedError

    def disconnect(self):
        raise NotImplementedError

    def create_dir(self, remote_dir):
        raise NotImplementedError

    def list_dir(self, remote_dir):
        raise NotImplementedError

    def upload_file(self, local_filepath, remote_dir, remote_filename):
        raise NotImplementedError

    def download_file(self, remote_dir, remote_filename, local_filepath):
        raise NotImplementedError

    def remove_file(self, remote_dir, remote_filename):
        raise NotImplementedError

    def exists_dir(self, remote_dir):
        raise NotImplementedError

    def exists(self, remote_dir, remote_filename):
        raise NotImplementedError
