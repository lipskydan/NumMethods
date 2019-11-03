package com.company;

import java.util.Random;

public class Vector {

    public static double[] generateVector(int n)
    {
        double[] vector = new double[n];

        Random random = new Random();
        for(int i = 0; i < n; i++) vector[i] = random.nextInt(100) + 1;
        return vector;
    }

    public static void printVector(double[] vector, int n)
    {
        for(int i = 0; i < n; i++)
        {
            System.out.println(vector[i]);
        }
        System.out.println("");
    }

    public static double[] sumVector(double[] vect1, double[] vect2, int n)
    {
        double[] x = new double[n];
        for(int i = 0; i < n; i++)
        {
            x[i] = vect1[i] + vect2[i];
        }
        return x;
    }

    public static double[] multScalVector(double scalar, double[] vect, int n)
    {
        double[] x = new double[n];
        for(int i = 0; i < n; i++)
        {
            x[i] = vect[i] * scalar;
        }
        return x;
    }

    public static double normaVect(double[] vector, int n)
    {
        double sum = 0;
        for(int i = 0; i < n; i++)
        {
            sum += Math.pow(vector[i], 2);
        }
        return Math.sqrt(sum);
    }

    public static double multVector(double[] v1, double[] v2, int n)
    {
        double res = 0;
        for (int i = 0; i < n; i++)
        {
            res += v1[i] * v2[i];
        }
        return res;
    }

    public static double[] sumScalVector(double scal, double[] vect, int n)
    {
        double[] res = new double[n];
        for (int i = 0; i < n; i++)
        {
            res[i] = scal + vect[i];
        }
        return res;
    }

}
