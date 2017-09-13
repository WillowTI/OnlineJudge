//题意：
//给定n个字符串
//已经按照字典序排序
//输出能由这个字典里的两个单词拼成的单词
//按照字典序
//分析：
//把所有输入的单词存入HashSet中
//遍历这个词典
//对每个单词遍历所有的2个字串
//看是否在HashSet中

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

public class Main {
	static HashSet<String> set = new HashSet<>();
	static ArrayList<String> list = new ArrayList<>();
	
	static boolean contain(String s)
	{
		for (int i = 1; i < s.length(); i++)
		{
			if(set.contains(s.substring(0, i)) && set.contains(s.substring(i)))
				return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		while (in.hasNext())
		{
			String s = in.next();
			set.add(s);
			list.add(s);
		}
		for (int i = 0; i < list.size(); i++)
		{
			String cur = list.get(i);
			if (contain(cur))
			{
				System.out.println(cur);
			}
		}
	}

}
