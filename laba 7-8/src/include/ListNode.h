#pragma once

#include <string>

#include "PCB.h"

// объявление класса ListNode который является обёрткой для PCB. 
class ListNode {
private:
    PCB data;
    ListNode* next;
public:
    ListNode(PCB d, ListNode* n);

    PCB getData() const;
    ListNode* getNext() const;
    ListNode* getNext(ListNode* newNext);
};