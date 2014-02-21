// BEGIN CUT HERE

// END CUT HERE
import java.util.*;

public class StrIIRec {
	private boolean format(int n, String minStr, char[] format, int minInv) {
		boolean[] flag = new boolean[n];
		for (int i = 0; i < n; i++)
			flag[i] = true;
		boolean large = false;

		for (int i = 0; i < n; i++) {
			int start = 0;
			if (large == false && i < minStr.length()) {
				start = (int) (minStr.charAt(i) - 'a');
			}
			boolean success = false;
			int rev = 0;
			for (int j = 0; j < start; j++)
				if (flag[j] == true)
					rev++;

			for (int j = start; j < n; j++) {
				if (flag[j] == true
						&& (minInv - rev) <= (n - i - 1) * (n - i - 2) / 2) {
					format[i] = (char) ('a' + j);
					flag[j] = false;
					success = true;
					minInv = minInv - rev;
					break;
				}
				if (flag[j])
					rev++;
			}

			if (!success) {
				return false;
			}

			if (i < minStr.length() && format[i] > minStr.charAt(i)) {
				large = true;
			}
		}
		return true;
	}

	public String recovstr(int n, int minInv, String minStr) {
		char[] tmp = new char[n];
		if (!format(n, minStr, tmp, minInv))
			return "";
		return new String(tmp);
	}

	// BEGIN CUT HERE
	public static void main(String[] args) {
		try {
			eq(0, (new StrIIRec()).recovstr(2, 1, "ab"), "ba");
			eq(1, (new StrIIRec()).recovstr(9, 1, "efcdgab"), "efcdgabhi");
			eq(2, (new StrIIRec()).recovstr(11, 55, "debgikjfc"), "kjihgfedcba");
			eq(3, (new StrIIRec()).recovstr(15, 0, "e"), "eabcdfghijklmno");
			eq(4, (new StrIIRec()).recovstr(9, 20, "fcdebiha"), "fcdehigba");
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
