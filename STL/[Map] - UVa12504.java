//题意：
//给定新旧两个字典
//按照字典序输出前者相比后者新增的键，删除的键，更新的键
//可能输入空的字典
//如果没有变化
//输出"No changes"
//每一个case后输出空行
//分析:
//由于要有序地输出
//所以考虑用TreeMap
//获得键值对是预处理过程的关键
//先用split(",")获得键值对的数组
//对于每一个数组再用split(":")获得键和值
//接下来判断空的字典
//split方法返回的String数组的长度至少是1
//所以可以通过看第二轮split下来的数组的长度是否是2的倍数来判断是否为一对有效的键值对
	
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Main {
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = in.nextInt();
		in.nextLine();
		for (int  t = 0; t < cas; t++)
		{
			String s1 = in.nextLine();
			String s2 = in.nextLine();
			TreeMap<String, String> map1 = new TreeMap<>();
			TreeMap<String, String> map2 = new TreeMap<>();
			s1 = s1.substring(1, s1.length() - 1);
			s2 = s2.substring(1, s2.length() - 1);
			String sub1[] = s1.split(",");
			String sub2[] = s2.split(",");
			for (int i = 0; i < sub1.length; i++)
			{
				String tmp[] = sub1[i].split(":");
				if (tmp.length % 2 == 0)
					map1.put(tmp[0], tmp[1]);
			}
			for (int i = 0; i < sub2.length; i++)
			{
				String tmp[] = sub2[i].split(":");
				if (tmp.length % 2 == 0)
					map2.put(tmp[0], tmp[1]);
			}
			boolean flag = false;
			boolean bigflag = false;//判断是否输出"No changes"，只要在三次检测中有一个成立的就不输出
			for (Map.Entry<String, String> entry : map2.entrySet())
			{
				String key = entry.getKey();
				if (!map1.containsKey(key))
				{
					bigflag = true;
					if (flag == false)
					{
						flag = true;
						System.out.print("+" + key);
					}
					else 
						System.out.print("," + key);
				}
			}
			if (flag)
				System.out.println();
			flag = false;
			for (Map.Entry<String, String> entry : map1.entrySet())
			{
				String key = entry.getKey();
				if (!map2.containsKey(key))
				{
					bigflag = true;
					if (flag == false)
					{
						flag = true;
						System.out.print("-" + key);
					}
					else 
						System.out.print("," + key);
				}
			}
			if (flag)
				System.out.println();
			flag = false;
			for (Map.Entry<String, String> entry : map1.entrySet())
			{
				String key = entry.getKey();
				if (map2.containsKey(key) && !map2.get(key).equals(entry.getValue()))
				{
					bigflag = true;
					if (flag == false)
					{
						flag = true;
						System.out.print("*" + key);
					}
					else 
						System.out.print("," + key);
				}
			}
			if (flag)
				System.out.println();
			if (!bigflag)
				System.out.println("No changes");
			System.out.println();
		}
	}
}