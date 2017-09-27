//题意：
//给定一些话题
//每个话题包括ID，询问的次数，开始询问的时间，处理一次询问的时间，询问一次的间隔时间
//一些人
//每个人包括ID，能处理的询问的一些ID
//如果有多个人瞄准了同一个任务
//两个人上一次处理任务的开始时间早的哪个优先
//如果相同，ID小的优先
//现在输出处理完所有询问要花的时间
//每次情形后输出一行空行
//分析：
//对于“询问一次的间隔时间”应该这样理解：
//从开始接受处理到下一次开始处理之间至少要花那么多时间
//在这段时间里一个人可以处理其他的询问，不一定非要等待
//一开始不理解题意，按照blog.h5min.cn/pb1995/article/details/48736317的做法实现了一遍


import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	static int taskNumber, personNumber, Time, tq[];//tq用来存储可以处理的task
	static HashMap<Integer, Integer> map = new HashMap<>();//taskID-输入的顺序
	static boolean isEnd;
	static Topic topics[];
	static Person persons[];
	static Comparator<Person> cpt = new Comparator<Person>() {
		
		@Override
		public int compare(Person o1, Person o2) {
			// TODO Auto-generated method stub
			if (o1.lastProcessTopicTime != o2.lastProcessTopicTime) 
				return o1.lastProcessTopicTime - o2.lastProcessTopicTime;
			return o1.id - o2.id;
		}
	};

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = 1;
		while ((taskNumber = in.nextInt()) != 0) {
			tq = new int[taskNumber];
			map.clear();
			isEnd = false;
			Time = 0;
			topics = new Topic[taskNumber];
			for (int i = 0; i < taskNumber; i++) {
				Topic t = new Topic(in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
				map.put(t.id, i);
				topics[i] = t;
			}
			personNumber = in.nextInt();
			persons = new Person[personNumber];
			for (int i = 0; i < personNumber; i++) {
				Person p = new Person(in.nextInt(), in.nextInt());
				for (int j = 0; j < p.taskNum; j++)
					p.task[j] = in.nextInt();
				p.lastProcessTopicTime = p.currentDoingTopicID = -1;
				persons[i] = p;
			}
			while (!isEnd) {
				update();
				check();
				//print();
				Time++;
			}
			System.out.printf("Scenario %d: All requests are serviced within %d minutes.\n", cas++, Time-1);
		}
	}
	
	public static void update() {
		for (int i = 0; i < taskNumber; i++) {
			if (topics[i].num > 0) {
				if (Time == topics[i].firstValidTime) {//第一次处理
					tq[i]++;
					topics[i].num--;
					topics[i].firstValidTime = -1;
					topics[i].lastProcessTime = Time;
				}
				if (Time - topics[i].lastProcessTime == topics[i].rest && topics[i].firstValidTime == -1) {//当前Time正好可以处理下一次
					tq[i]++;
					topics[i].num--;
					topics[i].lastProcessTime = Time;
				}
			}
		}
		Arrays.sort(persons, cpt);
		for (int i = 0; i < personNumber; i++) {//把在当前Time正好做完的人的信息更新一次
			if (persons[i].isWorking) {
				int index = map.get(persons[i].currentDoingTopicID);
				if (Time - persons[i].lastProcessTopicTime == topics[index].process) {
					persons[i].isWorking = false;
					persons[i].currentDoingTopicID = -1;
				}
			}
		}
		for (int i = 0; i < taskNumber; i++) {//把准备处理的task分配给空闲的人。这里和原blog上写的不一样，看不懂原来的，自己写了一个
			if (tq[i] > 0) {
				for (int j = 0; j < personNumber; j++) {
					if (!persons[j].isWorking && persons[j].canHandle(topics[i].id)) {
						tq[i]--;
						persons[j].isWorking = true;
						persons[j].currentDoingTopicID = topics[i].id;
						persons[j].lastProcessTopicTime = Time;
						break;
					}
				}
			}
		}
	}
	
	public static void check() {
		isEnd = true;
		for (int i = 0; i < personNumber; i++) {
			if (persons[i].isWorking) 
				isEnd = false;
		}
		for (int i = 0; i < taskNumber; i++) {
			if (topics[i].num > 0)
				isEnd = false;
		}
	}
	
	public static void print() {
		System.out.println("Time = " + Time);
		for(int i=0; i<personNumber; i++){
			System.out.printf("%-8d %-8d %-8d   ",persons[i].id, persons[i].currentDoingTopicID, persons[i].lastProcessTopicTime);
			System.out.println(persons[i].isWorking);
		}
		for(int i=0; i<taskNumber; i++){
			System.out.printf("%d:%d\t",topics[i].id,tq[i]);
		}
		System.out.printf("\n----------------\n");
	}
	
}

class Topic {
	int id, num, firstValidTime, process, rest, lastProcessTime;
	public Topic(int i, int n, int f, int p, int r) {
		id = i;
		num = n;
		firstValidTime = f;
		process = p;
		rest = r;
	}
}

class Person {
	int id, taskNum, task[], lastProcessTopicTime, currentDoingTopicID;
	boolean isWorking;
	public Person(int i, int n) {
		id = i;
		task = new int[n];
		taskNum = n;
	}
	
	public boolean canHandle(int id) {
		for (int i = 0; i < taskNum; i++) 
			if (task[i] == id)
				return true;
		return false;
	}
}
