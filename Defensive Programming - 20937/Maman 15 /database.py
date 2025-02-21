import sqlite3
from datetime import datetime
from uuid import UUID
import uuid
import logging
from threading import local


class DBClient:
    def __init__(self, cid, name):
        self.id = cid
        self.name = name
        self.public_key = None
        self.last_seen = datetime.now()
        self.AES_key = None
 

class Database:
    DB_NAME = 'defensive.db'

    # Modify the column type to BLOB
    CREATE_USERS_TABLE = """
        CREATE TABLE IF NOT EXISTS clients(
            ID BLOB PRIMARY KEY,
            Name TEXT,
            PublicKey BLOB,
            LastSeen DATETIME,
            AESKey BLOB
         
        );
    """

    CREATE_FILES_TABLE = """
        CREATE TABLE IF NOT EXISTS files(
            ID blob PRIMARY KEY,
            FileName VARCHAR(256),
            PathName VARCHAR(256),
            Verified BOOLEAN
        );
    """

    ## add load data option from server

    def __init__(self):
        self._thread_local = local()
       # self.db_conn = sqlite3.connect(Database.DB_NAME)
        #self.db_conn.text_factory = bytes
        self.__logger = logging.getLogger("Database")
        self._success = False

        self._create_tables()

    def _create_tables(self):
        with self._get_db_conn() as conn:
            conn.execute(Database.CREATE_USERS_TABLE)
            conn.execute(Database.CREATE_FILES_TABLE)

    def _get_db_conn(self):
        if not hasattr(self._thread_local, 'db_conn') or not self._thread_local.db_conn:
            self._thread_local.db_conn = sqlite3.connect(Database.DB_NAME)
            self._thread_local.db_conn.text_factory = bytes
        return self._thread_local.db_conn

    def registerClient(self, header, payload):
        new_client = DBClient(header.client_id, payload.name)
        with self._get_db_conn() as conn:
            cursor= conn.cursor()
            cursor.execute("INSERT INTO clients (ID, Name, LastSeen) VALUES (?,?,?)", (new_client.id,new_client.name,new_client.last_seen))
            cursor.close()
            conn.commit()
        self.__logger.info("User {} successfuly registered to DataBase.".format(payload.name))
        self._success = True


    def save_key(self,client_id,public_key,aes_key):
        with self._get_db_conn() as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT * FROM clients WHERE ID = ?", (client_id,))

            result = cursor.fetchone()

            if result:
                cursor.execute("UPDATE clients SET PublicKey = ? ,AESKey = ?, LastSeen = ? WHERE ID = ?",(public_key,aes_key,datetime.now(),client_id ))
               
            else:
                self.__logger.error("Client ID {} does not exist in the table.".format(client_id.bytes))

            cursor.close()
            conn.commit()
        
     
