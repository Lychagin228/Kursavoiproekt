#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>

// Функция вычисления f(x)
double f(double x) {
    if (x < -2.0) {
        return atan(2.0 * x);
    }
    else if (x < 0.0) {
        // Проверка деления на ноль
        if (fabs(x) < DBL_EPSILON) {
            return NAN; // Функция не определена при x = 0 в этой ветке
        }
        return (exp(x) - x - 1.0) / (x * x);
    }
    else {
        return sqrt(x * x + 4.0);
    }
}

// Пункт 1: Значение функции в точке
void calculate_value() {
    double x;
    printf("Введите x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    double result = f(x);
    if (isnan(result)) {
        printf("Ошибка! Функция не определена в точке x = %.2lf\n", x);
    }
    else {
        printf("f(%.2lf) = %.6lf\n", x, result);
    }
}

// Пункт 2: Таблица значений
void build_table() {
    double start, step;
    int count;

    printf("Введите начало интервала: ");
    if (scanf("%lf", &start) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите шаг: ");
    if (scanf("%lf", &step) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите количество отсчетов: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("\n| %-10s | %-15s |\n", "x", "f(x)");
    printf("|%-12s|%-17s|\n", "------------", "-----------------");

    double x = start;
    for (int i = 0; i < count; i++) {
        double result = f(x);
        if (isnan(result)) {
            printf("| %-10.2lf | %-15s |\n", x, "не определена");
        }
        else {
            printf("| %-10.2lf | %-15.6lf |\n", x, result);
        }
        x += step;
    }
    printf("\n");
}

// Пункт 3: Поиск минимума/максимума на отрезке
void find_extremum() {
    double a, b, step;

    printf("Введите начало отрезка: ");
    if (scanf("%lf", &a) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите конец отрезка: ");
    if (scanf("%lf", &b) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    if (a >= b) {
        printf("Ошибка! Начало отрезка должно быть меньше конца.\n");
        return;
    }

    printf("Введите шаг поиска: ");
    if (scanf("%lf", &step) != 1 || step <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    double min_val = DBL_MAX;
    double max_val = -DBL_MAX;
    double min_x = a;
    double max_x = a;
    int found_valid = 0;

    for (double x = a; x <= b; x += step) {
        double result = f(x);
        if (!isnan(result)) {
            found_valid = 1;
            if (result < min_val) {
                min_val = result;
                min_x = x;
            }
            if (result > max_val) {
                max_val = result;
                max_x = x;
            }
        }
    }

    if (!found_valid) {
        printf("На отрезке [%.2lf, %.2lf] функция не определена\n", a, b);
    }
    else {
        printf("Минимум: f(%.6lf) = %.6lf\n", min_x, min_val);
        printf("Максимум: f(%.6lf) = %.6lf\n", max_x, max_val);
    }
}

// Пункт 4: Поиск X по Y
void find_x_by_y() {
    double y, precision;

    printf("Введите Y: ");
    if (scanf("%lf", &y) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите точность: ");
    if (scanf("%lf", &precision) != 1 || precision <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    // Поиск на интервале [-10, 10] с шагом 0.001
    int found = 0;
    for (double x = -10.0; x <= 10.0; x += 0.001) {
        double result = f(x);
        if (!isnan(result) && fabs(result - y) < precision) {
            printf("Найдено: f(%.6lf) ≈ %.6lf (разница: %.6lf)\n",
                x, result, fabs(result - y));
            found = 1;
        }
    }

    if (!found) {
        printf("Не удалось найти x такой, что f(x) ≈ %.6lf с точностью %.6lf\n",
            y, precision);
    }
}

// Пункт 5: Производная в точке
void calculate_derivative() {
    double x;
    double h = 1e-7; // Малое приращение

    printf("Введите x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    // Проверяем, определена ли функция в точке и в соседних точках
    double fx = f(x);
    double fx_plus_h = f(x + h);

    if (isnan(fx) || isnan(fx_plus_h)) {
        printf("Ошибка! Нельзя вычислить производную - функция не определена\n");
        return;
    }

    double derivative = (fx_plus_h - fx) / h;
    printf("f'(%.2lf) ≈ %.6lf\n", x, derivative);
}

// Пункт 6: Вычисление определенного интеграла методом прямоугольников
void calculate_integral() {
    double a, b;
    int n;

    printf("Введите начало интервала: ");
    if (scanf("%lf", &a) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Введите конец интервала: ");
    if (scanf("%lf", &b) != 1) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    if (a >= b) {
        printf("Ошибка! Начало интервала должно быть меньше конца.\n");
        return;
    }

    printf("Введите количество разбиений: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка ввода!\n");
        while (getchar() != '\n');
        return;
    }

    double h = (b - a) / n;
    double sum = 0.0;
    int valid_points = 0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h; // Метод средних прямоугольников
        double result = f(x);
        if (!isnan(result)) {
            sum += result;
            valid_points++;
        }
    }

    if (valid_points == 0) {
        printf("Функция не определена на интервале [%.2lf, %.2lf]\n", a, b);
    }
    else if (valid_points < n) {
        printf("Внимание: функция не определена в некоторых точках интервала\n");
        printf("Интеграл ≈ %.6lf (вычислен по %d из %d точек)\n",
            sum * h, valid_points, n);
    }
    else {
        printf("Интеграл ≈ %.6lf\n", sum * h);
    }
}

int main() {
    setlocale(LC_CTYPE, "RUS");
    int choice;

    printf("=== АНАЛИЗ ФУНКЦИИ ===\n");
    printf("f(x) = {\n");
    printf("  arctan(2x),           x < -2\n");
    printf("  (e^x - x - 1)/x^2,   -2 <= x < 0\n");
    printf("  sqrt(x^2 + 4),        x >= 0\n");
    printf("}\n\n");

    do {
        printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
        printf("1. Значение функции в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Поиск минимума/максимума\n");
        printf("4. Поиск X по Y\n");
        printf("5. Производная в точке\n");
        printf("6. Вычисление интеграла\n");
        printf("7. Выход\n");
        printf("Выберите пункт: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            calculate_value();
            break;
        case 2:
            build_table();
            break;
        case 3:
            find_extremum();
            break;
        case 4:
            find_x_by_y();
            break;
        case 5:
            calculate_derivative();
            break;
        case 6:
            calculate_integral();
            break;
        case 7:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            break;
        }
    } while (choice != 7);

    return 0;
}