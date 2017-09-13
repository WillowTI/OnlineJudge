//题意：
//输入n个点
//判断是否存在一条竖直的直线使这n个点左右对称
//分析：
//输入可能会有重复的点
//那么对称过去也要有这么多的点
//这是唯一的坑点
//既然知道了重复的也要重复计算那就不能用HashSet了
//用HashMap
//Point-Integer(某一点-出现的次数)

import java.awt.Point;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	
	static Point[] array;
	static int n;
	static HashMap<Point, Integer> map = new HashMap<>();
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = in.nextInt();
		while (cas-- != 0)
		{
			map.clear();
			n = in.nextInt();
			array = new Point[n];
			for (int i = 0; i < n; i++)
			{
				Point p = new Point(in.nextInt(), in.nextInt());
				array[i] = p;
				if (map.containsKey(p))
					map.put(p, map.get(p) + 1);
				else 
					map.put(p, 1);
			}
			if (n == 1)
			{
				System.out.println("YES");
				continue;
			}
			boolean flag = false;
			MAIN:
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					if (array[i].y == array[j].y && check((array[i].x + array[j].x) / 2.0))
					{
						flag = true;
						break MAIN;
					}
					else if (array[i].x == array[j].x && check(array[i].x))
					{
						flag = true;
						break MAIN;
					}
				}
			}
			if (flag)
				System.out.println("YES");
			else 
				System.out.println("NO");
	}
			
}

	static boolean check(double index)
	{
		for (int i = 0; i < array.length; i++)
		{
			if(index != array[i].x)
			{
				int next = (int)(2 * index - array[i].x);
				int y = array[i].y;
				if (map.get(array[i]) != map.get(new Point(next, y)))
					return false;
			}
		}
		return true;
	}
	
}
