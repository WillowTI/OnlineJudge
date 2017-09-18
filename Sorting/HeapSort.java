import java.util.Arrays;

public class HeapSort {
	
	public static void Sort(int num[])
	{
		for (int i = num.length / 2 - 1; i >= 0; i--)
			heapAdjust(num, i, num.length);
		for (int i = num.length - 1; i > 0; i--)
		{
			int tmp = num[0];
			num[0] = num[i];
			num[i] = tmp;
			heapAdjust(num, 0, i);
		}
	}
	
	public static void heapAdjust(int num[], int parent, int end)
	{
		int tmp = num[parent];
		int child = 2 * parent + 1;
		while (child < end)
		{
			if (child + 1 < end && num[child] < num[child + 1])
				child++;
			if (tmp >= num[child])
				break;
			num[parent] = num[child];
			parent = child;
			child = child * 2 + 1;
		}
		num[parent] = tmp;
	}
	
	public static void main(String[] args)
	{
		int num[] = {1, 2, 34, 1, 45, 34, 12, 77};
		Sort(num);
		System.out.println(Arrays.toString(num));
	}

}
