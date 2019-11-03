import java.util.Random;

public class VectorGeneration {
    public static double[] generateVector(int n)
    {
//        double[] x = new double[n];
        double[] vector = new double[n];
//        for(int i = 0; i < n; i++)
//        {
//            x[i] = i + 1;
//        }
//
//        for(int i = 0; i < n; i++)
//        {
//            for(int k = 0; k < n; k++)
//            {
//                vector[i] += matrix[i][k] * x[k];
//            }
//        }

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

    public static double[][] multMatrixs(double[][] L, double[][] U, int n)
    {
        double[][] res = new double[n][n];

        for (int i=0; i < n; i++){
            for (int j=0; j < n; j++){
                for(int k=0; k<n; k++){
                    res[i][j] += L[i][k] * U[k][j];
                }
            }
        }

        return res;
    }

    public static void CompareMatrixs(double[][] A, double[][] B, int n)
    {

        for (int i=0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(A[i][j] != B[i][j]){
                    System.out.println("CompareMatrixs:: false");
                    return;
                }

            }
        }

        System.out.println("CompareMatrixs:: true");
    }


}
