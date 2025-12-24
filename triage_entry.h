#ifndef TRIAGEENTRY_H
#define TRIAGEENTRY_H

#include <string>

struct TriageEntry {

    int priority_level;

    std::string patient_id;
    std::string patientName;
    std::string doctor_id;
    std::string time_slot;

    int order;
    
    TriageEntry();
    TriageEntry(int priority, const std::string& patID, const std::string& patName, const std::string& docID, const std::string& slot, int ord);
    
};


struct TriageComparator {

    bool operator()(const TriageEntry& a, const TriageEntry& b) const {

        if (a.priority_level != b.priority_level) {
            return a.priority_level > b.priority_level; 
        }
        return a.order > b.order; 
    }
};

#endif