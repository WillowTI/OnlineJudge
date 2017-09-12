//题意：
//输入n对数字
//若某一对数字为(x, y)
//另一对数字为(y, x)
//那么这两对数字可以抵消
//判断这n对数字最后能否全部抵消
//分析：
//一开始用HashSet做的
//后来发现数字对是可以重复出现出现的
//这就导致如果加入已经出现的数字对时会忽略该操作
//然后用二维数组模拟
//当然这样也可以
//但是速度太慢了
//最后考虑用HashMap做
//用Point对应Integer（某一对数字-出现的次数）
//用二维数组一开始以为是TLE
//结果也过了(2000+ms)
//用HashMap(1000+ms)

import java.awt.Point;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int n;
		while ((n = in.nextInt()) != 0)
		{
			if (n % 2 == 1)
			{
				System.out.println("NO");
				for (int i = 0; i < 2 * n; i++)
					in.nextInt();
				continue;
			}
			int cnt = 0;
			HashMap<Point, Integer> map = new HashMap<>();
			for (int i = 0; i< n; i++)
			{
				int x = in.nextInt();
				int y = in.nextInt();
				Point p1 = new Point(x, y);
				Point p2 = new Point(y, x);
				if (map.containsKey(p2))
				{
					map.put(p2, map.get(p2) - 1);
					cnt--;
				}
				else 
				{
					map.put(p1, 1);
					cnt++;
				}
			}
			if (cnt == 0)
				System.out.println("YES");
			else 
				System.out.println("NO");
		}
	}
}