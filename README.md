# n-body_problem
Simulation of a dynamic system of N particles under the gravitational force in 3 dimensions. 

## Description of the system

The system of N particles is descrived by a system of N ODEs of second order and N initial conditions of position and speed. 
This system can be converted into 2N ODEs of first order and, assuming that the mass of each particle is constant, the 2 ODEs for each particle is reduced to 

<p align="center">
  <img width="314" height="140" src="https://user-images.githubusercontent.com/43704266/56372067-915eb000-61fe-11e9-8af6-f73e212ad4ec.png">
</p>

where *G* is the gravitational constant (6.67408 × 10^-11 m^3 kg^-1 s^-2), *v_i* and *r_i* are the speed and position vectors of the particle *i*, *m_j* is the mass of the particle *j*, *|a|* is the modulus of vector *a*, and *t* the time coordinate. 
