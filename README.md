# 🚀 Data Structures in Action: Real-World Applications

Welcome to our Data Structures repository! This project showcases practical, real-world implementations of advanced data structures in C++, moving away from abstract concepts into functional, real-life systems. 

---

## 🛠️ Project Components

The repository includes two main core systems:

### 1. 📚 Library Management System (`Library_Management_BST_AVL.cpp`)
An efficient book archiving and retrieval system powered by two tree structures:
* **Binary Search Tree (BST):** Used for standard indexing, in-order traversal, and quick range queries.
* **AVL Tree:** A self-balancing BST that guarantees $O(\log n)$ time complexity for search, insertion, and deletion by utilizing dynamic left/right rotations.
* *Bonus Feature:* Implements a **Closest Match Search** algorithm to find the nearest available book ID when an exact match isn't found.

### 2. 🏥 Emergency Room Patient Scheduler (`ER_Patient_Scheduler_Heap.cpp`)
A dynamic triage system for hospital emergency rooms using a **Custom Max-Heap**:
* Patients are automatically prioritized based on condition **Severity** and **Arrival Time** (FIFO for equal severity).
* *Bonus Feature:* Supports a dynamic **Severity Update** function which re-heaps (`up` or `down`) the patient's position instantly if their medical condition changes.

---

## 💻 Tech Stack & Tools

| Category | Technology / Tool |
| :--- | :--- |
| **Language** | C++ |
| **Concepts** | Object-Oriented Programming (OOP), Pointer Manipulation, Tree Rotations, Heapification |
| **Methodology** | AI-Assisted Development & Peer Review |

---

## 👥 Contributors & Team

This project was built with dedication and teamwork by:

* **Abdo Al Adawy**
* **Ahmed Osama**
* **Adham Saber**
* **Mazen Magdy**

### 🤖 AI Assistance
In the spirit of modern engineering, we leveraged **AI Assistance** as a collaborative tool to help optimize our algorithms, refine edge cases (especially in AVL rotations), and review code quality.

---
