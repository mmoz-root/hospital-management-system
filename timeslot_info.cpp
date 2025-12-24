#include "timeslot_info.h"
#include <iostream>

TimeSlotInfo::TimeSlotInfo() : time_slot(""), capacity(2) {}

TimeSlotInfo::TimeSlotInfo(const std::string& slot, int cap): time_slot(slot), capacity(cap) {}

bool TimeSlotInfo::is_full() const 
{
    return appointments.size() >= static_cast<size_t>(capacity);
}

bool TimeSlotInfo::add_appointment(const Appointment& a) {

    if (!is_full()) {
        appointments.push_back(a);
        return true;
    }
    return false;

}

bool TimeSlotInfo::removeAppointmentByPatientID(const std::string& patientID) {

    for (auto it = appointments.begin(); it != appointments.end(); ++it) {

        if (it->getPatientID() == patientID) {
            appointments.erase(it);
            return true;

        }
    }
    return false;
}

void TimeSlotInfo::addToWaitingList(const Patient& p) {

    waiting_list.push(p);

}

bool TimeSlotInfo::has_waiting_list() const {

    return !waiting_list.empty();

}

Patient TimeSlotInfo::pop_from_waiting_list() {

    Patient p = waiting_list.front();
    waiting_list.pop();
    return p;

}

std::string TimeSlotInfo::get_timeSlot() const { 
    return time_slot; 
}

int TimeSlotInfo::getCapacity() const { 
    return capacity; 
}
const std::vector<Appointment>& TimeSlotInfo::get_appointments() const { return appointments; }

int TimeSlotInfo::getWaitingListSize() const {

    return waiting_list.size();
}



void TimeSlotInfo::printSlotInfo() const {

    std::cout << "Appointments (" << appointments.size() << "/" << capacity << "):\n";

    for (const auto& apt : appointments) {
        std::cout << "  " << apt.getPatientID() << " - " << apt.getPatientName()
                  << " (priority " << apt.getPriorityLevel() << ")\n";
    }
    
    if (!waiting_list.empty()) {
        std::cout << "Waiting List (" << waiting_list.size() << " patients)\n";
    }

}