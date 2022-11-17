import numpy as np
from math import pi, sin, cos, tanh
import matplotlib.pyplot as plt
from scipy.optimize import minimize, Bounds
import scipy

def a_1(X):
    return np.tanh(X)

def a_2(X):
    return X

def nn_output(x_0, w):
    z_1 = [w[k] * x_0 + w[k+5] for k in range(5)]
    y_1 = [a_1(z_1[k]) for k in range(5)]
    z_2 = w[15] + sum([w[k+10] * y_1[k] for k in range(5)])
    y_2 = a_2(z_2)
    return y_2

def y(x):
    return 2 * ((sin(pi/2 * (x+1)))**4 + 1/4*(sin(pi/2 * (1 - abs(cos(pi/4*(x+1))))**4))**4) - 1


def mse(w):
    X_in = np.arange(-1, 1.01, 0.02)
    s = sum([(nn_output(x_in, w) - y(x_in)) ** 2 for x_in in X_in]) / len(X_in)
    return s


w = np.random.uniform(low=-5, high=5, size=(16,))
err = 1
while err > 1e-4:
    result = minimize(mse, w, method='Nelder-Mead', tol=1e-6, bounds=Bounds(-5, 5))
    w, err = result.x, result.fun
    # print(err)

plt.figure()
plot_x = np.arange(-1, 1, 0.02)
plot_y = [y(x) for x in plot_x]
plt.plot(plot_x, plot_y, label=f"Y")

plot_nn = [nn_output(x, w) for x in plot_x]
plt.plot(plot_x, plot_nn, label=f"NN")
plt.legend()
plt.show()

output_w = [ '%.15f' % el for el in w ]
print("(",end='')
print(*output_w,sep=',',end='')
print(")")
print('MSE = ' + str(err))