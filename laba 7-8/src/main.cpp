#include <iostream>
#include <string>

#include "include/PCB.h"
#include "include/ListNode.h"
#include "include/ProcessList.h"

int main(){
    ProcessList processList;  // создание списка процессов

    PCB p1(105, "safari", PCB::State::RUNNING, 0, {1,2});  // создание 3х процессов
    PCB p2(204, "yandex", PCB::State::RUNNING, 0, {3,4});
    PCB p3(204, "kaspersky", PCB::State::STOPPED, 0, {5,6});

    // добавление процессов 1,2 в список. Обработка ошибок выделения памяти

    try{
        processList.insert(p1);
    } catch (const std::runtime_error& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    try{
        processList.insert(p2);
    } catch (const std::runtime_error& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    processList.printList(); // печать списка процессов

    // добавление 3го процесса (ошибочного, где id уже существует)

    try{
        processList.insert(p3);
    } catch (const std::runtime_error& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    processList.printList();  // печать списка процессов

    processList.remove(205);  // удаление несуществующего процесса
    processList.remove(204);  // удаление существующего процесса

    processList.printList();  // печать списка процессов
}