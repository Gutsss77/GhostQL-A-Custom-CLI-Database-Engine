# GhostQL

A custom CLI database inspired by the MySQL command-line interface!

---

## Database Functions

### 1. Creating a Database
GhostQL uses a simple folder-based mechanism to represent databases because it is easy to understand and implement.

Use the command to create database:
```bash
CREATE DATABASE <name>
```
Create a folder named Databases if it does not exist (Note : Folder creates in **root** directory).
Inside the Databases folder, it will create a new folder with the specified database name <name>.
All user-created databases are stored as separate folders inside the Databases directory, each named according to the user’s input.

### 3. Use Command
As in MySQL the **USE** command makes a database active for performing operations, just like that the use command do the same thing.

Using the **USE** command:
```bash
USE <databaseName>
```
Use this command to set a database active for performing operation on it.
It uses SessionContext to manage active Database and root directory for it.

### 2. Creating Tables
GhostQL uses a simpe meachism of creating schemas defination in a metadata folder for users database.
I will going to use JSON for metadata handling and table data.
Struture defined as:
```bash
Databases
  └── user/                   ← database folder
      ├── metadata/           ← table definitions (schemas)
      │   └── table_name.meta
      └── data/               ← actual table data
          └── table_name.data
```
Using a new header file to handle json for metadata, included **json.hpp** in the libs folder. 
You can found that library officially at **https://github.com/nlohmann/json/releases** 
