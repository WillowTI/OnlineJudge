//题意：
//输入一些房屋的左下角坐标(x, y)， 宽度，深度，高度（都是浮点数）
//按照x递增，y递增的顺序输出能看到房屋的编号
//分析：
//按照x递增，y递增的顺序先排序
//对于排序后的数组一一检测能不能看得到
//怎样检测是一个问题
//可以观察到：能看到的房屋都处在一段连续的区间里
//这些区间是由房屋在x方向的起点和终点组成的
//可以把这些端点都放在一个集合里（因为要去重）
//对于每一个房屋
//检测在分区间的中点处是否可见（只要不是两个端点就行）
//只要有一个地方是可见的那就是可见的
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;
import java.util.TreeSet;

public class Main {

	static int n;
	static NODE building[];
	static Comparator<NODE> cpt = new Comparator<NODE>() {
		
		@Override
		public int compare(NODE o1, NODE o2) {
			// TODO Auto-generated method stub
			if (o1.x < o2.x)
				return -1;
			else if (o1.x > o2.x)
				return 1;
			else if (o1.y < o2.y)
				return -1;
			else 
				return 1;
		}
	};
	
	static boolean cover(int i, double location)//检测第i个房屋是否覆盖了location点
	{
		return building[i].x <= location && (building[i].x + building[i].width) >= location;
	}
	
	static boolean isvisible(int i, double location)//检测第i个房屋在location处是否可见
	{
		if (!cover(i, location))//首先它要覆盖这个点
			return false;
		for (int k = 0; k < n; k++)//对于每个也覆盖了这个点且比第i个房屋的y小的房屋，它的高度不能要严格小于第i个房屋
		{
			if (cover(k, location) && building[i].y > building[k].y && building[i].height <= building[k].height)
				return false;
		}
		return true;
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//File f = new File("in.txt");
		Scanner in = new Scanner(System.in);
		int cas = 1;
		while ((n = in.nextInt()) != 0)
		{
			building = new NODE[n];
			for (int i = 0; i < n; i++)
			{
				building[i] = new NODE();
				building[i].id = i + 1;
				building[i].x = in.nextDouble();
				building[i].y = in.nextDouble();
				building[i].width = in.nextDouble();
				building[i].depth = in.nextDouble();
				building[i].height = in.nextDouble();
			}
			Arrays.sort(building, cpt);
			TreeSet<Double> set = new TreeSet<>();
			for (int i = 0; i < n; i++)
			{
				set.add(building[i].x);
				set.add(building[i].x + building[i].width);
			}
			Double range[] = new Double[set.size()];
			range = set.toArray(range);
			if (cas != 1)
				System.out.println();
			System.out.print("For map #" + cas++ +", the visible buildings are numbered as follows:\n" + building[0].id);
			for (int i = 1; i < n; i++)
			{
				for (int j = 0; j < set.size() - 1; j++)
				{
					if (isvisible(i, (range[j] + range[j + 1]) / 2))
					{
						System.out.print(" " + building[i].id);
						break;
					}
				}
			}
			System.out.println();
		}
	}

}

class NODE
{
	int id;
	double x, y, width, depth, height;
}