//题意：
//给定一个数组
//对相邻的元素做差取绝对值（最后一项为数组的最后一项和第一项做差）
//生成一个数组
//判断这个数组是否之前出现过（输出"LOOP"）
//或者全部由0组成（输出"ZERO"）
//分析：
//一开始用set老老实实模拟的
//TLE
//是在想不到有什么可以优化的地方的
//HashSet的速度已经够快了
//去网上找代码
//题目有一句话说
//You may assume that the maximum number of steps of a Ducci sequence reaching zeros tuple
//or making a loop does not exceed 1,000.
//这句话应该理解为循环1000次
//如果还没出现全0那就是LOOP了
//那set就省掉了

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	static boolean allzero(ArrayList<Integer> list)
	{
		for (int i = 0; i < list.size(); i++)
			if (list.get(i) != 0)
				return false;
		return true;
	}
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = in.nextInt();
		while (cas-- != 0)
		{
			int n = in.nextInt();
			ArrayList<Integer> first = new ArrayList<>();
			for (int i = 0; i < n; i++)
				first.add(in.nextInt());
			int times = 500;
			int ans = 1;
			while (times-- != 0)
			{
				if (allzero(first))
				{
					ans = 0;
					break;
				}
				ArrayList<Integer> cur = new ArrayList<>();
				for (int i = 0; i < first.size(); i++)
				{
					cur.add(Math.abs(first.get(i) - first.get((i + 1) % n)));
				}
				first = cur;
			}
			if (ans == 0)
				System.out.println("ZERO");
			else 
				System.out.println("LOOP");
		}
	}
}

