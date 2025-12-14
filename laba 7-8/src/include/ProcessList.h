#pragma once

#include <string>

#include "ListNode.h"

// объявление класса ProcessList, который отвечает за цепочку, хранение процессов
class ProcessList {
private:
    ListNode* head;
public:
    ProcessList();
    ~ProcessList();

    bool insert(const PCB& newPCB);
    bool remove(int pid);
    void printList() const;
};
