// FINAL PROJECT
// Scheduler.cpp
// Ben Sprankle
// Chaffey College
// Version 2.17
// Date: 2025-04-16
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
    vector<pair<double, int> > blocked_pairs;

public:
    Scheduler(); // Constructor
    vector<string> reorder_tasks(vector<string> tasks, vector<int> priorities);
    vector<double> reorder_times(vector<double> times_per_task, vector<int> priorities);
    vector<int> reorder_priorities(vector<int> priorities);
    void print_schedule(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T);
    vector<double> get_time_T(vector<double> time_T, vector<pair<double, int> > blocked_pairs);
    vector<pair<double, int> > get_blocked_times(vector<pair<double, int> > blocked_pairs);
};

// Constructor Definition
Scheduler::Scheduler() {
    tasks.clear();
    priorities.clear();
    times_per_task.clear();
    time_T.clear();
    blocked_pairs.clear();
}

// Reorders tasks by priority (1 = most important)
vector<string> Scheduler::reorder_tasks(vector<string> tasks, vector<int> priorities) {
    vector<string> reordered_tasks = tasks;
    for (size_t i = 0; i < priorities.size(); i++) {
        for (size_t j = 0; j < priorities.size() - i - 1; j++) {
            if (priorities[j] > priorities[j + 1]) {
                // Swap priorities
                swap(priorities[j], priorities[j + 1]);
                // Swap corresponding tasks
                swap(reordered_tasks[j], reordered_tasks[j + 1]);
            }
        }
    }
    return reordered_tasks;
}
vector<double> Scheduler::reorder_times(vector<double> times_per_task, vector<int> priorities) {
    vector<double> reordered_times = times_per_task;
    for (size_t i = 0; i < priorities.size(); i++) {
        for (size_t j = 0; j < priorities.size() - i - 1; j++) {
            if (priorities[j] > priorities[j + 1]) {
                // Swap priorities
                swap(priorities[j], priorities[j + 1]);
                // Swap corresponding times
                swap(reordered_times[j], reordered_times[j + 1]);
            }
        }
    }
    return reordered_times;
}
vector<int> Scheduler::reorder_priorities(vector<int> priorities) {
    vector<int> reordered_priorities = priorities;
    for (size_t i = 0; i < priorities.size(); i++) {
        for (size_t j = 0; j < priorities.size() - i - 1; j++) {
            if (priorities[j] > priorities[j + 1]) {
                // Swap priorities
                swap(priorities[j], priorities[j + 1]);
                // Swap corresponding tasks
                swap(reordered_priorities[j], reordered_priorities[j + 1]);
            }
        }
    }
    return reordered_priorities;
}

// Dummy function to return time (for expansion later)
vector<double> Scheduler::get_time_T(vector<double> time_T, vector<pair<double, int> > blocked_pairs) {
    for (size_t i = 0; i < time_T.size(); i++) {
        for (size_t j = 0; j < blocked_pairs.size(); j++) {
            if (blocked_pairs[j].second == i + 1) {
                time_T[i] -= blocked_pairs[j].first;
            }
        }
    }
    cout << "\nAvailable time:\n";
    for (size_t i = 0; i < time_T.size(); i++) {
        cout << "Day " << i + 1 << ": " << time_T[i] << " hours\n" << endl;
    }
    return time_T;
}

// Dummy function to return blocked times (for expansion later)
vector<pair<double, int> > Scheduler::get_blocked_times(vector<pair<double, int> > blocked_pairs) {
    vector<pair<double, int> > blocked_pairs_updated = blocked_pairs;
    cout << "Please enter any days you have time blocked off use numbers: (ex 1 for monday)\n";
    int day;
    while (true) {
        cout << "Enter the day (0 to finish): ";
        cin >> day;
        if (day == 0) break;
        double time;
        cout << "Enter the time blocked on day: (in hours ex. 1.5h)" << day << ": ";
        cin >> time;
        blocked_pairs_updated.push_back(make_pair(time, day));
    }

     


    return blocked_pairs_updated;
}
// Prints the schedule
void Scheduler::print_schedule(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T) {
    vector<int> reordered_p = reorder_priorities(priorities);
    vector<string> reordered_t = reorder_tasks(tasks, priorities);
    vector<double> reordered_ti = reorder_times(times_per_task, priorities);
    vector<pair<double, int> > blocked_pairs;
    blocked_pairs = get_blocked_times(blocked_pairs);
    

    cout << "Schedual" << endl;
    for (int i = 0; i < tasks.size(); i++) {
        cout << "Task: " << reordered_t[i] << " | Priority: " << reordered_p[i] << " | Time: " << reordered_ti[i] << " hours" << endl;
    }
    cout << "\nBlocked times:\n";
    for (size_t i = 0; i < blocked_pairs.size(); i++) {
        cout << "Day " << blocked_pairs[i].second << ": " << blocked_pairs[i].first << " hours" << endl;
    }
    vector<double> time_TEdited = get_time_T(time_T, blocked_pairs);
    

}

int main() {
    Scheduler myScheduler;

    vector<string> tasks;
    vector<int> priorities;
    vector<double> times_per_task;
    vector<double> time_T(7, 24.0);
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
    myScheduler.print_schedule(tasks, priorities, times_per_task, time_T);

    return 0;
}
