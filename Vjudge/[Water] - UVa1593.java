//题意：
//给定一些文本
//文本的每一行由若干个空格分割单词
//现在让单词都左对齐
//两个单词之间由若干个空格分割
//要让长度尽可能短
//分析：
//计算出每一列的目标长度
//长度不足的补空格就行了


import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		ArrayList<ArrayList<String>> list = new ArrayList<>();
		int n = 0;
		int maxlength = 0;
		while (in.hasNext())
		{
			String s = in.nextLine();
			list.add(new ArrayList<String>());
			String sub[] = s.split(" +");
			ArrayList<String> cur = list.get(n);
			for (int i = 0; i < sub.length; i++)
				if (sub[i].length() != 0)
					cur.add(sub[i]);
			maxlength = Math.max(maxlength, cur.size());
			n++;
		}
		int length[] = new int[maxlength];
		for (int i = 0; i < maxlength; i++)
		{
			int tmp = 0;
			for (int j = 0; j < list.size(); j++)
			{
				if (i < list.get(j).size())
					tmp = Math.max(tmp,  list.get(j).get(i).length());
			}
			length[i] = tmp;
		}
		for (int i = 0; i < list.size(); i++)
		{
			for (int j = 0; j < list.get(i).size(); j++)
			{
				int len = list.get(i).get(j).length();
				System.out.print(list.get(i).get(j));
				if (j != list.get(i).size() - 1)
				{
					for (int k = len; k < length[j] + 1; k++)
						System.out.print(" ");
				}
			}
			System.out.println();
		}
	}
}