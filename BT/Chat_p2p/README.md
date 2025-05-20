# Chat P2P Application

## Project Description

A simple peer-to-peer (P2P) chat application running on Linux. It allows multiple nodes to connect directly via TCP sockets to exchange messages without a central server.

---

## Features

- User-friendly command-line interface (CLI).
- Display the local IP address and listening port.
- Connect to other peers using IP and port.
- List all active connections.
- Send messages directly to a peer by connection ID.
- Terminate connections by ID.
- Support basic commands: `help`, `myip`, `myport`, `connect`, `list`, `send`, `terminate`, `exit`.
- Multithreaded: server runs concurrently with CLI interface.

---

## Project Structure

- `cli.c`: Handles CLI input, command parsing, and execution.
- `network.c`: Manages network connections, TCP listening, sending, and receiving.
- `peer_manager.c`: Manages peer list, connection info

---

## Environment Requirements

- Operating System: Linux
- Compiler: GCC
- Libraries: POSIX sockets (available on Linux)

---

## Install project

```bash
make


