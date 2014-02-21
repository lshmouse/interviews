// BEGIN CUT HERE

// END CUT HERE
import java.util.*;

public class Suminator {
	public int findMissing(int[] program, int wantedResult) {
		int p = getPos(program);

		program[p] = 0;
		long a = getResult(program);

		if (a == wantedResult)
			return 0;

		program[p] = 1;
		long b = getResult(program);
		program[p] = 2;
		long c = getResult(program);

		if (b == c && b == wantedResult)
			return 1;
		
		
		long delta = c - b;
		if (delta == 0)
			return -1;
		
		if ((wantedResult - b + delta) % delta != 0)
			return -1;
		long ret = (wantedResult - b + delta) / delta;
		
		if (ret > 0)
			return (int) ret;
		else
			return -1;
	}

	public long getResult(int[] program) {
		long[] stack = new long[program.length];
		int top = 0;
		for (int i = 0; i < program.length; i++) {
			if (program[i] == 0) {

				long a = top > 0 ? stack[top - 1] : 0;
				top = top > 0 ? top - 1 : 0;
				long b = top > 0 ? stack[top - 1] : 0;
				top = top > 0 ? top - 1 : 0;

				stack[top++] = a + b;

			} else {
				stack[top++] = program[i];
			}
		}
		return top > 0 ? stack[top - 1] : 0;
	}

	public int getPos(int[] program) {
		for (int i = 0; i < program.length; i++) {
			if (program[i] == -1) {
				return i;
			}
		}
		return -1;
	}

	// BEGIN CUT HERE
	public static void main(String[] args) {
		try {
			eq(0, (new Suminator()).findMissing(new int[] { 7, -1, 0 }, 10), 3);
			eq(1, (new Suminator()).findMissing(new int[] { 100, 200, 300, 0,
					100, -1 }, 600), 0);
			eq(2, (new Suminator()).findMissing(new int[] { -1, 7, 3, 0, 1, 2,
					0, 0 }, 13), 0);
			eq(3, (new Suminator()).findMissing(new int[] { -1, 8, 4, 0, 1, 2,
					0, 0 }, 16), -1);
			eq(4, (new Suminator()).findMissing(new int[] { 1000000000,
					1000000000, 1000000000, 1000000000, -1, 0, 0, 0, 0 },
					1000000000), -1);
			eq(5, (new Suminator()).findMissing(new int[] { 7, -1, 3, 0 }, 3),
					-1);
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
