/*
Runge-Kutta 4 Method to solve the trajectory
of N particles under the gravitational force:
F = GMm/r^2 --(normalized)--> F' = M'm'/r'^2 .

* Initial data: "initial_data.csv" 
The 7 columns correspond to: rx, ry, rz, vx, vy, vz, m.
Each row corresponds to the data of each particle. 

* Final data: "results_R.txt" i "results_v.txt"
Each row corresponds to an instant of time (n-iteration).
The data is separated by blank spaces and correspond to:
rx1, ry1, rz1, ... , rxN, ryN, rzN   ("results_R.txt")
vx1, vy1, vz1, ... , vxN, vyN, vzN   (results_V.txt")
where the order of the particles is the same as "initial_data.csv". 
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 8			// number of particles
#define TF 3.154*25	// total time
#define NT 70000 	// number of iterations in time
#define AT TF/NT

int main(void) {

	//VARIABLES TO READ INITIAL DATA
    FILE *input;
    double read;
    int i;
    double R_n1[3*N]; // rx1, ry1, rz1, ... , rxN, ryN, rzN
    double V_n1[3*N]; // vx1, vy1, vz1, ... , vxN, vyN, vzN
    double M[N];      // m1, ... , mN
	//VARIABLES FOR RK4
    double R_n2[3*N];
    double V_n2[3*N];
    double Ria;
    int n, a;
    double k1R[3*N], k2R[3*N], k3R[3*N], k4R[3*N];
    double k1V[3*N], k2V[3*N], k3V[3*N], k4V[3*N];
	//VARIABLES TO WRTIE THE FINAL DATA
    FILE *outR;
    FILE *outV;
    
	//READ INITIAL DATA
    input = fopen("initial_data.csv", "r");
    for (i = 0; i < N; i++) {
        fscanf(input,"%lf,",&read);
        R_n1[3*i  ] = read;
        fscanf(input,"%lf,",&read);
        R_n1[3*i+1] = read;
        fscanf(input,"%lf,",&read);
        R_n1[3*i+2] = read;
        fscanf(input,"%lf,",&read);
        V_n1[3*i  ] = read;
        fscanf(input,"%lf,",&read);
        V_n1[3*i+1] = read;
        fscanf(input,"%lf,",&read);
        V_n1[3*i+2] = read;
        fscanf(input,"%lf\n",&read);
        M[i] = read;
    }
    fclose(input);

    //CALCULATIONS
    outR = fopen("results_R.txt", "w");
    outV = fopen("results_V.txt", "w");

    //--------------SAVE DATA--------------
    fprintf(outR, "%.10f",R_n1[0]);
    fprintf(outV, "%.10f",V_n1[0]);
    for (i = 1; i < 3*N; i++) {
        fprintf(outR, " %.10f",R_n1[i]);
        fprintf(outV, " %.10f",V_n1[i]);
    }
    fprintf(outR, "\n");
    fprintf(outV, "\n");

    //--------------RK4--------------
    for (n = 1; n < NT + 1; n++) {

        //--------------k1--------------
        for (i = 0; i < 3*N; i++) {
            k1R[i] = AT*V_n1[i];
        }
        for (i = 0; i < N; i++) {
            k1V[3*i  ] = 0; //x
            k1V[3*i+1] = 0; //y
            k1V[3*i+2] = 0; //z
            for (a = 0; a < N; a++) { if (a != i) {
                Ria = sqrt((R_n1[3*a  ] - R_n1[3*i  ])*(R_n1[3*a  ] - R_n1[3*i  ]) + 
                           (R_n1[3*a+1] - R_n1[3*i+1])*(R_n1[3*a+1] - R_n1[3*i+1]) + 
                           (R_n1[3*a+2] - R_n1[3*i+2])*(R_n1[3*a+2] - R_n1[3*i+2]) );
                k1V[3*i  ] += M[a]*(R_n1[3*a  ] - R_n1[3*i  ]) / (Ria*Ria*Ria);
                k1V[3*i+1] += M[a]*(R_n1[3*a+1] - R_n1[3*i+1]) / (Ria*Ria*Ria);
                k1V[3*i+2] += M[a]*(R_n1[3*a+2] - R_n1[3*i+2]) / (Ria*Ria*Ria);
            } }
            k1V[3*i  ] = k1V[3*i  ]*AT; //x
            k1V[3*i+1] = k1V[3*i+1]*AT; //y
            k1V[3*i+2] = k1V[3*i+2]*AT; //z
        }

        //--------------k2--------------
        for (i = 0; i < 3*N; i++) {
            k2R[i] = AT*(V_n1[i] + 0.5*k1V[i]);
        }
        for (i = 0; i < N; i++) {
            k2V[3*i  ] = 0; //x
            k2V[3*i+1] = 0; //y
            k2V[3*i+2] = 0; //z
            for (a = 0; a < N; a++) { if (a != i) {
                Ria = sqrt((R_n1[3*a  ] + 0.5*k1R[3*a  ] - R_n1[3*i  ] - 0.5*k1R[3*i  ])*(R_n1[3*a  ] + 0.5*k1R[3*a  ] - R_n1[3*i  ] - 0.5*k1R[3*i  ]) + 
                           (R_n1[3*a+1] + 0.5*k1R[3*a+1] - R_n1[3*i+1] - 0.5*k1R[3*i+1])*(R_n1[3*a+1] + 0.5*k1R[3*a+1] - R_n1[3*i+1] - 0.5*k1R[3*i+1]) + 
                           (R_n1[3*a+2] + 0.5*k1R[3*a+2] - R_n1[3*i+2] - 0.5*k1R[3*i+2])*(R_n1[3*a+2] + 0.5*k1R[3*a+2] - R_n1[3*i+2] - 0.5*k1R[3*i+2]) );
                k2V[3*i  ] += M[a]*(R_n1[3*a  ] + 0.5*k1R[3*a  ] - R_n1[3*i  ] - 0.5*k1R[3*i  ]) / (Ria*Ria*Ria);
                k2V[3*i+1] += M[a]*(R_n1[3*a+1] + 0.5*k1R[3*a+1] - R_n1[3*i+1] - 0.5*k1R[3*i+1]) / (Ria*Ria*Ria);
                k2V[3*i+2] += M[a]*(R_n1[3*a+2] + 0.5*k1R[3*a+2] - R_n1[3*i+2] - 0.5*k1R[3*i+2]) / (Ria*Ria*Ria);

            } }
            k2V[3*i  ] = k2V[3*i  ]*AT; //x
            k2V[3*i+1] = k2V[3*i+1]*AT; //y
            k2V[3*i+2] = k2V[3*i+2]*AT; //z
        }

        //--------------k3--------------
        for (i = 0; i < 3*N; i++) {
            k3R[i] = AT*(V_n1[i] + 0.5*k2V[i]);
        }
        for (i = 0; i < N; i++) {
            k3V[3*i  ] = 0; //x
            k3V[3*i+1] = 0; //y
            k3V[3*i+2] = 0; //z
            for (a = 0; a < N; a++) { if (a != i) {
                Ria = sqrt((R_n1[3*a  ] + 0.5*k2R[3*a  ] - R_n1[3*i  ] - 0.5*k2R[3*i  ])*(R_n1[3*a  ] + 0.5*k2R[3*a  ] - R_n1[3*i  ] - 0.5*k2R[3*i  ]) + 
                           (R_n1[3*a+1] + 0.5*k2R[3*a+1] - R_n1[3*i+1] - 0.5*k2R[3*i+1])*(R_n1[3*a+1] + 0.5*k2R[3*a+1] - R_n1[3*i+1] - 0.5*k2R[3*i+1]) + 
                           (R_n1[3*a+2] + 0.5*k2R[3*a+2] - R_n1[3*i+2] - 0.5*k2R[3*i+2])*(R_n1[3*a+2] + 0.5*k2R[3*a+2] - R_n1[3*i+2] - 0.5*k2R[3*i+2]) );
                k3V[3*i  ] += M[a]*(R_n1[3*a  ] + 0.5*k2R[3*a  ] - R_n1[3*i  ] - 0.5*k2R[3*i  ]) / (Ria*Ria*Ria);
                k3V[3*i+1] += M[a]*(R_n1[3*a+1] + 0.5*k2R[3*a+1] - R_n1[3*i+1] - 0.5*k2R[3*i+1]) / (Ria*Ria*Ria);
                k3V[3*i+2] += M[a]*(R_n1[3*a+2] + 0.5*k2R[3*a+2] - R_n1[3*i+2] - 0.5*k2R[3*i+2]) / (Ria*Ria*Ria);

            } }
            k3V[3*i  ] = k3V[3*i  ]*AT; //x
            k3V[3*i+1] = k3V[3*i+1]*AT; //y
            k3V[3*i+2] = k3V[3*i+2]*AT; //z
        }

        //--------------k4--------------
        for (i = 0; i < 3*N; i++) {
            k4R[i] = AT*(V_n1[i] + k3V[i]);
        }
        for (i = 0; i < N; i++) {
            k4V[3*i  ] = 0; //x
            k4V[3*i+1] = 0; //y
            k4V[3*i+2] = 0; //z
            for (a = 0; a < N; a++) { if (a != i) {
            	Ria = sqrt((R_n1[3*a  ] + k3R[3*a  ] - R_n1[3*i  ] - k3R[3*i  ])*(R_n1[3*a  ] + k3R[3*a  ] - R_n1[3*i  ] - k3R[3*i  ]) + 
                           (R_n1[3*a+1] + k3R[3*a+1] - R_n1[3*i+1] - k3R[3*i+1])*(R_n1[3*a+1] + k3R[3*a+1] - R_n1[3*i+1] - k3R[3*i+1]) + 
                           (R_n1[3*a+2] + k3R[3*a+2] - R_n1[3*i+2] - k3R[3*i+2])*(R_n1[3*a+2] + k3R[3*a+2] - R_n1[3*i+2] - k3R[3*i+2]) );
                k4V[3*i  ] += M[a]*(R_n1[3*a  ] + k3R[3*a  ] - R_n1[3*i  ] - k3R[3*i  ]) / (Ria*Ria*Ria);
                k4V[3*i+1] += M[a]*(R_n1[3*a+1] + k3R[3*a+1] - R_n1[3*i+1] - k3R[3*i+1]) / (Ria*Ria*Ria);
                k4V[3*i+2] += M[a]*(R_n1[3*a+2] + k3R[3*a+2] - R_n1[3*i+2] - k3R[3*i+2]) / (Ria*Ria*Ria);

            } }
            k4V[3*i  ] = k4V[3*i  ]*AT; //x
            k4V[3*i+1] = k4V[3*i+1]*AT; //y
            k4V[3*i+2] = k4V[3*i+2]*AT; //z
        }

        //--------------R & V--------------
        for (i = 0; i < 3*N; i++) {
            R_n2[i] = R_n1[i] + (k1R[i] + 2*k2R[i] + 2*k3R[i] + k4R[i])/6.;
            V_n2[i] = V_n1[i] + (k1V[i] + 2*k2V[i] + 2*k3V[i] + k4V[i])/6.;
        }

        //--------------SAVE DATA--------------
        fprintf(outR, "%.10f",R_n2[0]);
        fprintf(outV, "%.10f",V_n2[0]);
        for (i = 1; i < 3*N; i++) {
            fprintf(outR, " %.10f",R_n2[i]);
            fprintf(outV, " %.10f",V_n2[i]);
        }
        fprintf(outR, "\n");
        fprintf(outV, "\n");

        //--------------OLD = NEW--------------
        for (i = 0; i < 3*N; i++) {
            R_n1[i] = R_n2[i];
            V_n1[i] = V_n2[i];
        }

    }

    fclose(outR);
    fclose(outV);

	return 0;
}