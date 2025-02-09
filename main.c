#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define WIDTH 50
#define HEIGHT 10

void print_mesh(){
    for (size_t w = 0; w < WIDTH; w++){
        for (size_t h = 0 ; h < HEIGHT; h++){
            printf("%lf ",0.0);
        }
        printf("\n");

    }
}

void print_row(double* my_row){
    for (size_t w = 0; w < WIDTH; w++){
        printf("%lf ",my_row[w]);
    }
    printf("\n");
}


void take_step(size_t Nx, double r, double* u, double* dummy_u){
    for (size_t x = 1; x < Nx-1; x++){ // u[0] and u[WIDTH] are boundary conditions, which are not changed
        dummy_u[x] = u[x] + r * (u[x+1] - 2*u[x]+u[x-1]);
    }
    for (size_t x = 1; x < Nx; x++){
        u[x] = dummy_u[x];
    }
}

int main(){
    double L = 1.0;
    size_t Nx = WIDTH;
    double dx = L/Nx;
    double Nt = 50000;
    double dt = 0.01;
    double alpha = 0.01;
    double r = alpha* (dt/pow(dx,2.0));
    /* printf("%lf %lf %lf\n",dx,dt,r); */
    double* u = (double*)malloc(WIDTH*sizeof(double));
    double* dummy_u = (double*)malloc(WIDTH*sizeof(double));
    u[0] = 0.7;
    u[WIDTH-1] = 0.2;
    dummy_u[0] = 0.7;
    dummy_u[WIDTH-1] = 0.2;
    for (size_t t_step = 0; t_step < Nt ; t_step++){
        take_step(Nx,r,u,dummy_u);
        /*
        system("clear");
        print_row(u);
        fflush(stdout);
        usleep(10000);
        */
    }
    print_row(u);
    free(u);
    return 0;

}
