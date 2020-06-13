#include <iostream>
#include <cmath>
using namespace std;
inline double absolute_value(double temp)
{
	double temp_t = (temp>0.0) ? temp : temp*-1;
	return temp_t;
}

double quadretic_exterpolate(double y_l_1,double y_l_2,double y_l_3)
{
	double temp_e = 3*y_l_1 - 3*y_l_2 + y_l_3;
	return temp_e;
}

double function_value(double x,double y)                    /*function f(x,y) is defined here*/
{
    double temp_f= (x+sqrt(x))*sqrt(y);
    return temp_f;
}

double function_derivative(double x,double y)           /*function f'(x,y) with respect to y is defined here*/
{
    double temp_fd= (x+sqrt(x))/(2.0*sqrt(y));
    return temp_fd;
}

double function_yk1(double yk0, double yk1,double xk1, double h)            /*function F(y[k+1]) is defined here*/
{
	double temp_f_yk1 = yk0 - yk1 + h*function_value(xk1,yk1);
	return temp_f_yk1;
}

double function_derivative_yk1(double yk1,double xk1, double h)         /*function F'(y[k+1]) is defined here*/
{
	double temp_fd_yk1 = -1 + h*function_derivative(xk1,yk1);
	return temp_fd_yk1;
}

double find_root_yk1_method(double yk0,double yk1n0,double xk1, double h,double tolerance = 1e-8)	/*yk1n0 being the initial guess*/
{
	double yk1n1 = yk1n0 - function_yk1(yk0,yk1n0,xk1,h)/function_derivative_yk1(yk1n0,xk1,h);

	if(absolute_value(yk1n1-yk1n0)<=tolerance)
		return yk1n1;
	else
		return find_root_yk1_method(yk0,yk1n1,xk1,h,tolerance);
}

int main()
{
	double x0, y0, h, xn,x,y_c,y_l_1,y_l_2,y_l_3,initial_guess;
    cout << "Enter the value of x[0] : ";
    cin >> x0;
    cout << "Enter the value of y[0] : ";
    cin >> y0;
    cout << "Enter the value of x[n] : ";
    cin >> xn;
    cout << "Enter the step size \"h\" : ";
    cin >> h;
    y_l_1=y0;
    y_l_2=y0;
    y_l_3=y0;
    for(x=x0+h;x<(xn+h);x+=h)
    {
    	initial_guess=quadretic_exterpolate(y_l_1,y_l_2,y_l_3);
    	y_c=find_root_yk1_method(y_l_1,initial_guess,x,h);
    	cout << "At x = " << x << " the initial guess of y is : "<<initial_guess<<endl;
    	cout << "At x = " << x << " the actual value of y is : " << y_c << endl;
    	y_l_3=y_l_2;
    	y_l_2=y_l_1;
    	y_l_1=y_c;
    }
	return 0;
}