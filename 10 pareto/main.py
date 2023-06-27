import matplotlib.pyplot as plt

plt.figure()
plt.xlabel('H')
plt.ylabel('R')

x, y = [], []
try:
    while True:
        x += [float(input())]
        y += [float(input())]
except ValueError:
    pass
plt.plot(x, y,  color='blue', linestyle="", marker=".", markersize=.7)

x, y = [], []
try:
    while True:
        x += [float(input())]
        y += [float(input())]
except EOFError:
    pass

plt.plot(x, y,  color='red', linestyle="", marker=".", markersize=.7)
plt.savefig('plot.png', dpi=300)

