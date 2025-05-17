# Interplanetary File System (IPFS) with Ring Distributed Hash Table

## Project Overview

This project is a C++ implementation of a simplified Interplanetary File System (IPFS), developed as a semester project. The system emulates a distributed file-sharing network inspired by BitTorrent, focusing on efficient file storage and retrieval across a simulated network of machines. It leverages a **Ring Distributed Hash Table (DHT)** to manage data distribution and employs **B-trees** for indexing keys on each machine. The implementation supports dynamic machine management, hash-based file addressing, and a user-friendly command-line interface, showcasing advanced data structure usage and distributed system concepts.

The project simulates a distributed environment on a single machine, where files are represented as key-value pairs. Keys are hashes of file content, and values are stored in memory (as integers for simplicity). The Ring DHT organizes machines in a circular identifier space, and routing tables optimize search operations to O(log N) complexity, where N is the number of machines. This implementation demonstrates proficiency in C++, linked lists, B-trees, and distributed system principles.

## Features

- **Configurable Identifier Space**: Users can specify the size of the identifier space (4 to 160 bits), determining the range of possible keys (e.g., 4 bits allow 16 keys).
- **Flexible Machine Configuration**: Supports manual or random assignment of machine IDs, with dynamic addition of new machines during runtime.
- **Efficient File Management**: Enables insertion and deletion of key-value pairs, with automatic routing to the correct machine based on hash values.
- **B-Tree Indexing**: Each machine uses a B-tree to index keys (hashes), supporting efficient search and storage of key-value pairs, even for duplicate hashes.
- **Optimized Search with Routing Tables**: Implements routing tables with shortcuts to distant nodes, reducing search complexity to O(log N).
- **Path Tracing**: Displays the complete path taken by search, insertion, and deletion requests across the network, aiding in understanding the DHT's operation.
- **Interactive Interface**: Offers a menu-driven interface for configuring the system, managing files, and inspecting routing tables or B-trees.
- **Dynamic Updates**: Adjusts ID ranges and routing tables when new machines are added, ensuring seamless integration without disrupting functionality.

## Technical Background

The project is based on the IPFS model, where files are content-addressable using hashes. Unlike traditional file systems that rely on filenames, IPFS uses the hash of a file's content as its key, ensuring unique identification. The Ring DHT organizes machines in a circular identifier space, where each machine is responsible for a range of keys. For example, a machine with ID 12 might store keys from 8 to 12, as it is the successor of those keys (i.e., the smallest ID ≥ key).

The **routing table** for each machine contains pointers to other machines at exponentially increasing distances (e.g., succ(p + 2^(i-1))), enabling logarithmic-time searches. **B-trees** are used to index keys on each machine, with key-value pairs stored as linked lists to handle multiple values per hash. The system supports dynamic changes, such as adding new machines, by redistributing key ranges and updating routing tables.

## Prerequisites

To compile and run this project, ensure you have the following:

- **Compiler**: A C++ compiler supporting C++11 or later (e.g., g++, Visual Studio 2019, or clang++).
- **Operating System**: Developed and tested on Windows; compatible with Linux/macOS with minor adjustments (e.g., input/output handling).
- **Dependencies**: Uses standard C++ libraries:
  - `iostream` for input/output.
  - `cmath` for mathematical operations (e.g., `pow` for identifier space calculation).
  - `cstdlib` and `ctime` for random ID generation.
- **Development Environment**: Visual Studio 2019 is recommended for Windows users due to project configuration. For other platforms, a simple Makefile or command-line compilation suffices.

## Installation

Follow these steps to set up and run the project:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/salmansaleem08/ipfs-ring-dht.git
   cd ipfs-ring-dht
   ```

2. **Compile the Code**:
   - **Windows (Visual Studio 2019)**:
     - Open the project folder in Visual Studio.
     - Select `Build > Build Solution` (or press `Ctrl+Shift+B`).
     - Ensure the configuration is set to `Debug` or `Release` for x86/x64.
   - **Linux/macOS (g++)**:
     ```bash
     g++ -o ipfs main.cpp -std=c++11
     ```
     Note: Ensure all header files (`Header.h`, `functions.h`, `BTree.h`) are in the same directory.

3. **Run the Executable**:
   - Windows: Run the generated `.exe` from the `Debug` or `Release` folder, or use Visual Studio (`F5`).
   - Linux/macOS:
     ```bash
     ./ipfs
     ```

4. **Verify Setup**:
   The program should prompt you to enter the number of bits for the identifier space, confirming successful compilation.

## Usage

The project provides an interactive command-line interface. Below is a step-by-step guide to using the system, with an example workflow.

### 1. Launch the Program
Run the executable. The program starts by requesting:
- **Number of Bits**: Enter the size of the identifier space in bits (4–160). For example, 4 bits create a space of 2^4 = 16 keys.
- **Number of Machines**: Specify how many machines to simulate (must be ≤ total keys).

### 2. Configure the System
- **Machine ID Assignment**:
  - Choose `1` to manually assign IDs (e.g., 2, 7, 12).
  - Choose `2` for random ID assignment, ensuring unique IDs within the identifier space.
- **B-Tree Order**:
  - Choose `1` to set the same B-tree order for all machines (e.g., order 5).
  - Choose `2` to specify different orders for each machine (e.g., 3, 5, 4).
- The system sorts machine IDs in ascending order and initializes the Ring DHT, displaying the ring structure (IDs, key ranges, and B-tree orders).

### 3. Interact via Menu
After setup, a menu appears with the following options:
1. **Insert File in Form of Key-Value Pair**:
   - Select a machine ID to initiate the insertion.
   - Enter a key (e.g., 100) and value (e.g., 500).
   - The system computes a hash (`key % totalKeys`), routes the request to the correct machine, and inserts the pair into its B-tree.
   - Outputs the path taken (e.g., Machine 2 → Machine 7 → Machine 12) and the updated B-tree.
2. **Delete File Using Key**:
   - Select a machine ID and enter the key to delete.
   - The system routes to the target machine, removes the key-value pair, and shows the path and updated B-tree.
3. **Print Routing Table**:
   - Select a machine ID to display its routing table, showing indices and corresponding machine IDs.
4. **Add New Machine**:
   - Enter a new machine ID and B-tree order.
   - The system inserts the machine into the ring, updates key ranges and routing tables, and maintains system integrity.

### 4. Viewing B-Tree Details
After insertion or deletion, you can opt to view a specific B-tree node in depth by entering its hash value, displaying all associated keys and values.

## File Structure

The project is organized as follows:

```
ipfs-ring-dht/
├── main.cpp              # Main program, handles user input and system initialization
├── Header.h             # Defines RingDht class, MachineNode, RoutingTable, and Machine structures
├── functions.h          # Utility functions for ID assignment, B-tree configuration, and menu operations
├── BTree.h              # B-tree implementation for key-value pair storage and management
├── README.md            # This documentation file
```

### File Descriptions
- **main.cpp**: Orchestrates the program flow, including system setup, menu display, and user interaction. It initializes the RingDht object and calls utility functions.
- **Header.h**: Contains the core RingDht class, which manages the circular linked list of machines, routing tables, and B-tree operations. Defines structures like `Machine`, `MachineNode`, and `RoutingTable`.
- **functions.h**: Provides helper functions for:
  - Assigning machine IDs (`MachineArrayIdAssigner`).
  - Configuring B-tree orders (`BTreeMenuDisplay`).
  - Handling file insertion (`insertFileinFormofKeyValuePair`), deletion (`deleteFileFromKeys`), routing table display (`PrintRoutingTable`), and machine addition (`OptionToAddnewMachine`).
- **BTree.h**: Implements the B-tree data structure, including node management, insertion, deletion, and printing. Supports key-value pairs with linked lists for duplicate hashes.
- **FinalProject_final.pdf**: The project specification, outlining requirements and IPFS/DHT concepts.

## Implementation Details

### Ring DHT
- **Structure**: A circular singly linked list of `MachineNode` objects, each containing:
  - A `Machine` struct with an ID and number of associated keys.
  - A `RoutingTable` with arrays for indices and machine IDs.
  - A `BTree` object for key indexing.
  - Pointers to the next machine and routing table entries.
- **Key Assignment**: Each machine is responsible for keys where the machine's ID is the successor (smallest ID ≥ key). Key ranges are updated dynamically when machines are added.

### Routing Table
- **Design**: Each machine maintains a routing table with O(log N) entries, where entry `i` points to `succ(p + 2^(i-1))`, and `p` is the machine's ID.
- **Search Algorithm**: For a key `e` at machine `p`:
  - If `p = e`, the file is local; search the B-tree.
  - If `p < e ≤ FT[1]`, forward to the first routing table entry.
  - If `FT[j] < e ≤ FT[j+1]`, forward to entry `j`.
  - Uses modulo for circularity (e.g., `e % totalKeys`).
- **Complexity**: Achieves O(log N) lookups by halving the search space with each hop.

### B-Tree
- **Structure**: Each node stores keys (hashes) and pointers to key-value pairs (`KeyValuePairNode`). Supports duplicate hashes via linked lists.
- **Operations**:
  - **Insertion**: Adds a key-value pair, splitting nodes if full, maintaining B-tree properties.
  - **Deletion**: Removes a key-value pair, rebalancing the tree if underflow occurs.
  - **Search**: Locates a hash and retrieves associated key-value pairs.
- **Order**: Configurable per machine, affecting the minimum and maximum keys per node.

### Hashing
- **Method**: Uses `key % totalKeys` to map keys to the identifier space, simulating SHA-1 for simplicity.
- **Collision Handling**: Multiple key-value pairs with the same hash are stored in a linked list within the B-tree node.

### Dynamic Machine Addition
- **Process**:
  - Insert the new machine at the correct position in the ring based on its ID.
  - Update key ranges using `SetnoOfKeysAssociated`.
  - Rebuild routing tables (`SetRoutingTable`, `PointRoutingPointers`) to reflect the new topology.
- **Impact**: Key ranges are subdivided between the new machine and its successor, ensuring data redistribution.

## Potential Improvements

- Implement SHA-1 hashing for realistic file addressing.
- Add file system storage for values, supporting actual text or media files.
- Enable machine removal with data redistribution to neighbors.
- Introduce network sockets for true distributed execution across multiple machines.
- Enhance error handling for invalid inputs or edge cases.
- Add data persistence using a database or file storage.

## Contributing

Contributions are encouraged to enhance functionality or address limitations. To contribute:

1. **Fork the Repository**:
   ```bash
   git clone https://github.com/salmansaleem08/ipfs-ring-dht.git
   ```
2. **Create a Feature Branch**:
   ```bash
   git checkout -b feature/your-feature
   ```
3. **Make Changes**: Implement your feature or fix, ensuring code style consistency (e.g., use spaces, comment functions).
4. **Test Thoroughly**: Verify your changes work with existing functionality.
5. **Commit Changes**:
   ```bash
   git commit -m "Add your feature or fix"
   ```
6. **Push to GitHub**:
   ```bash
   git push origin feature/your-feature
   ```
7. **Open a Pull Request**: Describe your changes, referencing any related issues.

Please include unit tests if adding new features and update documentation as needed.

## Acknowledgments

- **Course**: Developed for CS2001 Data Structures, Fall 2023, at the National University of Computer and Emerging Sciences, Islamabad Campus.
- **Inspiration**: Draws from IPFS and BitTorrent, simplifying distributed file-sharing concepts for educational purposes.
- **Guidance**: Thanks to the course instructors for providing the project specification and feedback.
