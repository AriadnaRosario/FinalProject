#ifndef TASK_H
#define TASK_H
#include <string>

using namespace std;

class Task {
public:
    Task();
    
    int getId();
    string getTitle();
    string getDescription();
    string getCourse();
    int getPriority();
    string getdueDate();
    bool isCompleted();
    
    void setId(int _id);
    void setTitle(string _title);
    void setDescription(string _description);
    void setCourse(string _course);
    void setPriority(int _priority);
    void setdueDate(string _date);
    void markedCompleted();
    
private:
    int id;
    string title;
    string description;
    string course;
    int priority;
    string dueDate;
    bool completed;
    

};

#endif
