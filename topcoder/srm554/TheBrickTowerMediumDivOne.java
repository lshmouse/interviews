// BEGIN CUT HERE

// END CUT HERE
import java.util.*;

public class TheBrickTowerMediumDivOne {
	public int[] find(int[] heights) {
		int n = heights.length;
		int[] res = new int[n];
		boolean[] flag = new boolean[n];
		for (int i = 0; i < n; i++) {
			flag[i] = true;
		}
		for (int i = 0; i < n; i++) {
			int p = -1;
			for (int j = 0; j < n; j++)
				if (flag[j]) {
					if (p == -1 || heights[j] < heights[p]) {
						p = j;
					}
				}

			res[i] = p;
			flag[p] = false;
		}
		int left = 1 << 20;

		for (int i = 0; i < n; i++) {
			int p = i;
			for (int j = i + 1; j < n; j++) {
				if (res[j] < res[p] && heights[res[j]] <= left) {
					p = j;
				}
			}
			int tmp = res[p];
			for (int j = p - 1; j >= i; j--) {
				res[j + 1] = res[j];
			}
			res[i] = tmp;
			left = heights[res[i]];
		}
		return res;
	}

	// BEGIN CUT HERE
	public static void main(String[] args) {
		try {
			eq(0,
					(new TheBrickTowerMediumDivOne())
							.find(new int[] { 4, 7, 5 }), new int[] { 0, 2, 1 });
			eq(1,
					(new TheBrickTowerMediumDivOne()).find(new int[] { 4, 4, 4,
							4, 4, 4, 4 }), new int[] { 0, 1, 2, 3, 4, 5, 6 });
			eq(2,
					(new TheBrickTowerMediumDivOne()).find(new int[] { 2, 3, 3,
							2 }), new int[] { 0, 3, 1, 2 });
			eq(3,
					(new TheBrickTowerMediumDivOne()).find(new int[] { 13, 32,
							38, 25, 43, 47, 6 }), new int[] { 0, 6, 3, 1, 2, 4,
							5 });
			eq(4,
					(new TheBrickTowerMediumDivOne())
							.find(new int[] { 3, 3, 2 }), new int[] { 0, 1, 2 });
			eq(4,
					(new TheBrickTowerMediumDivOne())
							.find(new int[] { 2, 3, 3 }), new int[] { 0, 1, 2 });

			eq(4,
					(new TheBrickTowerMediumDivOne())
							.find(new int[] { 3, 2, 3 }), new int[] { 0, 1, 2 });
			

			eq(4,
					(new TheBrickTowerMediumDivOne())
							.find(new int[] { 2, 2, 3 }), new int[] { 0, 1, 2 });

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
