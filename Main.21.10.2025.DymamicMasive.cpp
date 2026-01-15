#include <iostream>
#include <iomanip>  
#include <cstdlib>  
#include <ctime>    
#include <windows.h>

using namespace std;


int** allocateMatrix(int rows, int cols) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}


void fillMatrix(int** matrix, int rows, int cols, int minVal, int maxVal) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
}


void printMatrix(int** matrix, int rows, int cols) {
    cout << "\n--- Сгенерированный массив ---\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
    cout << "------------------------------\n";
}


int* calculateColumnSums(int** matrix, int rows, int cols) {
    int* sums = new int[cols];
    for (int j = 0; j < cols; j++) {
        sums[j] = 0;
        for (int i = 0; i < rows; i++) {
            sums[j] += matrix[i][j];
        }
    }
    return sums;
}


void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(static_cast<unsigned int>(time(0)));

    int rows, cols, minVal, maxVal;

    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;
    cout << "Введите минимальное значение (диапазон): ";
    cin >> minVal;
    cout << "Введите максимальное значение (диапазон): ";
    cin >> maxVal;

    int** myMatrix = allocateMatrix(rows, cols);
    fillMatrix(myMatrix, rows, cols, minVal, maxVal);
    printMatrix(myMatrix, rows, cols);

    int* columnSums = calculateColumnSums(myMatrix, rows, cols);

    cout << "Суммы элементов по столбцам:\n";
    for (int j = 0; j < cols; j++) {
        cout << "Столбец " << j + 1 << ": " << columnSums[j] << endl;
    }

    deleteMatrix(myMatrix, rows);
    delete[] columnSums;

    return 0;
}
