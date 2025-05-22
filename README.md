# Movies Stack and Queue in C

This program manages a list of movies (name and year) using a doubly linked stack and a sorted queue.

## Features

* Input movies from **keyboard** or **text file** (`name|year` format).
* Store movies in a **doubly linked stack**.
* Transfer movies to a **queue sorted by year (descending)**.
* Print stack (forward and backward) and queue.
* Proper memory management.

## Usage

1. Edit `databasePath` variable to set your file path (if needed).
2. Compile:

   ```bash
   gcc -o movies movies.c
   ```
3. Run:

   ```bash
   ./movies
   ```
4. Choose input source:
   `1` — Keyboard
   `2` — File
5. Follow prompts to enter or load movies.
6. View results printed on screen.

## File Format Example

```
Inception|2010
The Matrix|1999
Interstellar|2014
```
