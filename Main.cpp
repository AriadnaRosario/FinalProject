#include <iostream>
#include "Tasklist.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"

using namespace std;

//Crea una tarea
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
    
    do {
        cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
        cin >> priority;

        if (priority < 1 || priority > 3) {
            cout << "Invalid option, try again" << endl;
        }

    } while (priority < 1 || priority > 3);
    cin.ignore();
    t.setPriority(priority);

    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, dueDate);
    t.setdueDate(dueDate);

    Tasklist.insertList(t);
    pending.enqueue(t);
    historial.push("The task was created " + to_string(id));
    hash.insert(t);

    cout << "The Task was created successfully";
}

//Busca una tarea usando la tabla hash
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

//Muestra el menu 
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

//Programa principal
int main() {
    tasklist Tasklist;
    Stack historial;
    Queue pending;
    HashTable hash;
    int option, id;
    
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
                break;

		case 5: 
                cout << "Enter ID to delete: ";
                cin >> id;
                Tasklist.removeList(id);
                hash.remove(id);
                historial.push("The task was removed " + to_string(id));
                break;
            
                case 6:
                break;
            
                case 7:
                break;
            
                case 8:
                break;
            
                case 9:
                historial.show();
                break;
           
                case 10:
                pending.show();
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
