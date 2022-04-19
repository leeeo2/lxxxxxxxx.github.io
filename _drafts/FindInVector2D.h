/**
* 题目：面试题三：判断一个数是否存在二维数组中,二维数组的每行每列都是升序序列
* 时间：2018-08-05 16:13
* 作者：李祥
* 来源：剑指offer P38
* 难点：以右上或者左下点为切入点，判断顶点与待求值的大小，可以排除一行或者一列
*       例如：以右上点为例，待求值大于右上点时，说明第一行所有值都小于待求值，所以可以排除第一行
*/

#include <iostream>
#include <iomanip>
#include <vector>

typedef std::vector<int> vec;
typedef std::vector<std::vector<int>> vec2i;

bool findInVector2D1(vec2i arr2d, int num){
	for (auto i : arr2d){
		for (auto j : i){
			if (num == j)
				return true;
		}
	}
	return false;
}

bool findInVector2D2(vec2i arr2d, int num){
	int rows = arr2d.size();
	int cols = arr2d[0].size();

	int i = 0, j = cols-1;
	while (i <rows){
		while (j >= 0){
			if (arr2d[i][j] == num){
				return true;
			}
			else if (arr2d[i][j] > num){
				j--;
				if (j == -1 )
					return false;
				continue;
			}
			else{
				i++;
				if (i == rows)
					return false;
				continue;
			}
		}
	}
	return false;
}




//////////////////////////////////////////////////////////////
//  test

void testFindInVector2D(){
	std::cout << "\n------------------------------------test FindInVector2D------------------------------------" << std::endl;

	vec2i arr2d{
		{ 1, 3, 5, 7, 9 },
		{ 3, 5, 7, 9, 11 },
		{ 5, 7, 9, 11, 13 },
		{ 7, 9, 11, 13, 15 },
		{ 9, 11, 13, 15, 17 } };

	std::cout << "原始数组：[" << std::endl;
	for (auto i : arr2d){
		for (auto j : i){
			std::cout <<std::setw(3)<< j << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "]" << std::endl;

	std::cout << "正样本:（1表示存在，0表示不存在）" << std::endl;
	for (auto i : arr2d){
		for (auto j : i){
			std::cout << std::setw(3) << j << " (" << findInVector2D2(arr2d, j) << ")";
		}
		std::cout << std::endl;
	}

	std::cout <<"负样本:"<< std::endl;
	for (auto i : arr2d){
		for (auto j : i){
			std::cout << std::setw(3) << j-1 << " (" << findInVector2D2(arr2d, j-1) << ")";
		}
		std::cout << std::endl;
	}


}
