import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class BubbleSort {
		
	public static void Sort(int num[])
	{
		for (int i = 0; i < num.length; i++)
		{
			for (int j = i + 1; j < num.length; j++)
			{
				if (num[i] > num[j])
				{
					int tmp = num[i];
					num[i] = num[j];
					num[j] = tmp;
				}
			}
		}
	}
	
	public static void shellsort1(int a[], int n)  
	{  
	    int i, j, gap;  
	  
	    for (gap = n / 2; gap > 0; gap /= 2) //步长  
	        for (i = 0; i < gap; i++)        //直接插入排序  
	        {  
	            for (j = i + gap; j < n; j += gap)   
	                if (a[j] < a[j - gap])  
	                {  
	                    int temp = a[j];  
	                    int k = j - gap;  
	                    while (k >= 0 && a[k] > temp)  
	                    {  
	                        a[k + gap] = a[k];  
	                        k -= gap;  
	                    }  
	                    a[k + gap] = temp;  
	                }  
	        }  
	} 
	
	public static void main(String args[]) throws FileNotFoundException
	{
		File f = new File("data25.txt");
		Scanner in = new Scanner(f);
		int n = in.nextInt();
		int num[] = new int[n];
		for (int i = 0; i < n; i++)
			num[i] = in.nextInt();
		long before = System.currentTimeMillis();
		Sort(num);
		long after = System.currentTimeMillis();
		System.out.println("Array size:" + n);
		System.out.println("Running time:" + (after - before) + "ms.");
		
		f = new File("data100.txt");
		in = new Scanner(f);
		n = in.nextInt();
		num = new int[n];
		for (int i = 0; i < n; i++)
			num[i] = in.nextInt();
		before = System.currentTimeMillis();
		Sort(num);
		after = System.currentTimeMillis();
		System.out.println("Array size:" + n);
		System.out.println("Running time:" + (after - before) + "ms.");
		
		f = new File("data1w.txt");
		in = new Scanner(f);
		n = in.nextInt();
		num = new int[n];
		for (int i = 0; i < n; i++)
			num[i] = in.nextInt();
		before = System.currentTimeMillis();
		Sort(num);
		after = System.currentTimeMillis();
		System.out.println("Array size:" + n);
		System.out.println("Running time:" + (after - before) + "ms.");
		
		f = new File("data1m.txt");
		in = new Scanner(f);
		n = in.nextInt();
		num = new int[n];
		for (int i = 0; i < n; i++)
			num[i] = in.nextInt();
		before = System.currentTimeMillis();
		Sort(num);
		after = System.currentTimeMillis();
		System.out.println("Array size:" + n);
		System.out.println("Running time:" + (after - before) + "ms.");
	}
}
