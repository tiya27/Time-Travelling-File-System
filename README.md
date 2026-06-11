# Time Travel File System

---

# Overview

Time Travel File System (TTFS) is a simplified in-memory version control system inspired by Git.

The system supports:

* file versioning
* snapshot management
* rollback operations
* branching histories
* historical inspection
* system-wide analytics

The project was developed as part of **COL106: Data Structures and Algorithms**.

---

# Core Data Structures Used

The implementation is built entirely using custom implementations of:

* Trees
* HashMaps
* Heaps

No STL implementations of these structures were used for the core system logic.

---

# Repository Structure

```text id="r5j90g"
.
├── main.cpp
├── compile.bat
├── compile.sh
└── README.md
```

---

# Features

## File Operations

* CREATE
* READ
* INSERT
* UPDATE
* SNAPSHOT
* ROLLBACK
* HISTORY

---

## System Analytics

* RECENT FILES
* BIGGEST TREES

---

# Versioning Model

Each file maintains a version tree where:

* every node represents a version
* snapshots are immutable
* rollback enables time travel
* branching histories are preserved

---

# Supported Commands

### Create File

```text id="ym9n2w"
CREATE <filename>
```

Creates a file with an initial root version.

---

### Read File

```text id="0plq7g"
READ <filename>
```

Displays the content of the active version.

---

### Insert Content

```text id="vb9ewr"
INSERT <filename> <content>
```

Appends content to the active version.

---

### Update Content

```text id="jex1f6"
UPDATE <filename> <content>
```

Replaces the current file content.

---

### Snapshot

```text id="u5h1lt"
SNAPSHOT <filename> <message>
```

Creates an immutable snapshot.

---

### Rollback

```text id="jlwm90"
ROLLBACK <filename> [versionID]
```

Moves the active version pointer backward in history.

---

### History

```text id="jlwm91"
HISTORY <filename>
```

Displays snapshot history from root to active node.

---

### Recent Files

```text id="jlwm92"
RECENT <num>
```

Lists files ordered by most recent modification time.

---

### Biggest Trees

```text id="jlwm93"
BIGGEST <num>
```

Lists files with the highest number of versions.

---

### Exit

```text id="jlwm94"
EXIT
```

Gracefully terminates the program.

---

# Compilation Instructions

## Windows

Use:

```bash id="jlwm95"
compile.bat
```

### Requirements

* Windows OS
* g++ compiler installed and configured in PATH

After successful compilation:

```text id="jlwm96"
Compilation successful. Run ttfs.exe to start.
```

Run using:

```bash id="jlwm97"
ttfs.exe
```

---

## Linux / Mac

Use:

```bash id="jlwm98"
chmod +x compile.sh
./compile.sh
```

After successful compilation:

```text id="jlwm99"
Compilation successful. Run ./ttfs to start.
```

Run using:

```bash id="jlwm100"
./ttfs
```

---

# Example Workflow

```text id="jlwm101"
CREATE notes
INSERT notes hello
SNAPSHOT notes initial_version
INSERT notes world
HISTORY notes
ROLLBACK notes 1
READ notes
EXIT
```

---

# Design Highlights

* Efficient version lookup using HashMaps
* Hierarchical version tracking using Trees
* Analytics support using Heaps
* Snapshot immutability semantics
* Time-travel rollback support
* Dynamic active-version management

---

# Error Handling

The program safely handles:

* invalid commands
* malformed inputs
* missing files
* invalid rollback operations
* incorrect version IDs
* inconsistent command structures

---

# Key Semantics

* Only snapshotted versions are immutable
* Version IDs are unique per file
* Versions are assigned sequentially
* Active versions can branch from historical states

---

# Technologies Used

| Category    | Tools                       |
| ----------- | --------------------------- |
| Language    | C++                         |
| Concepts    | Trees, HashMaps, Heaps      |
| Environment | GCC / Shell Scripts         |
| Paradigm    | Object-Oriented Programming |

---

# Future Improvements

* Persistent file storage
* Diff visualization
* Merge conflict handling
* Multi-user collaboration
* Disk-backed snapshots
* GUI-based version explorer

---

# Author

Tiya Mittal
