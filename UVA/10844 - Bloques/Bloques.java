import java.lang.*;
import java.util.Scanner;
import java.math.BigInteger;

public class Main 
{
 
	static int MAX = 900;

	public static void main (String[] args)
	{
		
		BigInteger[][] dp = new BigInteger[MAX+1][MAX+1];
		for(int i = 0; i <= MAX; i++) {
			for(int j = 0; j <= MAX; j++)
				dp[i][j] = BigInteger.ZERO;
		}
		dp[1][1] = BigInteger.ONE;
		for(int i = 2; i <= MAX; i++) {
			for(int j = 1; j <= i; j++) {
				dp[i][j] = dp[i-1][j-1].add(dp[i-1][j].multiply(new BigInteger(new String("" + j))));
			}
		}

		BigInteger[] res = new BigInteger[MAX+1];
		for(int i = 1; i <= MAX; i++) {
			res[i] = BigInteger.ZERO;
			for(int j = 1; j <= i; j++)
				res[i] = res[i].add(dp[i][j]);
		}

		Scanner sc = new Scanner(System.in);
		int i = sc.nextInt();
		while(i != 0) {

			System.out.println(i + ", " + res[i].toString());
			i = sc.nextInt();
		}
	   
	}
}
