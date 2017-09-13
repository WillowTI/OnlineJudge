//题意：
//有多个团队的人排队
//进队的人如果有队友在排队
//那么他会到最后一个队友的身后
//如果没有那就排到队伍最后
//
//分析：
//先用map存入每个人对应的队伍下标
//用一个队列表示当前队列的情况
//由于排队机制
//同一个队伍的的人总是排在一起的
//队列里的元素是在一块的队伍下标
//用队列数组表示分队里人的具体情况
//
//由于Queue是一个接口
//有好多方法没有实现
//就用LinkedList代替了
//因为LinkedList的插入删除操作比较快
//
//如果不用队列数组记录只用一个主队列模拟的话会超时

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {
	static HashMap<Integer, Integer> person = new HashMap<>();
	static LinkedList<Integer> mainqueue = new LinkedList<>();
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int team;
		int cas = 1;
		while ((team = in.nextInt()) != 0)
		{
			person.clear();
			mainqueue.clear();
			LinkedList<Integer> sub [] = new LinkedList [team];
			for (int i = 0; i < team; i++)
			{
				sub[i] = new LinkedList<>();
				int member = in.nextInt();
				for (int j = 0; j < member; j++)
					person.put(in.nextInt(), i);
			}
			System.out.println("Scenario #" + cas++);
			while (true)
			{
				String op = in.next();
				if (op.charAt(0) == 'S')
					break;
				if (op.charAt(0) == 'E')
				{
					int num = in.nextInt();
					int index = person.get(num);
					if (sub[index].isEmpty())
					{
						mainqueue.add(index);
					}
					sub[index].add(num);
				}
				else 
				{
					int t = mainqueue.get(0);
					System.out.println(sub[t].removeFirst());
					if (sub[t].isEmpty())
						mainqueue.remove(0);
				}
			}
			System.out.println();
		}
	}
}
