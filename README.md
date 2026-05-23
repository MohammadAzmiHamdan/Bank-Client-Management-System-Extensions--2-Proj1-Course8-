# 🏦 Banking Management System - C++

A complete console-based Banking Management System developed using **C++** as part of **Algorithms & Problem Solving Level 4 (Course 8)**.

This project simulates a real banking environment with authentication, authorization, transaction management, client management, and user administration systems while applying advanced programming fundamentals and problem-solving concepts.

---

# 📌 Project Overview

The system was designed to manage banking operations through a secure and organized console application.

It includes:

* Secure Login System
* Role-Based Access Control
* Client Management
* User Management
* Deposit & Withdraw Operations
* Persistent File Storage
* Permission Management using Bitwise Operations
* Transaction Processing
* Dynamic Menus & Navigation

The main goal of this project was to strengthen:

* Problem Solving Skills
* Algorithms Thinking
* File Handling
* Data Organization
* Modular Programming
* Software Design Principles

---

# ⚙️ Technologies Used

| Technology          | Purpose                      |
| ------------------- | ---------------------------- |
| C++                 | Core Programming Language    |
| File Handling       | Data Persistence             |
| Vectors             | Dynamic Data Storage         |
| Structs             | Data Representation          |
| Enums               | Menu & Permission Management |
| Bitwise Operations  | Role-Based Permissions       |
| Console Application | User Interface               |

---

# 🧠 System Features

| Module                | Description                                       |
| --------------------- | ------------------------------------------------- |
| Authentication System | Secure login using username and password          |
| Authorization System  | Access control based on permissions               |
| Client Management     | Add, update, delete, and search clients           |
| User Management       | Manage system users and permissions               |
| Transactions Module   | Deposit and withdraw money                        |
| Balance Tracking      | Display total balances of all clients             |
| File Storage          | Store and retrieve data from text files           |
| Validation System     | Prevent duplicate accounts and invalid operations |
| Dynamic Menus         | Interactive navigation between system modules     |

---

# 🔐 Permissions System

The system uses a permission-based architecture implemented with **Enums** and **Bitwise Operations**.

Each user can be assigned:

* Full Access
  or customized permissions such as:
* View Clients
* Add Clients
* Delete Clients
* Update Clients
* Find Clients
* Transactions Access
* Manage Users

This simulates real-world banking authorization systems.

---

# 📂 Project Structure

```bash
Banking-System/
│
├── Clients.txt
├── Users.txt
├── main.cpp
└── README.md
```

---

# 🗃️ Data Storage

The system uses text files to simulate database behavior.

### Client Record Format

```txt
AccountNumber#//#PinCode#//#ClientName#//#Phone#//#Balance
```

### User Record Format

```txt
Username#//#Password#//#Permissions
```

---

# 🖥️ Main System Menus

## Main Menu

```txt
[1] Show Clients List
[2] Add New Client
[3] Delete Client
[4] Update Client
[5] Find Client
[6] Transactions
[7] Manage Users
[8] Logout
```

## Transactions Menu

```txt
[1] Deposit
[2] Withdraw
[3] Total Balances
[4] Main Menu
```

## Manage Users Menu

```txt
[1] Show Users List
[2] Add New User
[3] Delete User
[4] Update User
[5] Find User
[6] Main Menu
```

---

# 🚀 Key Concepts Applied

* Functional Decomposition
* Problem Solving
* File Processing
* Data Validation
* Role-Based Access Control
* Structured Programming
* Clean Console UI
* Dynamic Data Management
* Bitwise Permission Handling
* Software Design Fundamentals

---

# 📸 Example Functionalities

✅ Login Authentication
✅ Add New Clients
✅ Update Client Information
✅ Delete Clients
✅ Deposit & Withdraw Operations
✅ Manage Users
✅ Permission Validation
✅ Search Functionality
✅ Total Balances Calculation

---

# 🎯 Learning Outcomes

Through this project, I improved my understanding of:

* Building complete console applications
* Designing modular systems
* Organizing large C++ projects
* Implementing real-world business logic
* Managing user permissions
* Handling persistent storage
* Writing scalable and maintainable code

---

# 🔥 Future Improvements

* Password Encryption
* Database Integration (SQL)
* GUI Version
* Account Transfer Feature
* Transaction History
* Exception Handling Enhancements
* OOP Refactoring
* Admin Dashboard

---

# 👨‍💻 Author

Mohammad Hamdan
Computer Information Systems Student

---

# ⭐ Final Note

This project represents an important milestone in my software engineering journey and my first fully integrated banking system built entirely in C++.

It reflects my passion for problem solving, system design, and continuous learning in software development.
