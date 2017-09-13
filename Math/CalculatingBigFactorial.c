//这是张臻炜给我的代码，也是他从其他地方找来的




#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void carry ( int bit[], int pos ) {	//计算进位
	int i, carray = 0;

	for ( i = 0; i <= pos; i++ ) {	//从0~pos逐位检查是否需要进位
		bit[i] += carray;	//累加进位

		if ( bit[i] <= 9 ) {	//小于9不进位
			carray = 0;

		} else if ( bit[i] > 9 && i < pos ) {	//大于9但不是最高位
			carray = bit[i] / 10;	//保存进位值
			bit[i] = bit[i] % 10;	//得到该位的一位数

		} else if ( bit[i] > 9 && i >= pos ) {	//大于9且是最高位
			while ( bit[i] > 9 ) {
				carray = bit[i] / 10;	//计算进位值
				bit[i] = bit[i] % 10;	//当前的一位数
				i++;
				bit[i] = carray;	//在下一位保存进位的值
			}
		}
	}
}

int main() {
	int num, pos, digit, i, j, m, n;
	double sum = 0;
	int *fact;	//保存阶乘结果的数组
	printf ( "输入及计算其阶乘的数：Num=" );
	scanf ( "%d", &num );

	for ( i = 1; i <= num; i++ ) {	//计算阶乘的位数
		sum += log10 ( i );
	}
	digit = ( int ) sum + 1;	//阶乘结果的数据长度

	if ( ! ( fact = ( int * ) malloc ( ( digit + 1 ) * sizeof ( int ) ) ) ) {	//分配保存阶乘位数的内存
		printf ( "分配内存失败！\n" );
		return 0;
	}

	for ( i = 0; i <= digit; i++ ) {	//初始化数组
		fact[i] = 0;
	}

	fact[0] = 1;	//设个位为1

	for ( int i = 2; i <= num; i++ ) {	//将2~num逐个与原来的积相乘
		for ( j = digit; j >= 0; j-- ) {	//查找最高位
			if ( fact[j] != 0 ) {
				pos = j;	//记录最高位
				break;
			}
		}

		for ( j = 0; j <= pos; j++ ) {	//每一位与i乘
			fact[j] *= i;	//进位处理
		}

		carry ( fact, pos );
	}

	for ( j = digit; j >= 0; j-- ) {	//查找最高位
		if ( fact[j] != 0 ) {
			pos = j;	//记录最高位
			break;
		}
	}

	m = 0;	//统计输出位数
	n = 0;	//统计输出行数
	printf ( "\n输出%d的阶乘结果（按任意键显示下一屏）：\n", num );
	m = 2 - pos % 3;	//按每3位分组，计算第一组

	for ( int i = pos; i >= 0; i-- ) {	//输出计算结果
		printf ( "%d", fact[i] );
		m++;

		if ( m % 3 == 0 ) {	//每3个数字输出一个空格
			printf ( " " );
		}

		if ( 40 == m ) {	//每行输出40个数字
			printf ( "\n" );
			m = 0;
			n++;

			if ( 10 == n ) {	//输出10行则暂停
				getch();
				printf ( "\n" );
				n = 0;
			}
		}
	}

	printf ( "\n\n" );
	printf ( "%d的阶乘共有%d位。\n", num, pos + 1 );
	getch();
	return 0;
}
//精确计算时必须要用到高精度乘法
//在int数组中每个元素只存了一位，浪费空间
