# Data-Structure-Driven-Student-Management-System---DS-Course-Project
A comprehensive, modular C++ application designed to automate and optimize various campus management workflows using advanced data structures and algorithms.

📋 Table of Contents

Overview
Key Features
Technical Architecture
Modules
Performance Metrics
Installation
Usage
Contributors

🌟 Overview
Modern educational institutions face significant challenges in managing large-scale student data, resource allocation, and academic workflows. This system addresses these challenges through algorithmic rigor, efficient data structures, and modular design principles.

✨ Key Features

🏆 Placement Ranking System - Merit-based student ranking using multi-tier comparison
📝 Admission Priority Management - Weighted scoring for candidate evaluation
📚 Subject Allotment - Two-phase allocation combining merit and preferences
⏰ Assignment Tracker - Deadline-based priority management system
📅 Exam Timetable Manager - Scheduling with undo/backtracking capabilities
📖 Library Management - Dual-layer inventory and transaction tracking
🗺️ Campus Navigation - Shortest path computation using Dijkstra's algorithm

🏗️ Technical Architecture
Data Structures Implemented

Arrays & Structs - Student data modeling
Priority Queue (Min-Heap) - Assignment deadline management
Doubly Linked List - Exam schedule with bidirectional traversal
Stack - Undo operations and transaction history
Singly Linked List - Library inventory management
Graph (Adjacency List) - Campus location mapping
Hash Map - O(1) lookup operations

Algorithms Utilized

Merge Sort - Stable O(n log n) sorting for rankings
Quick Sort - Space-efficient sorting for allocations
Dijkstra's Algorithm - Shortest path computation
Greedy Allocation - Preference-based subject assignment
Priority Queue Operations - Dynamic deadline management

📦 Modules
1. Placement Ranking System
cppData Structure: Struct Array
Algorithm: Merge Sort
Time Complexity: O(n log n)
Space Complexity: O(n)
Multi-tier comparison hierarchy: CGPA → Test Scores → Coding Scores
2. Admission Priority Management
cppData Structure: Struct Array
Algorithm: Merge Sort
Priority Formula: (JEE × 0.5) + (CET × 0.3) + (Board × 0.2)
Robust CSV parsing with error handling
3. Subject Allotment Framework
cppPhase 1: Quick Sort (CGPA-based ranking)
Phase 2: Greedy Allocation (Preference-based)
Complexity: O(n log n) + O(n × m)
4. Assignment Tracker
cppData Structure: Min-Heap + Hash Map
Operations:
  - Addition: O(log n)
  - Viewing: O(1)
  - Deletion: O(n log n)
  - Sorted Display: O(n log n)
5. Examination Timetable
cppData Structure: Doubly Linked List + Stack
Features: Bidirectional traversal, Unlimited undo capability
Complexity: Add/Delete O(k), Undo O(k)
6. Library Management
cppData Structure: Singly Linked List + Stack
Operations:
  - Book Addition: O(1)
  - Borrowing: O(n)
  - Return: O(1)
7. Campus Navigation
cppAlgorithm: Dijkstra's Shortest Path
Graph: Weighted, Undirected
Complexity: O((|V| + |E|) log |V|)
Default: 10 campus locations with calibrated distances
⚡ Performance Metrics
Tested on datasets with n ≤ 5000:

Placement Ranking: 2000 students in ~15ms
Subject Allotment: 1500 students in ~20ms
Campus Navigation: 10-location graph in <5ms

All modules demonstrate sub-second response times for typical workloads.
🚀 Installation
Prerequisites

C++ Compiler (GCC 7.0+ or equivalent)
Standard Template Library (STL)


# Navigate to project directory
cd student-management-system

# Compile the project
g++ -std=c++11 main.cpp -o student_management

# Run the application
./student_management
💻 Usage

Launch the application
Select from the main menu:

Placement Rankings
Admission Processing
Subject Allotment
Assignment Tracking
Exam Scheduling
Library Operations
Campus Navigation

🎯 Future Enhancements

Web-based interface for improved accessibility
Database integration for persistent storage
Real-time collaboration features
Mobile application development
Machine learning integration for predictive analytics
