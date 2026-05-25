#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// ================= TASK CLASS =================
class Task {
public:
    int id;
    string title;
    bool completed;

    Task(int i, string t, bool c) {
        id = i;
        title = t;
        completed = c;
    }
};

// ================= TASK MANAGER =================
class TaskManager {
private:
    vector<Task> tasks;
    string filename = "tasks.txt";

public:
    TaskManager() {
        loadTasks();
    }

    // ADD TASK
    void addTask(string title) {
        int id = tasks.size() + 1;
        tasks.push_back(Task(id, title, false));
        saveTasks();
        cout << "Task added successfully!\n";
    }

    // MARK AS COMPLETED
    void completeTask(int id) {
        for (auto &task : tasks) {
            if (task.id == id) {
                task.completed = true;
                saveTasks();
                cout << "Task marked as completed!\n";
                return;
            }
        }
        cout << "Task not found!\n";
    }

    // VIEW PENDING TASKS
    void viewPending() {
        cout << "\n--- Pending Tasks ---\n";
        for (auto &task : tasks) {
            if (!task.completed) {
                cout << task.id << ". " << task.title << endl;
            }
        }
    }

    // VIEW COMPLETED TASKS
    void viewCompleted() {
        cout << "\n--- Completed Tasks ---\n";
        for (auto &task : tasks) {
            if (task.completed) {
                cout << task.id << ". " << task.title << endl;
            }
        }
    }

    // SAVE TO FILE
    void saveTasks() {
        ofstream file(filename);
        for (auto &task : tasks) {
            file << task.id << "|" << task.title << "|" << task.completed << endl;
        }
        file.close();
    }

    // LOAD FROM FILE
    void loadTasks() {
        tasks.clear();
        ifstream file(filename);

        if (!file) return;

        string line;
        while (getline(file, line)) {
            int pos1 = line.find("|");
            int pos2 = line.rfind("|");

            int id = stoi(line.substr(0, pos1));
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            bool completed = stoi(line.substr(pos2 + 1));

            tasks.push_back(Task(id, title, completed));
        }

        file.close();
    }
};

// ================= MAIN FUNCTION =================
int main() {
    TaskManager tm;
    int choice;

    do {
        cout << "\n===== TASK MANAGER =====\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task as Completed\n";
        cout << "3. View Pending Tasks\n";
        cout << "4. View Completed Tasks\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore();

        if (choice == 1) {
            string title;
            cout << "Enter task: ";
            getline(cin, title);
            tm.addTask(title);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter task ID to complete: ";
            cin >> id;
            tm.completeTask(id);
        }
        else if (choice == 3) {
            tm.viewPending();
        }
        else if (choice == 4) {
            tm.viewCompleted();
        }
        else if (choice == 5) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}