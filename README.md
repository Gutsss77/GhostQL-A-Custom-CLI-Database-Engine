# GhostQL

A custom CLI database inspired by the MySQL command-line interface!

---

## Database Functions

### 1. Creating a Database
GhostQL uses a simple folder-based mechanism to represent databases, making it easy to understand and implement.

To create a database, use the following command:
```bash
CREATE DATABASE <name>
```
-- This command will first ensure that a Databases directory exists in the root directory.
-- Inside the Databases folder, it will create a new subfolder with the specified database name <name>.
-- Each user-created database is stored as a separate folder inside the Databases directory.

### 2. Use Command
Just like MySQL, GhostQL provides a USE command to set the current working database.
```bash
USE <databaseName>
```
-- This command sets the specified database as the active one for subsequent operations.
-- It uses SessionContext to manage the active database and its root directory.

### 3. Creating Tables
GhostQL uses a straightforward approach for schema and data handling:

-- Table schemas are stored as .meta files in a metadata/ folder.
-- Table data is stored as .data files in a data/ folder.
-- Both folders reside within the selected database directory.

Directory structure:
```bash
Databases
  └── user/                   ← database folder
      ├── metadata/           ← table definitions (schemas)
      │   └── table_name.meta
      └── data/               ← actual table data
          └── table_name.data
```
-- JSON is used for storing both metadata and table data.
-- A header file (json.hpp) is used for JSON handling.
-- You can find the library at:
    **https://github.com/nlohmann/json/releases**

### 4. Show Command
GhostQL includes a SHOW command, similar to MySQL, for listing databases or tables.
Usage:
```bash
SHOW DATABASES
SHOW TABLES
```
-- SHOW DATABASES lists all databases in the root Databases/ directory.
-- SHOW TABLES lists all tables in the active database.
More features and commands will be added soon!