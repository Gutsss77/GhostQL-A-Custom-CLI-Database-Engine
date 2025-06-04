# GhostQL

A custom CLI database inspired by the MySQL command-line interface!

---

## Database Functions

### 1. Creating a Database

GhostQL uses a simple folder-based mechanism to represent databases because it is easy to understand and implement.

Using the command:

```bash
CREATE DATABASE <name>;
```
GhostQL will:

Create a folder named Databases if it does not already exist.
Inside the Databases folder, it will create a new folder with the specified database name <name>.
All user-created databases are stored as separate folders inside the Databases directory, each named according to the user’s input.
