/*
 * 题意：
 * 输入房子的起始坐标和终止坐标和高度
 * 输出最后能看到的面积是多少
 * 高度高的能把低的覆盖掉
 * 还有一种技巧是矩形分割
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;
import java.util.TreeSet;

public class Main {
	static int height[], l[], r[], tree[];
	static Integer mapped[];//存放离散化后的数字
	static TreeSet<Integer> set = new TreeSet<Integer>();
	static HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			set.clear();
			map.clear();
			int n = in.nextInt();
			height = new int[n];
			l = new int [n];
			r = new int [n];
			tree = new int[n * 8 + 5];
			for (int i = 0; i < n; i++) {
				l[i] = in.nextInt();
				r[i] = in.nextInt();
				height[i] = in.nextInt();
				set.add(l[i]);
				set.add(r[i]);
			}
			discrete();
			int size = set.size();
			for (int i = 0; i < n; i++) {
				int x = map.get(l[i]);
				int y = map.get(r[i]);
				update(1, 1, size, x, y, height[i]);
			}
			long ans = query(1, 1, size);
			//dbg(1, 1, size);
			System.out.println(ans);
		}
	}
	
	public static void dbg(int node, int left, int right) {
		System.out.printf("(%d %d):%d\n", mapped[left - 1], mapped[right - 1], tree[node]);
		if (left + 1 == right)
			return;
		int mid = (left + right) / 2;
		dbg(node * 2, left, mid);
		dbg(node * 2 + 1, mid, right);
	}
	
	public static void discrete() {
		mapped = new Integer[set.size()];
		set.toArray(mapped);
		for (int i = 1; i <= set.size(); i++) 
			map.put(mapped[i - 1], i);
	}
	
	public static void update(int node, int left, int right, int ql, int qr, int val) {
		if (ql <= left && right <= qr) {
			tree[node] = Math.max(tree[node], val);//只记录最大的高度
			return;
		}
		int mid = (left + right) / 2;
		if (ql < mid)//注意要严格大于或小于，因为元线段的长度为1
			update(node * 2, left, mid, ql, qr, val);
		if (mid < qr)
			update(node * 2 + 1, mid, right, ql, qr, val);
	}
	
	public static long query(int node, int left, int right) {
		if (left + 1 == right)//访问到叶子节点时返回结果
			/*原先是tree[node] != 0就返回，想省时间，但是考虑：
			 *2 5 10
			 *1 5 3
			 *1 5 4
			 *最大的区间覆盖为4但是内部只有(1,2)是4，所以还是访问到叶子节点时才是一定正确的
			 */
			return (long)tree[node] * (mapped[right - 1] - mapped[left - 1]);
		push_down(node, left, right);//没有访问到时标记下拉
		int mid = (left + right) / 2;
		long a = query(node * 2, left, mid);
		long b = query(node * 2 + 1, mid, right);
		return a + b;
	}
	
	public static void push_down(int node, int left, int right) {
		if (tree[node] != 0) {
			tree[node * 2] = Math.max(tree[node * 2], tree[node]);//标记只记录最大值，小的被覆盖
			//同时是前面那组数据，在更新(1,5)区间时还是要保留前面的10
			tree[node * 2 + 1] = Math.max(tree[node * 2 + 1], tree[node]);
			tree[node] = 0;
		}
	}
}