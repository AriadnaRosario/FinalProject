#include <iostream>
#include "Tasklist.h"

using namespace std;

void createTask(tasklist& Tasklist) {
    Task t;

    cout << " --- CREATE TASK --- " << endl;

    cout << "Enter the ID of the task: ";
    while (true) {
        cin >> t.id;

        if (cin.fail()) {
            cout << "Invalid Id, try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (Tasklist.searchList(t.id) != nullptr) {
            cout << "ID already exists. Enter a different ID: ";
            cin.ignore(1000, '\n');
        }
        else {
            cin.ignore(1000, '\n');
            break;
        }
    }

    cout << "Enter title: ";
    getline(cin, t.title);

    cout << "Enter description: ";
    getline(cin, t.description);

    cout << "Enter course: ";
    getline(cin, t.course);
    
    do {
        cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
        cin >> t.priority;

        if (t.priority < 1 || t.priority > 3) {
            cout << "Invalid option, try again" << endl;
        }

    } while (t.priority < 1 || t.priority > 3);
    cin.ignore();

    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, t.dueDate);

    Tasklist.insertList(t);

    cout << "The Task was created successfully";
}

void searchTask(tasklist& Tasklist) {
    int id;

    cout << endl << " --- SEARCH TASK --- " << endl;
    cout << "Enter the ID: ";
    cin >> id;

    Node* result = Tasklist.searchList(id);

    if (result != nullptr) {
        Task t = result->task;

        cout << endl << " Task found: " << endl;
        cout << "[" << t.id << "] " << t.title << endl;
        cout << "Course: " << t.course << endl;
        cout << "Description: " << t.description << endl;
        cout << "Priority: " << t.priority << endl;
        cout << "Due Date: " << t.dueDate << endl;
        cout << "Status: ";
        if (t.completed) {
            cout << "Completed";
        } else {
            cout << "Pending";
        }
        cout << endl;
    } else {
        cout << "The task is not on the list" << endl;
    }
}

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

int main() {
    tasklist Tasklist;
    int option, id;
    
        do {
            option = menu();
            switch (option) {
                case 1:
                createTask(Tasklist);
                break;

            case 2:
                Tasklist.showList();
                break;

            case 3:
                searchTask(Tasklist);
                break;
            
            case 4:
                break;
            case 5: {
                cout << "Enter ID to delete: ";
                cin >> id;
                Tasklist.removeList(id);
                break;
            }
            
            case 6:
                break;
            
            case 7:
                break;
            
            case 8:
                break;
            
            case 9:
                break;
           
            case 10:
		break;
            
            case 11:
                break;
                
            case 12:
                break; 
                
            case 0:
                cout << "Exit..." << endl;
                break;
            }    
        } while (option != 0);

    return 0;
}
