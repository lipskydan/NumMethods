package com.company;
import javax.swing.*;
import java.util.ArrayList;
import java.util.Scanner;

public class MethodKachmage {

    public static double[] methodKachmage(double[][] A, int n, double[] b)
    {
        double eps = 0.0000001;
        double[] u0 = new double[n];
        double[] normaA = new double[n];
        ArrayList<Double> f = new ArrayList<Double>();
        ArrayList<Double> g = new ArrayList<Double>();
        for(int i = 0; i < n; i++)
        {
            u0[i] = 0;
            normaA[i] = Vector.normaVect(A[i], n);
        }
        int j, l = 0;

        double[] u1 = Vector.sumVector(u0, Vector.multScalVector((b[0] - Vector.multVector(A[0], u0, n)) / (normaA[0] * normaA[0]), A[0], n), n);

        for (int k = 1; k < Integer.MAX_VALUE; k++)
        {
            if (n == 2)
            {
                f.add(u1[0]);
                g.add(u1[1]);

                System.out.println("Y = " + u1[1] + ", X = " + u1[0]);
            }


            l++;
            j = (k % n);
            u0 = u1;
            u1 = Vector.sumVector(u0, Vector.multScalVector((b[j] - Vector.multVector(A[j], u0, n)) / (normaA[j] * normaA[j]), A[j], n), n);
            if(Math.abs(Vector.normaVect(u1, n) - Vector.normaVect(u0, n)) < eps)
            {
                break;
            }
        }

        double[] x = new double[f.size()];
        double[] y = new double[f.size()];
        for (int i = 0; i < f.size(); i++)
        {
            x[i] = f.get(i);
            y[i] = g.get(i);
        }

        if(n == 2)
        {
            SwingUtilities.invokeLater(() -> {
                Grafics ex = new Grafics(x, y, f.size());
                ex.setVisible(true);
            });
        }

        return u1;
    }

    public static double[][] chooseMatrix(int n)
    {
        double[][] matrix = new double[n][n];

        System.out.println("\nType of matrix:\n  1. random \n  2. diagonal domination \n" +
                "  3. symmetrical \n  4. symmetrical & diagonal domination\n  5. gilbert \n");

        Scanner in = new Scanner(System.in);
        System.out.print("Input type of matrix: "); int numType = in.nextInt();

        switch (numType){
            case 1:
                matrix = Matrix.randomMatrix(n);
                break;

            case 2:
                matrix = Matrix.diagonDominMatrix(n);
                break;

            case 3:
                matrix = Matrix.randomSymMatrix(n);
                break;

            case 4:
                matrix = Matrix.diagonDominSymMatrix(n);
                break;

            case 5:
                matrix = Matrix.gilbertMatrix(n);
                break;

            default:
                System.out.println("Unpredictable number :(");
                break;
        }

        return matrix;
    }

    public static void checkAnswer(double[][] A, double[] x, double[] b, int n)
    {
        double[] answer = new double[n];

        answer = MatrixVec.multMatrixVector(A,x,n);

        System.out.println("Compare result: ");
        System.out.println("My Answer <---> Real vector");

        for(int i = 0; i < n; i++)
        {
            System.out.println(answer[i] + " <---> " + b[i]);
        }
        System.out.println("");

    }

    public static void showSys(double[][] A, double[] b, int n)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++) {
                System.out.print(A[i][j] + " * " + "x"+(j+1));
                if (j != n-1) System.out.print(" + ");
            }
            System.out.print(" = " + b[i]);
            if(i != n-1) System.out.println(";");
            else System.out.println(".");
        }
    }
}
