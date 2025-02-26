# Encrypted File Transfer System

This project implements a client-server application that allows clients to securely transfer files from their computers to a server. The server is written in Python (version 3.11.4), and the client is written in C++ and will be tested using Visual Studio 2022.

---

## Architecture

The system uses a client-server architecture where:
- The client initiates the connection with the server.
- The client exchanges encryption keys with the server.
- The client then securely transfers the requested file.
- The client verifies the file integrity using checksum validation.
- In case of checksum mismatch, the client retries the transfer up to 3 times.

---

## Server

### General
- **Language:** Python (version 3.11.4)
- **Concurrency:** Supports multiple users using threads or selector.
- **Encryption Library:** Uses `Crypto.Cipher` from the `pycryptodome` package.
- **Version:** 3 (appears in server communication messages)

### Port Configuration
- The server reads the port number from a text file named `info.port` located in the same directory as the server code.
- If the file is not found, the server uses the default port **1357**.
- Example content of `info.port`:
    ```
    1234
    ```

### Data Storage
- The server maintains client data and received files in **RAM**.
- It also uses an **SQLite** database to:
  - Store the list of registered users, encryption keys, and received files.
  - Persist data across server restarts.
- The database is stored in a file named `defensive.db`.
- It also keeps a local folder with the files received from clients.

### Database Structure

#### Table: `clients`
| Field       | Type        | Description                                    |
|-------------|-------------|------------------------------------------------|
| `ID`        | 16 bytes    | Unique identifier for each client               |
| `Name`      | String(255) | ASCII username (null-terminated)                |
| `PublicKey` | 160 bytes   | Client's public key                            |
| `LastSeen`  | DateTime    | Timestamp of the last request from the client   |
| `AES Key`   | 128 bits    | AES key sent to the client                      |

#### Table: `files`
| Field       | Type        | Description                                    |
|-------------|-------------|------------------------------------------------|
| `ID`        | 16 bytes    | Unique identifier for each client               |
| `Name File` | String(255) | Filename as sent by the client (null-terminated)|
| `Name Path` | String(255) | Relative path of the stored file (null-terminated)|
| `Verified`  | Boolean     | Whether the checksum matched                    |

---

## Client

### General
- **Language:** C++
- **Compiler:** Visual Studio 2022
- **Encryption Library:** Uses `CryptoPP`
- **Version:** 3
- **Mode:** Can operate in batch mode for automation.

### Configuration File
- **Filename:** `info.transfer`
- **Location:** Same directory as the executable file.
- **Content Structure:**
    ```
    <IP Address>:<Port>
    <Client Name>
    <Path to File>
    ```
- **Example:**
    ```
    127.0.0.1:1234
    Michael Jackson
    New_product_spec.docx
    ```

### Unique ID and Name
- **Filename:** `info.me`
- **Location:** Same directory as the executable file.
- **Content Structure:**
    ```
    <Client Name>
    <Unique ID in Hex (ASCII)>
    <Private Key (Base64)>
    ```
- **Example:**
    ```
    Michael Jackson
    64f3f63985f04beb81a0e43321880182
    MIGdMA0GCSqGSIb3DQEBA...
    ```

---

## Communication Protocol

### General
- **Type:** Binary over TCP
- **Endianness:** Little-endian
- **Structure:**
  - Header:
    - `Client ID` (16 bytes)
    - `Version` (1 byte)
    - `Request Code` (2 bytes)
    - `Payload Size` (4 bytes)
  - Payload:
    - Varies depending on request type.

### Request Codes
- `1025`: Registration
- `1026`: Public Key Exchange
- `1027`: Reconnection
- `1028`: File Transfer
- `1029`: CRC Valid
- `1030`: CRC Invalid, Resend
- `1031`: CRC Invalid, Abort

### Response Codes
- `2100`: Registration Success
- `2101`: Registration Failed
- `2102`: Public Key Received, AES Sent
- `2103`: File Received with Valid CRC
- `2104`: Acknowledgement
- `2105`: Reconnection Success, AES Sent
- `2106`: Reconnection Failed
- `2107`: General Server Error

---

## Encryption

### Symmetric Encryption
- **Algorithm:** AES (CBC Mode)
- **Key Length:** 128 bits
- **Initialization Vector (IV):** Zeroed (All bytes are zero)

### Asymmetric Encryption
- **Algorithm:** RSA
- **Key Length:** 1024 bits
- **Library:**
  - Server: `pycryptodome` in Python
  - Client: `CryptoPP` in C++

---

## File Verification and Retry Mechanism

- The client verifies the file integrity using **CRC (Checksum)**.
- If the CRC does not match:
  - The client retries the transfer up to **3 times**.
  - If it fails after 3 attempts, the client exits with a detailed fatal error message.

---

## Dependencies

### Server
- **Python 3.11.4**
- **Packages:**
  - `pycryptodome` for encryption
  - `sqlite3` for database management

### Client
- **C++ Compiler:** Visual Studio 2022
- **Library:** `CryptoPP`

---

## Installation and Execution

### Server
1. Install the required Python packages:
    ```sh
    pip install pycryptodome
    ```
2. Place the `info.port` file in the same directory as the server code.
3. Run the server:
    ```sh
    python server.py
    ```

### Client
1. Compile the C++ client using Visual Studio 2022.
2. Place `info.transfer` and `info.me` files in the executable's directory.
3. Run the client executable.

---

## Error Handling

- On any server error, the client prints:
    ```
    error an with responded server
    ```
- The client retries the request up to **3 times** before exiting with a fatal error message.

---

## Security Considerations

- **AES CBC Mode** is used for symmetric encryption. Although the IV is zeroed for simplicity, it is recommended to use a random IV in a real-world application.
- **RSA (1024 bits)** is used for asymmetric encryption. For stronger security, consider using 2048-bit keys or higher.

---



