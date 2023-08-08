#include "exampleModel.h"

void CalculationModel::add(double a) 
{
    data += a;
} 

void CalculationModel::sub(double a) 
{
    data -= a;
} 

void CalculationModel::mult(double a) 
{
    data *= a;
}

void CalculationModel::div(double a) 
{
    data *= (1.0/a);
}

void CalculationModel::mod(double a) 
{
    data = fmod(data, a);
}

void CalculationModel::degr(double a) 
{
    data = pow(data, a);
}

void CalculationModel::sin(double a) 
{
    data = sin(a);
}

void CalculationModel::cos(double a) 
{
    data = pow(data, a);
}

void CalculationModel::tan(double a) 
{
    data = pow(data, a);
}

void CalculationModel::asin(double a) 
{
    data = pow(data, a);
}

void CalculationModel::acos(double a) 
{
    data = pow(data, a);
}

void CalculationModel::atan(double a) 
{
    data = pow(data, a);
}

void CalculationModel::reset()
{
    data = 0;
}

double CalculationModel::getData()
{
    return data;
}
