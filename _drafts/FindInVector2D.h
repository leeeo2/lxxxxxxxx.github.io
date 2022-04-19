/**
* ��Ŀ�������������ж�һ�����Ƿ���ڶ�ά������,��ά�����ÿ��ÿ�ж�����������
* ʱ�䣺2018-08-05 16:13
* ���ߣ�����
* ��Դ����ָoffer P38
* �ѵ㣺�����ϻ������µ�Ϊ����㣬�ж϶��������ֵ�Ĵ�С�������ų�һ�л���һ��
*       ���磺�����ϵ�Ϊ��������ֵ�������ϵ�ʱ��˵����һ������ֵ��С�ڴ���ֵ�����Կ����ų���һ��
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

	std::cout << "ԭʼ���飺[" << std::endl;
	for (auto i : arr2d){
		for (auto j : i){
			std::cout <<std::setw(3)<< j << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "]" << std::endl;

	std::cout << "������:��1��ʾ���ڣ�0��ʾ�����ڣ�" << std::endl;
	for (auto i : arr2d){
		for (auto j : i){
			std::cout << std::setw(3) << j << " (" << findInVector2D2(arr2d, j) << ")";
		}
		std::cout << std::endl;
	}

	std::cout <<"������:"<< std::endl;
	for (auto i : arr2d){
		for (auto j : i){
			std::cout << std::setw(3) << j-1 << " (" << findInVector2D2(arr2d, j-1) << ")";
		}
		std::cout << std::endl;
	}


}
