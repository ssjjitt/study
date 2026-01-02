import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets import load_breast_cancer
from sklearn.tree import DecisionTreeClassifier

# берем каждый признак из кансера и смотрим как он ваще влияет на дерево

cancer = load_breast_cancer()
tree = DecisionTreeClassifier(random_state=0).fit(cancer.data, cancer.target)

def plot_feature_importances(model): # автоматически посчитанный вклад каждого признака
    n_features = cancer.data.shape[1]
    plt.barh(range(n_features), model.feature_importances_, align='center')
    plt.yticks(np.arange(n_features), cancer.feature_names)
    plt.xlabel("Важность признака")
    plt.ylabel("Признак")
    plt.tight_layout()
    plt.show()

plot_feature_importances(tree)
