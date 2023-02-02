//Создать класс, определяющий одномерный массив и содержащий функцию, осуществляющую поиск максимального элемента в этом массиве. 
//Определить минимальный из максимальных элементов столбцов двумерной матрицы.  
//Создать класс-наследник, дополнив его функцией сортировки массива по возрастанию количества делителей элементов. 
//Определить число строк матрицы, упорядоченных по убыванию количества делителей.

//1. Создать класс и заполнить массив                                                                           (Done)
//2. Поиск максимального элемента                                                                               (Done)
//3. Определить минимальный из максимальных элементов столбцов двумерной матрицы                                (Done)
//  3.1 Создать массив и заполнить максимальными элементами столбцов                                            (Done)
//  3.2 Определить минимальное значение в этом массиве                                                          (Done)
//4. Создать класс наследник                                                                                    (Done)
//5. Добавить функцию сортировки массива по возрастанию кол-ва делителей элементов                              (Done)
//6. Подсчитать кол-во строк матрицы, упорядоченных по убыванию кол-ва делителей ("перевернуть сортировку")     (Done)
//7. Прописать исключительные ситуации                                                                          (Done)
//8. Подготовить тестовые данные                                                                                (Done)

#include <iostream>
#include <stdlib.h>

using namespace std;
class ArraySculptor {
protected:
    float* arr;
    int symbols;

    void sortFromMinToMax() {
        float temp;
        for (int i = 0; i < symbols; i++)
        {
            temp = arr[i];
            for (int j = i; j < symbols; j++)
                if (temp > arr[j])                      
                {
                    temp = arr[j];                      
                    arr[j] = arr[i];
                    arr[i] = temp;
                }
        }
    }

    void EnterArrayByCols(int numOfCol, float matrix[50][50]) {
        for (int i = 0; i < symbols; i++) {
            arr[i] = matrix[i][numOfCol];
        }
    }
    void EnterArrayByLines(int numOfLine, float matrix[50][50]) {
        for (int i = 0; i < symbols; i++) {
            arr[i] = matrix[numOfLine][i];
        }
    }

    float MAX(ArraySculptor array) {
        ArraySculptor tempArray(array);
        tempArray.sortFromMinToMax();
        return tempArray.arr[symbols - 1];
    }
    float MIN(ArraySculptor array) {
        ArraySculptor tempArray(array);
        tempArray.sortFromMinToMax();
        return tempArray.arr[0];
    }

    void printArray() {
        for (int i = 0; i < symbols; i++) {
            cout << arr[i];
        }
        cout << "\n";
    }

public:
    ArraySculptor(int symCount) {
        symbols = symCount;

        arr = new float[symCount];
    }
    ArraySculptor(int symCount, float matrix[50][50]) {
        symbols = symCount;

        arr = new float[symCount];
        (*this).EnterArrayByCols(0, matrix);
    }
    ArraySculptor(int symCount, int id, float matrix[50][50]) {
        symbols = symCount;

        arr = new float[symCount];
        (*this).EnterArrayByCols(id, matrix);
    }
    ArraySculptor(const ArraySculptor& source) { //конструктор копирования
        symbols = source.symbols;

        arr = new float[symbols];
        for (int i = 0; i < symbols; i++)
            arr[i] = source.arr[i];
    }

    float findMatrixMinOfMax(int coutOfCols, int numOfLines, float matrix[50][50]) {
        ArraySculptor arrOfMax(coutOfCols);
        ArraySculptor tmp(numOfLines);

        for (int i = 0; i < coutOfCols; i++) {
            tmp.EnterArrayByCols(i, matrix);
            arrOfMax.arr[i] = tmp.MAX(tmp);
        }

        return arrOfMax.MIN(arrOfMax);
    }
};

class ArraySculptorExtended : public ArraySculptor {
protected:
    int coutOfDivs(int num) {
        int count = 0;
        if (num < 0) {
            num *= -1;
        }
        for (int i = 1; i <= num; ++i) {
            if (num % i == 0)
                count++;
        }
        return count;
    }

    ArraySculptorExtended sortByCountOfDivs(ArraySculptorExtended tmp) {

        float temp = 0, minCount = 0;

        for (int i = 0; i < symbols; i++)
        {
            temp = arr[i];
            for (int j = i; j < symbols; j++)
                if (coutOfDivs(tmp.arr[i]) > coutOfDivs(tmp.arr[j]))
                {
                    temp = tmp.arr[j];
                    tmp.arr[j] = tmp.arr[i];
                    tmp.arr[i] = temp;

                    //tmp.printArray();
                }
        }

        return (tmp);
    }
    ArraySculptorExtended reverseArray(int idOfCol, float matrix[50][50])
    {
        ArraySculptorExtended tmp(*this);

        char temp;
        for (int i = 0; i < symbols / 2; i++)
        {
            temp = tmp.arr[i];
            tmp.arr[i] = tmp.arr[symbols - i - 1];
            tmp.arr[symbols - i - 1] = temp;
        }

        //printf("\n\n\tReversing our array: ");
        //tmp.printArray();

        return (tmp);
    }

public:
    ArraySculptorExtended(int numOfLines) : ArraySculptor(numOfLines) {}
    ArraySculptorExtended(const ArraySculptorExtended& source) : ArraySculptor(source) {}
    ArraySculptorExtended(int symCount, float matrix[50][50]) : ArraySculptor(symCount, matrix) {}
    ArraySculptorExtended(int symCount, int id, float matrix[50][50]) : ArraySculptor(symCount, id, matrix) {}

    int countOfDescNumOfDivs(int coutOfCols, int coutOfLines, float matrix[50][50]) {
        int count = 0;
        ArraySculptorExtended arraySculptor(coutOfCols);

        for (int i = 0; i < coutOfLines; i++) {
            arraySculptor.EnterArrayByLines(i, matrix);
            ArraySculptorExtended tmp(arraySculptor);
            tmp = tmp.sortByCountOfDivs(tmp);
            tmp = tmp.reverseArray(i, matrix);

            int check = 1;
            for (int j = 0; j < coutOfCols; j++) {
                if (!(coutOfDivs(tmp.arr[j]) == coutOfDivs(arraySculptor.arr[j]))) check = 0;
            }
            if (check == 1) count++;
        }

        return count;
    }
};

int main()
{
    int coutOfLines = 0, coutOfCols = 0;
    float matrix[50][50] = { 0 };

    //Задание размерности массива
    while (true)
    {
        cout << "\n\tWARNING! Max count of lines and cols is 50!\n";
        cout << "\n\n\tEnter count of elements in your two-dimensional array (lines then cols): \n";
        cout << "> ";
        cin >> coutOfLines; 
        cin >> coutOfCols;

        if (cin.fail()) // извлечение не производилось
        {
            cout << "\n\tInvalid values for the array! Try again\n";
            // сбрасываем биты состояния обратно в goodbit, чтобы мы могли использовать ignore()
            cin.clear();
            // очищаем недопустимый ввод из потока
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // попробовать снова
            continue;
        }
        // очищаем любой дополнительный ввод из потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Проверяем размер массива 
        if (coutOfLines >= 50 || coutOfCols >= 50 || coutOfCols <= 0 || coutOfLines <= 0) // убедиться, что значение возраста положительное
        {
            cout << "\n\tInvalid range for the array! Try again\n";
            continue;
        }
        break;
    }

    //Задание элементов массива
    while (true) {
        cout << "**Enter the array elements (line by line): \n";
        for (int i = 0; i < coutOfLines; i++) {
            cout << ("> ");

            for (int j = 0; j < coutOfCols; j++) {
                cin >> matrix[i][j];
            }
        }
        if (cin.fail())
        {
            cout << "\n\tInvalid values for the array! Try again\n";
            cout << ("> ");

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    //Вызываем напрямую через представителя класса родителя
    //ArraySculptor arraySculptor(coutOfLines);
    //arraySculptor.findMatrixMinOfMax(coutOfCols, matrix);

    //Вызываем через представителя класса наследника собственные функции и родителя
    ArraySculptorExtended arraySculptorExtended(coutOfLines, matrix);

    //Определяем минимальный из максимальных элементов столбцов двумерной матрицы
    float minOfMax = arraySculptorExtended.findMatrixMinOfMax(coutOfCols, coutOfLines, matrix);
    printf("\n\n\tThe minimum of the maximum elements of the\n\tcolumns of a two-dimensional matrix is: %f\n", minOfMax);

    //Определяем число строк матрицы, упорядоченных по убыванию количества делителей
    int count = arraySculptorExtended.countOfDescNumOfDivs(coutOfCols, coutOfLines, matrix);
    printf("\n\n\tThe number of rows of the matrix, ordered\n\tin descending order of the number of divisors: %d\n", count);

    return 0;
}

/*//////////////////////
Test 1:
3 3 

6 4 5 -> true
7 8 9 
1 2 3

result: 7 1
//////////////////////
Test 2:
2 4

5 6 7 8 
1 -4 0 9

result: 5 0
//////////////////////
Test 3:
4 5

4 5 3 2 1 -> true
-5 9 8 7 1
0 1 1 1 1
9 1 1 1 1 -> true

result: 1 2
//////////////////////
Test 4:
5 1

-90 -> true
6   -> true
-3  -> true
4   -> true
0   -> true

result: 6 5
//////////////////////
Test 5:
1 5

-90 6 -3 4 0

result: -90 0
//////////////////////
Необязательно! {
    3 3

    1 2 3
    4 5 6
    0 1 2

result: 4 0
}
//////////////////////
*/