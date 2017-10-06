//紫书把这道题放在STL的练习中
//但事实上这是Trie树的应用
//先介绍Trie树（字典树）的概念
//用树存储一些字符串
//每个节点包括一个next数组，用于存储下一个的值
//数组的大小就是每位能取的字符个数
//和一个id，用于记录这个字符串的下标
//如果两个字符串的前n个字符相同
//那么直到第n + 1个字符都有相同的父节点
//题意：
//对于Fibonacci的前100000项
//输入不超过40个数字的字符串
//输出最先匹配Fibonacci数列前缀的下标
//如果在这100000项中不存在，输出-1
//分析：
//用BigInteger做加法再一一匹配肯定超时
//那就用Trie树存储数字
//而且不要老老实实做加法
//因为输入的是前40个数字
//那只要计算高位就行了
//为了避低位的进位
//计算前50位
//看看BigInteger和模拟手算的区别在哪：
//假设在上一步的加法中是
//91111111
//32345678
//——————————
//123456789
//结果是91111111被替换成123456789
//下一步要计算
//123456789
// 32345678
//只保留高位8位
//12345678
// 3234567
//如果用BigInteger要把另一个东西也去掉最低位
//这样就避免了手算，略简便一点
//在文末会附上手算的代码

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	static Trie head = new Trie();
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		BigInteger fib[] = new BigInteger[2];
		fib[0] = fib[1] = BigInteger.ONE;
		add(fib[0].toString(), 0);
		for (int i = 2; i < 100000; i++) {
			int p = i % 2;
			int q = (p + 1) % 2;
			fib[p] = fib[p].add(fib[q]);
			if (fib[p].toString().length() > 50) {
				fib[p] = new BigInteger(fib[p].toString().substring(0, fib[p].toString().length() - 1));
				fib[q] = new BigInteger(fib[q].toString().substring(0, fib[q].toString().length() - 1));
			}
			add(fib[p].toString().substring(0, Math.min(40, fib[p].toString().length())), i);
		}
		while (in.hasNextInt()) {
			int cas = in.nextInt();
			for (int i = 0; i < cas; i++) {
				System.out.printf("Case #%d: %d\n", i + 1, query(in.next()));
			}
		}
	}
	public static void add(String s, int id) {
		Trie cur = head;
		for (int i = 0; i < s.length(); i++) {
			int v = s.charAt(i) - '0';
			if (cur.next[v] == null) 
				cur.next[v] = new Trie();
			cur = cur.next[v];
			if (cur.id == -1) 
				cur.id = id;
		}
	}
	public static int query(String s) {
		Trie cur = head;
		for (int i = 0; i < s.length(); i++) {
			cur = cur.next[s.charAt(i) - '0'];
			if (cur == null)
				return -1;
		}
		return cur.id;
	}
}

class Trie {
	int id = -1;
	Trie next[] = new Trie[10];
}
//以下是手写加法的代码

/***
	int fib[][] = new int[2][25000]//最大的数的长度略大于20000
	......
	//以下为循环体内的代码
	int p = i % 2;
	int q = (i + 1) % 2;
	for (int j = start; j < end; j++) {
		fib[p][j] += fib[q][j];
		if (fib[p][j] >= 10) {
			fib[p][j] -= 10;
			fib[p][j + 1]++;
		} 
	}
	if (fib[p][end] != 0)
		end++;
	if (end - start > 50)
		start++;
	char s[] = new char[51];
	int pos = 0;
	for (int j = end - 1; j >= start; j--) 
		s[pos++] = (char)(fib[p][j] + '0');
	add(s, end - start, i);
***/