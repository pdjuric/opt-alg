
# Write the function that calculates the value of antenna radiation function Fₛ
# Plot the |Fₛ| for n = 5, β = 20π 1/m, θ = π/4 and d = 1/20 m for at least 100 values of δ ∈ [0, 2π]
# Implement Brant's method (quadratic interpolation), and find the maximum of |Fₛ| for aforementioned parameters (ε=1e-7)

import math
import cmath
import matplotlib.pyplot as plt
import numpy as np

def F(delta):
    phi = delta + beta * d * math.cos(theta)
    f = 0.
    for k in range(0, n):
        f += cmath.exp(-1j * k * phi)
    return abs(f)


def Brant(x, iteration):
    matX = np.array([[xi**2, xi, 1] for xi in x])
    matY = np.array([ [F(delta)] for delta in x ])
    matK = np.matmul(np.linalg.inv(matX), matY)
    a, b, c = np.transpose(matK)[0]

    x.append( -b / (2 * a))

    opt_f_vals = [F(delta) for delta in x]
    idx = np.argmin(opt_f_vals)
    del x[idx]
    del opt_f_vals[idx]

    plot_x = np.linspace(3.1, 5, 30)
    plot_y = [a * t**2 + b * t + c for t in plot_x]
    plt.plot(plot_x, plot_y, label=f"F{iteration}")
    idx = np.argmax(opt_f_vals)
    return x, x[idx], opt_f_vals[idx]



n = 5
beta = 20 * math.pi
theta = math.pi/4
d = 1/20
x = np.linspace(0, 2 * math.pi , 110)

y = [F(delta) for delta in x]
plt.figure()
plt.plot(x, y, label='|Fₛ|')
plt.xlabel('delta')
plt.ylabel('F')

iteration = 1
x = [3, 4, 5]
x, curr_x, prev_max = Brant(x, iteration)
curr_max = 0
while True:
    iteration += 1
    x, curr_x, curr_max = Brant(x, iteration)
    if abs(curr_max - prev_max) < 1e-7:
        break
    prev_max = curr_max

plt.legend(loc="upper left")
plt.show()

print("max |Fₛ|: " + str(curr_max))
print("x: " + str(curr_x))