package com.company;

import java.util.Scanner;

public class Run {

    public static void run()
    {
        Boolean cont = true;

        while(cont){
            playList();
            cont = contProg();
        }
    }

    private static Boolean contProg()
    {
        Scanner in = new Scanner(System.in);
        String[] posAnswer = {"yes","Yes","YES","y","Y"};

        System.out.print("Would you like to continue?(yes/no)?: ");
        String answer = in.nextLine();

        return (posAnswer[0].equals(answer) || posAnswer[1].equals(answer) || posAnswer[2].equals(answer) || posAnswer[3].equals(answer) || posAnswer[4].equals(answer));
    }

    private static void playList()
    {
        double[][] A;
        double[] x;
        double[] b;

        Scanner in = new Scanner(System.in);

        System.out.print("Input size of matrix: "); int n = in.nextInt();

        System.out.println("1. Kachmage \n2. Jacobi \n");
        System.out.print("Input number:"); int number = in.nextInt();

        switch(number){
            case 1:
                System.out.println("\nMethod Kachmage");

                A = MethodKachmage.chooseMatrix(n);
                b = Vector.generateVector(n);

                x = MethodKachmage.methodKachmage(A, n, b);

                if(n <= 10)
                {
                    System.out.println("A: ");
                    Matrix.printMatrix(A, n);

                    System.out.println("b: ");
                    Vector.printVector(b, n);

                    MethodKachmage.showSys(A,b,n);

                    System.out.println("\nx: ");
                    Vector.printVector(x, n);
                }

                MethodKachmage.checkAnswer(A,x,b,n);
                break;

            case 2:
                System.out.println("\nMethod Jacobi");

                A = Matrix.randomSymMatrix(n);
                x = MethodJacobi.methodJacobi(A, n);

                if( n <= 10)
                {
                    System.out.println("A: ");
                    Matrix.printMatrix(A, n);
                }

                MethodJacobi.showEigenvalues(x,n);
                break;

            default:
                System.out.println("Unpredictable number :(");
                break;
        }

        System.out.println("");
    }
}
