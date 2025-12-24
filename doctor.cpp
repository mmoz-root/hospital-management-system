#include "doctor.h"
#include <iostream>

Doctor::Doctor() : doctor_id(""), name(""), specialty("") {}

Doctor::Doctor(const std::string& id, const std::string& n, const std::string& spec) : doctor_id(id), name(n), specialty(spec) {}

void Doctor::add_time_slot(const std::string& timeSlot, int capacity) {
    schedule[timeSlot] = TimeSlotInfo(timeSlot, capacity);

}


TimeSlotInfo* Doctor::getTimeSlot(const std::string& timeSlot) {

    auto it = schedule.find(timeSlot);
    if (it != schedule.end()) {
        return &(it->second);
    }
    return nullptr;
}

void Doctor::print_schedule() const {

    std::cout << "\nSchedule for Dr. " << name << " (" << doctor_id << ") \n";
    if (schedule.empty()) {
        std::cout << "No appointments scheduled!\n";
        return;

    }
    
    for (const auto& pair : schedule) {
        std::cout << "\nTime Slot: " << pair.first << "\n";
        pair.second.printSlotInfo();
    }

}

std::string Doctor::get_doctorID() const { 
    return doctor_id; 
}
std::string Doctor::getName() const { 
    return name; 
}

std::string Doctor::get_specialty() const { 
    return specialty; 
}

int Doctor::getTotalAppointments() const {
    int total = 0;
    for (const auto& pair : schedule) {
        total += pair.second.get_appointments().size();
    }
    return total;
}

const std::map<std::string, TimeSlotInfo>& Doctor::getSchedule() const {
    return schedule;
}