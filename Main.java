import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	
	static HashMap<String, Integer> name_size = new HashMap<>();
	static HashMap<String, HashMap<Integer, Integer>> index_value = new HashMap<>();
	static boolean flag = true;
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		File f = new File("in.txt");
		Scanner in = new Scanner(f);
		String s;
		INPUT:
		while (!(s = in.nextLine()).equals("."))
		{
			name_size.clear();
			index_value.clear();
			ArrayList<String> order = new ArrayList<>();
			do 
			{
				order.add(s);
			}while (!(s = in.nextLine()).equals("."));
			MAIN:
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
						if (sub[1].contains("["))
						{
							String rightname = sub[1].substring(0, sub[1].indexOf('['));
							int rightindex = calculate(sub[1].substring(sub[1].indexOf('[') + 1, sub[1].length() - 1));
							if (flag && index_value.get(rightname).containsKey(rightindex))
							{
								rightvalue = index_value.get(rightname).get(rightindex);
							}
							else
								flag = false;
						}
						else
						{
							rightvalue = Integer.parseInt(sub[1]);
						}
					}
					else 
						flag = false;
					if (!flag)
					{
						System.out.println(i + 1);
						continue INPUT;
					}
					else 
					{
						index_value.get(leftname).put(leftindex, rightvalue);
					}
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
		{
			return Integer.parseInt(s);
		}
		while (s.indexOf('[') != s.lastIndexOf('['))
		{
			
		}
	}
}
