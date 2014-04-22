#include <Python.h>
#include <stdio.h>

// Define things that may want to be changed
#define D 1
#define L 10
#define DX 0.5
#define TMAX 10
#define DT 0.1

int xSize, tSize;

// Creates 2D Array to Represent Function Values
double ** createFunctionArray(double xMax, double dx, double tMax, double dt)
{
	int i;

	int xSize = xMax / dx + 2;
	int tSize = tMax / dt + 2;

	double ** u;

	u = (double **) malloc(xSize * sizeof(double*));

	for (i = 0; i < xSize; i++)
	{
		u[i] = (double *)malloc(tSize * sizeof(double));
	}

	return u;
}

// Make an array for initial conditions
// Should be changed according to IC
double * createICArray()
{
	int i;

	double * ic = (double*)malloc(tSize * sizeof(double));

	// IC Array Filled
	for(i = 0; i < tSize; i++)
	{
		ic[i] = 50;
	}

	return ic;
}

// Make array for boundary conditions
// Should be changed according to BC
double ** createBCArray()
{
	int i;

	double ** bc = (double**)malloc(xSize * sizeof(double*));

	for (i = 0; i < xSize; i++)
	{
		bc[i] = (double *)malloc(2 * sizeof(double));
	}

	// BC Array Filled
	for(i = 0; i < xSize; i++)
	{
		bc[i][0] = 100;
		bc[i][1] = 0;
	}
	return bc;
}

// Fills initial conditions and boundary conditions of function
double ** fillBCIC(double ** u, double * ic, double ** bc)
{
	int x, t;

	// Initial Conditions
	for (t = 1; t < tSize; t++)
	{
		u[0][t] = ic[t];
	}

	// Boundary Conditions
	for (x = 1; x < xSize; x++)
	{
		u[x][0] = bc[x][0];
		u[x][xSize-1] = bc[x][1];
	}

	return u;
}

// Do the actual forward euler calculation
double ** eulerCalculation(double ** u)
{
	int x, t;

	for(x = 2; x < xSize; x++)
	{
		for(t = 2; t < tSize; t++)
		{
			u[x][t+1] = u[x][t] + D/(DX * DX) * (u[x+1][t] - 2*u[x][t] + u[x-1][t]);
		}
	}
}

int main(int argc, char ** argv)
{
		int x, t;
	double ** u = createFunctionArray(L, DX, TMAX, DT);
	double * ic = createICArray();
	double ** bc = createBCArray();

	u = fillBCIC(u, ic, bc);
	u = eulerCalculation(u);

	// Try to print array
	for(x = 0; x < xSize; x++)
	{
		for(t = 0; t < tSize; t++)
		{
			fprintf(stdout, "%f\t", u[x][t]);
		}
		fprintf(stdout, "\n");
	}

	return 0;
}