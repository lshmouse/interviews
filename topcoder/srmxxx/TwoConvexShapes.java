// BEGIN CUT HERE

// END CUT HERE
import java.util.*;

public class TwoConvexShapes {
	final static int MOD = 1000000007;

	public int countWays(String[] grid) {
		return (countWays(grid, 'W') + countWays(grid, 'B')) % MOD;
	}

	public int countWays(String[] grid, char left) {
		int m = grid.length;
		int n = grid[0].length();
		int[][][] dp = new int[m][n + 1][n + 1];

		boolean[] flag = new boolean[n + 1];
		getSplilt(grid[0], flag, left);
		for (int i = 0; i < n + 1; i++) {
			dp[0][i][i] = flag[i] ? 1 : 0;
		}

		for (int i = 0; i < m - 1; i++) {

			for (int j = 0; j < n + 1; j++)
				for (int k = 0; k < n + 1; k++)
					dp[i + 1][j][k] = 0;

			getSplilt(grid[i + 1], flag, left);

			for (int s = 0; s < n + 1; s++)
				if (flag[s]) {
					for (int j = 0; j < n + 1; j++) {
						for (int k = j; k < n + 1; k++) {
							if (s > j && k > j) {
								continue;
							}
							dp[i + 1][s][Math.max(s, k)] = (dp[i + 1][s][Math
									.max(s, k)] + dp[i][j][k])
									% MOD;
						}
					}
				}
			for (int j = 0; j < n + 1; j++) {
				for (int k = 0; k < n + 1; k++) {
					System.out.print(dp[i + 1][j][k] + " ");
				}
				System.out.println();
			}
		}
		int ret = 0;
		for (int j = 0; j < n + 1; j++)
			for (int k = 0; k < n + 1; k++)
				ret = (ret + dp[m - 1][j][k]) % MOD;
		return ret;

	}

	private void getSplilt(String str, boolean[] flag, char left) {
		for (int i = 0; i < str.length() + 1; i++) {
			flag[i] = true;

			for (int j = 0; j < i; j++) {
				if (str.charAt(j) != '?' && str.charAt(j) != left) {
					flag[i] = false;
					break;
				}
			}

			for (int j = i; j < str.length(); j++) {
				if (str.charAt(j) == left) {
					flag[i] = false;
					break;
				}
			}
		}
	}

	// BEGIN CUT HERE
	public static void main(String[] args) {
		try {
			eq(0, (new TwoConvexShapes())
					.countWays(new String[] { "??", "??" }), 14);
//			eq(1, (new TwoConvexShapes())
//					.countWays(new String[] { "B?", "??" }), 7);
//			eq(2, (new TwoConvexShapes()).countWays(new String[] { "WWB",
//					"WWW", "WWW", "WWW" }), 1);
//			eq(3, (new TwoConvexShapes()).countWays(new String[] { "BBBBBB",
//					"WWBBBB", "WBBBBB" }), 0);
//			eq(4, (new TwoConvexShapes()).countWays(new String[] { "?BB?",
//					"BBBB", "?BB?" }), 5);
//			eq(5, (new TwoConvexShapes()).countWays(new String[] {
//					"?WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
//					"B?WWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
//					"BB?WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
//					"BBB?WWWWWWWWWWWWWWWWWWWWWWWWWWW",
//					"BBBB?WWWWWWWWWWWWWWWWWWWWWWWWWW",
//					"BBBBB?WWWWWWWWWWWWWWWWWWWWWWWWW",
//					"BBBBBB?WWWWWWWWWWWWWWWWWWWWWWWW",
//					"BBBBBBB?WWWWWWWWWWWWWWWWWWWWWWW",
//					"BBBBBBBB?WWWWWWWWWWWWWWWWWWWWWW",
//					"BBBBBBBBB?WWWWWWWWWWWWWWWWWWWWW",
//					"BBBBBBBBBB?WWWWWWWWWWWWWWWWWWWW",
//					"BBBBBBBBBBB?WWWWWWWWWWWWWWWWWWW",
//					"BBBBBBBBBBBB?WWWWWWWWWWWWWWWWWW",
//					"BBBBBBBBBBBBB?WWWWWWWWWWWWWWWWW",
//					"BBBBBBBBBBBBBB?WWWWWWWWWWWWWWWW",
//					"BBBBBBBBBBBBBBB?WWWWWWWWWWWWWWW",
//					"BBBBBBBBBBBBBBBB?WWWWWWWWWWWWWW",
//					"BBBBBBBBBBBBBBBBB?WWWWWWWWWWWWW",
//					"BBBBBBBBBBBBBBBBBB?WWWWWWWWWWWW",
//					"BBBBBBBBBBBBBBBBBBB?WWWWWWWWWWW",
//					"BBBBBBBBBBBBBBBBBBBB?WWWWWWWWWW",
//					"BBBBBBBBBBBBBBBBBBBBB?WWWWWWWWW",
//					"BBBBBBBBBBBBBBBBBBBBBB?WWWWWWWW",
//					"BBBBBBBBBBBBBBBBBBBBBBB?WWWWWWW",
//					"BBBBBBBBBBBBBBBBBBBBBBBB?WWWWWW",
//					"BBBBBBBBBBBBBBBBBBBBBBBBB?WWWWW",
//					"BBBBBBBBBBBBBBBBBBBBBBBBBB?WWWW",
//					"BBBBBBBBBBBBBBBBBBBBBBBBBBB?WWW",
//					"BBBBBBBBBBBBBBBBBBBBBBBBBBBB?WW",
//					"BBBBBBBBBBBBBBBBBBBBBBBBBBBBB?W" }), 73741817);
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
