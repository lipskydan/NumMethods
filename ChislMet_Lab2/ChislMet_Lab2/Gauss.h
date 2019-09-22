#pragma once
class Gauss
{
private:
	double **a, *y, *x;
	int n;

private:
	double ** generMatr(int n);
	double * generY(int n);

	double ** generMatrRand(int n);
	double * generYRand(int n);

	void showX(double *x, int n);

	void sysOut(double **a, double *y, int n);
	double * gauss(double **a, double *y, int n);

public:
	Gauss();
	~Gauss();
	bool Continue();
	void run();
};

