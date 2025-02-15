#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <raylib.h>

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
    /* usleep(usl); */
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

int double_to_color(double value, double minVal, double maxVal){
    double norm = (value - minVal)/(maxVal - minVal);
    return (int)round(norm*255.0);
}

int main(){
    int n_of_zones = 50;
    int size_of_square = 50;
    // Raylib settings
    InitWindow(n_of_zones*size_of_square, 200, "1D heat equation");
    SetTargetFPS(60);
    /*#################################*/
    
    double L = 1.0;
    size_t Nx = n_of_zones;
    double dx = L/Nx;
    double Nt = 50000;
    double dt = 0.01;
    double alpha = 0.01;
    double r = alpha* (dt/pow(dx,2.0));
    double* u = (double*)malloc(n_of_zones*sizeof(double));
    for (int tmp_u = 0; tmp_u < n_of_zones; tmp_u++){
        u[tmp_u] = 0.2;
    }
    u[0] = 0.7;
    u[n_of_zones-1] = 0.2;

    char str[100];

    // Set up 1D boundary conditions
    
    int t_step  = 0;
    while(!WindowShouldClose()){
        take_step(Nx,r,u);
        flushed_print(u, 10000);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int zone = 0; zone < n_of_zones ; zone++){
            DrawRectangle(size_of_square*zone, 50, size_of_square, size_of_square, CLITERAL(Color){255,0,0,double_to_color(u[zone], u[n_of_zones-1],u[0])});
            sprintf(str, "%f.2f", round(u[zone]));
            DrawText(TextFormat("%f",str),size_of_square*(zone/2),25,2,SKYBLUE);
        }
        EndDrawing();
    }
    CloseWindow();
    free(u);
    return 0;

}
