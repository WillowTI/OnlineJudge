//题意：
//丑数是指不能被2， 3， 5以外的素数整除的数
//也就是因数只能是2， 3， 5
//输出第1500个丑数
//1为第一个数字
//
//分析：
//显然要有序的存放枚举出来的数字
//保存类型为Long
//避免在某一个点上poll出来的是负数
//数字的数值越小，优先级越大
//用PriorityQueue的话
//在添加的时候先判断是否contain再添加
//或者用TreeSet
//TreeSet中数值越小的优先级越大
//TreeSet应存放Long类型的元素
//用TreeSet更快

import java.util.Comparator;
import java.util.Scanner;
import java.util.TreeSet;

public class Main {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		Comparator<Long> comparator = new Comparator<Long>() {
			
			@Override
			public int compare(Long o1, Long o2) {
				// TODO Auto-generated method stub
				if (o1 > o2)
					return 1;
				else if (o1 < o2)
					return -1;
				else 
					return 0;
//				如果改写成
//				if (o1 > o2) 
//					return 1; 
//				else 
//					return -1;
//				那么没有0的情况也就判定为这两个数字不重复
			}
		};
		TreeSet<Long> pq = new TreeSet<>(comparator);
		int times = 1;
		long n = 1;
		while (times != 1500)
		{
			pq.add(n * 2);
			pq.add(n * 3);
			pq.add(n * 5);
			n = pq.pollFirst();
			times++;
		}
		System.out.println("The 1500'th ugly number is " + n +".");
	}
}
