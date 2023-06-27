import math
from scipy.optimize import linprog

profit = [10, 8, 6, 9, 18, 20, 15, 17, 15, 16, 13, 17]
A = [
    [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1],
    [5, 0, 0, 0, 6, 0, 0, 0, 13, 0, 0, 0],
    [0, 7, 0, 0, 0, 12, 0, 0, 0, 14, 0, 0],
    [0, 0, 4, 0, 0, 0, 8, 0, 0, 0, 9, 0, ],
    [0, 0, 0, 10, 0, 0, 0, 15, 0, 0, 0, 17]
]

b = [1000, 600, 500, 2880, 2880, 2880, 2880]

res = linprog([-i for i in profit], A_ub=A, b_ub=b, method='simplex')
print(round(abs(res.fun)))
x = [round(x) for x in res.x]

eq = 0
for row in A:
    if sum([row[i] * x[i] for i in range(len(x))]) > b[eq]:
        x = [math.floor(x) for x in res.x]
        break
    eq += 1
print(*x, sep=', ')
