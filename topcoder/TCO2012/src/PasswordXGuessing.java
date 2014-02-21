// BEGIN CUT HERE

// END CUT HERE
import java.util.*;

public class PasswordXGuessing {
	public long howMany(String[] guesses) {
		long res = 0;
		for (int i = 0; i < guesses.length; i++) {
			for (int j = 0; j < guesses[i].length(); j++) {
				char [] key =  guesses[i].toCharArray();
				for (int k = 0; k < 10; k++) {
					key[j] = (char) ('0' + k);
					if (Judge(guesses,new String(key))){
						res++;
					}
				}
			}
		}
		return res / guesses.length;
	}
	
	private boolean Judge(String[] guesses, String pwd) {		
		for (int i = 0; i < guesses.length; i++) {
			if (diff(guesses[i], pwd) != 1) {
				return false;
			}
		}
		return true;
	}

	private int diff(String string, String pwd) {
		int diff = 0;
		for (int i = 0; i < string.length(); i++) {
			if (string.charAt(i) != pwd.charAt(i)) {
				diff++;
			}
		}
		return diff;
	}

	// BEGIN CUT HERE
	public static void main(String[] args) {
		try {
			eq(0,
					(new PasswordXGuessing())
							.howMany(new String[] { "58", "47" }), 2L);
			eq(1,
					(new PasswordXGuessing()).howMany(new String[] { "539",
							"540", "541" }), 1L);
			eq(2,
					(new PasswordXGuessing()).howMany(new String[] { "12",
							"34", "56", "78" }), 0L);
			eq(3,
					(new PasswordXGuessing()).howMany(new String[] { "2", "3",
							"5" }), 7L);
			eq(4,
					(new PasswordXGuessing()).howMany(new String[] { "4747",
							"4747", "4747", "4747" }), 36L);
		} catch (Exception exx) {
			System.err.println(exx);
			exx.printStackTrace(System.err);
		}
	}

	private static void eq(int n, int a, int b) {
		if (a == b)
			System.err.println("Case " + n + " passed.");
		else
			System.err.println("Case " + n + " failed: expected " + b
					+ ", received " + a + ".");
	}

	private static void eq(int n, double a, double b) {
		if (Math.abs(a - b) < 1e-6)
			System.err.println("Case " + n + " passed.");
		else
			System.err.println("Case " + n + " failed: expected " + b
					+ ", received " + a + ".");
	}

	private static void eq(int n, char a, char b) {
		if (a == b)
			System.err.println("Case " + n + " passed.");
		else
			System.err.println("Case " + n + " failed: expected '" + b
					+ "', received '" + a + "'.");
	}

	private static void eq(int n, long a, long b) {
		if (a == b)
			System.err.println("Case " + n + " passed.");
		else
			System.err.println("Case " + n + " failed: expected \"" + b
					+ "L, received " + a + "L.");
	}

	private static void eq(int n, boolean a, boolean b) {
		if (a == b)
			System.err.println("Case " + n + " passed.");
		else
			System.err.println("Case " + n + " failed: expected " + b
					+ ", received " + a + ".");
	}

	private static void eq(int n, String a, String b) {
		if (a != null && a.equals(b))
			System.err.println("Case " + n + " passed.");
		else
			System.err.println("Case " + n + " failed: expected \"" + b
					+ "\", received \"" + a + "\".");
	}

	private static void eq(int n, int[] a, int[] b) {
		if (a.length != b.length) {
			System.err.println("Case " + n + " failed: returned " + a.length
					+ " elements; expected " + b.length + " elements.");
			return;
		}
		for (int i = 0; i < a.length; i++)
			if (a[i] != b[i]) {
				System.err
						.println("Case "
								+ n
								+ " failed. Expected and returned array differ in position "
								+ i);
				print(b);
				print(a);
				return;
			}
		System.err.println("Case " + n + " passed.");
	}

	private static void eq(int n, long[] a, long[] b) {
		if (a.length != b.length) {
			System.err.println("Case " + n + " failed: returned " + a.length
					+ " elements; expected " + b.length + " elements.");
			return;
		}
		for (int i = 0; i < a.length; i++)
			if (a[i] != b[i]) {
				System.err
						.println("Case "
								+ n
								+ " failed. Expected and returned array differ in position "
								+ i);
				print(b);
				print(a);
				return;
			}
		System.err.println("Case " + n + " passed.");
	}

	private static void eq(int n, String[] a, String[] b) {
		if (a.length != b.length) {
			System.err.println("Case " + n + " failed: returned " + a.length
					+ " elements; expected " + b.length + " elements.");
			return;
		}
		for (int i = 0; i < a.length; i++)
			if (!a[i].equals(b[i])) {
				System.err
						.println("Case "
								+ n
								+ " failed. Expected and returned array differ in position "
								+ i);
				print(b);
				print(a);
				return;
			}
		System.err.println("Case " + n + " passed.");
	}

	private static void print(int a) {
		System.err.print(a + " ");
	}

	private static void print(long a) {
		System.err.print(a + "L ");
	}

	private static void print(String s) {
		System.err.print("\"" + s + "\" ");
	}

	private static void print(int[] rs) {
		if (rs == null)
			return;
		System.err.print('{');
		for (int i = 0; i < rs.length; i++) {
			System.err.print(rs[i]);
			if (i != rs.length - 1)
				System.err.print(", ");
		}
		System.err.println('}');
	}

	private static void print(long[] rs) {
		if (rs == null)
			return;
		System.err.print('{');
		for (int i = 0; i < rs.length; i++) {
			System.err.print(rs[i]);
			if (i != rs.length - 1)
				System.err.print(", ");
		}
		System.err.println('}');
	}

	private static void print(String[] rs) {
		if (rs == null)
			return;
		System.err.print('{');
		for (int i = 0; i < rs.length; i++) {
			System.err.print("\"" + rs[i] + "\"");
			if (i != rs.length - 1)
				System.err.print(", ");
		}
		System.err.println('}');
	}

	private static void nl() {
		System.err.println();
	}
	// END CUT HERE
}
