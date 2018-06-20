/**
 * 给n个糖果，分给k个人
 * 每人分配x个，循环分配，直到被除尽或者没除尽的扔掉
 * x<=M，每个人的分配次数最大为D
 * 求第1个人最多分配多少糖果
 *
 * 注意到D很小，可以枚举分配次数i
 * i - 1是全部分配到每个人的，要想第1个人分配最多
 * 第i次就分配到第1个人
 * 那么x=n / (k * (i - 1) + 1)
 * 注意到(i - 1) * k + 1 <= n
 * 而且k * i * x + x > n
 * 算得x的下界
 * x的上界是M
 * 分配的糖果数是x * i
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import static java.lang.System.out;

public class Main {
    public static void main(String args[]) throws FileNotFoundException {
//        File f = new File("F:\\TestCode\\TestIntelliJ\\src\\in.txt");
        Scanner in = new Scanner(System.in);
        long n = in.nextLong();
        long k = in.nextLong();
        long M = in.nextLong();
        long D = in.nextLong();
        long ans = -1;
        for (long i = 1; i <= D && (i - 1) * k + 1 <= n; i++) {
            long x = n / (k * (i - 1) + 1);
            long L = (long) Math.ceil(n / (1.0 * k * i + 1));
            x = Math.min(x, M);
            if (x >= L)
                ans = Math.max(ans, x * i);
        }
        out.println(ans);
    }
}
