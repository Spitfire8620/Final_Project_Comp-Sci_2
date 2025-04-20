// FINAL PROJECT
// Scheduler.cpp
// Ben Sprankle
// Chaffey College
// Version 5.0
// Date: 2025-04-19
// This project is a simple scheduler program that lets you enter tasks,
// give each a priority and time, and then helps you see them in order
// while factoring in any blocked time during the week.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>

using namespace std;

// This is the base class used for polymorphism
class BaseScheduler {
public:
    virtual void run(vector<string>, vector<int>, vector<double>, vector<double>) = 0;
    virtual ~BaseScheduler() {}
};

// This is the actual scheduler – inherits from BaseScheduler so we can use polymorphism
class Scheduler : public BaseScheduler {
private:
    vector<string> tasks;
    vector<int> priorities;
    vector<double> times_per_task;
    vector<double> time_T;
    vector<pair<double, int> > blocked_pairs;

public:
    Scheduler();
    vector<string> reorder_tasks(vector<string> tasks, vector<int> priorities);
    vector<double> reorder_times(vector<double> times_per_task, vector<int> priorities);
    vector<int> reorder_priorities(vector<int> priorities);
    void print_schedule(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T);
    vector<double> get_time_T(vector<double> time_T, vector<pair<double, int> > blocked_pairs);
    vector<pair<double, int> > get_blocked_times(vector<pair<double, int> > blocked_pairs);
    void run(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T) override;
};

// Just making sure all the vectors start off clean
Scheduler::Scheduler() {
    tasks.clear();
    priorities.clear();
    times_per_task.clear();
    time_T.clear();
    blocked_pairs.clear();
}

// Sorts tasks based on priority (lower number = higher priority)
vector<string> Scheduler::reorder_tasks(vector<string> tasks, vector<int> priorities) {
    vector<string> reordered_tasks = tasks;
    vector<int> temp_priorities = priorities;
    for (size_t i = 0; i < temp_priorities.size(); i++) {
        for (size_t j = 0; j < temp_priorities.size() - i - 1; j++) {
            if (temp_priorities[j] > temp_priorities[j + 1]) {
                swap(temp_priorities[j], temp_priorities[j + 1]);
                swap(reordered_tasks[j], reordered_tasks[j + 1]);
            }
        }
    }
    return reordered_tasks;
}

// Same idea as above but for time per task
vector<double> Scheduler::reorder_times(vector<double> times_per_task, vector<int> priorities) {
    vector<double> reordered_times = times_per_task;
    vector<int> temp_priorities = priorities;
    for (size_t i = 0; i < temp_priorities.size(); i++) {
        for (size_t j = 0; j < temp_priorities.size() - i - 1; j++) {
            if (temp_priorities[j] > temp_priorities[j + 1]) {
                swap(temp_priorities[j], temp_priorities[j + 1]);
                swap(reordered_times[j], reordered_times[j + 1]);
            }
        }
    }
    return reordered_times;
}

// Sorts just the priority numbers (used for printing)
vector<int> Scheduler::reorder_priorities(vector<int> priorities) {
    vector<int> reordered_priorities = priorities;
    for (size_t i = 0; i < priorities.size(); i++) {
        for (size_t j = 0; j < priorities.size() - i - 1; j++) {
            if (reordered_priorities[j] > reordered_priorities[j + 1]) {
                swap(reordered_priorities[j], reordered_priorities[j + 1]);
            }
        }
    }
    return reordered_priorities;
}

// Takes out blocked time from your total available time
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

// This lets you enter any blocked hours for specific days
vector<pair<double, int> > Scheduler::get_blocked_times(vector<pair<double, int> > blocked_pairs) {
    vector<pair<double, int> > blocked_pairs_updated = blocked_pairs;
    cout << "Please enter any days you have time blocked off (use numbers: 1 for Monday, etc.)\n";
    int day;
    while (true) {
        cout << "Enter the day (0 to finish): ";
        cin >> day;
        if (day == 0) break;
        if (day < 1 || day > 7) {
            cout << "Please enter a valid day between 1 and 7.\n";
            continue;
        }
        double time;
        while (true) {
            cout << "Enter the time blocked on day " << day << " (in hours, e.g., 1.5): ";
            cin >> time;
            if (time > 16.0 || time <= 0) {
                cout << "Please enter a valid time between 0 and 16 hours.\n";
            } else {
                break;
            }
        }
        blocked_pairs_updated.push_back(make_pair(time, day));
    }
    return blocked_pairs_updated;
}

// This is where everything is printed and sorted
void Scheduler::print_schedule(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T) {
    vector<int> reordered_p = reorder_priorities(priorities);
    vector<string> reordered_t = reorder_tasks(tasks, priorities);
    vector<double> reordered_ti = reorder_times(times_per_task, priorities);
    vector<pair<double, int> > blocked_pairs;
    blocked_pairs = get_blocked_times(blocked_pairs);
    vector<double> time_TEdited = get_time_T(time_T, blocked_pairs);
    // This is where we check if I entered my takss correctly
    cout << "\nSchedule:\n";
    for (int i = 0; i < tasks.size(); i++) {
        cout << "Task: " << reordered_t[i] << " | Priority: " << reordered_p[i] << " | Time: " << reordered_ti[i] << " hours" << endl;
    }
   // This is where I check if I entered my blocked times correctly
    cout << "\nBlocked times:\n";
    for (size_t i = 0; i < blocked_pairs.size(); i++) {
        cout << "Day " << blocked_pairs[i].second << ": " << blocked_pairs[i].first << " hours" << endl;
    }
    // This is the main piece of logic that creates the schedule
    cout << "\nPlanned Schedule:\n";
    for (size_t i = 0; i < reordered_t.size(); i++) {
        double time_needed = reordered_ti[i];
        // It does it per day
        for (size_t day = 0; day < time_TEdited.size(); day++) {
            // It makes sure I dont go over the max time available while still allowing 8 hours to sleep
            if (time_needed <= 0) break;
            if (time_TEdited[day] > 0) {
                double hours = min(time_needed, time_TEdited[day]);
                // It checks if I have enough time left for the task
                time_TEdited[day] -= hours;
                time_needed -= hours;
                // It prints the task and how many hours I should spend on it
                cout << "Day " << (day + 1) << ": " << reordered_t[i] << " " << hours << " hours" << endl;
            }
        }
        if (time_needed > 0) {
            cout << reordered_t[i] << " - Not enough time to finish. " << time_needed << " hours left unscheduled.\n";
        }
    }
}

// This just connects to the base class and satisfies the polymorphism requirement
void Scheduler::run(vector<string> tasks, vector<int> priorities, vector<double> times_per_task, vector<double> time_T) {
    print_schedule(tasks, priorities, times_per_task, time_T);
}

//  MAIN DRIVER
int main() {
    BaseScheduler* myScheduler = new Scheduler();
    vector<string> tasks;
    vector<int> priorities;
    vector<double> times_per_task;
    vector<double> time_T(7, 16.0);
    // This clears the console screen
    cout << "\033[2J\033[1;1H";
    cout << "Welcome to Scheduler!\n\n";
    cout << "Please enter your tasks (type 'done' to finish):\n";

    string task;
    while (true) {
        cin >> task;
        // This checks if the user is done entering tasks
        if (task == "done" || task == "Done" || task == "DONE") break;
        // This checks if the task is a duplicate
        bool duplicate = false;
        for (string& t : tasks) {
            if (t == task) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            cout << "You already entered this task. Try another.\n";
            continue;
        }
        tasks.push_back(task);
    }
    // This gets the users priorities for each task
    cout << "\nPlease enter the priority (1 to " << tasks.size() << ", 1 = most important) for each task:\n";
    vector<bool> used_priorities(tasks.size() + 1, false);
    for (size_t i = 0; i < tasks.size(); i++) {
        int priority;
        while (true) {
            cout << tasks[i] << ": ";
            cin >> priority;
            // This makes sure they have a valid priority
            if (priority < 1 || priority > tasks.size()) {
                cout << "Please enter a priority between 1 and " << tasks.size() << ".\n";
                continue;
            }
            // This checks if the priority is already used
            if (used_priorities[priority]) {
                cout << "This priority is already used. Choose a different one.\n";
                continue;
            }
            used_priorities[priority] = true;
            break;
        }
        priorities.push_back(priority);
    }
    // This gets the time for each task
    cout << "\nPlease enter the time (in hours, e.g., 1, 1.5, 1.25) for each task:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        double time;
        while (true) {
            // This checks if the user entered a valid time
            cout << tasks[i] << ": ";
            cin >> time;
            if (time <= 0 || time > 16.0) {
                cout << "Please enter a valid time between 0 and 16 hours.\n";
                continue;
            }
            break;
        }
        times_per_task.push_back(time);
    }
    // This sends all the data to the scheduler
    cout << "\nHere is your schedule:\n\n";
    myScheduler->run(tasks, priorities, times_per_task, time_T);

    delete myScheduler;
    return 0;
}
