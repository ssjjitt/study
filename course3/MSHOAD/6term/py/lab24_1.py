import numpy as np

# сколько раз каждый признак появляется для каждого класса

X = np.array([[0, 1, 0, 1], [1, 0, 1, 1], [0, 0, 0, 1], [1, 0, 1, 0]])
y = np.array([0, 1, 0, 1])

counts = {}
for label in np.unique(y):
    counts[label] = X[y == label].sum(axis=0)

print("Частоты признаков:\n{}".format(counts))
