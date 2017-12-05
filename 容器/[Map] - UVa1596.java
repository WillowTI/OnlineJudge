//题意：
//输入一些数组的声明和赋值操作
//让你判断是否都是合法的
//不合法的使出哪一行不合法（从1开始计数）
//不合法的情况只有数组下标越界和使用未赋值的变量
//合法的输出0
//分析：
//声明语句不包含"="
//赋值有"="
//声明语句把数组名和大小记录下来
//可以用HashMap(name-size)
//赋值语句分别检测"="左右两边是否都合法
//由于下标也可以用数组元素来表示（如a[b[0]]）
//所以可以用递归的方法计算其值
//用HashMap保存哪个数组的下标记录的什么值
//也就是通过name查找另一个HashMap
//这个内层的HashMap(index-value)

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	
	static HashMap<String, Integer> name_size = new HashMap<>();
	static HashMap<String, HashMap<Integer, Integer>> index_value = new HashMap<>();
	static boolean flag = true;//flag记录这句赋值语句是否合法
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		String s;
		INPUT:
		while (!(s = in.nextLine()).equals("."))
		{
			name_size.clear();
			index_value.clear();
			ArrayList<String> order = new ArrayList<>();//先把所有的命令都保存下来，逐行模拟
			do 
			{
				order.add(s);
			}while (!(s = in.nextLine()).equals("."));
			for (int i = 0; i < order.size(); i++)
			{
				String ord = order.get(i);
				if (ord.contains("="))
				{
					flag = true;
					String sub[] = ord.split("=");
					String leftname = sub[0].substring(0, sub[0].indexOf('['));
					int rightvalue = 0;
					int leftindex = calculate(sub[0].substring(sub[0].indexOf('[') + 1, sub[0].length() - 1));
					if (flag && leftindex >= 0 && leftindex < name_size.get(leftname))
					{
						rightvalue = calculate(sub[1]);
					}
					else 
						flag = false;
					if (!flag)
					{
						System.out.println(i + 1);
						continue INPUT;
					}
					else 
						index_value.get(leftname).put(leftindex, rightvalue);
				}
				else 
				{
					String name = ord.substring(0, ord.indexOf('['));
					int size = Integer.parseInt(ord.substring(ord.indexOf('[') + 1, ord.length() - 1));
					name_size.put(name, size);
					index_value.put(name, new HashMap<>());
				}
			}
			System.out.println("0");
		}
	}
	
	static int calculate(String s)
	{
		if (!s.contains("["))
			return Integer.parseInt(s);
		String name = s.substring(0, s.indexOf('['));
		int index = calculate(s.substring(s.indexOf('[') + 1, s.length() - 1));
		if (!flag || index == -1 || !index_value.get(name).containsKey(index) || index_value.get(name).get(index) == -1)
		{
			flag = false;
			return -1;//一旦检测到不合法的就返回-1，因为题目说了数组的元素的都是非负的，这样便于后续的判断
		}
		return index_value.get(name).get(index);
	}
}
