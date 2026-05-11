import numpy as np
from sympy import symbols, integrate, lambdify
import matplotlib.pyplot as plt


def f(x):
    return -x ** 2 + 5


# Отрезок интегрирования и количество разбиений
a, b = 0, 3
n_values = [10, 50, 100, 500]  # Разные кол-ва разбиений для анализа точности

print("=" * 70)
print(f"ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ")
print(f"Функция: y = -x² + 5")
print(f"Отрезок: [{a}, {b}]")
print("=" * 70)

# ===== 1. АНАЛИТИЧЕСКИЙ РАСЧЕТ (SymPy) =====
print("\n1 АНАЛИТИЧЕСКИЙ РАСЧЕТ (SymPy):")
print("-" * 70)

x = symbols('x')

# Неопределённый интеграл
antiderivative = integrate(f(x), x)
print(f"Первообразная F(x) = {antiderivative}")

# Определённый интеграл ( F(b) - F(a) )
analytical_result = integrate(f(x), (x, a, b))
print(f"∫f(x)dx на [{a}, {b}] = {analytical_result}")
analytical_result = float(analytical_result)
print(f"Точное значение = {analytical_result:.10f}")

# ===== 2. МЕТОД ПРЯМОУГОЛЬНИКОВ =====
print("\n2  МЕТОД ПРЯМОУГОЛЬНИКОВ:")
print("-" * 70)


def rectangles_left(f, a, b, n):
    """
    Метод левых прямоугольников.
    Для каждого интервала берём значение функции в ЛЕВОЙ точке.

    Args:
        f: функция для интегрирования
        a, b: границы отрезка
        n: количество разбиений

    """
    h = (b - a) / n  # Ширина одного прямоугольника (дельта x)
    integral = 0

    # Сумма площади прямоугольников
    for i in range(n):
        x_left = a + i * h  # Левая точка интервала
        integral += f(x_left) * h  # Площадь = высота * ширина

    return integral


def rectangles_right(f, a, b, n):
    """
    Метод правых прямоугольников.
    Для каждого интервала берём значение функции в ПРАВОЙ точке.

    """
    h = (b - a) / n
    integral = 0

    for i in range(1, n + 1):  # i начинается с 1, не с 0
        x_right = a + i * h  # Правая точка интервала
        integral += f(x_right) * h

    return integral


# Вывод методов прямоугольников
print("Левые прямоугольники:")
for n in n_values:
    result = rectangles_left(f, a, b, n)
    error = abs(result - analytical_result)
    print(f"  n={n:3d}: {result:.10f}, погрешность = {error:.2f}")

print("\nПравые прямоугольники:")
for n in n_values:
    result = rectangles_right(f, a, b, n)
    error = abs(result - analytical_result)
    print(f"  n={n:3d}: {result:.10f}, погрешность = {error:.2f}")

# ===== 3. МЕТОД ТРАПЕЦИЙ =====
print("\n3️  МЕТОД ТРАПЕЦИЙ:")
print("-" * 70)


def trapezoids(f, a, b, n):
    """
    Метод трапеций.
    Вместо прямоугольников используем трапеции.
    Формула: S = (b-a)/n * (y_0/2 + y_1 + y_2 + ... + y_n-1 + y_n/2)

    Геометрический смысл: под кривой строим трапеции вместо прямоугольников.
    """
    h = (b - a) / n
    integral = 0

    # Первая точка
    integral += f(a) * h / 2

    # Промежуточные точки (с коэффициентом 2)
    for i in range(1, n):
        x_i = a + i * h
        integral += f(x_i) * h

    # Последняя точка
    integral += f(b) * h / 2

    return integral


print("Метод трапеций:")
for n in n_values:
    result = trapezoids(f, a, b, n)
    error = abs(result - analytical_result)
    print(f"  n={n:3d}: {result:.10f}, погрешность = {error:.2f}")

# ===== 4. МЕТОД ПАРАБОЛ (СИМПСОНА) =====
print("\n4  МЕТОД ПАРАБОЛ (СИМПСОНА):")
print("-" * 70)


def simpsons_rule(f, a, b, n):
    """
    Метод парабол (правило Симпсона).
    Вместо прямых линий используем параболы.

    Формула: S = h/3 * (f(x0) + 4*f(x1) + 2*f(x2) + 4*f(x3) + ... + f(xn))

    Важно: n ДОЛЖНО быть чётным!

    """
    if n % 2 != 0:
        n += 1  # Если n нечётное, увеличиваем на 1

    h = (b - a) / n
    integral = 0

    # Первая точка
    integral += f(a)

    # Промежуточные точки
    for i in range(1, n):
        x_i = a + i * h
        # Коэффициент чередуется: 4, 2, 4, 2, ...
        coeff = 4 if i % 2 == 1 else 2
        integral += coeff * f(x_i)

    # Последняя точка
    integral += f(b)

    # Умножаем на h/3
    integral *= h / 3

    return integral


print("Метод парабол (Симпсона):")
for n in n_values:
    result = simpsons_rule(f, a, b, n)
    error = abs(result - analytical_result)
    print(f"  n={n:3d}: {result:.10f}, погрешность = {error:.2f}")

# ===== 5. СРАВНЕНИЕ И АНАЛИЗ ТОЧНОСТИ =====
print("\n5  СРАВНЕНИЕ ВСЕХ МЕТОДОВ:")
print("-" * 70)

# Таблица для n=100
n_test = 100
print(f"\nТочка сравнения: n = {n_test}\n")

methods = {
    "Аналитический": analytical_result,
    "Левые прямоугольники": rectangles_left(f, a, b, n_test),
    "Правые прямоугольники": rectangles_right(f, a, b, n_test),
    "Трапеции": trapezoids(f, a, b, n_test),
    "Симпсон": simpsons_rule(f, a, b, n_test),
}

print(f"{'Метод':<25} {'Результат':<20} {'Ошибка':<15}")
print("-" * 60)

for method_name, result in methods.items():
    if method_name == "Аналитический":
        print(f"{method_name:<25} {result:<20.10f} {'точное значение':<15}")
    else:
        error = abs(result - analytical_result)
        error_percent = (error / analytical_result) * 100 if analytical_result != 0 else 0
        print(f"{method_name:<25} {result:<20.10f} {error:.2f} ({error_percent:.4f}%)")

# ===== АНАЛИЗ СХОДИМОСТИ =====
print("\nАНАЛИЗ СХОДИМОСТИ (как n влияет на точность):")
print("-" * 70)
print(f"{'n':<6} {'Прямоуг. (лев)':<18} {'Трапеции':<18} {'Симпсон':<18}")
print("-" * 60)

for n in [10, 20, 50, 100, 200, 500]:
    err_rect = abs(rectangles_left(f, a, b, n) - analytical_result)
    err_trap = abs(trapezoids(f, a, b, n) - analytical_result)
    err_simp = abs(simpsons_rule(f, a, b, n) - analytical_result)
    print(f"{n:<6} {err_rect:<18.2f} {err_trap:<18.2f} {err_simp:<18.2f}")

print("\nВывод: увеличение n снижает погрешность. Симпсон сходится быстрее всех")
