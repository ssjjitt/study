import sklearn
import mglearn
import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import pandas as pd

print("---------------------------")
# forge - набор данных, который содержит два признака X и y
X, y = mglearn.datasets.make_forge()
# создаем диаграмму рассеяния
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
plt.legend(["Класс 0", "Класс 1"], loc=4)
plt.xlabel("Первый признак")
plt.ylabel("Второй признак")
print("форма массива X: {}".format(X.shape))
plt.show()

#print("---------------------------")
# иллюстрация алгоритмов регрессии - wave - синтетический набор
# wave - 1 входной признак и отклик, который мы и моделируем
X, y = mglearn.datasets.make_wave(n_samples=40)
plt.plot(X, y, 'o')
plt.ylim(-3, 3)
plt.xlabel("Признак")
plt.ylabel("Целевая переменная")
plt.show()

print("---------------------------")
# два набора по раку молочной железы
from sklearn.datasets import load_breast_cancer
# загрузили
cancer = load_breast_cancer()
print("Ключи cancer(): \n{}".format(cancer.keys()))
# 569 предметов на 30 признаков
print("Форма массива data для набора cancer: {}".format(cancer.data.shape))
# Преобразуем данные в DataFrame для удобства
df = pd.DataFrame(cancer.data, columns=cancer.feature_names)
# Выбираем два признака для визуализации
plt.scatter(df['mean radius'], df['mean texture'], c=cancer.target, cmap='coolwarm')
plt.xlabel('Средний радиус')
plt.ylabel('Средняя текстура')
plt.title('Диаграмма рассеяния для двух признаков')
plt.show()

print("---------------------------")
# набор данных, чтобы спрогнозировать стоимость домов\
# boston больше не поддерживается, поэтому california
from sklearn.datasets import fetch_california_housing
california = fetch_california_housing()
print("форма массива data для набора california: {}".format(california.data.shape))
# загрузили
X, y = california.data, california.target
print("форма массива X: {}".format(X.shape))
# алгоритм k = 1 ближайших соседей
mglearn.plots.plot_knn_classification(n_neighbors=1)
plt.show()
# алгоритм k = 3 ближайших соседей
mglearn.plots.plot_knn_classification(n_neighbors=3)
plt.show()

print("---------------------------")
# применение k ближайших соседей
from sklearn.model_selection import train_test_split
X, y = mglearn.datasets.make_forge()
# делим данные на обучающий и тестовый наборы
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
from sklearn.neighbors import KNeighborsClassifier
# используем 3 соседа для классификации
clf = KNeighborsClassifier(n_neighbors=3)
# fit - построение набора
clf.fit(X_train, y_train)
# predict - получаем прогнозы
print("Прогнозы на тестовом наборе: {}".format(clf.predict(X_test)))
# оценка обобщающей способности
print("Правильность на тестовом наборе: {:.2f}".format(clf.score(X_test, y_test)))
# создаем график с разными значениями соседей
fig, axes = plt.subplots(1, 3, figsize=(10, 3))
for n_neighbors, ax in zip([1, 3, 9], axes):
 clf = KNeighborsClassifier(n_neighbors=n_neighbors).fit(X, y)
 mglearn.plots.plot_2d_separator(clf, X, fill=True, eps=0.5, ax=ax, alpha=.4) # поверхность
 mglearn.discrete_scatter(X[:, 0], X[:, 1], y, ax=ax) # точечки
 # заголовки подписи
 ax.set_title("количество соседей:{}".format(n_neighbors))
 ax.set_xlabel("признак 0")
 ax.set_ylabel("признак 1")
axes[0].legend(loc=3)
plt.show()

print("---------------------------")
# Загрузим набор данных о раке молочной железы и разобьем на обучающую и тестовую выборки
from sklearn.datasets import load_breast_cancer
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, stratify=cancer.target, random_state=66)
training_accuracy = []
test_accuracy = []
neighbors_settings = range(1, 11)

# Оценка точности модели для разных значений количества соседей
for n_neighbors in neighbors_settings:
    clf = KNeighborsClassifier(n_neighbors=n_neighbors)
    clf.fit(X_train, y_train)
    training_accuracy.append(clf.score(X_train, y_train))  # Точность на обучающем наборе
    test_accuracy.append(clf.score(X_test, y_test))  # Точность на тестовом наборе

# Построение графика зависимости точности от количества соседей
plt.plot(neighbors_settings, training_accuracy, label="правильность на обучающем наборе")
plt.plot(neighbors_settings, test_accuracy, label="правильность на тестовом наборе")
plt.ylabel("Правильность")  # Подпись для оси Y
plt.xlabel("количество соседей")  # Подпись для оси X
plt.legend()  # Легенда
plt.show()

print("---------------------------")
# Визуализация регрессии k ближайших соседей для различных значений соседей
mglearn.plots.plot_knn_regression(n_neighbors=1)
plt.show()
mglearn.plots.plot_knn_regression(n_neighbors=3)
plt.show()

print("---------------------------")
# Пример регрессии с использованием KNeighborsRegressor
from sklearn.neighbors import KNeighborsRegressor
X, y = mglearn.datasets.make_wave(n_samples=40)
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
reg = KNeighborsRegressor(n_neighbors=3)
reg.fit(X_train, y_train)  # Обучаем регрессионную модель
print("Прогнозы для тестового набора:\n{}".format(reg.predict(X_test)))  # Прогнозируем для тестового набора
print("R^2 на тестовом наборе: {:.2f}".format(reg.score(X_test, y_test)))  # Оценка точности модели

# Построение графиков для различных значений соседей
fig, axes = plt.subplots(1, 3, figsize=(15, 4))
line = np.linspace(-3, 3, 1000).reshape(-1, 1)  # Линия для прогнозов
for n_neighbors, ax in zip([1, 3, 9], axes):
    reg = KNeighborsRegressor(n_neighbors=n_neighbors)
    reg.fit(X_train, y_train)
    ax.plot(line, reg.predict(line))  # Строим прогноз на основе линии
    ax.plot(X_train, y_train, '^', c=mglearn.cm2(0), markersize=8)  # Обучающие данные
    ax.plot(X_test, y_test, 'v', c=mglearn.cm2(1), markersize=8)  # Тестовые данные
    ax.set_title(
        "{} neighbor(s)\n train score: {:.2f} test score: {:.2f}".format(
            n_neighbors, reg.score(X_train, y_train), reg.score(X_test, y_test)))  # Заголовок с точностью
    ax.set_xlabel("Признак")  # Подпись для оси X
    ax.set_ylabel("Целевая переменная")  # Подпись для оси Y
axes[0].legend(["Прогнозы модели", "Обучающие данные/ответы",
                "Тестовые данные/ответы"], loc="best")  # Легенда
plt.show()