#include "patient.h"

Patient::Patient() : patient_id(""), name(""), priority_level(5) {}

Patient::Patient(const std::string& id, const std::string& n, int priority) : patient_id(id), name(n), priority_level(priority) {}

std::string Patient::get_patient_id() const { 
    return patient_id; 
}

std::string Patient::getName() const {

    return name; 
}

int Patient::get_priorityLevel() const { 
    return priority_level; }

void Patient::set_patient_id(const std::string& id) { 
    patient_id = id; 
}
void Patient::setName(const std::string& n) { 
    name = n; 
}


void Patient::set_priority_level(int priority) { 
    priority_level = priority; 

}

std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << p.patient_id << " - " << p.name << " (priority " << p.priority_level << ")";
    return os;
}