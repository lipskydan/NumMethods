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

	double ** generMatrGilbert(int n);
	double ** generMatrDiag(int n);

	void showX(double *x, int n);
	void showMatr();

	void checkRes();

	void sysOut();
	double * gauss(double **a, double *y, int n);

public:
	Gauss();
	~Gauss();
	bool Continue();
	void run();
};

