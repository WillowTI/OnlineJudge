/**
 * 1看作1，0看作-1，记录前缀和
 * 用map保存某个前缀和第一次出现的下标
 * 在处理某个前缀和时i-map[sum]表示平衡串的长度
 * 注意一定要添加map[0]=0，否则输入10或者01答案会是0
 * 如果把0看作0行不行？
 * 不行。这样就无法记录0出现的次数了
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			int n = in.nextInt();
			int ans = 0, sum = 0;
			String s = in.next();
			HashMap<Integer, Integer> map = new HashMap<>();
			map.put(0, 0);
			for (int i = 1; i <= n; i++) {
				if (s.charAt(i - 1) == '1')
					sum++;
				else
					sum--;
				if (!map.containsKey(sum))
					map.put(sum, i);
				ans = Math.max(ans, i - map.get(sum));
			}
			System.out.println(ans);
		}
	}

}