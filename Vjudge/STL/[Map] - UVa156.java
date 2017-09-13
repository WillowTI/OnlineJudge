//题意：
//给定一些字符串
//在忽略大小写的情况下
//如果某一个字符串通过变换字符顺序得到另一个字符串的话
//这两个字符串就是重复的
//最后按照字典序输出所有不重复的字符串
//保留原来的大小写
//
//分析：
//先把每一字符串变成小写
//再按照字符大小排序
//这样判断两个字符串是否重复就好办了
//用HashMap存某个字符串出现的次数（初始化为0）
//答案应该是出现0次的字符串


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		ArrayList<String> list = new ArrayList<>();
		HashMap<String, Integer> map = new HashMap<>();
		String s;
		while (in.hasNext())
		{
			s = in.next();
			if (!s.equals("#"))
			{
				list.add(s);
				String sort = reverse(s);
				if (!map.containsKey(sort))
					map.put(sort, new Integer(0));
				else 
					map.replace(sort, map.get(sort) + 1);
			}
		}
		ArrayList<String> ans = new ArrayList<>();
		for (String tmp : list)
			if(map.get(reverse(tmp)) == 0)
				ans.add(tmp);
		Collections.sort(ans);
		for (String a : ans)
			System.out.println(a);
	}
	
	public static String reverse(String s)
	{
		s = s.toLowerCase();
		char c[] = s.toCharArray();
		Arrays.sort(c);
		String ret = new String(c);
		return ret;
	}
}
