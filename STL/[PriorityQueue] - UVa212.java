//题意：
//给定手术室的个数，休息室的个数，开始工作的时间
//从手术室到休息室的运送时间，结束一场手术后的整理时间，结束一场休息后的整理时间
//病人的个数和每个病人的名字，手术时间，休息时间
//输出两张表
//1.每个病人开始与结束手术与休息的时间和在哪个手术室与休息室的编号
//2.每间手术室和休息室的使用时间与总的工作时间之比
//总工作时间是从开始到最后一个病人出院的时间段
//注：
//1.当多个病人可以进行手术时，按照病人输入的顺序进入由小到大的手术室编号
//当多个病人可以进行休息时，按照手术室编号从小到大的顺序进入休息室从小到大（题目表述不清）
//2.题目说只模拟一种情况，但实际上有多组输入
//每组输入都有行末空行
//3.输出的时候两张变表格之间有一个空行
//4.总时间可能为0，除以0的情况单独考虑
//5.当病人出手术室就要决定他去哪个休息室了
//看样例第4个和第6个人，如果认为是刚进休息室时决定的话6刚好能进2好休息室
//但这不符合题意，说明应该是手术结束的时候决定的
//6.输出的时候要注意格式化输出
//分析：
//先用优先级队列模拟进手术的过程
//对手术室排序：结束时间小的在前，结束时间相同的编号小的在前
//再模拟进休息室的过程
//对病人排序：结束时间小的在前，结束时间相同的手术室编号小的在前
//最后输出信息
//对病人排序：编号小的在前

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Main {
	static int n, m , T, t1, t2, t3, k;
	static ArrayList<Patient> patient = new ArrayList<>();//存放病人
	static ArrayList<ROOM> bed = new ArrayList<>();//存放休息室
	static PriorityQueue<ROOM> operating;//存放手术室
	static Room_BED Room[] = new Room_BED[50];//每个手术室的使用情况
	static Room_BED Bed[] = new Room_BED[50];//每个休息室的使用情况
	static Comparator<ROOM> cpt1 = new Comparator<ROOM>() {
		
		@Override
		public int compare(ROOM a, ROOM b) {
			// TODO Auto-generated method stub
			if (a.end != b.end)
				return a.end - b.end;
			return a.id - b.id;
		}
	};
	static Comparator<Patient> cpt2 = new Comparator<Patient>() {
		
		@Override
		public int compare(Patient a, Patient b) {
			// TODO Auto-generated method stub
			if (a.oend != b.oend) 
				return a.oend - b.oend;
			return a.room - b.room;
		}
	};
	static Comparator<Patient> cpt3 = new Comparator<Patient>() {
		
		@Override
		public int compare(Patient a, Patient b) {
			// TODO Auto-generated method stub
			return a.id - b.id;
		}
	};
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		for (int i = 0; i < 50; i++) {
			Room[i] = new Room_BED();
			Bed[i] = new Room_BED();
		}
		while (in.hasNextInt()) {
			patient.clear();
			bed.clear();
			n = in.nextInt();
			m = in.nextInt();
			T = in.nextInt();
			t1 = in.nextInt();
			t2 = in.nextInt();
			t3 = in.nextInt();
			k = in.nextInt();
			int max = 0;
			for (int i = 0; i < k; i++) {
				Patient p = new Patient(in.next(), in.nextInt(), in.nextInt());
				p.id = i;
				patient.add(p);
			}
			for (int i = 0; i < 50; i++)//房间信息归位
				Bed[i].minutes = Room[i].minutes = 0;
			operating = new PriorityQueue<>(cpt1);
			for (int i = 0; i < n; i++) {
				ROOM r = new ROOM();
				r.id = i + 1;
				operating.add(r);
			}
			for (int i = 0; i < k; i++) {
				ROOM x = operating.poll();
				if (x.end == 0) //第一次需要初始化时间
					x.start = T * 60;
				else 
					x.start = x.end + t2;
				x.end = patient.get(i).timeo + x.start;
				Room[x.id].minutes += patient.get(i).timeo;
				patient.get(i).obegin = x.start;
				patient.get(i).oend = x.end;
				patient.get(i).room = x.id;
				operating.add(x);
			}
			Collections.sort(patient, cpt2);
			for (int i = 0; i < m; i++) {
				ROOM a = new ROOM();
				a.id = i + 1;
				bed.add(a);
			}
			for (int i = 0; i < k; i++) {
				int end = patient.get(i).oend;
				for (int j = 0; j < m; j++) {
					if (end >= (bed.get(j).end == 0 ? 0 : bed.get(j).end + t3)) {//如果手术结束时间大于等于休息准备就绪的时间那就说明可行
						patient.get(i).bed = j + 1;
						patient.get(i).rbegin = bed.get(j).start = end + t1;
						patient.get(i).rend = bed.get(j).end = end + t1 + patient.get(i).timer;
						Bed[j + 1].minutes += patient.get(i).timer;
						break;
					}
				}
			}
			for (int i = 0; i < k; i++)
				max = Math.max(max, patient.get(i).rend - T * 60);//病人的时间是加上开始时间的，所以要减去初始时间
			Collections.sort(patient, cpt3);
			System.out.println(" Patient          Operating Room          Recovery Room");
			System.out.println(" #  Name     Room#  Begin   End      Bed#  Begin    End");
			System.out.println(" ------------------------------------------------------");
			for (int i = 0; i < k; i++) {
				Patient p = patient.get(i);
				System.out.printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n", 
						i + 1, p.name, p.room, p.obegin / 60, p.obegin % 60, p.oend / 60, p.oend % 60, 
						p.bed, p.rbegin / 60, p.rbegin % 60, p.rend / 60, p.rend % 60);
			}
			System.out.println();
			for (int i = 0; i < m; i++) {
				if (max == 0) 
					Bed[i + 1].used = 0.00;
				else 
					Bed[i + 1].used = (double)Bed[i + 1].minutes * 100 / max;
			}
			for (int i = 0; i < n; i++) {
				if (max == 0) 
					Room[i + 1].used = 0.00;
				else 
					Room[i + 1].used = (double)Room[i + 1].minutes * 100 / max;
			}
			System.out.println("Facility Utilization");
			System.out.println("Type  # Minutes  % Used");
			System.out.println("-------------------------");
			for (int i = 0; i < n; i++) 
				System.out.printf("Room %2d %7d %7.2f\n", i + 1, Room[i + 1].minutes, Room[i + 1].used);
			for (int i = 0; i < m; i++)
				System.out.printf("Bed  %2d %7d %7.2f\n", i + 1, Bed[i + 1].minutes, Bed[i + 1].used);
			System.out.println();
		}
	}
}

class Room_BED {
	int minutes;
	double used;
}

class Patient {
	String name;
	int room, bed, id;
	int obegin, oend, rbegin, rend, timeo, timer;//手术开始时间，手术结束时间，休息开始时间，休息结束时间。都已经加上开始时间了
	public Patient(String  s, int o, int r) {
		name = s;
		timeo = o;
		timer = r;
	}
}

class ROOM {
	int id, start, end;
}