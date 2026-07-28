# C++ Networked Tic-Tac-Toe (TCP / Winsock)

A multi-threaded, client-server implementation of the classic Tic-Tac-Toe game written in C++ for Windows. The game supports two players playing over a local network or on the same machine using Windows Sockets (`Winsock2`) and C++ multithreading.

This project was built as a personal learning experience to understand network programming, multi-client synchronization, and low-level C++ socket concepts.

---

## Key Features

* **Client-Server Architecture:** Separates game state logic (Server) from the user interface/input (Client).
* **TCP Winsock Communication:** Uses reliable stream sockets (`Winsock2`) for real-time packet exchange between the server and connected clients.
* **Multithreaded Server:** Handles client connections and game requests concurrently using `std::thread` without blocking the main process loop.
* **2-Player Online Matchmaking:** Automatically pairs two connected clients into an active Tic-Tac-Toe session.

---

## Technical Highlights & Concepts Learned

* **Socket API:** Socket creation, binding, listening, accepting incoming connections, and sending/receiving byte buffers (`send` / `recv`).
* **Concurrency & Synchronization:** Thread management for each client, preventing race conditions when modifying the shared board state.
* **Game State Management:** Validating turns, evaluating win/draw conditions on the server side, and broadcasting updated states back to clients.

---

## Build & Run Instructions

### 1. Build the Solution

1. Open `TicTacToeCPP.sln` in **Visual Studio**.
2. Set the configuration to **x64 | Debug** (or **Release**).
3. Build the entire solution (**Ctrl + Shift + B**).

---

### 2. Run the Demonstration

Open **three** separate Command Prompt (`cmd.exe`) windows.

#### Step 1: Navigate to the Build Directory

In each terminal window, change directory to where the compiled `.exe` files are located:

```cmd
cd /d E:\Users\notkh\source\repos\TicTacToeCPP\TicTacToe\x64\Debug

```

#### Step 2: Start the Server

In the **first** terminal window, start the server application:

```cmd
TicTacToeServer.exe

```

*The server will start listening for incoming client connections.*

#### Step 3: Start Player 1 Client

In the **second** terminal window, launch the first client:

```cmd
TicTacToeClient.exe

```

#### Step 4: Start Player 2 Client

In the **third** terminal window, launch the second client:

```cmd
TicTacToeClient.exe

```

Once both clients connect, the server will assign player symbols (`X` and `O`) and the game match will begin.

---

## How It Works

```text
       +------------------+
       | TicTacToeServer  |
       |  (Host / Board)  |
       +--------+---------+
                |
     +----------+----------+
     |                     |
     | (TCP Socket 1)      | (TCP Socket 2)
     v                     v
+----+-----------+    +----+-----------+
| Client 1 (X)   |    | Client 2 (O)   |
+----------------+    +----------------+

```

1. **Initialization:** The Server initializes Winsock (`WSAStartup`) and listens on a dedicated TCP port.
2. **Connection Handling:** Each incoming connection spawns a new worker thread to listen for player input.
3. **Turn Logic:** The Server prompts the active player for input, validates the move, updates the global board, and broadcasts the updated state to both players.
4. **Game End:** Upon detecting a win or tie, the Server sends the final game result to both clients and terminates or resets the session.

## Example
### Example 1

<img width="1199" height="1872" alt="image" src="https://github.com/user-attachments/assets/2b791153-229e-4e77-a16e-478c20e0adfe" />

### Example 2

<img width="1199" height="1868" alt="image" src="https://github.com/user-attachments/assets/2968562a-873e-4770-bc8a-a3f9c472f9bf" />


