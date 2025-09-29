import sys
import pandas as pds
import mglearn
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
import IPython
import sklearn
from sklearn.datasets import load_iris
# набор данных ирис, он похож на словарь(ключ значения)
iris_dataset = load_iris()
print("Ключи iris_dataset: \n{}".format(iris_dataset.keys()))
# краткое описание набора данных DESCR
print(iris_dataset['DESCR'] + "\n...")
# массив строк с сортами цветов которые нужно предсказать
print("Названия ответов: {}".format(iris_dataset['target_names']))
# описание каждого признака
print("Названия признаков: \n{}".format(iris_dataset['feature_names']))
# data – массив NumPy,
# который содержит количественные измерения длины чашелистиков,
# ширины чашелистиков, длины лепестков и ширины лепестков
print("Тип массива data: {}".format(type(iris_dataset['data'])))
# строка в data = цвет ириса
# столбец = четыре измеренных признака для цветка
# 150 различных цветов по 4 признакам
print("Форма массива data: {}".format(iris_dataset['data'].shape))
# признаки для пяти
print("Первые пять строк массива data:\n{}".format(iris_dataset['data'][:5]))
# target содержит сорта уже измеренных цветов
print("Тип массива target: {}".format(type(iris_dataset['target'])))
print("Форма массива target: {}".format(iris_dataset['target'].shape))
# сорта кодируются как числа от 0 до 2
print("Ответы:\n{}".format(iris_dataset['target']))
from sklearn.model_selection import train_test_split
# функция перемешивает набор данных и разбивает на две части
# X - данные, y - метки
# X_train - 75% набора
#X_test - 25%
X_train, X_test, y_train, y_test = train_test_split(
iris_dataset['data'], iris_dataset['target'], random_state=0)
print("форма массива X_train: {}".format(X_train.shape))
print("форма массива y_train: {}".format(y_train.shape))
print("форма массива X_test: {}".format(X_test.shape))
print("форма массива y_test: {}".format(y_test.shape))
iris_dataframe = pds.DataFrame(X_train, columns=iris_dataset.feature_names)
# матрица диаграмм рассеяния
# на экране 2 измерения(мб 3)
# чтобы всё вместить на график используется матрица
from pandas.plotting import scatter_matrix
# NumPy преобразовать в DataFrame
# scatter_matrix - создает парные диаграммы рассеивания
# по диагонали - гистограммы
grr = scatter_matrix(iris_dataframe, c=y_train, figsize=(15, 15), marker='o',
 hist_kwds={'bins': 20}, s=60, alpha=.8, cmap=mglearn.cm3)
plt.show()