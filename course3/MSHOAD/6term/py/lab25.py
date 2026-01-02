import numpy as np
import matplotlib.pyplot as plt
import mglearn
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
from sklearn.datasets import make_moons, load_breast_cancer

print("-------------------- ЗАДАНИЕ 1: RandomForest на make_moons --------------------")
# игрушечный датасет make_moons()
X, y = make_moons(n_samples=100, noise=0.25, random_state=3)
X_train, X_test, y_train, y_test = train_test_split(X, y, stratify=y, random_state=42)

# рандомный лес - 5 деревьев
forest = RandomForestClassifier(n_estimators=5, random_state=2)
forest.fit(X_train, y_train)

fig, axes = plt.subplots(2, 3, figsize=(20, 10))
for i, (ax, tree) in enumerate(zip(axes.ravel(), forest.estimators_)):
    ax.set_title(f"Дерево {i}")
    mglearn.plots.plot_tree_partition(X_train, y_train, tree, ax=ax)

mglearn.plots.plot_2d_separator(forest, X_train, fill=True, ax=axes[-1, -1], alpha=0.4)
axes[-1, -1].set_title("Случайный лес")
mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train, ax=axes[-1, -1])
plt.tight_layout()
plt.show()

# отдельные деревья - шумные
# лес - норм кент, плавный ровный

print("-------------------- ЗАДАНИЕ 2: RandomForest на Breast Cancer --------------------")
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, random_state=0
)

forest = RandomForestClassifier(n_estimators=100, random_state=0)
forest.fit(X_train, y_train)

print("Точность (train): {:.3f}".format(forest.score(X_train, y_train)))
print("Точность (test): {:.3f}".format(forest.score(X_test, y_test)))

def plot_feature_importances_cancer(model, title="Важность признаков"):
    n_features = cancer.data.shape[1]
    plt.barh(range(n_features), model.feature_importances_, align='center')
    plt.yticks(np.arange(n_features), cancer.feature_names)
    plt.xlabel("Важность признака")
    plt.ylabel("Признак")
    plt.title(title)
    plt.tight_layout()
    plt.show()

plot_feature_importances_cancer(forest, "RandomForest - Важность признаков")

print("-------------------- ЗАДАНИЕ 3: Gradient Boosting (по умолчанию) --------------------")
# max_depth=3
# learning_rate=0.1
gbrt = GradientBoostingClassifier(random_state=0)
gbrt.fit(X_train, y_train)
print("Точность (train): {:.3f}".format(gbrt.score(X_train, y_train)))
print("Точность (test): {:.3f}".format(gbrt.score(X_test, y_test)))

gbrt = GradientBoostingClassifier(random_state=0, max_depth=1)
gbrt.fit(X_train, y_train)
print("Точность (train): {:.3f}".format(gbrt.score(X_train, y_train)))
print("Точность (test): {:.3f}".format(gbrt.score(X_test, y_test)))

gbrt = GradientBoostingClassifier(random_state=0, learning_rate=0.01)
gbrt.fit(X_train, y_train)
print("Точность (train): {:.3f}".format(gbrt.score(X_train, y_train)))
print("Точность (test): {:.3f}".format(gbrt.score(X_test, y_test)))

# max_depth — насколько "умные" деревья;
# learning_rate — как быстро модель учится;

print("-------------------- ЗАДАНИЕ 4: Gradient Boosting - Важность признаков --------------------")
# градиентный бустинг
gbrt = GradientBoostingClassifier(random_state=0, max_depth=1)
gbrt.fit(X_train, y_train)
plot_feature_importances_cancer(gbrt, "Gradient Boosting - Важность признаков")
