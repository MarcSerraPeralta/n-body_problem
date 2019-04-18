# n-body_problem
Simulation of a dynamic system of N particles under the gravitational force in 3 dimensions. 

## Description of the system

The system of N particles is descrived by a system of N ODEs of second order and N initial conditions of position and speed. 
This system can be converted into 2N ODEs of first order and, assuming that the mass of each particle is constant, the 2 ODEs for each particle is reduced to 

<p align="center">
  <img width="314" height="140" src="https://user-images.githubusercontent.com/43704266/56372067-915eb000-61fe-11e9-8af6-f73e212ad4ec.png">
</p>

where *G* is the gravitational constant (6.67408 × 10^-11 m^3 kg^-1 s^-2), *v_i* and *r_i* are the speed and position vectors of the particle *i*, *m_j* is the mass of the particle *j*, *|a|* is the modulus of vector *a*, and *t* the time coordinate. 

## Nondimensionalization

In order to remove the units and work with values close to 1, the following substitution as been used

<p align="center">
  <img width="571" height="63" src="https://user-images.githubusercontent.com/43704266/56374536-b30e6600-6203-11e9-9048-2ac035ec6c56.png">
</p>

where *alpha* is the cartesian coordinate of a vector (*alpha* = {x, y, z}, p.e. *v_alpha* = {*v_x*, *v_y*, *v_z*}), and *r_A* and *v_A* are the characteristical position and speed of the system (p.e. the position and speed in the aphelion). 
Then, the 2N ODEs system (of 3D vectors) is transformed into a 6N ODEs system (of scalars),

<p align="center">
  <img width="600" height="148" src="https://user-images.githubusercontent.com/43704266/56374439-72aee800-6203-11e9-8983-3893640bba58.png">
</p>

## Runge-Kutta 4

The method used to calculate the evolution of the system is the Runge-Kutta 4 (RK4), which is an iterative and explicit method. For our ODEs system, the method results in 

<p align="center">
  <img width="712" height="359" src="https://user-images.githubusercontent.com/43704266/56374452-79d5f600-6203-11e9-9812-1418122908ca.png">
</p>

using the initial conditions

<p align="center">
  <img width="174" height="39" src="https://user-images.githubusercontent.com/43704266/56374458-7e021380-6203-11e9-91ea-3d1607f86c76.png">
  and 
  <img width="173" height="37" src="https://user-images.githubusercontent.com/43704266/56374460-7fcbd700-6203-11e9-8bb2-5b86f514a4e2.png">
</p>

where the superindex *(n)* refers to the value of the variable in the n-iteration, and *h* is the time separation between two consequent iterations (*h* = *(total time)/(number of iterations)*). 
