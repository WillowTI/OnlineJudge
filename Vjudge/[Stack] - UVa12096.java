题意：
模拟栈操作
PUSH：空集入栈
DUP：复制栈顶元素并入栈
UNION：从栈顶出栈两个集合，入栈二者的并集
INTERSECT：从栈顶出栈两个集合，入栈二者的交集
ADD：从栈顶出栈两个集合，然后把先出栈的集合加入到后出栈的集合，并入栈

分析：
里面的元素是集合的集合
可以无限嵌套
出现新元素的唯一时候就是ADD操作
可以把已经出现的集合添加到ArrayList中
HashSet的元素表示这是哪些集合的集合
空集就代表为空
用HashMap记录HashSet对应ArrayList的索引
如果这个HashSet没有出现过就添加进去

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Stack;

public class Main {
	static HashMap<HashSet<Integer>, Integer> IDcache = new HashMap<>();
	static ArrayList<HashSet<Integer>> Setcache = new ArrayList<>();
	static Stack<Integer> s = new Stack<>();
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = in.nextInt();
		for (int t = 0; t < cas; t++)
		{
			IDcache.clear();
			Setcache.clear();
			s.clear();
			int n = in.nextInt();
			for (int i = 0; i < n; i++)
			{
				String op = in.next();
				if (op.charAt(0) == 'P')
					s.push(ID(new HashSet<Integer>()));
				else if (op.charAt(0) == 'D')
					s.push(s.peek());
				else 
				{
					HashSet<Integer> x1 = (HashSet<Integer>)(Setcache.get(s.pop())).clone();
					HashSet<Integer> x2 = (HashSet<Integer>)(Setcache.get(s.pop())).clone();
					HashSet<Integer> x = new HashSet<>();
					ID(x1);
					ID(x2);
					if (op.charAt(0) == 'U')
					{
						x1.addAll(x2);
						x = x1;
					}
					if (op.charAt(0) == 'I')
					{
						x1.retainAll(x2);
						x = x1;
					}
					if (op.charAt(0) == 'A')
					{
						x = x2;
						x.add(ID(x1));
					}
					s.push(ID(x));
				}
				System.out.println(Setcache.get(s.peek()).size());
			}
			System.out.println("***");
		}
	}
	
	public static int ID(HashSet<Integer> x)
	{
		if (IDcache.containsKey(x))
			return IDcache.get(x);
		Setcache.add(x);
		int ret = Setcache.size() - 1;
		IDcache.put(x, ret);
		return ret;
	}
}
