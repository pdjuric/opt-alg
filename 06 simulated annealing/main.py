import ctypes
import time

import matplotlib.pyplot as plt
import struct
import os
import sys

# only for MacOS

# from ctypes import CDLL
# system('mkdir output')
# system('g++ -c -o ./output/IOA_6.txt.o IOA_6.txt.cpp')
# system('cd output')
# system('g++ -shared -o ./IOA_6.txt.so IOA_6.txt.o')
#
# libPath = '/Users/pavle/Library/Mobile Documents/com~apple~CloudDocs/in progress/IOA1_domaci/output/IOA_6.txt.cpp.o'
# lib = CDLL(libPath)
#
# calc = lib.solve
# calc.restype = ctypes.POINTER(ctypes.c_int)
# calc.argtypes = [ctypes.c_int, ctypes.Array(ctypes.POINTER(ctypes.c_char))]
# res = calc(array_type(*taskNumbers))

ITER_NUM = 100000
REANNEAL_NUM = 10
THREAD_NUM = 20


def readInts(filename):
    arr = []
    with open(filename, mode="rb") as f:
        while True:
            x = f.read(4)
            if len(x) == 0:
                break
            y = f.read(4)
            arr.append([int.from_bytes(x, "little"), int.from_bytes(y, "little")])
    return arr


def get_all_points(arr):
    y = []
    curr_x = 0
    old_it, old_cost = None, None
    for it, cost in arr:
        while old_it is not None and curr_x < it:
            y.append(old_cost)
            curr_x += 1

        old_it, old_cost = it, cost

    while curr_x < ITER_NUM:
        y.append(old_cost)
        curr_x += 1

    return y


output_dir = input()
ITER_NUM, REANNEAL_NUM, THREAD_NUM = int(input()), int(input()), int(input())


# fig = plt.figure(figsize=(12, 20))
# left = fig.add_subplot(121)
# right = fig.add_subplot(122)

plt.figure(figsize=(19, 6))
fig0 = plt.subplot2grid((1, 2), (0, 0))
fig1 = plt.subplot2grid((1, 2), (0, 1))

x = range(0, ITER_NUM)
ys = []
lines = []
for iteration in range(THREAD_NUM):
    elided_y = readInts(os.path.join(output_dir, "plot_points_" + str(iteration) + ".dat"))
    y = get_all_points(elided_y)
    lines.append(fig0.loglog(x, y)[0])
    ys.append(y)


# arr = readInts(os.path.join(output_dir, "plot_points_avg.dat"))
# plot(arr)
# plt.show()

avg = []
for i in range(ITER_NUM):
    avg.append(sum([ys[j][i] for j in range(THREAD_NUM)]) / THREAD_NUM)

x = [i for i in range(0, ITER_NUM)]
fig1.loglog(x, avg)

fig0.legend(lines, ['iter' + str(i) for i in range(ITER_NUM)], bbox_to_anchor=(-.22, .5), loc='center left')
plt.show()