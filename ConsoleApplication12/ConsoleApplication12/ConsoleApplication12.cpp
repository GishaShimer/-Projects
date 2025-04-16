#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void Create(int**& mass, int hight, int width)
{
    mass = new int* [hight];
    for (int i = 0; i < hight; i++) {
        mass[i] = new int[width];
    }
}

void Fill(int** mass, int hight, int width)
{
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            mass[i][j] = rand() % 100;
        }
    }
}

void Show(int** mass, int hight, int width)
{
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            cout << setw(2) << mass[i][j] << " ";
        }
        cout << "\n";
    }
}

void Delete(int** mass, int hight)
{
    for (int i = 0; i < hight; i++) {
        delete[] mass[i];
    }
    delete[] mass;
}
/*
1. написати функцію, яка буде знаходити максимальний елемент масива і видаляти його рядок і стовпчик
*/

void Ex1(int**& mass, int& hight, int& width)
{
    int max = mass[0][0];
    int maxRow = 0;
    int maxCol = 0;


    for (int i = 0; i < hight; i++)//пошук максимального числа
    {
        for (int j = 0; j < width; j++)
        {
            if (mass[i][j] > max)
            {
                max = mass[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }

    int** temp;
    Create(temp, hight - 1, width - 1);//створення тимчасового масива

    int newRow = 0;


    for (int i = 0; i < hight; i++)//основний код
    {
        int newCol = 0;
        if (i != maxRow)
        {
            for (int j = 0; j < width; j++)
            {
                if (j != maxCol)
                {
                    temp[newRow][newCol] = mass[i][j];
                    newCol++;
                }
            }
            newRow++;
        }
    }

    cout << "max number is " << max << " in " << maxCol + 1 << " column" << " and " << maxRow + 1 << " row\n";//вивід для легшого пошуку

    Delete(mass, hight);
    mass = temp;
    hight--;
    width--;
}
/*
2. написати функцію, яка буде знаходити мінімальний елемент масива та ставити перед / після нього рядок і стовпчик, заповнений нулями
*/


void Ex2(int**& mass, int& hight, int& width)
{
    if (hight <= 2 || width <= 0) {
        cout << "Error\n";
        return;
    }


    int min = mass[0][0];
    int minRow = 0;
    int minCol = 0;

    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            if (mass[i][j] < min) {
                min = mass[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }
    cout << "Minimum element: " << min << "\n";


    if (minRow > 0 && minRow < hight - 1) {
        for (int j = 0; j < width; j++) {
            mass[minRow - 1][j] = 0;
            mass[minRow + 1][j] = 0;
        }
    }
    if (minCol > 0 && minCol < width - 1) {
        for (int i = 0; i < hight; i++) {
            mass[i][minCol - 1] = 0;
            mass[i][minCol + 1] = 0;
        }
    }
}

int main()
{
    srand(time(NULL));

    int hight, width;
    int** mass = nullptr;
    bool job = 1;
    int choice;
    cout << "Enter hight of array\n";
    cin >> hight;
    cout << "Enter width of array\n";
    cin >> width;
    cout << "_________________\n";

    Create(mass, hight, width);
    Fill(mass, hight, width);
    Show(mass, hight, width);
    cout << "_________________\n";

    while (job)
    {
        cout << "Enter your choice\n1-Ex1\n2-Ex2\n3-Show\n4-New sizes\n5-Exit\n";
        cout << "_________________\n";
        cin >> choice;

        cout << "_________________\n";
        switch (choice)
        {
        case 1:
            Ex1(mass, hight, width);
            Show(mass, hight, width);
            cout << "_________________\n";
            break;
        case 2:
            Ex2(mass, hight, width);
            Show(mass, hight, width);
            cout << "_________________\n";
            break;
        case 3:
            Show(mass, hight, width);
            cout << "_________________\n";
            break;
        case 4:
            cout << "Enter height of array\n";
            cout << "_________________\n";
            cin >> hight;
            cout << "_________________\n";
            cout << "Enter width of array\n";
            cout << "_________________\n";
            cin >> width;
            cout << "_________________\n";
            Create(mass, hight, width);
            Fill(mass, hight, width);
            Show(mass, hight, width);
            cout << "_________________\n";
            break;
        case 5:
            job = 0;
            break;
        default:
            cout << "Wrong choice\n";
            cout << "_________________\n";
            break;
        }
    }

    Delete(mass, hight);
}
