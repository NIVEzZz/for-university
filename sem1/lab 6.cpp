#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

void arr_sort(short* &arr, const short NMax) {
    for (short i = 0; i < NMax - 1; ++i) {
        for (short j = i + 1; j < NMax; ++j) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

void free_matrix(short** &matrix, const short N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void output(const short N, const short M, short** matrix) {
    cout << endl;
    for (short i = 0; i < N; ++i) {
        for (short j = 0; j < M; ++j) {
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void output(const short N, short* matrix) {
    cout << endl;
    for (short i = 0; i < N; ++i) {
        cout << *(matrix + i) << " ";
    }
}

void input_error(short &x) {
    cin >> x;
    while (x < 0) {
        cout << "ошибка" << endl;
        cin >> x;
    }
}

void matrix_converter(short** &matrix, const short N, const short M, const short C, const short D) {
    for (short i = 0; i < N; ++i) {
        for (short j = 0; j < M; ++j) {
            if (i < 2 && j < 2) {
                continue;
            }
            matrix[i][j] = ((i - 1) * C) + ((j - 1) * D);
        }
    }
}

void array_fill_by_trash(short* &arr_of_index, const short I) {
    for (short i = 0; i < I; ++i) {
        arr_of_index[i] = -1;
    }
}

short counter_0_column(short* arr_of_index, const short I) {
    short count_of_0_column = 0;
    for (short i = 0; i < I; ++i) {
        short* element = (arr_of_index + i);
        if (*element >= 0) {
            ++count_of_0_column;
        }
    }
    return count_of_0_column;
}

bool founder_number_in_array(short* &arr_of_index, const short I, const short A) {
    for (short i = 0; i < I; ++i) {
        if (arr_of_index[i] == A) {
            return true;
        }
    }
    return false;
}

void pusher_number_in_array(short* &arr_of_index, const short I, const short A) {
    if (founder_number_in_array(arr_of_index, I, A)) {
        return;
    }
    for (short i = 0; i < I; ++i) {
        if (arr_of_index[i] == -1) {
            arr_of_index[i] = A;
            return;
        }
    }
}

void array_of_index_0_column(short** &matrix, short* &arr_of_index, const short N, const short M) {
    for (short i = 0; i < N; ++i) {
        for (short j = 0; j < M; ++j) {
            if (matrix[i][j] == 0) {
                pusher_number_in_array(arr_of_index, M, j);
            }
        }
    }
}

void deleter_0_column_from_matrix(short** &matrix, const short N, const short M, short* arr_of_index, short count_of_0_column, short& new_B) {
    new_B = M - count_of_0_column;

    for (short j = 0; j < count_of_0_column; j++) {
        short colToRemove = arr_of_index[j] - j;
        for (short new_M = colToRemove; new_M < M - 1; new_M++) {
            for (short new_N = 0; new_N < N; new_N++) {
                matrix[new_N][new_M] = matrix[new_N][new_M + 1];
            }
        }
    }

    for (short x = 0; x < N; x++) {
        matrix[x] = (short*)realloc(matrix[x], new_B * sizeof(short));
    }

}

int main() {

    setlocale(LC_ALL, "Russian");
    const short N = 2;
    const short M = 2;
    short** matrix = (short**)malloc(N * sizeof(short*));
    for (int i = 0; i < M; ++i) {
        matrix[i] = (short*)calloc(M, sizeof(short));
    }

    //Ввод матрицы 2х2
    input_error(matrix[0][0]);
    const short A = matrix[0][0] + N;

    input_error(matrix[0][1]);
    const short B = matrix[0][1] + M;

    cin >> matrix[1][0];
    const short C = matrix[1][0];

    cin >> matrix[1][1];
    const short D = matrix[1][1];

    /*for (short i = 1; i < N; ++i) {
        for (short j = 0; j < M; ++j) {
            cin >> matrix[i][j];
        }
    }*/

    output(N, M, matrix);

    //Преобразование начальной матрицы 
    matrix = (short**)realloc(matrix, A * sizeof(short*));
    for (short i = 0; i < A; ++i) {
        if (i < 2) {
            matrix[i] = (short*)realloc(matrix[i], B * sizeof(short));
        }
        else {
            matrix[i] = (short*)malloc(B * sizeof(int));
        }
    }
    matrix_converter(matrix, A, B, C, D);
    output(A, B, matrix);

    //Получение индексов столбцов с 0
    short* arr_of_index = (short*)calloc(B, sizeof(short));
    array_fill_by_trash(arr_of_index, B);
    array_of_index_0_column(matrix, arr_of_index, A, B);

    short count_of_0_column = counter_0_column(arr_of_index, B);

    if (count_of_0_column == 0) {
        free(arr_of_index);
        free_matrix(matrix, A);
        return 0;
    }

    arr_of_index = (short*)realloc(arr_of_index, count_of_0_column * sizeof(short));
    arr_sort(arr_of_index, count_of_0_column);
    
    //Удаление 0 столбцов из матрицы
    short new_B = 0;
    deleter_0_column_from_matrix(matrix, A, B, arr_of_index, count_of_0_column, new_B);

    output(A, new_B, matrix);

    free_matrix(matrix, A);
    free(arr_of_index); 

    //Задание 2

    float* a2 = new float;
    float* b2 = new float;

    cin >> *a2;
    cin >> *b2;
    *a2 *= 3;

    float temp = *a2;
    *a2 = *b2;
    *b2 = temp;

    cout << *a2 << " " << *b2;

    delete a2;
    delete b2;

    return 0;
}
