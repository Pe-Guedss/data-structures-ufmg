#include <iostream>

int main()
{
    int valQuantity = 0, i = 0;
    std::cin >> valQuantity;

    int *numArr = nullptr;
    numArr = new (int[valQuantity]);
    int aux;
    while (i < valQuantity)
    {
        std::cin >> aux;
        numArr[i] = aux;
        i++;
    }

    delete[] numArr;
    return 0;
}