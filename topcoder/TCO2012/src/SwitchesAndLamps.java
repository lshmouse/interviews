import java.util.*;

public class SwitchesAndLamps {
	public int theMin(String[] switches, String[] lamps) {
		int n = switches[0].length();
		boolean[][] flag = new boolean[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				flag[i][j] = true;
			}
		}
		for (int i = 0; i < switches.length; i++) {
			for (int j = i + 1; j < switches.length; j++) {
				for (int k = 0; k < switches[i].length(); k++) {
					for (int l = 0; l < lamps[i].length(); l++) {
						if (switches[i].charAt(k) != lamps[i].charAt(l)) {
							flag[k][l] = false;
						}
						if (switches[j].charAt(k) != lamps[j].charAt(l)) {
							flag[k][l] = false;
						}
						if (switches[i].charAt(k) == switches[j].charAt(k)) {
							if (lamps[i].charAt(l) != lamps[j].charAt(l)) {
								flag[k][l] = false;
							}
						}
						if (switches[i].charAt(k) != switches[j].charAt(k)) {
							if (lamps[i].charAt(l) == lamps[j].charAt(l)) {
								flag[k][l] = false;
							}
						}
					}
				}
			}
		}
		int[] sumA = new int[n];
		int[] sumB = new int[n];
		for (int i = 0; i < n; i++) {
			sumA[i] = 0;
			for (int j = 0; j < n; j++) {
				if (flag[i][j])
					sumA[i]++;
			}
			if (sumA[i] == 0)
				return -1;
		}
		for (int i = 0; i < n; i++) {
			sumB[i] = 0;
			for (int j = 0; j < n; j++) {
				if (flag[j][i])
					sumB[i]++;
			}
			if (sumB[i] == 0)
				return -1;
		}
		
		int res = 0;
		boolean[] count = new boolean[n];
		for (int i = 0; i < n; i++)
			count[i] = true;
		
		for (int i = 0; i < n; i++) {
			if (count[i] == false)
				continue;
			for (int j = 0; j < n; j++) {
				if (flag[i][j]) {
					if (sumA[i] != sumB[j])
						return -1;
					for (int k = 0; k < n; k++) {
						if (flag[k][j]) {
							count[k] = false;
						}
					}
				}
			}
			System.out.println(sumA[i]);
			res = Math.max(res, sumA[i] -1);
		}
		return res;
	}

}


// Powered by FileEdit
// Powered by CodeProcessor


// Powered by FileEdit
// Powered by CodeProcessor
