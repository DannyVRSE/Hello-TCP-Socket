# Simplex-Talk: TCP Client-Server Application

## Overview

This repository contains a simple TCP client-server application written in C. The server listens for incoming connections and prints received messages to the console. The client connects to the server, sends messages entered by the user, and terminates when the input ends.

### Files

1. **Server (`server.c`)**: A TCP server that listens for client connections on a specified port and prints received messages.
2. **Client (`client.c`)**: A TCP client that connects to the server, sends user input to the server, and terminates when the input ends.

## Prerequisites

- A C compiler (e.g., `gcc`)
- Basic knowledge of TCP/IP and socket programming

## Compilation

To compile the server and client programs, use the following commands:

```bash
gcc -o server server.c
gcc -o client client.c
