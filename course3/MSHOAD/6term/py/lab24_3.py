from sklearn.tree import DecisionTreeClassifier
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split

# обучаем дерево на кансере молочной железы
# сравниваем деревья с разной глубиной

cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, stratify=cancer.target, random_state=42)

tree = DecisionTreeClassifier(random_state=0)
tree.fit(X_train, y_train)

print("Точность на обучающем наборе: {:.3f}".format(tree.score(X_train, y_train)))
print("Точность на тестовом наборе: {:.3f}".format(tree.score(X_test, y_test)))

# тут срезаем лишнее, убираем шум, лучше для новых данных

tree = DecisionTreeClassifier(max_depth=4, random_state=0)
tree.fit(X_train, y_train)

print("Точность на обучающем наборе: {:.3f}".format(tree.score(X_train, y_train)))
print("Точность на тестовом наборе: {:.3f}".format(tree.score(X_test, y_test)))
