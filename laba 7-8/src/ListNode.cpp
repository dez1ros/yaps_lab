#include "include/ListNode.h"

ListNode::ListNode(PCB d, ListNode* n) : data(d), next(n) {}  // конструктор класса

PCB ListNode::getData() const { // getter функция для data
    return data;
}

ListNode* ListNode::getNext() const {  // getter функция для next
    return next;
}

ListNode* ListNode::getNext(ListNode* newNext) {  // перегрузка функции для изменения переменной next
    next = newNext;
    return next;
}