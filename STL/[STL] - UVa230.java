//题意：
//先输入图书的信息
//每行信息包括一本书的标题和作者名字
//输入里的标题是用双引号括起来的
//但是真正的标题不包含括号
//标题和作者用"by"分割
//作者名有可能有双引号
//原本的书架是有序的
//按照作者名的升序排
//作者名相同时按照标题的升序排
//接下来是借书，还书，排序的命令
//借书把书从书架上拿走
//还书把书暂时放在一起
//排序的时候把还过来的书放回书架上
//输出每本书具体放在哪里
//包括放在第一个和某本书后面两种位置
//处理的顺序按照初始化的排序标准
//分析：
//用LinkedList模拟书架
//虽然一一遍历比较慢
//但是胜在删除和插入操作
//用HashMap保存标题和作者名
//用ArrayList保存归还的书

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {
	static Comparator<NODE> cpt = new Comparator<NODE>() {
		
		@Override
		public int compare(NODE o1, NODE o2) {
			// TODO Auto-generated method stub
			if(!o1.author.equals(o2.author))
				return o1.author.compareTo(o2.author);
			return o1.title.compareTo(o2.title);
		}
	};
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		String s;
		LinkedList<NODE> list = new LinkedList<>();
		HashMap<String, String> map = new HashMap<>();
		while (!(s = in.nextLine()).equals("END"))
		{
			int loc = s.indexOf("by");
			String title = s.substring(1, loc - 2);
			String author = s.substring(loc + 3);
			map.put(title, author);
			NODE n = new NODE(title,author);
			list.add(n);
		}
		ArrayList<NODE> ReturnList = new ArrayList<>();
		Collections.sort(list, cpt);
		while (!(s = in.nextLine()).equals("END"))
		{
			if (s.charAt(0) == 'B')
			{
				String title = s.substring(s.indexOf('\"') + 1, s.length() - 1);
				for (int i = 0; i < list.size(); i++)
				{
					if (list.get(i).title.equals(title))
					{
						list.remove(i);
						break;
					}
				}
			}
			else if (s.charAt(0) == 'R')
			{
				String title = s.substring(s.indexOf('\"') + 1, s.length() - 1);
				ReturnList.add(new NODE(title, map.get(title)));
			}
			else 
			{
				Collections.sort(ReturnList, cpt);
				for (int i = 0; i < ReturnList.size(); i++)
				{
					NODE cur = ReturnList.get(i);
					if (list.size() == 0 || cpt.compare(cur, list.getFirst()) < 0)
					{
						list.addFirst(cur);
						System.out.println("Put \"" + cur.title + "\" first");
					}
					else 
					{
						for (int j = 0; j < list.size(); j++)
						{
							if (j != list.size() - 1 && cpt.compare(list.get(j), cur) < 0 && cpt.compare(cur, list.get(j + 1)) < 0)
							{
								System.out.println("Put \"" + cur.title + "\" after \"" + list.get(j).title + "\"");
								list.add(j + 1, cur);
								break;
							}
							else if (j == list.size() - 1 && cpt.compare(list.get(j), cur) < 0)
							{
								System.out.println("Put \"" + cur.title + "\" after \"" + list.get(j).title + "\"");
								list.add(j + 1, cur);
								break;
							}
						}
					}
				}
				ReturnList.clear();
				System.out.println("END");
			}
		}
	}
}

class NODE
{
	String title, author;
	NODE (String s1, String s2)
	{
		title = s1;
		author = s2;
	}
}