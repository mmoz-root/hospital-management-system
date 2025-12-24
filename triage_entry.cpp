#include "triage_entry.h"

TriageEntry::TriageEntry() : priority_level(5), patient_id(""), patientName(""),doctor_id(""), time_slot(""), order(0) {}


TriageEntry::TriageEntry(int priority, const std::string& patID, const std::string& patName,const std::string& docID, const std::string& slot, int ord)
    : priority_level(priority), patient_id(patID), patientName(patName),  doctor_id(docID), time_slot(slot), order(ord) {}