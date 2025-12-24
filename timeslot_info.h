#ifndef TIMESLOTINFO_H
#define TIMESLOTINFO_H

#include <string>
#include <vector>
#include <queue>
#include "appointment.h"
#include "patient.h"

class TimeSlotInfo {

private:
    std::string time_slot;
    int capacity;
    std::vector<Appointment> appointments;
    std::queue<Patient> waiting_list;


public:
    TimeSlotInfo();
    TimeSlotInfo(const std::string& slot, int cap);
    
    bool is_full() const;
    bool add_appointment(const Appointment& a);
    bool removeAppointmentByPatientID(const std::string& patientID);
    void addToWaitingList(const Patient& p);
    bool has_waiting_list() const;
    Patient pop_from_waiting_list();
    
    std::string get_timeSlot() const;
    int getCapacity() const;
    const std::vector<Appointment>& get_appointments() const;
    int getWaitingListSize() const;
    
    void printSlotInfo() const;
};

#endif