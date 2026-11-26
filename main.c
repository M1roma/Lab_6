#include <stdio.h>
#include "lib.h"

int main() {
double x_start = 0.0, x_end = 0.0, step = 0.0;
int points_count = 0;
char group[50];
char brigade[50];

// CЧитування вхідних даних з input.txt 
if (!read_input_data("input.txt", &x_start, &x_end, &points_count,
                     &step, group, brigade)) {
    printf("Error: Cannot open input.txt!\n");
    return 1;
}

// Запис результатів, групи та номера бригади у текстовий і бінарний файли
if (!write_results("output.txt", "data.bin", x_start, points_count,
                   step, group, brigade)) {
    printf("Error: Cannot create output files!\n");
    return 1;
}

// Считування бінарного файлу та виведення результатів на екран
if (!read_and_print_binary("data.bin")) {
    printf("Error: Cannot read data.bin!\n");
    return 1;
}

return 0;
}
