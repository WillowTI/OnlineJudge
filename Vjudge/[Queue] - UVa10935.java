//题意：
//给定n个数字
//从1开始添加到队列里
//每一步操作把第一个元素丢掉
//再把第二个元素放到队尾去
//最后当只剩一个元素的时候
//输出之前丢掉的元素和最后留下的元素
//
//分析：
//模拟队列操作
//把丢掉的元素保存到数组里
//当队列长度为1时开始输出
//注意一个特殊情况：当n = 1时
//输出丢掉的元素的第一个元素是没有空格的
//这是在udebug里发现的
//在样例里看不到

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int n;
		while ((n = in.nextInt()) != 0)
		{
			int simulate[] = new int[1000];
			for (int i = 0; i < n; i++)
				simulate[i] = i + 1;
			int length = n;
			int pos = 0;
			int discard[] = new int[1000];
			int discardlen = 0;
			while (length - pos != 1)
			{
				discard[discardlen++] = simulate[pos++];
				simulate[length++] = simulate[pos++];
			}
			int ans = simulate[pos];
			System.out.print("Discarded cards:");
			if (discardlen > 0)
				System.out.print(" ");
			for (int i = 0; i < discardlen; i++)
			{
				System.out.print(discard[i]);
				if (i != discardlen - 1)
					System.out.print(", ");
			}
			System.out.println();
			System.out.println("Remaining card: " + ans);
		}
	}
}