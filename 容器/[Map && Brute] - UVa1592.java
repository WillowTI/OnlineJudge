//题意：
//给定m行n列的字符串
//求是否存在r1, r2, c1, c2
//使得(r1, c1) == (r2, c1) 并且 (r2, c1) == (r2, c2)
//
//分析：
//先预处理字符串
//把字符串用数字代替
//每个数字代表了自定义字典的下标
//
//第一种方法是枚举两列
//扫描每一行
//把每一行的结果存到map里
//如果扫到某一行发现map里已经有这个元素了就说明找到了

import java.awt.Point;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	static HashMap<String, Integer> dic = new HashMap<>();
	static ArrayList<String> list = new ArrayList<>();
	public static void main(String[] args) throws FileNotFoundException {
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int m, n;
		while (in.hasNext())
		{
			m = in.nextInt();
			n = in.nextInt();
			in.nextLine();
			int words [][] = new int [m][n];
			String s;
			dic.clear();
			list.clear();
			for (int i = 0; i < m; i++)
			{
				s = in.nextLine();
				String sub []= s.split(",");
				for (int j = 0; j < n; j++)
					words[i][j] = ID(sub[j]);
			}
			int r1 = 0, r2 = 0, c1 = 0, c2 = 0, flag = 0;
			MAIN:
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					HashMap<Point, Integer> map = new HashMap<>();
					for (int k = 0; k < m; k++)
					{
						Point cur = new Point(words[k][i], words[k][j]);
						if (map.containsKey(cur))
						{
							r1 = map.get(cur) + 1;
							r2 = k + 1;
							c1 = i + 1;
							c2 = j + 1;
							flag = 1;
							break MAIN;
						}
						else 
						{
							map.put(cur, k);
						}
					}
				}
			}
			if (flag == 0)
			{
				System.out.println("YES");
			}
			else 
			{
				System.out.println("NO");
				System.out.println(r1 + " " + r2);
				System.out.println(c1 + " " + c2);
			}
		}
	}
	
	static int ID(String s)
	{
		if (dic.containsKey(s))
			return dic.get(s);
		int ret = list.size();
		list.add(s);
		dic.put(s, ret);
		return ret;
	}
}

//第二种方法是枚举两行
//扫描每一列
//当有两列的数字相同时说明找到了
//
//两种方法比较下来第一种更快
//第二种已经快达到时间限制了
//暴力搜索的效率还是比不上map

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	static HashMap<String, Integer> dic = new HashMap<>();
	static ArrayList<String> list = new ArrayList<>();
	public static void main(String[] args) throws FileNotFoundException {
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int m, n;
		while (in.hasNext())
		{
			m = in.nextInt();
			n = in.nextInt();
			in.nextLine();
			int words [][] = new int [m][n];
			String s;
			dic.clear();
			list.clear();
			for (int i = 0; i < m; i++)
			{
				s = in.nextLine();
				String sub []= s.split(",");
				for (int j = 0; j < n; j++)
					words[i][j] = ID(sub[j]);
			}
			int r1 = 0, r2 = 0, c1 = 0, c2 = 0, flag = 0;
			MAIN:
			for (int i = 0; i < m; i++)
			{
				for (int j = i + 1; j < m; j++)
				{
					int times = 0;
					for (int k = 0; k < n; k++)
					{
						if (words[i][k] == words[j][k])
						{
							if (times == 0)
							{
								r1 = i + 1;
								r2 = j + 1;
								c1 = k + 1;
							}
							else 
							{
								c2 = k + 1;
							}
							times++;
						}
						if (times == 2)
						{
							flag = 1;
							break MAIN;
						}
					}
				}
			}
			if (flag == 0)
			{
				System.out.println("YES");
			}
			else 
			{
				System.out.println("NO");
				System.out.println(r1 + " " + r2);
				System.out.println(c1 + " " + c2);
			}
		}
	}
	
	static int ID(String s)
	{
		if (dic.containsKey(s))
			return dic.get(s);
		int ret = list.size();
		list.add(s);
		dic.put(s, ret);
		return ret;
	}
}
