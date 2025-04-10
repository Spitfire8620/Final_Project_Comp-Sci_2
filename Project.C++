// FINAL PROJECT
// Scheduler.cpp
// Ben Sprankle
// Chaffey College
// Version 1.0
// Date: 2025-04-05
// This project is a simple scheduler program that allows users to input tasks,
// categorize them by importance, and view them in order.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>

using namespace std;

class Scheduler {
private:
    vector<string> tasks;
    vector<int> priorities;
    vector<double> times_per_task;
    vector<double> time_T;
    vector<string> blocked_times_Names;
    vector<double> blocked_times;

public:
    Scheduler(); // Constructor
    vector<string> reorder(vector<string> tasks, vector<int> priorities);
    void print_schedule(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T, vector<string> blocked_times_Names, vector<double> blocked_times);
    vector<double> get_time_T(vector<double> time_T);
    vector<string> get_blocked_times(vector<string> blocked_times_Names, vector<double> blocked_times);
};

// Constructor Definition
Scheduler::Scheduler() {
    tasks.clear();
    priorities.clear();
    times_per_task.clear();
    time_T.clear();
    blocked_times_Names.clear();
    blocked_times.clear();
}

// Reorders tasks by priority (1 = most important)
vector<string> Scheduler::reorder(vector<string> tasks, vector<int> priorities) {
    vector<pair<int, string> > paired;

    for (size_t i = 0; i < tasks.size(); i++) {
        paired.push_back(make_pair(priorities[i], tasks[i]));
    }

    sort(paired.begin(), paired.end()); // Sort by priority (ascending)

    vector<string> reordered_tasks;
    for (const auto& p : paired) {
        reordered_tasks.push_back(p.second);
    }

    return reordered_tasks;
}

// Dummy function to return time (for expansion later)
vector<double> Scheduler::get_time_T(vector<double> time_T) {
    return time_T;
}

// Dummy function to return blocked times (for expansion later)
vector<string> Scheduler::get_blocked_times(vector<string> blocked_times_Names, vector<double> blocked_times) {
    return blocked_times_Names;
}

// Prints the schedule
void Scheduler::print_schedule(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T, vector<string> blocked_times_Names, vector<double> blocked_times) {
    vector<pair<int, string> > schedule;
    for (size_t i = 0; i < tasks.size(); ++i) {
        schedule.push_back(std::make_pair(priorities[i], tasks[i]));
    }

    sort(schedule.begin(), schedule.end());
    

    cout << "Task Schedule (Ordered by Priority):\n";
    for (const auto& item : schedule) {
        cout << "Priority " << item.first << ": " << item.second << endl;
    }
}

int main() {
    Scheduler myScheduler;

    vector<string> tasks;
    vector<int> priorities;
    vector<double> times_per_task;
    vector<double> time_T;
    vector<string> blocked_times_Names;
    vector<double> blocked_times;
    cout << "\033[2J\033[1;1H"; // Clear screen
    cout << "Welcome to Scheduler!\n\n";
    cout << "Please enter your tasks (type 'done' to finish):\n";

    string task;
    while (true) {
        cin >> task;
        if (task == "done"||task == "Done"||task == "DONE") break;

        // Check for duplicate
        if (find(tasks.begin(), tasks.end(), task) != tasks.end()) {
            cout << "You already entered this task. Try another.\n";
            continue;
        }
        tasks.push_back(task);
    }

    cout << "\nPlease enter the priority (1-5, 1 = most important) for each task:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        int priority;
        cout << tasks[i] << ": ";
        cin >> priority;
        priorities.push_back(priority);
    }
    cout << "\nPlease enter the time (in hours ex: 1h, 1.5h, 1.25h) for each task:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        double time;
        cout << tasks[i] << ": ";
        cin >> time;
        times_per_task.push_back(time);
    }

    cout << "\nHere is your schedule:\n\n";
    myScheduler.print_schedule(tasks, priorities, times_per_task, time_T, blocked_times_Names, blocked_times);

    return 0;
}
