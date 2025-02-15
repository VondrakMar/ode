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

void flushed_print(double* arr_to_print, int usl){ 
    system("clear");
    print_row(arr_to_print);
    fflush(stdout);
    usleep(usl);
}

void take_step(size_t Nx, double r, double* u){
    // u[0] and u[WIDTH] are boundary conditions, which are not changed
    double tmp_prv = u[0];
    for (size_t x = 1; x < Nx-1; x++){
        double tmp_u = u[x] + r * (u[x+1] - 2*u[x]+tmp_prv);
        tmp_prv = u[x];
        u[x] = tmp_u;
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
    double* u = (double*)malloc(WIDTH*sizeof(double));
    u[0] = 0.7;
    u[WIDTH-1] = 0.2;
    for (size_t t_step = 0; t_step < Nt ; t_step++){
        take_step(Nx,r,u);
        flushed_print(u, 10000);
    }
    free(u);
    return 0;

}
