from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, export_graphviz
import pydotplus

# визуализация дерева и сохранение её в PDF

cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, stratify=cancer.target, random_state=42)

clf = DecisionTreeClassifier(max_depth=4, random_state=0)
clf.fit(X_train, y_train)

dot_data = export_graphviz(clf, out_file=None,
                           feature_names=cancer.feature_names,
                           class_names=cancer.target_names,
                           filled=True, rounded=True,
                           special_characters=True)

graph = pydotplus.graph_from_dot_data(dot_data)
graph.write_pdf("D:/univer/!МСХОАД/py/cancer.pdf")
