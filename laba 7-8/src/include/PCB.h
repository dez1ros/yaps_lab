#pragma once

#include <string>
#include <vector>

// объявление структуры PCB, где будет храниться вся нужная информация по процессу
struct PCB
{
    int processID;
    std::string processName;
    enum class State { RUNNING, WAITING, STOPPED } state;
    int commandCounter;
    std::vector<int> cpuRegisters;

    PCB(int pid, std::string pname, State s, int cmdC, std::vector<int> cpuReg) 
        : processID(pid), processName(pname), state(s), commandCounter(cmdC), cpuRegisters(cpuReg) {}
};
