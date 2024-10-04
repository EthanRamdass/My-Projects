#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to hold information about a task
struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

// Function prototypes
void displayMenu();
void addTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);

int main() {
    vector<Task> tasks;  // Vector to store all tasks
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

// Function to display the menu
void displayMenu() {
    cout << "\n--- To-Do List Menu ---\n";
    cout << "1. Add a task\n";
    cout << "2. View tasks\n";
    cout << "3. Mark task as completed\n";
    cout << "4. Delete a task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// Function to add a new task to the to-do list
void addTask(vector<Task>& tasks) {
    string description;
    cin.ignore(); // Ignore leftover newline character
    cout << "Enter task description: ";
    getline(cin, description);

    tasks.push_back(Task(description));
    cout << "Task added successfully.\n";
}

// Function to view all tasks in the to-do list
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks in the to-do list.\n";
    } else {
        cout << "\n--- To-Do List ---\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i].description;
            if (tasks[i].completed) {
                cout << " [Completed]";
            }
            cout << "\n";
        }
    }
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available to mark as completed.\n";
        return;
    }

    int taskNumber;
    viewTasks(tasks);
    cout << "Enter the task number to mark as completed: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        tasks[taskNumber - 1].completed = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Function to delete a task from the to-do list
void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available to delete.\n";
        return;
    }

    int taskNumber;
    viewTasks(tasks);
    cout << "Enter the task number to delete: ";
    cin >> taskNumber;

    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        tasks.erase(tasks.begin() + taskNumber - 1);
        cout << "Task deleted successfully.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}
