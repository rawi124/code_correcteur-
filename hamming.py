import numpy as np


m, k = 4, 3
n = m + 4

M = np.random.randint(m, size=(4))
H = np.array([[1, 0, 0, 1, 0, 1, 1],[0, 1, 0, 1, 1, 1, 0],[0, 0, 1, 0, 1, 1, 1]])
G = np.array([
[1, 1, 0, 1, 0, 0, 0],
[0, 1, 1, 0, 1, 0, 0],
[1, 1, 1, 0, 0, 1, 0],
[1, 0, 1, 0, 0, 0, 1]])

C, C1, C2 = np.zeros(n), np.zeros(n),np.zeros(n)

G1 = np.transpose(G)

C = G1.dot(M)
i = 0
while i < 7 :
    C[i] = C[i] % 2
    i = i + 1
print(C, "\n\n\n\n\n", G1)
