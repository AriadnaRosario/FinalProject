# Smart Academic Task Planner

## Authors
- Raul Vivaldi
- Ariadna Rosario

## Problem

A large portion of the student community struggles with organizing academic assignments. This disorganization can lead to poor time management, late submissions, and even missed submissions. This project aims to reduce the number of students experiencing these problems.

## Objetive

The main objective of the system is to help the student community manage their academic tasks by organizing assignments, projects, priorities, dependencies, and recent actions.

## Decription

This project is a terminal-based acdemic task planner developed in C++. The system allows users to create, search, edit, delete, prioritized, add dependencies, action history and file persistence to tasks. It uses custom implementations of the used data structures.

## Data structures used

- Link list is used to store all tasks
- Stack is used to store action histoy 
- Queue is used to store pending tasks
- Hash Table is used for fast searching
- Graph is used to manage tasks dependencies
- 
## Features

- Create tasks
- Show tasks
- Search tasks
- Edit tasks
- Delete tasks
- Mark tasks as completed
- View tasks as priority
- Manage tasks dependencies
- View action history
- View pending tasks
- Sava tasks to file
- Load tasks from files

## Compilation

compile using g++ main.cpp Task.cpp Tasklist.cpp Queue.cpp Stack.cpp HashTable.cpp Graph.cpp 

## Execution

./a.out
