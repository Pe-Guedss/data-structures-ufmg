#include <iostream>

#define swapElements(A, B) \
    {                      \
        int aux = A;       \
        A = B;             \
        B = aux;           \
    }

void orderArr(int *arr, int n)
{
    int i, j, min;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[i])
            {
                swapElements(arr[j], arr[i]);
            }
        }
    }
}

void countDuplicates(int *arr, int n)
{
    int i = 0;
    int count = 0, aux = arr[i];
    while (i < n)
    {
        count++;
        i++;
        if (arr[i] != aux)
        {
            std::cout << aux << " aparece " << count << " vez(es)" << std::endl;
            count = 0;
        }

        aux = arr[i];
    }
}

int main()
{
    int valQuantity = 0, i = 0;
    std::cin >> valQuantity;

    int *numArr = nullptr;
    numArr = new int[valQuantity];
    int aux;
    while (i < valQuantity)
    {
        std::cin >> aux;
        numArr[i] = aux;
        i++;
    }

    orderArr(numArr, valQuantity);
    countDuplicates(numArr, valQuantity);

    delete[] numArr;
    return 0;
}