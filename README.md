# Movies Stack and Queue Management in C

This C program allows you to enter movie information (title and release year) either from the keyboard or from a text file, stores the data in a doubly linked stack, and then transfers it to a queue sorted by the release year.

## Description

* Movie data is stored in the `INFORMATION` structure.
* A doubly linked stack (`STACK_ELEMENT`) is used for initial storage.
* Data is transferred from the stack to a queue (`QUEUE_ELEMENT`), sorted by release year in descending order.
* Supports two input methods:

  * From keyboard.
  * From a text file (line format: `title|year`).

## Movie File Format

Each line should be in the format:

```
Movie Title|Year
```

Example:

```
Inception|2010
The Matrix|1999
Interstellar|2014
```

## Structures

* `INFORMATION` — contains movie title (string) and release year (int).
* `STACK_ELEMENT` — element of the doubly linked stack.
* `QUEUE_ELEMENT` — element of the singly linked queue.

## Implementation Details

* The stack is a doubly linked list to enable forward and backward printing.
* The queue is sorted by year in descending order.
* Uses dynamic memory allocation.
* Input validation for year and data source choice.

## Limitations

* Movie years must be between 0 and 2025.
* Maximum line length is 100 characters.
