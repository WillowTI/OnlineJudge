//题意：
//给定n个字符串
//把最大的长度记为M
//长度在1到60之间
//把它们按照字典序从第一列开始放置
//要让行数尽可能少
//输出的时候最后一列有M个字符（长度不够用空格填充）
//前面的有M + 2个字符
//
//分析：
//先确定列数和行数
//设列数为x
//有x - 1列占用M + 2个字符和1列占用M个字符
//得到方程(x - 1) * (M + 2) + M = 60
//解得x
//列数确定后行数也能确定
//最后输出

import java.util.Arrays;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		while (in.hasNext())
		{
			int n = in.nextInt();
			int maxlen = 0;
			String str[] = new String[n];
			for (int i = 0; i < n; i++)
			{
				str[i] = in.next();
				maxlen = Math.max(maxlen, str[i].length());
			}
			Arrays.sort(str);
			int col = (60 - maxlen) / (maxlen + 2) + 1;
			int row = n / col;
			if (n % col != 0)
				row++;
			//不能整除的时候要多加一行
			//紫书上是(n - 1) / col + 1
			//实际上是一样的
			for (int i = 0; i < 60; i++)
				System.out.print("-");
			System.out.println();
			for (int i = 0 ;i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (j * row + i < n)
					{
						System.out.print(str[j * row + i]);
						int times;
						if (j + 1 < col && (j+ 1) * row + i < n)
							times = maxlen + 2;
						else 
							times = maxlen;
						//紫书上是times = j == col - 1 ? M : M + 2;
						//如果不能填满整个矩阵的话，最后一个元素的下标也不可能是col - 1
						//那就判定为是M而不是M + 2
						//所以一定要用几句话解决的话应该是times = (j == col - 1 || j * row + i == n - 1) ? maxlen : maxlen + 2;
						for (int t = 0; t < times - str[j * row + i].length(); t++)
							System.out.print(" ");
					}
				}
				System.out.println();
			}
		}
	}
	
}
