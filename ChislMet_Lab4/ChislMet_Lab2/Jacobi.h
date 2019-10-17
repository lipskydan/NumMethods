#pragma once
class Jacobi
{
private:
	double **a, *y, *x;
	int n;

public:
	Jacobi();
	~Jacobi();
	bool Continue();
	void run();

	

private:
	double ** generMatr(int n);
	double * generY(int n);

	double * generYRand(int n);
	double ** generMatrDiag(int n);

	void showX(double *x, int n);
	void showMatr();

	void checkRes();

	void sysOut(double **a, double *y, int n);

	double * jacobi(double **a, double *y, int n);
};

