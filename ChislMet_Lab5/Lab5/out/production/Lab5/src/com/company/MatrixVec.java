package com.company;

public class MatrixVec {

    public static double[] multMatrixVector(double[][] A, double[] x0, int n)
    {
        double[] x = new double[n];
        for(int i = 0; i < n; i++)
        {
            for(int k = 0; k < n; k++)
            {
                x[i] += A[i][k] * x0[k];
            }
        }
        return x;
    }

}
