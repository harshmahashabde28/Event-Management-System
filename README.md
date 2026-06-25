# Event Management System

A Command-Line Interface (CLI) application built to manage event venues, client bookings, and automated billing[cite: 1]. 

This project was developed to practice fundamental computer science concepts, specifically focusing on manual memory management and algorithm implementation in C++.

### Technical Highlights
* **Custom Data Structures:** Utilizes dynamically allocated linked lists (`EventNode`) to manage event data without relying on standard library containers[cite: 1].
* **Algorithmic Efficiency:** Implements an in-place Merge Sort algorithm (`mergeSort`, `mergeSortedLists`) tailored for linked list traversal to maintain organized event IDs[cite: 1].
* **Object-Oriented Design:** Encapsulates state and behavior within distinct `User`, `EventNode`, and `EventManager` classes[cite: 1].

### Features
* Add and manage event venues with specified capacities and time limits[cite: 1].
* Browse available unbooked venues[cite: 1].
* Secure event slots by capturing client details (Name, Phone, Advance Payment)[cite: 1].
* Search active client bookings via first name[cite: 1].
* Generate dynamic final invoices calculating food costs, staff requirements, and fixed overheads[cite: 1].

### How to Run
1. Compile the `main.cpp` file using a standard C++ compiler (e.g., GCC or MSVC).
2. Run the generated executable in a Windows environment (utilizes `<conio.h>` and `system("cls")` for terminal rendering).
