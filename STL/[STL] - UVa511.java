//题意：
//给定一些Map的名字，对角的两个坐标
//Location的名字，坐标
//现在对于给定的Location的名字和想要的查询等级查询一个地图
//查询等级是这样定义的：
//对于包含这个Location的一系列地图，其面积越大，等级越低，面积相同的等级相同
//如果有多个地图处于同一等级上
//按照：
//1.地图中心和查询地名距离的增序
//2.地图长(y轴)/宽(x轴)与0.75的差的增序
//3.地名和地图右下角距离的降序
//4.地图左下角x坐标的增序
//当然也有可能查询的地名根本不在Location中和不在地图覆盖的范围中
//分析：
//细节很多
//先处理Map
//输入的只保证对角坐标，并不保证是怎么对角法
//所以要提取出左上，右上，左下，右下的坐标
//对于每一个查询
//先把符合要求的地图存到数组中
//（如果这个数组大小为0就说明不在地图覆盖的范围中）
//按照地图大小排序并计算rank
//如果有多个rank
//按照第二种标准排序
//取第0个元素

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
	static Coordinate co;//由于第二种排序是受目标地点的坐标影响的，所以要全局
	static ArrayList<MAP> ansmap;//存放覆盖了查询目标的Map
	static ArrayList<MAP> maplist = new ArrayList<>();//存放输入的Map
	static HashMap<String, Coordinate> locationmap = new HashMap<>();//存放Location

	static Comparator<MAP> cpt1 = new Comparator<MAP>() {
		
		@Override
		public int compare(MAP o1, MAP o2) {
			// TODO Auto-generated method stub
			if (o1.area > o2.area)
				return -1;
			return 1;
		}
	};
	static Comparator<MAP> cpt2 = new Comparator<MAP>() {
		
		@Override
		public int compare(MAP o1, MAP o2) {
			// TODO Auto-generated method stub
			double x = co.x;
			double y = co.y;
			double distance1 = (o1.midx - x) * (o1.midx - x) + (o1.midy - y) * (o1.midy - y);
			double distance2 = (o2.midx - x) * (o2.midx - x) + (o2.midy - y) * (o2.midy - y);
			if  (distance1 < distance2)
				return -1;
			else if (distance1 > distance2)
				return 1;
			double ratiodiffer1 = Math.abs((o1.y[1] - o1.y[3]) / (o1.x[1] - o1.x[3]) - 0.75);
			double ratiodiffer2 = Math.abs((o2.y[1] - o2.y[3]) / (o2.x[1] - o2.x[3]) - 0.75);
			if (ratiodiffer1 < ratiodiffer2)
				return -1;
			else if (ratiodiffer1 > ratiodiffer2)
				return 1;
			double distancedr1 = (o1.x[2] - x) * (o1.x[2] - x) + (o1.y[2] - y) * (o1.y[2] - y);
			double distancedr2 = (o2.x[2] - x) * (o2.x[2] - x) + (o2.y[2] - y) * (o2.y[2] - y);
			if (distancedr1 > distancedr2)
				return -1;
			else if (distancedr1 < distancedr2)
				return 1;
			if (o1.x[0] < o2.x[0])
				return -1;
			else 
				return 1;
		}
	};
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		in.nextLine();
		String s;
		while (!(s = in.next()).equals("LOCATIONS"))
		{
			MAP m = new MAP();
			m.name = s;
			double x[] = new double[2];
			double y[] = new double[2];
			for (int i = 0; i < 2; i++)
			{
				x[i] = in.nextDouble();
				y[i] = in.nextDouble();
			}
			double midx = (x[0] + x[1]) / 2;
			double midy = (y[0] + y[1]) / 2;
			Arrays.sort(x);//处理四个顶点的坐标
			Arrays.sort(y);
			for (int i = 0; i < 4; i++)
			{
				if (i == 0 || i == 3)
					m.x[i] = x[0];
				else 
					m.x[i] = x[1];
				if (i < 2)
					m.y[i] = y[1];
				else 
					m.y[i] = y[0];
			}
			m.midx = midx;
			m.midy = midy;
			m.area = (m.x[2] - m.x[0]) * (m.y[0] - m.y[2]);
			maplist.add(m);
		}
		while (!(s = in.next()).equals("REQUESTS"))
		{
			Coordinate c = new Coordinate();
			c.x = in.nextDouble();
			c.y = in.nextDouble();
			locationmap.put(s, c);
		}
		while (!(s = in.next()).equals("END"))
		{
			int level = in.nextInt();
			ansmap = new ArrayList<>();
			int flag = 0;//flag为0说明不存在这个Location
			System.out.print(s + " at detail level " + level + " ");
			if (locationmap.containsKey(s))
			{
				flag++;//flag >= 1说明存在这个Location
				co = locationmap.get(s);
				double x = co.x, y = co.y;
				for (int i = 0; i < maplist.size(); i++)
				{
					double minx = maplist.get(i).x[3], maxx = maplist.get(i).x[1];
					double miny = maplist.get(i).y[3], maxy = maplist.get(i).y[1];
					if (minx <= x && x <= maxx && miny <= y && y <= maxy)
						ansmap.add(maplist.get(i));
				}
				if (ansmap.size() != 0)//如果有地图覆盖到了这个Location
				{
					Collections.sort(ansmap, cpt1);
					HashMap<Integer, Integer> map = new HashMap<>();//rank-times
					int tmp = 1;
					int maxrank = 1;
					for (int i = 0; i < ansmap.size();)
					{
						int times = 1;
						ansmap.get(i++).rank = tmp;
						maxrank = tmp;
						while (i < ansmap.size() && ansmap.get(i).area == ansmap.get(i - 1).area)
						{
							ansmap.get(i++).rank = tmp;
							times++;
						}
						map.put(tmp, times);
						tmp++;
					}
					String ans = "";
					if (maxrank < level)//如果要求的rank等级过高就找到能使用的最大的rank(maxrank)
					{
						flag++;//并把flag更新为2
						level = maxrank;
					}
					if (map.get(level) == 1)//如果这个rank下只有1个Map与之对应那就是答案了
					{
						Collections.sort(ansmap, cpt1);
						ans = ansmap.get(level - 1).name;
					}
					else 
					{
						ArrayList<MAP> tmpans = new ArrayList<>();
						for (int i = 0; i < maplist.size(); i++)//否则对于这个rank下的Map都添加到数组中并按照第二种标准排序
							if (maplist.get(i).rank == level)
								tmpans.add(maplist.get(i));
						Collections.sort(tmpans, cpt2);
						ans = tmpans.get(0).name;//答案在第0个元素
					}
					if (flag == 1) //flag为1时代表不需要调整恰当的rank
						System.out.print("using ");
					else //flag为2时说明要求的rank等级过高
						System.out.print("no map at that detail level; using ");
					System.out.println(ans);
				}
				else //如果没有地图覆盖到
					System.out.println("no map contains that location");
			}
			else 
				System.out.println("unknown location");
		}
	}
}

class MAP//存放地图
{
	String name;
	double x[] = new double[4];
	double y[] = new double[4];
	double midx, midy, area;
	int rank;
	public String toString()
	{
//		System.out.println(Arrays.toString(x));
//		System.out.println(Arrays.toString(y));
//		System.out.println(area + " " + rank);
		return name + " " + area + " " + rank;
	}
}

class Coordinate//存放Location
{
	double x, y;
	public String toString()
	{
		return x + " " + y;
	}
}