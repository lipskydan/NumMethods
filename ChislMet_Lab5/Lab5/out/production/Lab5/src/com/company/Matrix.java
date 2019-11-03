package com.company;

import java.util.Random;

public class Matrix {

    //////////////// - TYPE OF MATRIX - ////////////////

    public static double[][] randomMatrix(int n)
    {
        Random random = new Random();
        double[][] matrix = new double[n][n];
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                matrix[i][j] = random.nextInt(100) + 1;
            }
        }
        return matrix;
    }

    public static double[][] randomSymMatrix(int n)
    {
        Random random = new Random();
        double[][] matrix = new double[n][n];
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                matrix[i][j] = random.nextInt(21);
            }
        }

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    matrix[i][j] = matrix[j][i];
                }

            }
        }
        return matrix;
    }

    public static double[][] diagonDominMatrix(int n)
    {
        double[][] matrix = randomMatrix(n);
        for(int i = 0; i < n; i++)
        {
            int sum = 0;
            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    sum += Math.abs(matrix[i][j]);
                }
            }
            if(Math.abs(matrix[i][i]) < sum)
            {
                matrix[i][i] += (sum-matrix[i][i]) + 1;
            }
        }
        return matrix;
    }

    public static double[][] diagonDominSymMatrix(int n)
    {
        double[][] matrix = randomSymMatrix(n);
        for(int i = 0; i < n; i++)
        {
            int sum = 0;
            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    sum += Math.abs(matrix[i][j]);
                }
            }
            if(Math.abs(matrix[i][i]) < sum)
            {
                matrix[i][i] += (sum-matrix[i][i]) + 1;
            }
        }

//        for(int i = 0; i < n; i++)
//        {
//            for(int j = 0; j < n; j++)
//            {
//                if(i != j)
//                {
//                    matrix[i][j] = matrix[j][i];
//                }
//
//            }
//        }
        return matrix;
    }

    public static double[][] gilbertMatrix(int n)
    {
        double[][] matrix = new double[n][n];
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                matrix[i][j] = ((double)1/((i+1)+(j+1)-1));
            }
        }
        return matrix;
    }

    /////////////// - Arithmetic operation - ///////////////

    public static double[][] multiplyMatrix(double[][] a, double[][] b, int n)
    {
        double[][] result = new double[n][n];
        for (int i=0; i<n; ++i)
        {
            for (int j=0; j<n; ++j)
            {
                for (int k=0; k<n; ++k)
                {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }

    public static double[][] sumMatrix(double[][] a, double[][] b, int n)
    {
        double[][] result = new double[n][n];
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                result[i][j] = a[i][j] + b[i][j];
            }
        }
        return result;
    }

    public static double[][] multScalMatrix(double k, double[][]matrix, int n)
    {
        double[][] result = new double[n][n];
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                result[i][j] = k * matrix[i][j];
            }
        }
        return result;
    }

    /////////////// - Other - ///////////////

    public static double normaMatrix(double[][] matrix, int n)
    {
        double x, max = 0.0;
        for (int i = 0; i < n; i++)
        {
            double s = 0.0;
            for (int j = 0; j < n; j++)
            {
                x = matrix[i][j];
                s += Math.abs(x);
            }
            if (s > max)
                max = s;
        }

        return max;
    }

    public static double[][] transpose(double[][] matrix, int n)
    {
        double[][] transpose = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                transpose[i][j] = matrix[j][i];
            }
        }
        return transpose;
    }

    public static void printMatrix(double[][] matrix, int n)
    {
        for(int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //System.out.print((Math.round(matrix[i][j]*1000.0)/1000.0) + "  ");
                System.out.print(matrix[i][j] + "  ");
            }
            System.out.println("");
        }
        System.out.println("");
    }

}
