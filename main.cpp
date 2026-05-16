#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> tasks;
vector<bool> completed;

void saveTasks() {
    ofstream file("tasks.txt");

    for (int i = 0; i < tasks.size(); i++) {
        file << tasks[i] << "|" << completed[i] << endl;
    }

    file.close();
}

void loadTasks() {
    ifstream file("tasks.txt");

    if (!file.is_open()) {
        return;
    }

    string task;
    bool status;

    while (getline(file, task, '|')) {
        file >> status;
        file.ignore();

        tasks.push_back(task);
        completed.push_back(status);
    }

    file.close();
}

void addTask() {
    string task;

    cin.ignore();

    cout << "Enter task: ";
    getline(cin, task);

    tasks.push_back(task);
    completed.push_back(false);

    cout << "Task added successfully.\n";
}

void viewTasks() {
    if (tasks.size() == 0) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n===== TASK LIST =====\n";

    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i];

        if (completed[i]) {
            cout << " [Completed]";
        }
        else {
            cout << " [Pending]";
        }

        cout << endl;
    }
}

void completeTask() {
    int number;

    cout << "Enter task number to complete: ";
    cin >> number;

    if (number < 1 || number > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }

    completed[number - 1] = true;

    cout << "Task marked as completed.\n";
}

void deleteTask() {
    int number;

    cout << "Enter task number to delete: ";
    cin >> number;

    if (number < 1 || number > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks.erase(tasks.begin() + number - 1);
    completed.erase(completed.begin() + number - 1);

    cout << "Task deleted successfully.\n";
}

int main() {
    loadTasks();

    int choice;

    do {
        cout << "\n===== TASK TRACKER =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Complete Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addTask();
            break;

        case 2:
            viewTasks();
            break;

        case 3:
            completeTask();
            break;

        case 4:
            deleteTask();
            break;

        case 5:
            saveTasks();
            cout << "Tasks saved. Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}