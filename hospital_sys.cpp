#include "hospital_sys.h"
#include <iostream>
#include <limits>


HospitalSystem::HospitalSystem() : triage_order_counter(0), default_capacity(2) {}


void HospitalSystem::add_doctor(const std::string& doctorID, const std::string& name, const std::string& specialty) {

    if (doctors.find(doctorID) != doctors.end()) {
        std::cout << "Error: Doctor with ID " << doctorID << " already exists.!\n";
        return;
    }
    
    doctors[doctorID] = Doctor(doctorID, name, specialty);
    std::cout << "Doctor " << doctorID << " added successfully!\n";

}

void HospitalSystem::list_doctors() const {

    if (doctors.empty()) {
        std::cout << "No doctors in system!\n";
        return;
    }
    
    std::cout << "\nAll Doctors:\n";
    for (const auto& pair : doctors) {
        const Doctor& doc = pair.second;
        std::cout << "ID: " << doc.get_doctorID() 
                  << " | Name: " << doc.getName()
                  << " | Specialty: " << doc.get_specialty()
                  << " | Appointments: " << doc.getTotalAppointments() << "\n";
    }

}

void HospitalSystem::viewDoctorSchedule(const std::string& doctorID) const {

    auto it = doctors.find(doctorID);
    if (it == doctors.end()) {
        std::cout << "Error: Doctor " << doctorID << " isnot found!\n";
        return;
    }
    
    it->second.print_schedule();

}

void HospitalSystem::schedule_appointment(const std::string& patientID, const std::string& patientName,int priorityLevel, const std::string& doctorID,
                                        const std::string& timeSlot) {

    auto it = doctors.find(doctorID);

    if (it == doctors.end()) {

        std::cout << "Error: Doctor " << doctorID << " isnot found!\n";
        return;
    }
    
    Doctor& doctor = it->second;
    TimeSlotInfo* slot = doctor.getTimeSlot(timeSlot);
    
    
    if (slot == nullptr) {

        doctor.add_time_slot(timeSlot, default_capacity);
        slot = doctor.getTimeSlot(timeSlot);

    }
    
    Appointment apt(doctorID, patientID, patientName, timeSlot, priorityLevel);
    
    if (!slot->is_full()) {
        slot->add_appointment(apt);
        

        TriageEntry entry(priorityLevel, patientID, patientName, doctorID, timeSlot, triage_order_counter++);

        triage_queue.push(entry);
        
        std::cout << "Appointment scheduled for " << patientName << " with Dr " << doctor.getName() << " at " << timeSlot << "\n";
    } 
    else{

        Patient patient(patientID, patientName, priorityLevel);
        slot->addToWaitingList(patient);
        std::cout << "Time slot full, " << patientName << " added to waiting list for Dr. " << doctor.getName() 
            << " at " << timeSlot << ".\n";

    }
}

void HospitalSystem::cancel_appointment(const std::string& doctorID, const std::string& timeSlot,const std::string& patientID) {

    auto it = doctors.find(doctorID);

    if (it == doctors.end()) {

        std::cout << "Error: Doctor " << doctorID << " isnot found!\n";
        return;
    }
    
    Doctor& doctor = it->second;

    TimeSlotInfo* slot = doctor.getTimeSlot(timeSlot);
    

    if (slot == nullptr) {
        std::cout << "Error: Time slot " << timeSlot << " not found for Dr. " << doctorID << "\n";
        return;
    }
    
    if (slot->removeAppointmentByPatientID(patientID)) {

        std::cout << "Appointment for " << patientID << " at " << timeSlot << " with Dr. " << doctorID << " cancelled!\n";
        

        if (slot->has_waiting_list()) {
            Patient waitingPatient = slot->pop_from_waiting_list();

            Appointment newApt(doctorID, waitingPatient.get_patient_id(), waitingPatient.getName(), timeSlot, waitingPatient.get_priorityLevel());
            slot->add_appointment(newApt);
            

            TriageEntry entry(waitingPatient.get_priorityLevel(),  waitingPatient.get_patient_id(),
                            waitingPatient.getName(), doctorID, timeSlot, triage_order_counter++);

            triage_queue.push(entry);
            
            std::cout << waitingPatient.getName() << " moved from waiting list to confirmed appointment at " 
            << timeSlot << ".\n";

        }
    } 

    else {
        std::cout << "No appointment found for " << patientID << " at " << timeSlot << " with Dr. " << doctorID << ".\n";
    }

}

void HospitalSystem::list_appointments_for(const std::string& doctorID, const std::string& timeSlot) const {

    auto it = doctors.find(doctorID);

    if (it == doctors.end()) {

        std::cout << "Error: Doctor " << doctorID << " isnot found!\n";
        return;
    }
    
    const Doctor& doctor = it->second;
    const std::map<std::string, TimeSlotInfo>& schedule = doctor.getSchedule();
    auto slotIt = schedule.find(timeSlot);

    
    if (slotIt == schedule.end()) {
        std::cout << "No appointments for time slot " << timeSlot << ".\n";
        return;
    }
    
    std::cout << "\nDoctor: " << doctorID << ", Time: " << timeSlot << "\n";
    slotIt->second.printSlotInfo();

}

void HospitalSystem::call_next_patient() {

    if (triage_queue.empty()) {
        std::cout << "No patients waiting to be called!\n";
        return;
    }
    
    TriageEntry entry = triage_queue.top();
    triage_queue.pop();
    call_history.push(entry);
    
    std::cout << "\nCalling next patient\n";
    std::cout << "Next patient:\n";
    std::cout << "  Patient ID: " << entry.patient_id << "\n";
    std::cout << "  Name: " << entry.patientName << "\n";
    std::cout << "  Priority: " << entry.priority_level << "\n";
    std::cout << "  Doctor: " << entry.doctor_id << "\n";
    std::cout << "  Time slot: " << entry.time_slot << "\n";
}

void HospitalSystem::undo_last_call() {

    if (call_history.empty()) {
        std::cout << "No calls to undo!\n";
        return;
    }
    
    TriageEntry entry = call_history.top();
    call_history.pop();
    triage_queue.push(entry);
    
    std::cout << "Last call undone, " << entry.patientName << " returned to triage queue.\n";
}

void HospitalSystem::find_patient_appointments(const std::string& patientID) const {
    std::cout << "\nAppointments for Patient " << patientID << " \n";
    bool found = false;
    
    for (const auto& docPair : doctors) {

        const Doctor& doctor = docPair.second;

        const std::map<std::string, TimeSlotInfo>& schedule = doctor.getSchedule();
        
        for (const auto& slotPair : schedule) {

            const TimeSlotInfo& slot = slotPair.second;
            const std::vector<Appointment>& appointments = slot.get_appointments();
            
            for (const auto& apt : appointments) {
                if (apt.getPatientID() == patientID) {

                    std::cout << "Doctor: " << doctor.getName() << " (" << doctor.get_doctorID() << ")\n";
                    std::cout << "Time: " << apt.get_time_slot() << "\n";
                    std::cout << "Priority: " << apt.getPriorityLevel() << "\n\n";

                    found = true;

                }
            }
        }
    }
    
    if (!found) {
        std::cout << "No appointments found for patient " << patientID << ".\n";
    }

}

void HospitalSystem::display_menu() const {
    std::cout << "\nHOSPITAL APPOINTMENT SYSTEM\n";

    std::cout << "1. Add doctor\n";
    std::cout << "2. List all doctors\n";
    std::cout << "3. View doctor schedule\n";
    std::cout << "4. Schedule appointment\n";
    std::cout << "5. Cancel appointment\n";
    std::cout << "6. List appointments for a doctor and time slot\n";
    std::cout << "7. Call next patient (triage)\n";
    std::cout << "8. Undo last call\n";
    std::cout << "9. Find patient appointments\n";
    std::cout << "0. Exit\n";

    std::cout << "Enter your choice: ";
}

void HospitalSystem::run() {

    int choice;
    std::string doctorID, name, specialty, patientID, patientName, timeSlot;
    int priorityLevel;
    
    while (true) {

        display_menu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                std::cout << "Enter doctor ID: ";
                std::getline(std::cin, doctorID);

                std::cout << "Enter doctor name: ";
                std::getline(std::cin, name);

                std::cout << "Enter specialty: ";
                std::getline(std::cin, specialty);


                add_doctor(doctorID, name, specialty);

                break;
                
            case 2:

                list_doctors();
                break;
                
            case 3:

                std::cout << "Enter doctor ID: ";
                std::getline(std::cin, doctorID);
                viewDoctorSchedule(doctorID);
                break;
                
            case 4:

                std::cout << "Enter patient ID: ";
                std::getline(std::cin, patientID);

                std::cout << "Enter patient name: ";
                std::getline(std::cin, patientName);

                std::cout << "Enter priority level (1==high, 5==low): ";
                std::cin >> priorityLevel;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter doctor ID: ";
                std::getline(std::cin, doctorID);
                std::cout << "Enter time slot (type: 09:00): ";
                std::getline(std::cin, timeSlot);

                schedule_appointment(patientID, patientName, priorityLevel, doctorID, timeSlot);

                break;
                
            case 5:
                std::cout << "Enter doctor ID: ";
                std::getline(std::cin, doctorID);

                std::cout << "Enter time slot: ";
                std::getline(std::cin, timeSlot);

                std::cout << "Enter patient ID: ";
                std::getline(std::cin, patientID);
                cancel_appointment(doctorID, timeSlot, patientID);

                break;
                
            case 6:
                std::cout << "Enter doctor ID: ";
                std::getline(std::cin, doctorID);
                std::cout << "Enter time slot: ";
                std::getline(std::cin, timeSlot);
                list_appointments_for(doctorID, timeSlot);

                break;
                
            case 7:
                call_next_patient();
                break;
                
            case 8:
                undo_last_call();
                break;
                
            case 9:
                std::cout << "Enter patient ID: ";
                std::getline(std::cin, patientID);
                find_patient_appointments(patientID);

                break;
                
            case 0:
                std::cout << "Exited system\n";
                return;
                
            default:
                std::cout << "Invalid choice, Please try again!\n";
        }
    }
}