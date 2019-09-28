#pragma once
class Seidel
{
private:

	double **a, *y, *x;
	int n;

public:

	Seidel();
	~Seidel();
	bool Continue();
	void run();

private:

	double * generYRand(int n);
	double ** generMatrDiag(int n);

	void showX(double *x, int n);
	void showMatr();

	void checkRes();

	void sysOut(double **a, double *y, int n);

	double * seidel(double **a, double *y, int n);
};
