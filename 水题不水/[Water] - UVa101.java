import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	static int ai, aj, bi, bj, n;
	static ArrayList<ArrayList<Integer>> list = new ArrayList<ArrayList<Integer>>();
	//一开始不知道怎么声明ArrayList数组，后来发现只要ArrayList套一个ArrayList就行了
	public static void find(int a, int b)
	{
		int cnt = 0;
		for (int i = 0;i < n; i++)
		{
			for (int j = 0; j < list.get(i).size(); j++)
			{
				if (a == list.get(i).get(j))
				{
					ai = i;
					aj = j;
					cnt++;
				}
				if (b == list.get(i).get(j))
					//这里是一个坑点，因为a有可能是等于b的，所以a判断完后b也要判断
					//一开始写的是else if ...就错了
				{
					bi = i;
					bj = j;
					cnt++;
				}
				if (cnt == 2)
					break;
			}
		}
	}
	
	public static void onto ()
	{
		while (aj < list.get(ai).size())
		{
			int num = list.get(ai).get(aj);
			list.get(ai).remove(aj);
			list.get(bi).add(num);
		}
	}
	
	public static void clear (int pi, int pj)
	{
		while (pj + 1< list.get(pi).size())
		{
			int num = list.get(pi).get(pj + 1);
			list.get(pi).remove(pj + 1);
			list.get(num).add(num);
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
			Scanner in = new Scanner(System.in);
			n = in.nextInt();
			String s1;
			for (int i = 0; i < n; i++)
			{
				list.add(i, new ArrayList<Integer>());
				list.get(i).add(i);
			}
			while (in.hasNext())
			{
				s1 = in.next();
				if (s1.charAt(0) == 'q')
					break;
				int a = in.nextInt();
				String s2 = in.next();
				int b = in.nextInt();
				find(a, b);
				if (ai != bi)
				{
					if (s1.charAt(0) == 'm')
						clear(ai, aj);
					if (s2.charAt(1) == 'n')
						clear(bi, bj);
					onto();
				}
			}
			for (int i = 0; i < n; i++)
			{
				System.out.print(i + ":");
				for (int j = 0; j < list.get(i).size(); j++)
					System.out.print(" " + list.get(i).get(j));
				System.out.println();
			}
	}
}
