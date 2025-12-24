#include "appointment.h"


Appointment::Appointment() : doctor_id(""), patientID(""), patient_name(""),  timeSlot(""), priority_level(5) {}


Appointment::Appointment(const std::string& docID, const std::string& patID, const std::string& patName, const std::string& slot, int priority)
    : doctor_id(docID), patientID(patID), patient_name(patName), timeSlot(slot), priority_level(priority) {}

std::string Appointment::get_doctor_id() const { 
    return doctor_id; 
}
std::string Appointment::getPatientID() const { 
    return patientID; 

}

std::string Appointment::getPatientName() const { 
    return patient_name; 
}
std::string Appointment::get_time_slot() const { 
    return timeSlot; 

}
int Appointment::getPriorityLevel() const { 
    return priority_level; 

}