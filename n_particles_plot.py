# -*- coding: utf-8 -*-
"""
N PARTICLES PLOT

Plots the trajectory of all the particles in the file "results_R.txt".

"""

import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt


data=np.loadtxt("results_R.txt",unpack=True)

mpl.rcParams['legend.fontsize'] = 8

fig = plt.figure()
ax1 = fig.gca(projection='3d')
ax1.set_xlabel('X axis')
ax1.set_ylabel('Y axis')
ax1.set_zlabel('Z axis')

for i in range(int(len(data)/3)):
    ax1.plot(data[3*i], data[3*i+1], data[3*i+2], label=str(i))

plt.legend()
plt.show()
