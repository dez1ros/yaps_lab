#include <iostream>
#include <vector>
#include <string>

template<typename ElemT, typename KeyT, typename SumT>
struct GroupInfo
{
    KeyT key;
    int count;
    ElemT minElem;
    ElemT maxElem;
    SumT sum;
    double avg;
};

template<typename ElemT, typename KeyFT, typename ValueFT>
auto groupStats(ElemT* arr, int n, KeyFT keyFunc, ValueFT valueFunc) {
    using Key = decltype(keyFunc(arr[0]));
    using Value = decltype(valueFunc(arr[0]));
    
    std::vector<GroupInfo<ElemT, Key, Value>> groups;
    
    
    for (int i = 0; i < n; i++) {
        ElemT x = arr[i];
        
        Key key = keyFunc(x);
        Value value = valueFunc(x);

        bool is_found = false;
        for (auto& group : groups) {
            if (group.key == key) {
                group.count++;
                if (x < group.minElem) {
                    group.minElem = x;
                }
                if (x > group.maxElem) {
                    group.maxElem = x;
                }
                group.sum += value;
                group.avg = static_cast<double>(group.sum / group.count);
                is_found = true;
                break;
            }
        }

        if (!is_found) {
            GroupInfo<ElemT, Key, Value> new_group;
            new_group.key = key;
            new_group.count = 1;
            new_group.minElem = x;
            new_group.maxElem = x;
            new_group.sum = value;
            new_group.avg = static_cast<double>(value);
            groups.push_back(new_group);
        }

    }

    return groups;
}

template<typename ElemT, typename KeyT, typename SumT>
void printGroups(const std::vector<GroupInfo<ElemT, KeyT, SumT>>& groups) {
    std::cout << "KEY | COUNT | MIN | MAX | SUM | AVG\n";
    std::cout << "-----------------------------------\n";
    for (const auto& g : groups) {
        std::cout 
            << g.key << "   | "
            << g.count << "     | "
            << g.minElem << "   | "
            << g.maxElem << "   | "
            << g.sum << "   | "
            << g.avg << "\n";
    }
    std::cout << "\n";
}

int main() {
    int arrI[] = {12, 25, 37, 42};
    int nI = sizeof(arrI) / sizeof(arrI[0]);

    auto groupsInt = groupStats(arrI, nI,
        [](int x){ return x % 10; },
        [](int x){ return x; }
    );

    printGroups(groupsInt);

    double arrD[] = {-5.5, 3.2, 12.0, 7.5, 15.3};
    int nD = sizeof(arrD) / sizeof(arrD[0]);

    auto groupsDouble = groupStats(arrD, nD,
        [](double x) {
            if (x < 0) return 0;
            else if (x <= 10) return 1;
            else return 2;
        },
        [](double x) { return x; }
    );

    printGroups(groupsDouble);

    std::string arrS[] = {"fqwefwq", "afds", "faaew", "afewadg", "eeeee"};
    int nS = sizeof(arrS) / sizeof(arrS[0]);

    auto groupsString = groupStats(arrS, nS,
        [](const std::string& s){ return s[0]; },
        [](const std::string& s){ return static_cast<int>(s.size()); }
    );

    printGroups(groupsString);

    return 0;
}
