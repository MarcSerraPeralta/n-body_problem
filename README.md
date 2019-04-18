# N-Body Gravitational Problem

Simulation of a dynamic system of N particles under the gravitational force in 3 dimensions. 

## Description of the system

The system of N particles is descrived by a system of N ODEs of second order and N initial conditions of position and speed, using 2nd Newton's Law and Newton's law of universal gravitation. 
This system can be converted into 2N ODEs of first order and, assuming that the mass of each particle is constant, the 2 ODEs for each particle are reduced to 

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

Click [here](n_particles_RK4.cpp) to see the RK4 code. 

## Estimation of errors

The estimation of errors has been done using the conservation of both energy and angular momentum. The error is determined comparing the energy and angular momentum's modulus of the system in the initial and final state or iteration. 

Click [here](check_conservation.py) to see the code for the estimation of errors. 

A part from the errors due to computation, the mathematical model has also its approximations that should be taken into account when analyzing system which are not described by the gravitational law. 

1. TWO PARTICLES COLLIDING. The formulas descrived above do not descrive the effects of two particles colliding as we consider them as points. Once they get very close, the code cannot calculate accurately the next iteration so a jump in the error can be observed (function [PLOT_ERROR](check_conservation.py)).

2. RELATIVISTIC EFFECTS. If one of the particles has a great mass and the other particles get close to it, relativistic effects should be considered. This is the example of [Mercury](https://en.wikipedia.org/wiki/Tests_of_general_relativity#Perihelion_precession_of_Mercury) in the solar system, because it is very close to the Sun. 

## Application: Solar System

The main application of this code is centered in the solar system. Some examples, from simple to complex, are:

- Determine the orbit's variables of the planets (aphelion, perihelion, period...)
- Check the 2nd Law of Kepler
- Determine the mean anomaly of the planets
- Determine if an asteroid is NEO and/or PHO

In this [webpage](https://ssd.jpl.nasa.gov/horizons.cgi#results), you can find the information for the initial conditions. To get the cartesian coordinates of the objects:

1. Click on *change* next to *Ephemeris Type* and select *Vector table*. Finally click on *Use Selection Above*. 
2. Click on *change* next to *Target Body* and select the body from which you want the coordinates. 
3. Click on *change* next to *Coordinate Origin* and search "@0" to select *Solar System Barycenter (SSB)*. 
4. Click on *change* next to *Time span* and select the date from which you want to start the simulation (all data from all bodies should be taken from the same date). 
5. Click on *Generate Ephemeris*
6. Go to the line where your chosen date and X, Y, Z appear. For example, if 2019-Apr-18 is selected:

2458591.500000000 = A.D. **2019-Apr-18 00:00:00.0000 TDB** 

 X =-2.089197670392227E-01 Y = 1.581041484991311E+00 Z = 3.802086917814641E-02
 
 VX=-1.335337752542632E-02 VY=-6.379473197539670E-04 VZ= 3.142747436519678E-04
 
 LT= 9.213328042903418E-03 RG= 1.595238299695790E+00 RR= 1.124040429122816E-03
 
 7. The cartesian coordinates corresponding to the initial conditions in AU and AU/day (units) are the ones next to: X, Y, Z, VX, VY, VZ. 
