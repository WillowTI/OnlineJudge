import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		File f = new File("in.txt");
		Scanner in = new Scanner(f);
		String s;
		while (!(s = in.nextLine()).equals("."))
		{
			HashMap<String, Integer> name_size = new HashMap<>();
			HashMap<String, HashMap<Integer, Integer>> index_value = new HashMap<>();
			ArrayList<String> order = new ArrayList<>();
			do 
			{
				order.add(s);
			}while (!(s = in.nextLine()).equals("."));
			int ans = 0;
			MAIN:
			for (int i = 0; i < order.size(); i++)
			{
				String ord = order.get(i);
				if (ord.contains("="))
				{
					boolean flag = true;
					String sub[] = ord.split("=");
					while (sub[0].lastIndexOf('[') != sub[0].indexOf('['))
					{
						
					}
				}
				else 
				{
					String name = ord.substring(0, ord.indexOf('['));
					int size = Integer.parseInt(ord.substring(ord.indexOf('[') + 1, ord.length() - 1));
					name_size.put(name, size);
				}
			}
			System.out.println(name_size);	
		}
	}
}