import java.util.concurrent.TimeUnit;

public class Methods {
    public static double[] methodGaussa(double[][] matrix, int n, double[] b)
    {
        for(int p =0; p < n; p++)
        {
            int max = p;
            for(int i = p+1; i < n; i++)
            {
                if(Math.abs(matrix[i][p]) > Math.abs(matrix[max][p]))
                {
                    max = i;
                }
            }

            double[] temp = matrix[p];
            matrix[p] = matrix[max];
            matrix[max] = temp;

            double t = b[p];
            b[p] = b[max];
            b[max] = t;

            if(Math.abs(matrix[p][p]) <= 1e-10)
            {
                System.out.println("No");
            }

            for(int i = p+1; i < n; i++)
            {
                double alpha = matrix[i][p] / matrix[p][p];
                b[i] -= alpha* b[p];
                for (int j = p; j < n; j++)
                {
                    matrix[i][j] -= alpha * matrix[p][j];
                }
            }
        }

        double[] result = new double[n];
        for(int i = n -1; i >= 0; i--)
        {
            double sum = 0;
            for(int j = i + 1; j < n; j++)
            {
                sum += matrix[i][j] * result[j];
            }
            result[i] = (b[i] - sum) / matrix[i][i];
        }

        return result;
    }

    public static double[] methodGaussaUtoch(double[][] matrix, int n, double[] b)
    {
        double[] x0 = methodGaussa(matrix, n, b);
//        for(int i = 0; i < n; i++)
//        {
//            x0[i] = i+0.95;
//        }

        VectorGeneration.printVector(x0, n);

        double[] eps = new double[n];
        double[] delta = new double[n];
        double[] Ax0 = VectorGeneration.multMatrixVector(matrix, x0, n);

        for(int i = 0; i < n; i++)
        {
            eps[i] = b[i] - Ax0[i];
        }

        delta = methodGaussa(matrix, n, eps);
        System.out.println("delta = ");
        VectorGeneration.printVector(delta, n);
        double[] res = new double[n];
        for(int i = 0; i < n; i++)
        {
            res[i] = x0[i] + delta[i];
        }

        return res;
    }

    public static double[] methodLU(double[][] matrix, int n, double[] b)
    {
        double[][] U = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            U[i] = matrix[i].clone();
        }

        double[][] L = new double[n][n];

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                L[i][j] = 0;
            }
        }

        for(int i = 0; i < n; i++)
        {
            for(int j = i; j < n; j++)
            {
                L[j][i] = U[j][i] / U[i][i];
            }
        }

        for(int k = 1; k < n; k++)
        {
            for(int i = k-1; i < n; i++)
            {
                for(int j = i; j < n; j++)
                {
                    L[j][i] = U[j][i]/U[i][i];
                }
            }

            for(int i = k; i < n; i++)
            {
                for(int j = k-1; j < n; j++)
                {
                    U[i][j] = U[i][j]-L[i][k-1]*U[k-1][j];
                }
            }
        }

        System.out.println("L = ");
        MatrixGeneration.printMatrix(L, n);
        System.out.println("U = ");
        MatrixGeneration.printMatrix(U, n);

        System.out.println("L*U = ");
        double[][] LU = VectorGeneration.multMatrixs(L,U,n);
        MatrixGeneration.printMatrix(LU, n);

        VectorGeneration.CompareMatrixs(matrix,LU,n);

        double[] y = new double[n];
        double[] x = new double[n];

        for(int i = 0; i < n; i++)
        {
            double sum = 0;
            for(int j = 0; j < n; j++)
            {
                sum += L[i][j] * y[j];
            }
            y[i] = (b[i] - sum) / L[i][i];
        }
        for(int i = n-1; i >= 0; i--)
        {
            double sum = 0;
            for(int j = i + 1; j < n; j++)
            {
                sum += U[i][j] * x[j];
            }
            x[i] = (y[i] - sum) / U[i][i];
        }

        return x;
    }

    public static double[] methodJacobiMatrix(double[][] A, int n, double[] b)
    {
        double eps = 0.0001;
        double[][] C = new double[n][n];
        double[][] D = new double[n][n];
        double[][] R = new double[n][n];

        double[] x0 = new double[n];

        for(int i = 0; i < n; i++)
        {
            x0[i] = 0;
        }

        //x0 = VectorGeneration.generateVector(n);

        for(int i = 0; i < n; i++)
        {
            D[i][i] = A[i][i];
            for(int j = 0; j < n; j++)
            {
                if(i < j)
                {
                    R[i][j] = A[i][j];
                }
                else if(i > j)
                {
                    C[i][j] = A[i][j];
                }
            }
        }

        double[][] B = MatrixGeneration.multiplyMatrix(MatrixGeneration.multScalMatrix(-1, InvertMatrix.invert(D), n), MatrixGeneration.sumMatrix(C, R, n), n);
        double normaB = MatrixGeneration.normaMatrix(B, n);
        System.out.println("B = ");
        MatrixGeneration.printMatrix(B, n);

        if(normaB > 1)
        {
            //System.out.println("Sufficient condition of Jacobi is not working");
            return x0;
        }
        //System.out.println("The norm of the matrix = " + normaB + " < 0");

        double[] x1 = VectorGeneration.sumVector(VectorGeneration.multMatrixVector(B, x0, n), VectorGeneration.multMatrixVector(InvertMatrix.invert(D), b, n), n);

        double error = 0;
        for(int i = 0; i < n; i++)
        {
            error += Math.abs(x1[i]-x0[i]);
        }
        while(error > eps)
        {
            error = 0;
            x0 = x1;
            x1 = VectorGeneration.sumVector(VectorGeneration.multMatrixVector(B, x0, n), VectorGeneration.multMatrixVector(InvertMatrix.invert(D), b, n), n);
            for(int i = 0; i < n; i++)
            {
                error += Math.abs(x1[i]-x0[i]);
            }
        }

        return x1;
    }

    public static double[] methodZeidelyaMatrix(double[][] A, int n, double[] b)
    {
        double eps = 0.00001;
        double[][] C = new double[n][n];
        double[][] D = new double[n][n];
        double[][] R = new double[n][n];

        double[] x0 = new double[n];
        for(int i = 0; i < n; i++)
        {
            x0[i] = 0;
        }

        for(int i = 0; i < n; i++)
        {
            D[i][i] = A[i][i];
            for(int j = 0; j < n; j++)
            {
                if(i < j)
                {
                    R[i][j] = A[i][j];
                }
                else if(i > j)
                {
                    C[i][j] = A[i][j];
                }
            }
        }

        double[][] B = MatrixGeneration.multiplyMatrix(InvertMatrix.invert(MatrixGeneration.sumMatrix(C, D, n)), R, n);
        double normaB = MatrixGeneration.normaMatrix(B, n);
        System.out.println("B = ");
        MatrixGeneration.printMatrix(B, n);

        if(normaB > 1)
        {
            //System.out.println("Sufficient condition of Jacobi is not working");
            return x0;
        }
        //System.out.println("The norm of the matrix = " + normaB + " < 0");

        double[] x1 = VectorGeneration.multMatrixVector(InvertMatrix.invert(MatrixGeneration.sumMatrix(C, D, n)),
                VectorGeneration.sumVector(b, VectorGeneration.multScalVector(-1,
                        VectorGeneration.multMatrixVector(R, x0, n), n), n), n);
        double error = 0;
        for(int i = 0; i < n; i++)
        {
            error += Math.abs(x1[i]-x0[i]);
        }
        while(error > eps)
        {
            error = 0;
            x0 = x1;
            x1 = VectorGeneration.multMatrixVector(InvertMatrix.invert(MatrixGeneration.sumMatrix(C, D, n)),
                    VectorGeneration.sumVector(b, VectorGeneration.multScalVector(-1,
                            VectorGeneration.multMatrixVector(R, x0, n), n), n), n);
            for(int i = 0; i < n; i++)
            {
                error += Math.abs(x1[i]-x0[i]);
            }
        }

        return x1;
    }

    public static void printResult(double[] x, int n)
    {
        System.out.println("x = ");
        for(int i = 0; i < n; i++)
        {
            System.out.println(x[i]);
        }
        System.out.println("");
    }

    public static void CheckX(double[] b, double[] x, double[][] A, int n, String str) throws InterruptedException {
        System.out.println("Checking  ......  " + str);
        double[] tmp = new double[n];
        tmp = VectorGeneration.multMatrixVector(A,x,n);

        System.out.println("b' = ");
        for(int i = 0; i < n; i++)
        {
            System.out.println(tmp[i]);
        }
        System.out.println("");

        System.out.print("Was checked ");
        int timeCheck = 5;
        while(timeCheck > 0){
            TimeUnit.MILLISECONDS.sleep(250);
            System.out.print(".");
            timeCheck--;
        }
        TimeUnit.MILLISECONDS.sleep(250);

        for(int i=0; i<n; i++) {
                if (tmp[i] >= b[i] + 0.1){
                    System.out.println(" wrong result");
                    return;
                }
        }

        System.out.println(" successfully");
    }

}


