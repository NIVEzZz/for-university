import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def read_data():
    data = pd.read_csv("data.csv", sep=';')
    x = data.iloc[:, 0].values
    y = data.iloc[:, 1].values
    return x, y


def moving_average(y, L):
    N = len(y)
    z = np.full(N, np.nan)
    for k in range(L, N - L):
        z[k] = np.mean(y[k - L:k + L + 1])
    return z


def exponential_smoothing(y, alpha, beta):
    N = len(y)
    t = np.zeros(N)
    t[0] = y[0]
    for k in range(1, N):
        t[k] = alpha * y[k] + beta * t[k - 1]
    return t


def plot_smoothing(x, y, smoothed, title):
    plt.figure(figsize=(12, 6))
    plt.plot(x, y, 'b-', label='Исходные данные', linewidth=1, alpha=0.7)
    plt.plot(x, smoothed, 'r-', label='Сглаженные данные', linewidth=2)
    plt.xlabel('Время')
    plt.ylabel('Значение')
    plt.title(title)
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.show()



x, y = read_data()

plt.figure(figsize=(12, 6))
plt.plot(x, y, 'b-', linewidth=1)
plt.xlabel('Время')
plt.ylabel('Значение')
plt.title('Исходный временной ряд')
plt.grid(True, alpha=0.3)
plt.show()

N = len(y)
print(f"Длина наблюдений N = {N}")

L_values = [2, 3, 5, 7]
for L in L_values:
    if 2 * L + 1 <= N:
        z = moving_average(y, L)
        plot_smoothing(x, y, z, f'Скользящее среднее (L={L})')

smoothing_params = [(0.1, 0.9), (0.3, 0.7), (0.5, 0.5), (0.7, 0.3)]
for alpha, beta in smoothing_params:
    t = exponential_smoothing(y, alpha, beta)
    plot_smoothing(x, y, t, f'Экспоненциальное сглаживание (α={alpha}, β={beta})')
