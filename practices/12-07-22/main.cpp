#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::string result = "";
    std::vector<int> shelf(0);

    int boxesAmount = 0;
    while (std::cin >> boxesAmount) {

        int intervalStart = 0, intervalEnd = 0;
        for (int i = 0; i < boxesAmount; i++) {
            std::cin >> intervalStart >> intervalEnd;  
            for (int j = intervalStart; j <= intervalEnd; j++) {
                shelf.push_back(j);
            }
        }

        std::sort(shelf.begin(), shelf.end());

        int gearCode = -1;
        std::cin >> gearCode;

        int firstIndexOf = -1, lastIndexOf = -1;
        for (int i = 0; i < shelf.size(); i++) {
            if (shelf[i] != gearCode) {
                continue;
            }
            if (firstIndexOf == -1) {
                firstIndexOf = i;
                lastIndexOf = i;
            }
            else lastIndexOf = i;
        }

        if (firstIndexOf != -1)
            std::cout << gearCode << " found from " << firstIndexOf << " to " << lastIndexOf << std::endl;
        else
            std::cout << gearCode << " not found" << std::endl;
        shelf.clear();
    }
    

    return 0;
}