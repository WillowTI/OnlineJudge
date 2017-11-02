import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	static HashMap<Pair, Long> map = new HashMap<>();
	static long[] fib = new long[90];//fib记录fibonacci数列(1, 2, 3...)
	static long[] ps = new long[90];//ps记录前缀和(1, 3, 6...)89个正好不超过long的范围
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = in.nextInt();
		fib[0] = ps[0] = 1;
		fib[1] = 2;
		ps[1] = 3;
		for (int i = 2; i < 90; i++) {
			fib[i] = fib[i - 1] + fib[i - 2];
			ps[i] = ps[i - 1] + fib[i];
		}
		for (int t = 0 ;t < cas; t++) {
			System.out.printf("case #%d:\n", t);
			long num = in.nextLong();
			if (num == 0)
				System.out.println("0");//如果用query的方法，0会输出1，所以单独考虑
			else 
				System.out.println(query(num, 88));
		}
	}
	
	public static long query(long k, long m) {//返回用[0,m]的fibonacci序列分割k的方法数
		if (k < 0 || ps[(int)m] < k)//如果k小于0或者最大的前缀和都无法满足k那一定不行
			return 0;
		if (k == 0)//说明正好被分割完，完成1种方法
			return 1;
		Pair p = new Pair(k, m);
		if (map.containsKey(p))//用map保存点对，避免重复遍历
			return map.get(p);
		long ret = 0;
		for (int i = 0; i < m; i++) //数组是从0开始的，所以从0开始到m-1遍历。不能到m因为不能重复使用数字
			ret += query(k - fib[i], i);
		map.put(p, ret);//把结果放到map中
		return ret;
	}
}

class Pair {
	long x, y;
	public Pair(long a, long b) {
		x = a;
		y = b;
	}
	@Override
	public int hashCode() {//由于要hash比较，所以重写hashCode和equals方法
		return (int)(x + y);
	}
	@Override
	public boolean equals(Object obj) {
		Pair other = (Pair) obj;
		return x == other.x && y == other.y;
	}
	@Override
	public String toString() {
		return "Pair [x=" + x + ", y=" + y + "]";
	}
}