import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String argv[]) throws IOException, InterruptedException {
        double[][] A = MatrixGeneration.randomMatrix(1);
        double[] b;

        double[] x1;
        double[] x1_1;
        double[] x2;
        double[] x3;
        int n=0;

        Boolean cont = true;

        Scanner scan = new Scanner(System.in);

        while(cont = true){

            System.out.println("1. Gauss\n2. Jacobi\n3. Seidel\n");

            //Scanner scan = new Scanner(System.in);
            System.out.println("Input number: "); int index = scan.nextInt();

            switch(index){
                case 1: // GAUSS
                    System.out.println("Type of matrix:\n 1. Random (LU)\n 2. Diag (LU)\n 3. Gilbert (LU and Utoch)\n");
                    System.out.println("Input number: "); int index1 = scan.nextInt();
                    System.out.println("Input size of matrix: "); n = scan.nextInt();

                    switch(index1){
                        case 1:
                            A = MatrixGeneration.randomMatrix(n);
                            break;
                        case 2:
                            A = MatrixGeneration.diagonDominMatrix(n);
                            break;
                        case 3:
                            A = MatrixGeneration.gilbertMatrix(n);
                            break;
                        default:
                            break;
                    }

                    b = VectorGeneration.generateVector(n);
                    System.out.println("b = ");
                    VectorGeneration.printVector(b, n);

                    System.out.println("A = ");
                    MatrixGeneration.printMatrix(A, n);

                    System.out.println("Solution by LU method: ");
                    x1 = Methods.methodLU(A, n, b);
                    Methods.printResult(x1, n);

                    Methods.CheckX(b,x1,A,n,"LU method");

                    if (index1 == 3){
                        System.out.println("Solution by method Gauss with Utoch: ");
                        x1_1 = Methods.methodGaussaUtoch(A, n, b);
                        Methods.printResult(x1_1, n);

                        Methods.CheckX(b,x1_1,A,n,"method Gauss with Utoch");
                    }

                    break;

                case 2: // Jacobi
                    System.out.println("Type of matrix: Diag ");
                    System.out.println("Input size of matrix: "); n = scan.nextInt();

                    A = MatrixGeneration.diagonDominMatrix(n);
                    System.out.println("A = ");
                    MatrixGeneration.printMatrix(A, n);

                    b = VectorGeneration.generateVector(n);
                    System.out.println("b = ");
                    VectorGeneration.printVector(b, n);

                    x2 = Methods.methodJacobiMatrix(A, n, b);
                    Methods.printResult(x2, n);

                    Methods.CheckX(b,x2,A,n,"method Jacobi");

                    break;

                case 3: // Seidel
                    System.out.println("Type of matrix: Diag ");
                    System.out.println("Input size of matrix: "); n = scan.nextInt();

                    A = MatrixGeneration.diagonDominMatrix(n);
                    System.out.println("A = ");
                    MatrixGeneration.printMatrix(A, n);

                    b = VectorGeneration.generateVector(n);
                    System.out.println("b = ");
                    VectorGeneration.printVector(b, n);

                    x3 = Methods.methodZeidelyaMatrix(A, n, b);
                    Methods.printResult(x3, n);

                    Methods.CheckX(b,x3,A,n,"method Seidel");

                    break;
                default:
                    break;
            }

            System.out.println("Would you like to continue?: (yes / no)");
            String answer = scan.next();
            if (answer.equals("yes") || answer.equals("YES") || answer.equals("Yes")) {
                cont = true;
            } else {
                cont = false;
                return;
            }

        }
    }
}
