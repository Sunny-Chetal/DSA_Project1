# AVL Tree
---

A self balancing AVL Tree implementation in C++ that stores and manages student records by name and 8 digit UFID. The tree automatically rebalances after every insertion and deletion using single and double rotations to maintain O(log n) operations.

## Features
---

### Commands
---

All nine commands are read from stdin and dispatched to the tree:

`insert "NAME" UFID` — Insert a student record. Validates that the name contains only letters/spaces and the UFID is exactly 8 digits. Prints `successful` or `unsuccessful`

`remove UFID` — Remove the node with the given 8 digit UFID. Handles leaf, single child, and two child cases. Prints `successful` or `unsuccessful`

`search UFID` — Search by numeric UFID; prints the matching name, or `unsuccessful`

`search "NAME"` — Search by name; prints all matching UFIDs, or `unsuccessful`

`printInorder` — Print all names comma separated in sorted (inorder) order

`printPreorder` — Print all names comma separated in preorder

`printPostorder` — Print all names comma separated in postorder

`printLevelCount` — Print the height of the tree

`removeInorder N` — Remove the Nth node from the inorder traversal

### Balancing
---

After each insertion, the tree walks back up the affected ancestors and applies the appropriate rotation when a node's balance factor falls outside [−1, 1]

### Input Validation
---

- UFID must be exactly 8 numeric digits (validated with `std::regex`)
- Name must contain only letters and spaces
- Duplicate UFIDs are rejected before insertion
- Out-of-range `removeInorder` indices print `unsuccessful`

## Tech Stack
---

| | |
|---|---|
| Language | C++14 |
| Build system | CMake 3.22+ |
| Testing | [Catch2 v3.5.2](https://github.com/catchorg/Catch2) |
| Input parsing | `stringstream` + `std::quoted` |
| Tree traversal | Iterative with explicit `std::stack` (In/Pre/Post-order) |

---

## Getting Started
---

### Build with CMake (CLion / VS Code)
---

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

Run the `Main` executable and pipe in a command file:

```bash
./cmake-build-debug/Main < test-io/input-files/1.txt
```

### Build with g++ (command line)

```bash
g++ -std=c++14 -Werror -Wuninitialized -o build/test_io src/main.cpp
```

Run a test:

```bash
./build/test_io < test-io/input-files/1.txt
```

### Input Format
---

```
N
command1
command2
...
```

The first line is the number of commands. Each subsequent line is one command.

Example:

```
4
insert "Alice Smith" 12345678
insert "Bob Jones" 87654321
search 12345678
printInorder
```

Expected output:

```
successful
successful
Alice Smith
Alice Smith, Bob Jones
```

---

## Testing
---

### Catch2 Unit Tests
---

```bash
cmake --build cmake-build-debug --target Tests
./cmake-build-debug/Tests
```

The unit tests are written in [test/test.cpp](test/test.cpp) using Catch2. They cover:

| Test Case | What it checks |
|---|---|
| Unsuccessful Test | Rejects invalid UFID length, invalid name, remove/search on missing nodes |
| Balanced Insert | All four rotation cases (LL, RR, LR, RL) verified via preorder output |
| 100 Inserts | Random insertions stay sorted in inorder; 10 random removals stay correct |
| Removal Tests | Leaf removal, single-child removal, and two-child (inorder successor) removal |
| Edge Cases | Duplicate UFID rejection, printing an empty tree, `removeInorder` with negative N |
| Search Test | Search by UFID and by name both return true on existing records |
| PostOrder Test | Postorder traversal returns nodes in correct order after a rebalancing rotation |
