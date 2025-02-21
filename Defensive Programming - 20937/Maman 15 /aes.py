from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
import logging

AES_BYTES = 16

def create_AES():
    aes_key = get_random_bytes(AES_BYTES)

    return aes_key


def encrypt_AES(publickey: bytes, short_data: bytes) -> bytes:
    
    """ Encrypts short data using RSA with the provided public key. """
    loaded_key = RSA.importKey(publickey)
    return PKCS1_OAEP.new(loaded_key).encrypt(short_data)
