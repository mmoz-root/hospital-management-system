#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:

    std::string doctor_id;
    std::string patientID;
    std::string patient_name;
    std::string timeSlot;
    int priority_level;


public:

    Appointment();
    Appointment(const std::string& docID, const std::string& patID, const std::string& patName, const std::string& slot, int priority);
    
    std::string get_doctor_id() const;
    std::string getPatientID() const;
    std::string getPatientName() const;
    std::string get_time_slot() const;
    int getPriorityLevel() const;
    
};

#endif