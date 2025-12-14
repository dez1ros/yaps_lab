#include "include/ProcessList.h"
#include "include/PCB.h"
#include <iostream>
#include <vector>

ProcessList::ProcessList() : head(nullptr) {}  // конструктор класса

ProcessList::~ProcessList() {   // деструктор класса, в котором очищается память
    ListNode* temp = head;
    while (temp != nullptr) {
        ListNode* ByeByeNode = temp;
        temp = temp->getNext();
        delete ByeByeNode;
    }
}

bool ProcessList::insert(const PCB& newPCB) {  // функция обертывания и добавления нового процесса в цепь
    ListNode* newNode;
    try{
        newNode = new ListNode(newPCB, nullptr);
    } catch (const std::bad_alloc&){
        throw std::runtime_error("Ошибка выделения памяти");
    }

    if (!head) {
        head = newNode;
        std::cout << "Процесс с ID " << newPCB.processID << " добавлен в список" << std::endl;
        return true;
    }
    
    ListNode* current = head;

    while (current) {
        if (current->getData().processID == newPCB.processID) {
            delete newNode;
            std::cout << "Процесс с ID " << newPCB.processID << " уже существует в списке" << std::endl;
            return false;
        }
        current = current->getNext();
    }

    current = head;

    while (current){
        if (current->getNext() == nullptr){
            current->getNext(newNode);
            break;
        }
        current = current->getNext();
    } 

    std::cout << "Процесс с ID " << newPCB.processID << " добавлен в список" << std::endl;
    return true;
}

bool ProcessList::remove(int pid) {  // функция удаления процесса из цепи
    if (!head) {
        std::cout << "Список пуст. Нечего удалять." << std::endl;
        return false;
    }

    if (head->getData().processID == pid) {
        ListNode* temp = head;
        head = head->getNext();
        delete temp;
        std::cout << "Процесс с ID " << pid << " удален из списка" << std::endl;
        return true;
    }

    ListNode* current = head;
    ListNode* previous = nullptr;

    while (current && current->getData().processID != pid) {
        previous = current;
        current = current->getNext();
    }

    if (!current) {
        std::cout << "Процесс с ID " << pid << " не найден в списке" << std::endl;
        return false;
    }

    previous->getNext(current->getNext());
    delete current;
    std::cout << "Процесс с ID " << pid << " удален из списка" << std::endl;
    return true;
}

void ProcessList::printList() const{   // вывод всех процессов
    ListNode* current = head;
    std::cout << "-----------ВСЕ ПРОЦЕССЫ--------------" << std::endl;
    if (!current) {
        std::cout << "В настоящее время запущенных процессов нет" << std::endl;
    }

    while (current){
        std::cout << "processID: " << current->getData().processID << std::endl;
        std::cout << "processName: " << current->getData().processName << std::endl;
        std::cout << "State: ";
        switch(current->getData().state){
            case PCB::State::RUNNING: std::cout << "Running" << std::endl;break;
            case PCB::State::WAITING: std::cout << "Waiting" << std::endl;break;
            case PCB::State::STOPPED: std::cout << "Stopped" << std::endl;break;
        }

        std::cout << "commandCounter: " << current->getData().commandCounter << std::endl;
        std::cout << "cpuRegisters: ";

        for (int a: current->getData().cpuRegisters){
            std::cout << a << ", ";
        }
        std::cout << std::endl;
        std::cout << "-------------------------" << std::endl;

        current = current->getNext();
    }
}