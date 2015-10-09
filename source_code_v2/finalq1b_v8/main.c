//Code modified by Vincent Chiu.  Based on code by professor Kristin Schleich.
//Pendulum with NO Driving force, damping of 10.0.
//duffing oscillator final project

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


void initialise (double *, double *, double *, int *);
void derivatives(double, double *, double *, double);
void euler(double *, double *, int, double, double, double *);
void output( FILE *, double, double, double *, double, double);
void output_damp(FILE *output_file, double, double);
void filenamemaker(FILE *, double);
void runge_kutta_2(double *, double *, int, double, double, double *, void (*)(double, double*, double*));
void runge_kutta_4(double *, double *, int, double , double , double *, void (*)(double, double *, double *));

int main()
{
    printf("Welcome to Chiu Industries.  q1b finding critical damping value vs initial velocity duffing Pendulum Calculator.  NO Driving Force Mode. \n");
    FILE *output_file;
    FILE *output_file_damp;
    //declarations of variables
    int number_of_steps;
    double initial_x, initial_v, final_t, E_initial;
    double h;
    double y[2], dydt[2], yout[2];
    double t;
    double gamma;
    double period_initial = 10.0;
    int printInterval = 10;
    int printCounter = 0;
    double count;
    int negValueFinder = 0;


    initial_v = -50.1;
    int outsidecount;
    output_file_damp = fopen("damping_vi_5.dat", "w");
    for(outsidecount = 0; outsidecount<11; outsidecount++)
    {
        double damp = 10.0;
        printf("\n %d \n", outsidecount);

        //output_damp(output_file_damp, initial_v, damp);
        //output_file = fopen("finalq1a_rk4_vinitial_0pt1_gamma_neg0pt1_v1.dat", "w");

//THIS IS WHRE COUNT USED TO BE BELOW
        gamma = 0.1;
        for(count = 0; count<3000; count++)
        {
            negValueFinder = 0;
            //THIS IS WHERE COUNT USED TO BE ABOVE


//    filenamemaker(output_file, damp);
            double d = damp;
            char somenumber[50];
            sprintf(somenumber,"%2.5f", d);
            char str_output[20]= {0}, str_two[]=".dat";
            strcpy(str_output, "finalq1b_damp_");       // copies "one" into str_output
            strcat(str_output, somenumber);
            strcat(str_output, "_vi_");
            strcat(str_output, ".dat");    //  attaches str_two to str_output
            //printf("The Output string is: %s", str_output);
           // output_file = fopen(str_output, "w");




            t = 0.0;
           // fprintf(output_file, "Damping constant is: \n");
           // fprintf(output_file, "#%12.5E \n", damp);
            //fprintf(output_file, "#%12.10E \n", gamma);

            final_t = period_initial*10.0;
            h = 0.05;
            number_of_steps = final_t/h;
            initial_x = 0.0;
            //initial_v = 0.1;

            assert(number_of_steps >0);
            //initialise position and velocity
            y[0] = initial_x;
            y[1] = initial_v;
            E_initial = 0.5*y[0]*y[0] + 0.5*y[1]*y[1];
            t=0.0;

            //output(output_file, h, t, y, E_initial, initial_v);



            while(t<=final_t)
            {
                derivatives(t,y,dydt, damp);
                //euler(y, dydt, 2, t, h, yout);
                runge_kutta_4(y, dydt, 2, t, h, yout, derivatives);
                y[0]=yout[0];
                y[1]=yout[1];

                if(y[0]<0)
                {
                    negValueFinder++;
                }
                if(printCounter == printInterval)
                {
                   // output(output_file, h, t, y, E_initial, damp);
                    printCounter = 0;
                }
                else {}
                printCounter++;

                t+=h;

            }
            if(negValueFinder==0)
            {
                printf("At value of %lf is critical damping!", damp);
               // fprintf(output_file, "\n At value of %lf is critical damping!", damp);
                 output_damp(output_file_damp, initial_v, damp);
                 break;
                //fclose(output_file);
                //return 0;
            }
            //initial_v = initial_v+1.0;
            damp = damp + 0.01;
            //fclose(output_file);
        }

        initial_v=initial_v+10.0;

    }
     fclose(output_file_damp);




    return 0;


} //end main program

void initialise(double *initial_x, double *initial_v, double *final_t, int *number_of_steps)
{

    printf("Read in from screen the initial position x, initial velocity v, final time and number of steps \n");
    scanf("%lf %lf %lf %d", initial_x, initial_v, final_t, number_of_steps);
    return;

} // end of function initialise


// this function provides the first derivative of y[0] and y[1]; i.e.
// it provides the rhs of the couple first order equations of motion
//for the harmonic oscillator with omega=1

void derivatives(double t, double *y, double *dydt, double damp)
{

    double gamma = 0.2;

    dydt[0] = y[1];

    dydt[1] = -y[0]-gamma*pow(y[0],3)-damp*y[1];// positive gamma
}// end of function derivatives

// This function computes the first derivative with centered algorithm

void euler(double *y, double *dydt, int n, double t, double h, double *yout)
{
    int i;
    for(i=0; i<n; i++)
    {
        yout[i]=y[i] + h*dydt[i];
    }
}  // end of euler integrator

// function to write out the final results

void output(FILE *output_file, double h, double t, double *y, double E_initial, double gamma)
{
    fprintf(output_file, "%12.5E \t %12.10E \t %12.10E \t %12.10E \t %12.10E \t %12.10E \n", h, t, y[0], y[1], 0.5*y[0]*y[0]+0.5*y[1]*y[1]-E_initial, gamma);
    return;

}//end of function output


void output_damp(FILE *output_file, double initial_v, double damp)
{
    fprintf(output_file, "%12.10E \t %12.10E \n", initial_v, damp);
    return;

}//end of function output

void filenamemaker(FILE *output_file, double damp)
{

    double d = damp;
    char somenumber[50];
    sprintf(somenumber,"%2.5f", d);
    char str_output[20]= {0}, str_two[]=".dat";
    strcpy(str_output, "finalq1b_damp_");       // copies "one" into str_output
    strcat(str_output, somenumber);
    strcat(str_output, "_vi_");
    strcat(str_output, ".dat");    //  attaches str_two to str_output
    printf("The Output string is: %s", str_output);
    output_file = fopen(str_output, "w");


}//end of function output



void runge_kutta_2(double *y, double *dydt, int n, double x, double h, double *yout, void (*derivatives)(double, double*, double *))
{

    int i;
    double xh;
    double *dyt, *yt;
    // allocate space for local vectors
    dyt = (double *)malloc(n*sizeof(double));
    yt = (double *)malloc(n*sizeof(double));
    xh = x+h/2.0;
    for (i=0; i<n; i++)
    {
        yt[i] = y[i]+h/2.0*dydt[i];
    }

//computation of y_t+1/2h = yt +h/2 dy/dt using k1 = h dy/dt
    (*derivatives)(xh,yt,dyt);
// find k2 which is h* dyt

    for(i=0; i<n; i++)
    {
        yout[i] = y[i] +h*dyt[i];
    }// increment yout using yout = y+h k2
    free(dyt);
    free(yt);

}//end of function runge katta 2




void runge_kutta_4(double *y, double *dydx, int n, double x, double h, double *yout, void (*derivatives)(double, double *, double *))
{
    int i;
    double      xh,hh,h6;
    double *dym, *dyt, *yt;
    //   allocate space for local vectors
    dym = (double *) malloc(n*sizeof(double));
    dyt =  (double *) malloc(n*sizeof(double));
    yt =  (double *) malloc(n*sizeof(double));
    hh = h*0.5;
    h6 = h/6.;
    xh = x+hh;
    for (i = 0; i < n; i++)
    {
        yt[i] = y[i]+hh*dydx[i];
    }
    (*derivatives)(xh,yt,dyt);     // computation of k2, eq. 3.60
    for (i = 0; i < n; i++)
    {
        yt[i] = y[i]+hh*dyt[i];
    }
    (*derivatives)(xh,yt,dym); //  computation of k3, eq. 3.61
    for (i=0; i < n; i++)
    {
        yt[i] = y[i]+h*dym[i];
        dym[i] += dyt[i];
    }
    (*derivatives)(x+h,yt,dyt);    // computation of k4, eq. 3.62
    //      now we upgrade y in the array yout
    for (i = 0; i < n; i++)
    {
        yout[i] = y[i]+h6*(dydx[i]+dyt[i]+2.0*dym[i]);
    }
    free(dym);
    free(dyt);
    free(yt);
}       //  end of function Runge-kutta 4




