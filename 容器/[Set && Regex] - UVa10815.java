//题意：
//把输入文本的单词提取出来
//添加到词典里
//按字典序输出
//
//分析：
//输入的文本含有标点符号
//以'-'和'''分割的是两个单词
//其余的忽略
//用正则表达式很方便

import java.util.Scanner;
import java.util.TreeSet;

public class Main {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		TreeSet<String> set = new TreeSet<>();
		//HashSet不支持排序
		//TreeSet支持排序，String已经实现了Comparator
		//如果要按照其他的排序准则，在构造函数里传一个实现了compareTo函数的Comparable
		while (in.hasNext())
		{
			String s = in.next();
			String s1[] = s.split("[-']");//意思是以-或'为分隔符
			for (int i = 0; i < s1.length; i++)
			{
				s1[i] = s1[i].replaceAll("[^a-zA-Z]", "");//意思是把字母以外的东西删除
				s1[i] = s1[i].toLowerCase();
				if (s1[i].length() != 0)
					set.add(s1[i]);
			}
		}
		for(String value : set)
            System.out.println(value);
	}
}
