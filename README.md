
# Calculator Application with Network Logging in C

# Overview
This project is a simple client-server calculator application written in C. It allows clients to connect to a server over a network, send arithmetic expressions for computation, and receive the results. The server processes the expressions, handles invalid inputs, supports basic arithmetic operations (addition, subtraction, multiplication, division), and also includes extended operations like exponentiation (^) and modulus (%). Both the client and server log all activities, including data transfer sizes and processing times.
  

# Features
  ## Client Application
- Send Arithmetic Expressions: Users can input arithmetic expressions (e.g., 5 + 3, 2 ^ 3) and send them to the server for computation.
- Receive and Display Results: The client receives the result from the server and displays it to the user.
- Input Validation: Ensures that only valid arithmetic expressions are sent to the server.
- Logging: All sent requests and received responses are logged with timestamps, the type of operation, and the result.

## Server Application
- Receive and Process Requests: The server listens for client connections, processes arithmetic expressions, and returns results.
- Handle Multiple Clients: The server can handle multiple client connections simultaneously.
- Error Handling: The server returns appropriate error messages for invalid expressions, operators, or division/modulus by zero.
- Extended Operations: Supports additional operations like exponentiation (^) and modulus (%).
- Advanced Logging: Logs include the client IP address, the received expression, the computed result, the size of the data transferred, and the time taken to process each request.

# Getting Started
## Prerequisites
  - Ubuntu Software
  - GCC C Compiler

## Compilation and Execution
### Server
- #### Compile the Server:
      gcc server.c -o server    
- #### Run the Server:
      ./server

### Client
- #### Compile the Client:
       gcc client.c -o client      
- #### Run the Client:
      ./client

## Example Usage
 - Client Input: 5 + 3
   
   Server Output: 8
   
- Client Input: 2 ^ 3

  Server Output: 8

## Log Files
- Client Logs: client_log.txt
- Server Logs: server_log.txt

## Sample Log Entry (Server)

Thu Aug 22 00:12:15 2024
 Client: 127.0.0.1, Expression: 2 + 3
, Result: 5, Time Taken: 6.154591 seconds, Data Size: 1 bytes

## Sample Log Entry (Client)

Thu Aug 22 00:12:15 2024
 Operation: 2 + 3
, Result: 5

## Challenges Faced
- Ensuring that only valid expressions are processed by the server required careful handling of edge cases, such as division by zero.
- Balancing detailed logging with performance was challenging, especially when logging time-sensitive operations.
