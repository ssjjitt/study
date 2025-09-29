# Установка пакетов:
# pip install sympy numpy matplotlib pandas scipy ipython scikit-learn mglearn

# Импорт библиотек
import sympy as sp
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# SymPy расчёты
x = sp.symbols('x')
f = x**2 + 1

# 2.1. Производная функции f(x) = x² + 1
derivative = sp.diff(f, x)
print("Производная функции f(x) = x² + 1:", derivative)

# 2.2. Интеграл функции f(x) = x² + 1 на отрезке [0, 1]
integral = sp.integrate(f, (x, 0, 1))
print("Интеграл функции f(x) = x² + 1 на [0, 1]:", integral)

# 2.3. Предел функции f(x) = 1/x² + 1 при x → ∞
limit = sp.limit(1/x**2 + 1, x, sp.oo)
print("Предел функции f(x) = 1/x² + 1 при x → ∞:", limit)

# NumPy операции
# 3.1. Создание одномерного массива из 20 случайных целых чисел
array = np.random.randint(0, 10, 20)
print("\nОдномерный массив из 20 случайных чисел:\n", array)

# 3.2. Преобразование массива в двумерный массив [4,5]
array_2d = array.reshape(4, 5)
print("\nДвумерный массив [4,5]:\n", array_2d)

# 3.3. Разделение массива на 2 массива
array_split = np.split(array_2d, 2)
print("\nПервый массив:\n", array_split[0])
print("\nВторой массив:\n", array_split[1])

# 3.4. Найти все значения, равные 6 в первом массиве
values_equal_6 = np.where(array_split[0] == 6)
print("\nИндексы значений равных 6 в первом массиве:", values_equal_6)

# 3.5. Подсчёт количества найденных значений
count_values_equal_6 = np.sum(array_split[0] == 6)
print("Количество элементов, равных 6:", count_values_equal_6)

# 3.6. Найти мин, макс и среднее значение во втором массиве
min_value = np.min(array_split[1])
max_value = np.max(array_split[1])
mean_value = np.mean(array_split[1])
print(f"\nМин значение: {min_value}, Макс значение: {max_value}, Среднее значение: {mean_value}")

# Pandas операции
# 4.1. Изучение структур данных Series и DataFrame (пример)
# 4.2. Создание объектов Series из массива и словаря
series_from_array = pd.Series(array)
series_from_dict = pd.Series({'a': 1, 'b': 2, 'c': 3})
print("\nSeries из массива:\n", series_from_array)
print("\nSeries из словаря:\n", series_from_dict)

# 4.3. Выполнение математических операций
series_sum = series_from_array + 2
series_mul = series_from_array * 2
print("\nСложение серии +2:\n", series_sum)
print("\nУмножение серии на 2:\n", series_mul)

# 4.4. Создание DataFrame из массива, словаря и Series
df_from_array = pd.DataFrame(array_2d)
df_from_dict = pd.DataFrame({'A': [1, 2, 3], 'B': [4, 5, 6]})
df_from_series = pd.DataFrame(series_from_array, columns=['Value'])

print("\nDataFrame из массива:\n", df_from_array)
print("\nDataFrame из словаря:\n", df_from_dict)
print("\nDataFrame из серии:\n", df_from_series)

# Matplotlib графики
# 5.1. Построение графика функции f(x) = x² + 1
x_vals = np.linspace(-10, 10, 100)
y_vals = x_vals**2 + 1

plt.figure()
plt.plot(x_vals, y_vals, label='f(x) = x² + 1')
plt.title('График функции f(x) = x² + 1')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()
plt.grid()
plt.show()

# 5.2. Построение графика поверхности функции f(x, y) = x² + 2y² + 1
from mpl_toolkits.mplot3d import Axes3D

x_vals = np.linspace(-5, 5, 50)
y_vals = np.linspace(-5, 5, 50)
x_vals, y_vals = np.meshgrid(x_vals, y_vals)
z_vals = x_vals**2 + 2*y_vals**2 + 1

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(x_vals, y_vals, z_vals, cmap='viridis')
plt.title('График поверхности f(x, y) = x² + 2y² + 1')
plt.show()

# 5.3. Построение нескольких диаграмм
# Столбчатая диаграмма
plt.figure()
plt.bar(range(5), [3, 7, 2, 5, 6])
plt.title('Столбчатая диаграмма')
plt.show()

# Гистограмма
plt.figure()
plt.hist(array, bins=5, color='skyblue', edgecolor='black')
plt.title('Гистограмма')
plt.show()

# Круговая диаграмма
plt.figure()
plt.pie([10, 20, 30, 40], labels=['A', 'B', 'C', 'D'], autopct='%1.1f%%')
plt.title('Круговая диаграмма')
plt.show()

# 6. Установка и изучение пакетов:
# 6.1. Scipy – библиотека для научных вычислений (оптимизация, интеграция, интерполяция и т.д.)
# 6.2. IPython – улучшенная оболочка для Python с автодополнением и визуализацией
# 6.3. Sklearn – библиотека для машинного обучения (регрессия, классификация, кластеризация и т.д.)
# 6.4. Mglearn – инструменты для визуализации данных в машинном обучении
