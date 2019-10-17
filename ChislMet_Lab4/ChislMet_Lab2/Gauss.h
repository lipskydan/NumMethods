#pragma once
class Gauss
{
private:
	double **A, *b, *x;

	double **L, **U, *y1, *x1;

	int n;

private:
	double ** generMatr(int n);
	double * generB(int n);

	double ** generMatrRand(int n);
	double * generBRand(int n);

	double ** generMatrGilbert(int n);
	double ** generMatrDiag(int n);

	void showX(double *x, int n);
	void showMatr();

	void checkRes();

	void sysOut();

	double * gauss(double **a, double *y, int n);

	double ** generL(int n);
	double ** generU(int n);

	void showMatrUL(double ** a);

	void run_usual();
	void run_modify();

public:
	Gauss();
	~Gauss();
	bool Continue();
	void run();
};

