Scheduler Project - Final

Author

Ben Sprankle Chaffey CollegeVersion 5.0 — April 19, 2025

Project Summary

This is a weekly task scheduler written in C++ that allows the user to:

Enter a list of tasks

Assign a unique priority to each task (lower number = higher priority)

Specify how long each task will take (up to 24 hours)

Block out specific hours on any day of the week

Automatically schedule tasks into available time, front-loading by priority

If a task requires more time than is available in a day, it is split across multiple days. If there is not enough total time in the week to complete all tasks, the program clearly states how much time is left unscheduled.

Key Features

Polymorphism: The scheduler uses a base class (BaseScheduler) and a derived class (Scheduler) to demonstrate polymorphism.

Input Validation: Prevents invalid input such as duplicate tasks, reused priorities, or time values over 16 hours. This is to make sure time is left for sleep.

Task Ordering: Tasks are automatically reordered by priority using bubble sort.

Blocked Time: Users can block time on specific days, which is subtracted from the available 24 hours.

Front-Loading Strategy: The scheduler fills each day with the highest priority task first, pushing remaining time to the next day if needed.

Edge Case Handling: Covers a range of edge cases like partial task completion, excessive total time, and empty schedules.

How to Compile & Run

g++ Scheduler.cpp -o Scheduler
./Scheduler

Example Use Case

Welcome to Scheduler!
Please enter your tasks (type 'done' to finish):
> Homework
> Project
> Gym
> done

Please enter the priority (1 to 3, 1 = most important):
Homework: 1
Project: 2
Gym: 3

Please enter the time for each task:
Homework: 6
Project: 4
Gym: 2

Enter blocked times (1 = Monday, 0 to finish):
Day: 1, Time: 3
Day: 5, Time: 2

--- Output Example ---
Planned Schedule:
Day 1: Homework 3h
Day 2: Homework 3h
Day 3: Project 4h
Day 4: Gym 2h

Notes

This program was designed as a final project and focuses on clarity, priority-based planning, and real-world scheduling logic.

Polymorphism is implemented to meet project requirements but can be extended in future versions (e.g., supporting recurring tasks or categories).
