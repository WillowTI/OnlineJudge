import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {
	
	static LinkedList<String> list [] = new LinkedList[10000007];
	
	public static int hash(String s) {
		int ret = 0;
		for (int i = 0; i < s.length(); i++) {
			ret *= 31; 
			ret += (int)s.charAt(i);
			ret %= 10000007;
		}
		return ret;
	}
	
	public static boolean contains(String s) {
		int hash = hash(s);
		if (list[hash].size() == 0)
			return false;
		for (String cur : list[hash]) {
			if (s.equals(cur)) 
				return true;
		}
		return false;
	}
	
	public static void add(String s) {
		int hash = hash(s);
		if (!contains(s)) {
			list[hash].add(s);
		}
	}
	
	public static void init() {
		for (int i = 0; i < 10000007; i++)
			list[i] = new LinkedList<>();
	}

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		File f = new File("dictionary.txt");
		Scanner in = new Scanner(f);
		init();
		while (in.hasNext()) {
			String s = in.next();
			list[hash(s)].add(s);
		}
		f = new File("paper.txt");
		in = new Scanner(f);
		while (in.hasNextLine()) {
			String next = in.nextLine();
			String sub[] = next.split("[^a-zA-Z]");
			for (String cur : sub) {
				if (cur.length() != 0) {
					
				}
			}
		}
	}

}
