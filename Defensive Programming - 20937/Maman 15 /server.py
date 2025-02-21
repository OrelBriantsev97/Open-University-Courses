import socket
from connection import Connection
from database import Database
import logging


class Server:
    PORT_FILE = "port.info"
    HOST='127.0.0.1'
    DEFAULT_PORT=1357

    def __init__(self):
        self.__port=self.getPort()
        self.__logger = logging.getLogger("Server")

    def getPort(self):
       try:
          with open(Server.PORT_FILE,"r") as pfile:
            port=int(pfile.read())
            return port

       except:
         self.__logger.error(f"port.info file is not available, using default port {Server.DEFAULT_PORT}")
         return Server.DEFAULT_PORT
       
    def connect(self):
      db=Database()
      with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
         s.bind((Server.HOST,self.__port))
         s.listen()
         self.__logger.info(f"Server listen on {Server.HOST}:{self.__port}")
         cSocket, addr = s.accept()
        #need to add clasff that represent threads - sessions
         with cSocket:
            self.__logger.info('Connected by', addr)
            Connection(cSocket, db).handle_request()
               


