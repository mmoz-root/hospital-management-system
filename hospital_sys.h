#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include <map>
#include <queue>
#include <stack>
#include <string>
#include "doctor.h"
#include "triage_entry.h"

class HospitalSystem {
    
private:
    std::map<std::string, Doctor> doctors;

    std::priority_queue<TriageEntry, std::vector<TriageEntry>, TriageComparator> triage_queue;
    std::stack<TriageEntry> call_history;

    int triage_order_counter;
    int default_capacity;


public:
    HospitalSystem();
    
    void add_doctor(const std::string& doctorID, const std::string& name, const std::string& specialty);
    void list_doctors() const;
    void viewDoctorSchedule(const std::string& doctorID) const;
    
    void schedule_appointment(const std::string& patientID, const std::string& patientName,int priorityLevel, const std::string& doctorID, const std::string& timeSlot);

    void cancel_appointment(const std::string& doctorID, const std::string& timeSlot, const std::string& patientID);
    void list_appointments_for(const std::string& doctorID, const std::string& timeSlot) const;
    
    void call_next_patient();
    void undo_last_call();
    
    void find_patient_appointments(const std::string& patientID) const;
    
    void display_menu() const;


    void run();
};

#endif