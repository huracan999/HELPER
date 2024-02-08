#define _USE_MATH_DEFINES
#include <iostream>
#include <functional>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

double FirstExample(const double& x)
{
	return (1 / (1 + sqrt(2 * x)));
}
double SecondExample(const double& x)
{
	return (exp(x) * sin(x));
}
double ThreeExample(const double& x)
{
	return (1 / (3 + 2 * cos(x)));
}
double LeftRectangle(const double& a, const double& b, const double& eps, vector <function<double(const double&)>> examples)
{
	
	double step, square, h, x = a, square_temp = 0;
	int n = 1, s;
	cout << "Select example 1-3\n";
	cin >> s;
	h = examples[--s](x);
	step = (b - a);
	if (h == 0)
	{
		h = examples[s](a + 0.01);
	}
	square = h * step;
	while (fabs(square-square_temp) >= eps)
	{
		square_temp = square;
		n *= 2;
		step /= n;
		square = h * step;	
	}
	square = 0;
	while (x <= b)
	{
		h = examples[s](x);
		square += (h * step);
		x += step;
	}
	return square;
}
double RightRectangle(const double& a, const double& b, const double& eps, vector <function<double(const double&)>> examples)
{
	double step, square, h, x, square_temp = 0;
	int n = 1, s;
	step = (b - a);
	cout << "Select example 1-3\n";
	cin >> s;
	h = examples[--s](step);
	square = h * step;
	while (fabs(square-square_temp) >= eps)
	{
		square_temp = square;
		n *= 2;
		step /= n;
		square = h * step;
	}
	x = step;
	square = 0;
	while (x <= b)
	{
		h = examples[s](x);
		square += (h * step);
		x += step;
	}
	return square;
}
double MediumRectangle(const double& a, const double& b, const double& eps, vector <function<double(const double&)>> examples)
{
	double step, square, h, x, square_temp = 0;
	int n = 1, s;
	cout << "Select example 1-3\n";
	cin >> s;	
	step = (b - a);
	h = examples[--s](step/2);
	square = h * step;
	while (fabs(square-square_temp) >= eps)
	{
		square_temp = square;
		n *= 2;
		step /= n;
		h = examples[s](step / 2);
		square = h * step;
	}
	x = step / 2;
	square = 0;
	while (x <= b)
	{
		h = examples[s](x);
		square += (h * step);
		x += step;
	}
	return square;
}
double Trapezium(const double& a, const double& b, const double& eps, vector <function<double(const double&)>> examples)
{
	double step, square, h, x = a, square_temp = 0;
	int n = 1, s;
	cout << "Select example 1-3\n";
	cin >> s;
	step = (b - a);
	square = (examples[--s](a) + examples[s](b) / 2) * step;
	while (fabs(square-square_temp) >= eps)
	{
		square_temp = square;
		n *= 2;
		step /= n;
		square = (examples[s](a) + examples[s](step) / 2) * step;
	}
	x = step / 2;
	square = 0;
	while (x <= b)
	{
		h = examples[s](x);
		square += (examples[s](x)+ examples[s](x+step))/2 * step;
		x += step;
	}
	return square;
}
double Simpson(const double& a, const double& b, const double& eps, vector <function<double(const double&)>> examples)
{
	double step, square, h, x = a;
	int n = 1, s;
	double square_temp = 0;
	cout << "Select example 1-3\n";
	cin >> s;	
	step = (b - a);
	square = (examples[--s](a) + examples[s](step) / 2) * step;
	while (fabs(square-square_temp) >= eps)
	{
		square_temp = square;
		n *= 2;
		step = (b - a) / n;
		square = (examples[s](a) + examples[s](step) / 2) * step;
		
	}
	square = 0;
	for (int i = 0; i < n; i++)
	{
		const double x1 = a + i * step;
		const double x2 = a + (i + 1) * step;
		square += (x2 - x1) / 6.0 * (examples[s](x1) + 4.0 * examples[s](0.5 * (x1 + x2)) + examples[s](x2));

	}
	return square;
}
int counterAcc(double eps)
{
	int counter = 0;
	while (eps < 1)
	{
		eps *= 10;
		counter++;
	}
	return counter;
}

int main()
{
	double b, a, square, eps;
	int c, counter;
	vector <function<double(const double&)>> examples = {FirstExample,SecondExample,ThreeExample};
	vector<function<double(const double&, const double&, const double&, vector < function<double(const double&)>>)>> formules = {LeftRectangle,RightRectangle,MediumRectangle,Trapezium,Simpson};
	cout << "Enter the boundaries of the segment [a,b]\n";	
	cin >> a >> b;
	
	if (a > b)
	{
		swap(a, b);
	}
	cout << "Enter the accuracy \n";
	cin >> eps;
	while (eps >= 1 || eps<=0)
	{
		cout << "Error, re-enter the accuracy\n";
		cin >> eps;
	}
	counter = counterAcc(eps);
	cout << "Choose formula 1-5\n";
	cin >> c;
	square = formules[--c](a, b, eps, examples);
	cout.precision(counter);
	std::cout << "Result: " << fixed << square;

	return 0;
}