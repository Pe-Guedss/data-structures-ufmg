#include <iostream>

void swapElements(int *arr, int pos, int *element)
{
    int aux = -1;
    aux = arr[pos];
    arr[pos] = *element;
    *element = aux;
}

void orderArr(int *arr, int n)
{
    int i = 0, j = 0;
    while (i < n)
    {
        int minimumValue = arr[i];
        for (j = i; j < n; j++)
        {
            minimumValue >= arr[j] ? 0 : minimumValue = arr[j];
        }
        swapElements(arr, i, &minimumValue);
        i++;
    }
}

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

    orderArr(numArr, valQuantity);

    delete[] numArr;
    return 0;
}