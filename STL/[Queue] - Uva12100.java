//题意:
//给定一些打印任务的优先级和所要关注的任务的位置（从0开始计数）
//从0号位置开始打印
//打印遵循一下规则：
//1.如果队列中存在比下一个要打印的任务的优先级更高的任务
//那么把下一个要打印的任务丢到队列末尾
//2.调整任务位置不花费时间
//3.每次打印一个任务花费1分钟
//输出打印所关注的任务花了多长时间
//分析：
//这不是一道典型的PriorityQueue
//所以还是用Queue模拟
//从队首开始遍历
//如果是合法的就打印
//否则丢到队尾

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = in.nextInt();
		while (cas-- != 0)
		{
			int n = in.nextInt();
			int focus = in.nextInt();
			int quest[] = new int[10000];
			int priority[] = new int[10];//保存优先级(index)对应的任务数量
			for (int i = 0; i < n; i++)
			{
				quest[i] = in.nextInt();
				priority[quest[i]]++;
			}
			int time = 0;
			int head = 0;
			int tail = n;
			while (head < tail)
			{
				if (isvalid(quest[head], priority))
				{
					if (head == focus)
					{
						time++;
						System.out.println(time);
						break;
					}
					else 
					{
						time++;
						priority[quest[head]]--;
						head++;
					}
				}
				else 
				{
					quest[tail] = quest[head];
					if (head == focus)
						focus = tail;
					head++;
					tail++;
				}
			}
		}
	}
	
	static boolean isvalid(int num, int priority[])//判断是否存在比当前任务更高优先级的任务
	{
		for (int i = num + 1; i < priority.length; i++)
			if (priority[i] > 0)
				return false;
		return true;
	}
}
