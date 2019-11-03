package com.company;

public class MethodJacobi {

    public static double[] methodJacobi(double[][] A, int n)
    {
        int k = 0, i = 0, j = 0;
        double eps = 0.00001;

        double[][] A1;
        double[][] H = new double[n][n];
        double[][] vectors = new double[n][n];

        while (true)
        {
            k++;
            double max = 0;
            for (int l = 0; l < n; l++)
            {
                for(int p = 0; p < n; p++)
                {
                    if (p > l)
                    {
                        if (Math.abs(A[l][p]) > max)
                        {
                            max = A[l][p];
                            i = l;
                            j = p;
                        }
                    }
                }
            }

            if (max < eps)
            {
                break;
            }

            double fi = 0.5 * Math.atan(2*max/(A[i][i]-A[j][j]));

            for (int l = 0; l < n; l++)
            {
                for(int p = 0; p < n; p++)
                {
                    H[l][p] = 0;
                }
                H[l][l] = 1;
            }

            H[i][i] = Math.cos(fi);
            H[i][j] = -Math.sin(fi);
            H[j][i] = Math.sin(fi);
            H[j][j] = Math.cos(fi);

//            System.out.println("    H" + k + " = ");
//            Matrix.printMatrix(H, n);

            if(k == 1)
            {
                vectors = H;
            }
            else
            {
                vectors = Matrix.multiplyMatrix(vectors, H, n);
            }

//            System.out.println("    vectors" + k + " = ");
//            Matrix.printMatrix(vectors, n);

            A1 = Matrix.multiplyMatrix(Matrix.multiplyMatrix(Matrix.transpose(H, n), A, n), H, n);
            A = A1;
        }

        double[] vlasniNum = new double[n];
        for (int q = 0; q < n; q++)
        {
            vlasniNum[q] = A[q][q];
        }

        return vlasniNum;
    }

    public static void showEigenvalues(double[] a, int n)
    {
        System.out.println("Eigenvalues: ");
        for(int i = 0; i < n; i++)
        {
            System.out.println("x" + (i+1) + " = " + a[i]);
        }
    }

}
