/**
 * 题意：
 * 给定一个黑板，在上面贴海报
 * 输入起始和终止端点
 * 后面的海报会覆盖前面的海报
 * 输出最后能看到的海报的数量
 * 分析：
 * 由于黑板的长度很大，不能直接以黑板为线段操作
 * 要先把原始的坐标离散化为从小到大的下标
 * 但是考虑这样一组数据：
 * 1 10
 * 1 4
 * 6 10
 * 最后染色为1 1 2 2
 * 所以要在相差大于2的地方插入一个数字
 */


import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
import java.util.TreeSet;

public class Main {
	static final int maxn = 20005;
	static int size, ans, l[], r[];
	static int tree[] = new int[maxn * 16];//记录能看到的海报的编号，没有的记为-1
	static boolean vis[] = new boolean[maxn * 3];//查询的时候使用，false代表没有被记录进去
	static TreeSet<Integer> set  = new TreeSet<Integer>();//存放海报的起始和终止端点以及离散化后添加进的点
	static HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();//把离散化后的点从小到大排序，数字映射为下标
	//一开始我写的是map = new HashMap<>()，结果CE，说明POJ的编译器已经过时了
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = in.nextInt();
		while (cas-- != 0) {
			set.clear();
			map.clear();
			ans = 0;
			int n = in.nextInt();
			l = new int[n];
			r = new int[n];
			Arrays.fill(tree, -1);
			Arrays.fill(vis, false);
			for (int i = 0; i < n; i++) {
				l[i] = in.nextInt();
				r[i] = in.nextInt();
				set.add(l[i]);
				set.add(r[i]);
			}
			discret();
			mapped();
			size = set.size();
			for (int i = 0; i < n; i++) {
				int x = map.get(l[i]);
				int y = map.get(r[i]);
				update(1, 0, size - 1, x, y, i);
			}
			query(1, 0, size - 1);
			System.out.println(ans);
		}
	}
	
	public static void discret() {
		Integer tmp[] = new Integer[set.size()];
		set.toArray(tmp);
		for (int i = 1; i < tmp.length; i++)
			if (tmp[i] - tmp[i - 1] > 1)
				set.add(tmp[i] - 1);
	}
	
	public static void mapped() {
		Integer tmp[] = new Integer[set.size()];
		set.toArray(tmp);
		for (int i = 0; i < tmp.length; i++) 
			map.put(tmp[i], i);
	}
	
	public static void update(int node, int left, int right, int ql, int qr, int val) {
		if (ql <= left && right <= qr) {
			tree[node] = val;
			return;
		}
		push_down(node);
		int mid = (left + right) / 2;
		if (ql <= mid)
			update(node * 2, left, mid, ql, qr, val);
		if (mid < qr)
			update(node * 2 + 1, mid + 1, right, ql, qr, val);
	}
	
	public static void push_down(int node) {
		if (tree[node] != -1) {
			tree[node * 2] = tree[node * 2 + 1] = tree[node];
			tree[node] = -1;
		}
	}
	
	public static void query(int node, int l, int r) {
		if (tree[node] != -1) {
			if (!vis[tree[node]]) {
				ans++;
				vis[tree[node]] = true;
			}
			return;
		}
		if (l == r)
			return;
		int mid = (l + r) / 2;
		query(node * 2, l, mid);
		query(node * 2 + 1, mid + 1, r);
	}
}

/*
 * 事实上，这样的做法还是有问题的
 * 1 10
 * 1 4
 * 5 10
 * 答案应该是3，但是这个程序输出2
 * 4 5的差没有超过2所以中间不会补数字进去
 * 我一开始的做法是在update左闭右开的区间，也就是update(1, 0, size - 1, x, y - 1, i)
 * 但是这样反而WA了
 * 说明POJ本身也没有考虑到这样的问题
 */
