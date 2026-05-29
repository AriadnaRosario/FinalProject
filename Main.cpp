#include <iostream>
#include <string>
#include "Tasklist.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "Graph.h"

using namespace std;

//Validates that the date is not before 2026 and that it is a valid date
bool validDate(string date) {
    if (date.length() != 10) {
        return false;
    }

    if (date[4] != '-' || date[7] != '-') {
        return false;
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 2026) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    int daysInMonth;

    if (month == 2) {
        daysInMonth = 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    }
    else {
        daysInMonth = 31;
    }

    if (day < 1 || day > daysInMonth) {
        return false;
    }

    return true;
}

//Creates a task
void createTask(tasklist& Tasklist, Stack& historial, Queue& pending, HashTable& hash) {
    Task t;
    int id;
    string title;
    string description;
    string course;
    int priority;
    string dueDate;

    cout << " --- CREATE TASK --- " << endl;
    
    cout << "Enter the ID of the task: ";
    while (true) {
        cin >> id;

        if (cin.fail()) {
            cout << "Invalid ID, try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (cin.peek() != '\n') {
            cout << "Invalid ID, try again: ";
            cin.ignore(1000, '\n');
        }
        else if (hash.exists(id)) {
            cout << "ID already exists. Enter a different ID: ";
            cin.ignore(1000, '\n');
        }
            else {
        cin.ignore(1000, '\n');
            break;
        }
    }
    t.setId(id);

    cout << "Enter title: ";
    getline(cin, title);
    t.setTitle(title);

    cout << "Enter description: ";
    getline(cin, description);
    t.setDescription(description);

    cout << "Enter course: ";
    getline(cin, course);
    t.setCourse(course);
    
    cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
    cin >> priority;
    
    while (priority < 1 || priority > 3) {
        cout << "Invalid option, try again: ";
        cin >> priority;
    } 
    cin.ignore();
    t.setPriority(priority);
    
    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, dueDate);
    
    while (!validDate(dueDate)) {
    cout << "Invalid date, try again: ";
    getline(cin, dueDate);
    }
    t.setdueDate(dueDate);

    Tasklist.insertList(t);
    pending.enqueue(t);
    historial.push("The task was created " + to_string(id));
    hash.insert(t);

    cout << "The Task was created successfully";
}

//Searches a task using the hash table
void searchTask(HashTable& hash) {
    int id;

    cout << endl << " --- SEARCH TASK --- " << endl;
    cout << "Enter the ID: ";
    cin >> id;

    Task* result = hash.search(id);

    if (result != nullptr) {
        cout << endl << "Task found:" << endl;
        cout << "[" << result->getId() << "] " << result->getTitle() << endl;
        cout << "Course: " << result->getCourse() << endl;
        cout << "Description: " << result->getDescription() << endl;
        cout << "Priority: " << result->getPriority() << endl;
        cout << "Due Date: " << result->getdueDate() << endl;
        cout << "Status: ";

        if (result->isCompleted()) {
            cout << "Completed";
        } else {
            cout << "Pending";
        }

        cout << endl;
    } else {
        cout << "The task is not in the hash table." << endl;
    }
}

// Remove a task by ID
void deleteTask(tasklist& Tasklist, HashTable& hash, Queue& pending, Stack& historial) {
    int id;
    
    cout << "Enter ID to delete: ";
    cin >> id;
    Tasklist.removeList(id);
    hash.remove(id);
    pending.removeTask(id);
    historial.push("The task was removed " + to_string(id));
}    

// Marks the task as completed
void completeTask(tasklist& Tasklist, HashTable& hash, Queue& pending, Stack& historial, Graph& graph) {
    int id;
    
    cout << "Enter ID of the task that you want to mark as completed: ";
    cin >> id;

    Node* node = Tasklist.searchList(id);

    if (node == nullptr) {
        cout << "Task not found" << endl;
    }
    else {
        if (graph.canComplete(Tasklist, id)) {
        node->task.markedCompleted();
        pending.removeTask(id);
        hash.update(node->task);
        historial.push("Task completed " + to_string(id));
        cout << "Task completed successfully" << endl;
        }
    }
}

//Show tasks by priorities
void viewPriority(tasklist& Tasklist) {
    int priority;
    
    do {
        cout << "Enter priority to view (1=High, 2=Medium, 3=Low): ";
        cin >> priority;

        if (priority < 1 || priority > 3) {
        cout << "Invalid option, try again" << endl;
        }
        
    } while (priority < 1 || priority > 3);   
    Tasklist.showPriority(priority);
}

//Adds dependecies between tasks
void manageDependencies(tasklist& Tasklist, Graph& graph, Stack& historial) {
    int taskId;
    int prereqId;
    
    cout << endl << " --- MANAGE DEPENDENCIES --- " << endl;
    cout << "Enter the ID of the source task: ";
    cin >> taskId;
                
    if (Tasklist.searchList(taskId) == nullptr) {
        cout << "Invalid, task does not exist." << endl;
        return;
    }
    cout << "Enter the ID of the prerequisite task: ";
    cin >> prereqId;

    if (Tasklist.searchList(prereqId) == nullptr) {
        cout << "Invalid, prerequisite task does not exist." << endl;
        return;
    }
    bool added = graph.addDependency(taskId, prereqId, Tasklist);
    if (added) {
        historial.push("Dependency added: Task " + to_string(taskId) +
        " depends on Task " + to_string(prereqId));
    }
    else {
        historial.push("Dependency rejected: Task " + to_string(taskId) +
        " depends on Task " + to_string(prereqId));
    }
}

//Lets you edit a task
void editTask(tasklist& Tasklist, HashTable& hash, Stack& historial) {
    int id, option;
    string title;
    string description;
    string course;
    int priority;
    string date;

    cout << "Enter task ID to edit: ";
    cin >> id;

    Node* task = Tasklist.searchList(id);

    if (task == nullptr) {
        cout << "Task not found" << endl;
        return;
    }

    do {
        cout << endl << "What do you want to edit?" << endl;
        cout << "1. Title" << endl;
        cout << "2. Description" << endl;
        cout << "3. Course" << endl;
        cout << "4. Priority" << endl;
        cout << "5. Due date" << endl;
        cout << "0. Exit" << endl;
        cout << "Select an option: ";
        cin >> option;
        cout << endl;
        cin.ignore();

        switch(option) {

        case 1: {
            cout << "Enter new title: ";
            getline(cin, title);
            task->task.setTitle(title);
            historial.push("Edited title of task ID " + to_string(id)) ;
            break;
        }

        case 2: {
            cout << "Enter new description: ";
            getline(cin, description);
            task->task.setDescription(description);
            historial.push("Edited description of task ID " + to_string(id));
            break;
        }

        case 3: {
            cout << "Enter new course: ";
            getline(cin, course);
            task->task.setCourse(course);
            historial.push( "Edited course of task ID " + to_string(id)) ;
            break;
        }

        case 4: {
            cout << "Enter new priority: ";
            cin >> priority;
            task->task.setPriority(priority);
            historial.push("Edited priority of task ID "+ to_string(id));
            break;
        }

        case 5: {
           // cin.ignore();
            cout << "Enter new due date: ";
            getline(cin, date);
            task->task.setdueDate(date);
            historial.push("Edited due date of task ID " + to_string (id));
            break;
        }    

        case 0:
            cout << "Exit..." << endl;
            break;
        }
        
    } while (option < 0 || option > 5);

    cout << "Task was successfully edited" << endl;
}

//shows the menu 
int menu() {
    int option;
    
    do {
        cout << endl << "======================================== " << endl;
        cout << "     SMART ACADEMIC TASK PLANNER " << endl;
        cout << "======================================== " << endl;
        cout << " 1.  Create task" << endl;
        cout << " 2.  Show all tasks" << endl;
        cout << " 3.  Search task" << endl;
        cout << " 4.  Edit task" << endl;
        cout << " 5.  Delete task" << endl;
        cout << " 6.  Mark task as completed" << endl;
        cout << " 7.  View task by priority" << endl;
        cout << " 8.  Manage dependencies" << endl;
        cout << " 9.  View action history" << endl;
        cout << "10. View pending task queue" << endl;
        cout << "11. Save data" << endl;
        cout << "12. Load data" << endl;
        cout << " 0.  Exit" << endl;
        cout << "======================================== " << endl;
        cout << "Select an option: ";
        cin >> option;
	    cout << endl;
        
        if (option < 0 || option > 12 )
            cout << "Invalid option, try again" << endl << endl;
    } while (option < 0 || option > 12);
    return option;

}

//Main program
int main() {
    tasklist Tasklist;
    Stack historial;
    Queue pending;
    HashTable hash;
    Graph graph;
    int option;
        do {
            option = menu();
            switch (option) {
                case 1:
                createTask(Tasklist, historial, pending, hash);
                break;

                case 2:
                Tasklist.showList();
                break;

                case 3:
                searchTask(hash);
                break;
            
                case 4:
                editTask(Tasklist, hash, historial);
                break;
                
                case 5: 
                deleteTask(Tasklist, hash, pending, historial);
                break;
            
                case 6:
                completeTask(Tasklist, hash, pending, historial, graph);
                break;
                
                case 7: 
                viewPriority(Tasklist);
                break;
            
                case 8:
                manageDependencies(Tasklist, graph, historial);
                break;
            
                case 9:
                historial.show();
                break;
           
                case 10:
                pending.show();
                break;
            
                case 11:
                Tasklist.saveData("tasks.txt");
                graph.saveDependencies("dependencies.txt");
                historial.push("Data saved to files");
                historial.saveHistory("history.txt");
                break;
                
                case 12:
                Tasklist.loadData("tasks.txt", hash, pending);
                graph.loadDependencies("dependencies.txt", Tasklist);
                historial.loadHistory("history.txt");
                historial.push("Data loaded from files");
                break; 
                
                case 0:
                cout << "Exit..." << endl;
                break;
            }    
        } while (option != 0);
	return 0;
}
