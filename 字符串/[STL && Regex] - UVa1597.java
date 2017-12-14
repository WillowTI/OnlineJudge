//题意：
//给定若干篇文章和查询
//查询包括
//1.word（查询包括word的文章）
//2.word1 OR word2（查询包括word1或word2的文章）
//3.word1 AND word2（查询包括word1和word2的文章）
//4.NOT word（查询不包括word的文章）
//前三种输出至少包含一个关键字的行
//第四种输出整篇文章
//多篇文章之间输出"----------"
//单词之间用非单词字符分割
//单词的比较忽略大小写
//但是得输出原文
//分析：
//用ArrayList存储原文
//用HashSet数组存储每一篇文章出现的单词
//用HashMap数组存储每一篇文章每一行出现的单词(Integer-String)
//分离出每一行出现的单词时用到了正则表达式

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int passagenum = in.nextInt();
		in.nextLine();
		ArrayList<String> list[] = new ArrayList[passagenum];
		for (int i = 0; i < passagenum; i++)
		{
			String s = in.nextLine();
			list[i] = new ArrayList<>();
			while (!s.equals("**********"))
			{
				list[i].add(s);
				s = in.nextLine();
			}
		}
		HashSet<String> bigset[] = new HashSet[passagenum];
		HashMap<Integer, HashSet<String>> map[] = new HashMap[passagenum];
		for (int i = 0; i < passagenum; i++)
		{
			bigset[i] = new HashSet<>();
			map[i] = new HashMap<>();
			for (int j = 0; j < list[i].size(); j++)
			{
				map[i].put(j, new HashSet<>());
				String sub[] = list[i].get(j).toLowerCase().split("[^a-z]");
				for (String s : sub)
					if (s.length() != 0)
						{
							bigset[i].add(s);
							map[i].get(j).add(s);
						}
			}
		}
		int ordernumber = in.nextInt();
		in.nextLine();
		while (ordernumber-- != 0)
		{
			String order = in.nextLine();
			String suborder[] = order.split(" ");
			boolean flag = false;
			if (suborder.length == 1)
			{
				for (int i = 0; i < passagenum; i++)
				{
					if (bigset[i].contains(order))
					{
						if (flag)
							System.out.println("----------");
						flag = true;
						for (int j = 0; j < map[i].size(); j++)
							if (map[i].get(j).contains(order))
								System.out.println(list[i].get(j));
					}
				}
			}
			else if (suborder.length == 2)
			{
				for (int i = 0; i < passagenum; i++)
				{
					if (!bigset[i].contains(suborder[1]))
					{
						if (flag)
							System.out.println("----------");
						flag = true;
						for (int j = 0; j < list[i].size(); j++)
							System.out.println(list[i].get(j));
					}
				}
			}
			else 
			{
				if (suborder[1].equals("OR"))
				{
					for (int i = 0; i < passagenum; i++)
					{
						if (bigset[i].contains(suborder[0]) || bigset[i].contains(suborder[2]))
						{
							if (flag)
								System.out.println("----------");
							flag = true;
							for (int j = 0; j < list[i].size(); j++)
								if (map[i].get(j).contains(suborder[0]) || map[i].get(j).contains(suborder[2]))
									System.out.println(list[i].get(j));
						}
					}
				}
				else 
				{
					for (int i = 0; i < passagenum; i++)
					{
						if (bigset[i].contains(suborder[0]) && bigset[i].contains(suborder[2]))
						{
							if (flag)
								System.out.println("----------");
							flag = true;
							for (int j = 0; j < list[i].size(); j++)
								if (map[i].get(j).contains(suborder[0]) || map[i].get(j).contains(suborder[2]))
									System.out.println(list[i].get(j));
						}
					}
				}
			}
			if (!flag)
				System.out.println("Sorry, I found nothing.");
			System.out.println("==========");
		}
	}
}
