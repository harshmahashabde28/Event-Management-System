<h1 align="center">Event Management System</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B" alt="C++">
  <img src="https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows" alt="Windows">
  <img src="https://img.shields.io/badge/Concept-Data_Structures-blue?style=for-the-badge" alt="Data Structures">
</p>

> A Command-Line Interface (CLI) application built to manage event venues, process client bookings, and generate automated financial invoices.

## Table of Contents
- [Overview](#overview)
- [Technical Architecture](#technical-architecture)
- [Key Features](#key-features)
- [Installation & Execution](#installation--execution)

---

## Overview
Developed to reinforce low-level memory management and algorithmic efficiency. This system entirely bypasses the C++ Standard Template Library (STL) for its core data structures, relying instead on manual implementations to demonstrate technical depth and control.

## Technical Architecture
* **Custom Linked Lists:** Implements dynamic node allocation (`EventNode`) to maintain a lightweight memory footprint.
* **In-Place Merge Sort:** Utilizes a highly efficient, custom-built Merge Sort algorithm (`splitList`, `mergeSortedLists`) to systematically order event IDs without requiring auxiliary array memory.
* **Object-Oriented Design:** Encapsulates system state into distinct `User`, `EventNode`, and `EventManager` structures.

## Key Features
| Feature | Description |
| :--- | :--- |
| **Venue Management** | Define total capacity, time limits, and unique venue names. |
| **Booking System** | Secure open slots by capturing client demographics and advance payments. |
| **Query Engine** | Search active client booking records via first name using linear traversal. |
| **Automated Billing** | Calculate dynamic final costs (food, hourly staff, fixed overhead) based on actual event metrics. |

## Installation & Execution
This application is optimized for Windows environments.

```bash
# 1. Clone the repository
git clone [https://github.com/harshmahashabde28/Event-Management-System.git](https://github.com/harshmahashabde28/Event-Management-System.git)

# 2. Navigate to the directory
cd Event-Management-System

# 3. Compile the code using a standard C++ compiler
g++ main.cpp -o EventManager.exe

# 4. Run the executable
EventManager.exe
