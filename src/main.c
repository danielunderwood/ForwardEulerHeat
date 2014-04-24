#include <Python.h>
#include <stdio.h>
#include <Math.h>

// Define things that may want to be changed
#define D 1
#define L 10
#define DX 0.5
#define TMAX 100
#define DT 0.01

int xSize = L/DX + 2;
int tSize = TMAX/DT + 2;

// Creates 2D Array to Represent Function Values
double ** createFunctionArray(double xMax, double dx, double tMax, double dt)
{
	int i;

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
	for(i = 0; i < xSize; i++)
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

	double ** bc = (double**)malloc(tSize * sizeof(double*));

	for (i = 0; i < tSize; i++)
	{
		bc[i] = (double *)malloc(2 * sizeof(double));
	}

	// BC Array Filled
	for(i = 0; i < tSize; i++)
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
	for (x = 0; x < xSize-1; x++)
	{
		u[x][0] = ic[x];
	}

	// Boundary Conditions
	for (t = 0; t < tSize-1; t++)
	{
		u[0][t] = bc[t][0];
		u[xSize-2][t] = u[xSize-1][t];
	}

	return u;
}

// Do the actual forward euler calculation
double ** eulerCalculation(double ** u)
{
	int x, t = 0;

	for(t = 0; t < tSize-2; t++)
	{
		for(x = 1; x < xSize-2; x++)
		{
			u[x][t+1] = u[x][t] + D * DT /(DX * DX) * (u[x+1][t] - 2*u[x][t] + u[x-1][t]);
		}
	}
    
    	return u;
}

// Fix BC for Fixed Slope
// TODO: Refactor this into setting BC (Also doesn't seem to work)
double ** fixedSlopeBC(double ** u)
{
    int x;
    
    for(x = 0; x < xSize - 1; x++)
    {
        u[x][1] = u[x][0];
        u[x][xSize-2] = u[x][xSize - 1];
    }
    return u;
}

int main(int argc, char ** argv)
{
    	int x, t = 0;
	FILE * dataFile;
	double ** u = createFunctionArray(L, DX, TMAX, DT);
	double * ic = createICArray();
	double ** bc = createBCArray();

	u = fillBCIC(u, ic, bc);
	u = eulerCalculation(u);
    u = fillBCIC(u, ic, bc);
    //u = fixedSlopeBC(u);
    
	// Try to print array
	dataFile = fopen("data.dat", "w+");
	for(t = 0; t < tSize-1; t++)
	{
		for(x = 0; x < xSize-1; x++)
		{
            fprintf(dataFile, "%.2f\t", u[x][t]);
		}
		fprintf(dataFile, "\n");
	}

	fclose(dataFile);

	return 0;
}
