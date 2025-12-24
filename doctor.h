#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <map>
#include "timeslot_info.h"

class Doctor {
private:
    std::string doctor_id;
    std::string name;
    std::string specialty;
    std::map<std::string, TimeSlotInfo> schedule;

public:
    Doctor();
    Doctor(const std::string& id, const std::string& n, const std::string& spec);
    
    void add_time_slot(const std::string& timeSlot, int capacity);
    TimeSlotInfo* getTimeSlot(const std::string& timeSlot);
    void print_schedule() const;
    
    std::string get_doctorID() const;
    std::string getName() const;
    std::string get_specialty() const;
    int getTotalAppointments() const;
    
    const std::map<std::string, TimeSlotInfo>& getSchedule() const;
};

#endif