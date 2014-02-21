import java.math.BigInteger;
import java.util.Scanner;

public class BinomialCoefficients {
	public static void main(String args[]) throws Exception {
		Scanner in = new Scanner(System.in);
		int T = in.nextInt();
		while (T-- > 0) {
			BigInteger n = in.nextBigInteger();
			BigInteger p = in.nextBigInteger();
			BigInteger res = n.add(BigInteger.ONE);
			BigInteger tmp = BigInteger.ONE;
			
			while (n.compareTo(BigInteger.ZERO) > 0) {
				tmp = tmp.multiply(n.mod(p).add(BigInteger.ONE));
				n = n.divide(p);
			}
			System.out.println(res.subtract(tmp));
		}
	}
}