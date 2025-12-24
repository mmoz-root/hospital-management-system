#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>

class Patient {
private:
    std::string patient_id;
    std::string name;
    int priority_level;

public:

    Patient();
    Patient(const std::string& id, const std::string& n, int priority);
    
    std::string get_patient_id() const;
    std::string getName() const;
    int get_priorityLevel() const;
    
    void set_patient_id(const std::string& id);
    void setName(const std::string& n);
    void set_priority_level(int priority);
    
    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif