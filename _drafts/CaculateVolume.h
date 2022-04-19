/**
* ��Ŀ����һ����ͬ�߶ȵ�̨�ף���һ�������ʾ��ÿ��Ԫ�ر�ʾ̨�׸߶ȣ�̨��֮�䰼��ȥ�ĵط����Ի�ˮ��
*       ��һ���ܻ�����ˮ��
* ʱ�䣺2018-08-08 18:38
* ���ߣ�����
* ��Դ������ͷ��2018����c++�������
* �ѵ㣺
*/

#include <iostream>
#include <vector>
#include <queue>

int CaculateVolume(std::vector<int> &arr){
	int size = arr.size();
	int res = 0;

	std::queue<int> points;
	points.push(0);
	for (int i = 1; i < size; i++){
		if (arr[i - 1]<arr[i] && arr[i + 1]<arr[i]){
			points.push(i);
		}
	}

	int s = points.size();
	int low, high;
	while (!points.empty()){
		int n1 = points.front();
		points.pop();
		if (points.empty()){
			break;
		}
		int n2 = points.front();
		low = arr[n1] < arr[n2] ? n1 : n2;

		for (int j = n1 + 1; j < n2; j++){
			res += arr[low] - arr[j];
		}
	}
	return res;
}

void TestCaculateVolume(){
	std::cout << "\n------------------------------------test CaculateVolume------------------------------------" << std::endl;
	std::vector<int> arr = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
	std::cout << CaculateVolume(arr) << std::endl;
}