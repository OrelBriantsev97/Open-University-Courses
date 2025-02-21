import threading
import logging
from protocol import *
from database import Database 
from aes import *
import sys

FAILED_REGISTER = 0
SUCCESS_REGISTER_PAYLOAD_SIZE = 255
class Connection:
      
    def __init__(self,cSocket,database):
        self.__client=cSocket
        self.__db=database
        self.__logger = logging.getLogger("Connection")

    def start(self):
        # Start a new thread for handling requests
        threading.Thread(target=self.handle_request).start()

    def handle_request(self):
        while True:
            try:
                request_header =get_req_header(self.__client)
                request_header_type=ClientRequestCode(request_header.code)
                request_payload=get_req_payload(self.__client,request_header_type)
                
                if request_header_type == ClientRequestCode.Register :
                    self.__db.registerClient(request_header,request_payload)
                    if  self.__db._success == True :
                        response = SuccessfulRegister(request_header.client_id)
                        res_header_bytes=encode_header(response)
                        res_payload_bytes=encode_payload(response)

                        self.__client.send(res_header_bytes)
                        self.__client.send(res_payload_bytes)
                    
                    else :
                        response = FailedRegister()
                        res_bytes=encode_header(response)
                        self.__client.send(res_bytes)

                if request_header_type ==ClientRequestCode.SendPublicKey:
                    self.__logger.debug(f"Generating key for user {request_header.client_id}.")
                    aes_key= create_AES()
                    self.__db.save_key(request_header.client_id,request_payload.public_key, aes_key)
                    enc_AES=encrypt_AES(request_payload.public_key,aes_key)
                    response = SendAES(request_header.client_id,enc_AES)
                    res_header_bytes=encode_header(response)
                    self.__client.send(res_header_bytes)
                    self.__client.send(response.client_id)
                    self.__client.send(response.key)
                #nned to create replay object with the encrypted data and send to client to recive 
            except Exception as e:
            # Handle exceptions, e.g., client disconnects
                self.__logger.error(f"Error handling requests: {e}")
                self.__client.close()
                break

        

        
