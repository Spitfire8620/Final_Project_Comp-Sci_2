// FINAL PROJECT
// Scheduler.cpp
// Ben Sprankle, 
// Chaffey College
// Version 0.0
// Date: 2025-4-5
// This project is supposed to be a real world example of how C++ can be used to make daily life easier.
// This is a simple scheduler program that allows users to input tasks, which the program categorises by importance and scheuals acourdingly.




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
    vector<double> time_per_task;
    vector<double> time_T;
    vector<string> blocked_times_Names;
    vector<double> blocked_times;

    public: 
    Scheduler() {vector<string> tasks; vector<int> priorities; vector<double> time_per_task; vector<double> time_T; vector<string> blocked_times_Names; vector<double> blocked_times;}
    vector<string> reorder (vector<string> tasks, vector<int> priorities) {}
    vector<double> get_time_per_task(vector<string> tasks, vector<int> priorities, vector<double> time_per_task) {}
    vector<string> print_schedual(vector<string> tasks, vector<int> priorities, vector<double> time_T, vector<string> blocked_times_Names, vector<double> blocked_times) {}
    vector<string> get_tasks(vector<string> tasks) {}
    vector<int> get_priorities(vector<string> tasks, vector<int> priorities) {}
    vector<double> get_time_T(vector<double> tiem_T) {}
    vector<string> get_blocked_times(vector<string> blocked_times_Names, vector<double> blocked_times) {}


};

Scheduler::Scheduler() {
    // Constructor to initialize the scheduler
    tasks.clear();
    priorities.clear();
    time_T.clear();
    blocked_times_Names.clear();
    blocked_times.clear();
}
vector<string> Scheduler::reorder (vector<string> tasks, vector<int> priorities) {

};
vector<double> Scheduler::get_time_per_task(vector<string> tasks, vector<int> priorities, vector<double> time_per_task) {
    
};
vector<string> Scheduler::print_schedual(vector<string> tasks, vector<int> priorities, vector<double> time_T, vector<string> blocked_times_Names, vector<double> blocked_times) {

};
vector<string> Scheduler::get_tasks(vector<string> tasks) {

};
vector<int> Scheduler::get_priorities(vector<string> tasks, vector<int> priorities) {

};
vector<double> Scheduler::get_time_T(vector<double> tiem_T) {

};
vector<string> Scheduler::get_blocked_times(vector<string> blocked_times_Names, vector<double> blocked_times) {

};





int main() {
    Scheduler myScheduler;
    // Get tasks
    // Get priorities
    // Get time required for each task
    // Get blocked times
    // Calculate the schedule

    vector<string> tasks = {"Math", "Writing", "Gym"};
    vector<int> priorities = {3, 1, 2};
    //Time Per Day from 1-N
    vector<double> time_T = {1.5, 0.5, 2.0};
    vector<string> blocked_times_Names = {"Meeting", "Lunch"};
    vector<double> blocked_times = {12.0, 13.0};


    cout << "Here is your schedual!:\n\n" << endl; 
    myScheduler.print_schedual(tasks, priorities, time_T, blocked_times_Names, blocked_times);
    
    return 0;
}
