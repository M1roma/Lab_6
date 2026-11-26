#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

// МАтематична функія //
double f(double x) {
return x / ((x + 2.0) * (x + 2.0));
}

//Считування вхідних данних с файлу //

int read_input_data(const char *filename, double *x_start, double *x_end,
int *points, double *step, char *group, char *brigade) {
FILE *in_file = fopen(filename, "r");
if (in_file == NULL) {
return 0;
}

fscanf(in_file, "%lf", x_start);
fscanf(in_file, "%lf", x_end);
fscanf(in_file, "%d", points);
fscanf(in_file, "%lf", step);
fscanf(in_file, " %49[^\n]", group); // Зчитуємо назву групи
fscanf(in_file, " %49[^\n]", brigade); // Зчитуємо номер бригади

fclose(in_file);
return 1;
}

// Запис у текстовий та бінарний файли //

int write_results(const char *txt_name, const char *bin_name, double x_start,
int points, double step, const char *group, const char *brigade) {
FILE *out_txt = fopen(txt_name, "w");
FILE *out_bin = fopen(bin_name, "wb");

if (out_txt == NULL || out_bin == NULL) {
if (out_txt) fclose(out_txt);
if (out_bin) fclose(out_bin);
return 0;
}

// Запис шапки таблиці у текстовий файл
fprintf(out_txt, "+-------+--------------+--------------+\n");
fprintf(out_txt, "| # | x | f(x) |\n");
fprintf(out_txt, "+-------+--------------+--------------+\n");

// Запис кількості рядків N у бінарний файл
fwrite(&points, sizeof(int), 1, out_bin);

// Запис у два файли
double x = x_start;
for (int i = 0; i < points; i++) {
double y = f(x);

 fprintf(out_txt, "| %5d | %12.6lf | %12.6lf |\n", i + 1, x, y);

 fwrite(&x, sizeof(double), 1, out_bin);
 fwrite(&y, sizeof(double), 1, out_bin);

 x += step;
}

// Запис групи та номера бригади у текстовий файл
fprintf(out_txt, "+-------+--------------+--------------+\n");
fprintf(out_txt, "Group: %s\n", group);
fprintf(out_txt, "Brigade: %s\n", brigade);

// Запис групи та номера бригади у бінарний файл 
char group_buf[50] = {0};
char brigade_buf[50] = {0};
strncpy(group_buf, group, 49);
strncpy(brigade_buf, brigade, 49);

fwrite(group_buf, sizeof(char), 50, out_bin);
fwrite(brigade_buf, sizeof(char), 50, out_bin);

fclose(out_txt);
fclose(out_bin);
return 1;
}

// Считування бінарного файлу та виведення його на консоль //

int read_and_print_binary(const char *bin_name) {
FILE *in_bin = fopen(bin_name, "rb");
if (in_bin == NULL) {
return 0;
}

int N = 0;
fread(&N, sizeof(int), 1, in_bin);

double *dyn_arr = (double *)malloc(2 * N * sizeof(double));
if (dyn_arr == NULL) {
fclose(in_bin);
return 0;
}

// Зчитуємо 2N чисел таблиці
fread(dyn_arr, sizeof(double), 2 * N, in_bin);

// Зчитуємо назву групи та номер бригади з бінарного файлу
char group_buf[50] = {0};
char brigade_buf[50] = {0};
fread(group_buf, sizeof(char), 50, in_bin);
fread(brigade_buf, sizeof(char), 50, in_bin);

fclose(in_bin);

// Виведення таблиці та інформації про групу/бригаду на екран  //
  
printf("Data successfully read from binary file (N = %d):\n\n", N);
printf("+-------+--------------+--------------+\n");
printf("| Point | x | f(x) |\n");
printf("+-------+--------------+--------------+\n");

for (int i = 0; i < N; i++) {
printf("| %5d | %12.6lf | %12.6lf |\n", i + 1, dyn_arr[2 * i], dyn_arr[2 * i + 1]);
}
printf("+-------+--------------+--------------+\n");
printf("Group: %s\n", group_buf);
printf("Brigade: %s\n", brigade_buf);

free(dyn_arr);
return 1;
}
