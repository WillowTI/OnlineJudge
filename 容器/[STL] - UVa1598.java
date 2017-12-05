//题意：
//给定n条指令
//指令分3种
//1.BUY size price（想以price的代价买到size个东西）
//2.SELL size price（想以price的利润卖出size个东西）
//3.CANSEL id（取消第id个指令，从1开始计数）
//当BUY的最高价格大于等于SELL的最低价格时就发生交易
//size为BUY的最高价格的最小id的size与SELL的最大价格的最小id的size的较小者
//直到条件不满足为止
//当有多个相同price的指令满足条件时按照输入的先后顺序处理
//每发生一次交易输出TRADE size price
//对于BUY指令，price按照sell的price
//（想象成买家有一个估价，在低于这个价格的所有商家里总归要找最便宜的）
//SELL相反
//即使两条指令的price一样但是仍按照两条指令来进行
//如果没有一个满足条件的特殊处理，具体输出看print函数
//分析：
//书上说用PriorityQueue来做
//但是每操作一次其size就会被改变
//那就用ArrayList每出现一次改变就sort一次
//毫无悬念的TLE了
//网上的做法就是这里的做法
//开多个map来存储信息（具体存放什么信息看代码注释）
//（我一开始只用了两个ArrayList实在是太简单了）
//由于要有序的处理所以用TreeMap和TreeSet
//map.descendingMap()返回键值从大到小的map

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.TreeSet;

public class Main {
	
	static TreeMap<Integer, TreeSet<Integer>> buy = new TreeMap<>();//money - id set
	static TreeMap<Integer, TreeSet<Integer>> sell = new TreeMap<>();
	static TreeMap<Integer, Integer> buy_whole = new TreeMap<>();//money - whole size
	static TreeMap<Integer, Integer> sell_whole = new TreeMap<>();
	static ArrayList<Order> order = new ArrayList<>();

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		boolean first = true;
		while (in.hasNextInt()) {
			buy.clear();
			sell.clear();
			buy_whole.clear();
			sell_whole.clear();
			order.clear();
			if (first) 
				first = false;
			else 
				System.out.println();
			int n = in.nextInt();
			for (int t = 0; t < n; t++) {
				String s = in.next();
				if (s.charAt(0) == 'B') {
					int size = in.nextInt();
					int price = in.nextInt();
					Order o = new Order(size, price, 0, t);
					order.add(o);
					if (!buy.containsKey(price)) {
						buy.put(price, new TreeSet<>());
					}
					buy.get(price).add(t);
					if (!buy_whole.containsKey(price)) {
						buy_whole.put(price, 0);
					}
					buy_whole.put(price, buy_whole.get(price) + size);
					trade(false);
				} else if (s.charAt(0) == 'S') {
					int size = in.nextInt();
					int price = in.nextInt();
					Order o = new Order(size, price, 1, t);
					order.add(o);
					if (!sell.containsKey(price)) {
						sell.put(price, new TreeSet<>());
					}
					sell.get(price).add(t);
					if (!sell_whole.containsKey(price)) {
						sell_whole.put(price, 0);
					}
					sell_whole.put(price, sell_whole.get(price) + size);
					trade(true);
				} else {
					boolean flag = false;
					int index = in.nextInt() - 1;
					if (index >= 0 && index < order.size()) {
						order.add(new Order(0, 0, 2, t));
						if (order.get(index).type == 0 && order.get(index).size != 0) {//如果不加后半句限制条件可能会有NullPointExceptioon
							buy.get(order.get(index).price).remove(order.get(index).id);//首先从set中移除id
							if (buy.get(order.get(index).price).isEmpty()) 
								buy.remove(order.get(index).price);//如果删完后set为空，那就把这个set删掉
							buy_whole.put(order.get(index).price, buy_whole.get(order.get(index).price) - order.get(index).size);//这个price下的size减掉被取消订单的size
							if (buy_whole.get(order.get(index).price) == 0) //如果删完后size为0就把这对K-V删掉
								buy_whole.remove(order.get(index).price);
						} else if (order.get(index).type == 1 && order.get(index).size != 0) {//对于SELL的指令同理
							sell.get(order.get(index).price).remove(order.get(index).id);
							if (sell.get(order.get(index).price).isEmpty()) 
								sell.remove(order.get(index).price);
							sell_whole.put(order.get(index).price, sell_whole.get(order.get(index).price) - order.get(index).size);
							if (sell_whole.get(order.get(index).price) == 0) 
								sell_whole.remove(order.get(index).price);
						}
						order.get(index).size = 0;
					}
				}
				print();
			}
		}
	}
	public static void print() {
		System.out.print("QUOTE ");
		if (buy_whole.size() == 0)
			System.out.print("0 0 - ");
		else {
			System.out.print(buy_whole.get(buy_whole.descendingMap().firstKey()) + " ");
			System.out.print(buy_whole.descendingMap().firstKey() + " - ");
		}
		if (sell_whole.size() == 0)
			System.out.print("0 99999");
		else {
			System.out.print(sell_whole.get(sell_whole.firstKey()) + " ");
			System.out.print(sell_whole.firstKey());
		}
		System.out.println();
	}
	public static void trade(boolean flag) {
		while (!buy.isEmpty() && !sell.isEmpty()) {//由于这里和CANCEL操作直接把为空/为0的V删除了，所以只要判断是否为空就知道能不能做
			int price1 = buy.descendingMap().firstKey();
			int price2 = sell.firstKey();
			if (price1 >= price2) {//只要能匹配到就做
				int id1 = buy.get(price1).first();
				int id2 = sell.get(price2).first();
				int size = Math.min(order.get(id1).size, order.get(id2).size);
				order.get(id1).size -= size;
				order.get(id2).size -= size;
				buy_whole.put(price1, buy_whole.get(price1) - size);
				sell_whole.put(price2, sell_whole.get(price2) - size);
				System.out.println("TRADE " + size + " " + (flag ? price1 : price2));
				if (order.get(id1).size == 0) buy.get(price1).remove(id1);//和CANCEL的操作类似
				if (order.get(id2).size == 0) sell.get(price2).remove(id2);
				if (buy_whole.get(price1) == 0) buy_whole.remove(price1);
				if (sell_whole.get(price2) == 0) sell_whole.remove(price2);
				if (buy.get(price1).isEmpty()) buy.remove(price1);
				if (sell.get(price2).isEmpty()) sell.remove(price2);
			}
			else 
				return;
		}
	}
}

class Order {
	int type, size, price, id;//type代表操作的类型，0为BUY，1为SELL，2为CANCEL
	public Order(int s, int p, int t, int i) {
		size = s;
		price = p;
		type = t;
		id = i;
	}
}