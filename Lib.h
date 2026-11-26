#ifndef LIB_H
#define LIB_H

/**

@brief Обчислює значення математичної функції f(x) = x / (x + 2)^2.
@PARAM x Аргумент функції.
@return Значення функції f(x).
*/
double f(double x);
/**

@brief Зчитує параметри табулювання, шифр групи та номер бригади з текстового файлу.
@PARAM filename Ім'я вхідного текстового файлу.
@PARAM x_start Початкове значення аргументу x.
@PARAM x_end Кінцеве значення аргументу x.
@PARAM points Кількість точок обчислення.
@PARAM step Крок зміни аргументу x.
@PARAM group Буфер для збереження назви групи.
@PARAM brigade Буфер для збереження номера бригади.
@return 1 у разі успішного читання, 0 — якщо файл не вдалося відкрити.
*/
int read_input_data(const char *filename, double *x_start, double *x_end,
int *points, double *step, char *group, char *brigade);
/**

@brief Табулює функцію та записує результати, групу і бригаду в текстовий та бінарний файли.
@PARAM txt_name Ім'я вихідного текстового файлу.
@PARAM bin_name Ім'я вихідного бінарного файлу.
@PARAM x_start Початкове значення аргументу x.
@PARAM points Кількість точок.
@PARAM step Крок зміни x.
@PARAM group Назва групи.
@PARAM brigade Номер бригади.
@return 1 у разі успіху, 0 — при помилці створення файлів.
*/
int write_results(const char *txt_name, const char *bin_name, double x_start,
int points, double step, const char *group, const char *brigade);
/**

@brief Зчитує дані з бінарного файлу (таблицю, групу та бригаду) і виводить на екран.
@PARAM bin_name Ім'я бінарного файлу.
@return 1 у разі успіху, 0 — при помилці відкриття або виділення пам'яті.
*/
int read_and_print_binary(const char *bin_name);

#endif
