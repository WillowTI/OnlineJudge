//题意：
//给定一些邮箱地址和一些发送任务
//让你模拟这些操作
//并输出每步操作返回的3位码
//
//分析：
//虽然题目里给了很多非法的情况
//但是事实上大部分都避免了
//那就只要考虑处理任务的先后顺序了

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		HashSet<String> all = new HashSet<>();//all存放所有的完整地址
		while (true)
		{
			String s = in.next();
			if (s.equals("*"))
				break;
			s = in.next();
			int n = in.nextInt();
			for (int i = 0; i < n; i++)
				all.add(in.next() + "@" + s);
		}
		in.nextLine();
		while (true)
		{
			String s = in.next();
			if (s.equals("*"))
				break;
			String sender = s;
			String sendersub[] = s.split("@");
			HashSet<String > receiver = new HashSet<>();//判断收件人是否已经出现
			ArrayList<String> mta = new ArrayList<>();//按照输入的顺序存放后缀
			HashMap<String, ArrayList<String>> dest = new HashMap<>();//后缀-该后缀的完整收件人
			while (true)
			{
				s = in.next();
				if (s.equals("*"))
					break;
				if (receiver.contains(s))
					continue;
				receiver.add(s);
				String sub[] = s.split("@");
				if (!dest.containsKey(sub[1]))
				{
					mta.add(sub[1]);
					dest.put(sub[1], new ArrayList<String>());
				}
				dest.get(sub[1]).add(s);
			}
			in.nextLine();
			ArrayList<String> data = new ArrayList<>();
			while (true)
			{
				s = in.nextLine();
				if (s.equals("*"))
					break;
				data.add(s);
			}
			for (int i = 0;  i < mta.size(); i++)
			{
				String suffix = mta.get(i);
				ArrayList<String> target = dest.get(suffix);
				System.out.println("Connection between " + sendersub[1] +" and " + suffix);
				System.out.println("     HELO " + sendersub[1]);
				System.out.println("     250");//后缀永远是合法的
				System.out.println("     MAIL FROM:<" + sender + ">");
				System.out.println("     250");//发件人永远是合法的
				boolean flag = false;//只要有一个收件人是合法的就输出数据
				//If there is not at least one authorized recipient at a particular MTA, the DATA is not sent. 
				for (int j = 0; j < target.size(); j++)
				{
					System.out.println("     RCPT TO:<" + target.get(j) + ">");
					if (all.contains(target.get(j)))
					{
						flag = true;
						System.out.println("     250");
					}
					else 
						System.out.println("     550");
				}
				if (flag)
				{
					System.out.println("     DATA");
					System.out.println("     354");
					for (int j = 0; j < data.size(); j++)
						System.out.println("     " + data.get(j));
					System.out.println("     .");
					System.out.println("     250");
				}
				System.out.println("     QUIT");
				System.out.println("     221");
			}
		}
	}
}
