/**
* 题目：面试题四：实现一个函数，将字符串中的空格替换成”%20"。
* 时间：2018-08-07 10:46
* 作者：李祥
* 来源：剑指offer P44
* 难点：时间和空间复杂度
*/

#include <iostream>
#include <string>

//方法一：新建新的字符串，在新的字符串中替换

void ReplaseBlankSpace1(char str[]){
	if (str == nullptr)
		return;
	char tmp[1024];
	int size = strlen(str);
	int j = 0;
	for (int i = 0; i < size; i++){
		if (str[i] != ' '){
			tmp[j++] = str[i];
		}
		else{
			tmp[j++] = '%';
			tmp[j++] = '2';
			tmp[j++] = '0';

		}
	}
	tmp[j] = '\0';
	int len = strlen(tmp);
	memcpy(str, tmp, strlen(tmp));
}

//不允许使用辅助内存，只能在源字符串上做修改，但源字符串后面有足够剩余
//方法二：从前往后扫描，遇到空格就将后面的字符串后移两个字符长度，把"%20"插入进去
void ReplaseBlankSpace2(char *str){
	if (str == nullptr)
		return;

	int i = 0;
	while (str[i] != '\0'){
		if (str[i] == ' '){
			memcpy(&str[i + 3], &str[i + 1], strlen(str) - i);
			str[i++] = '%';
			str[i++] = '2';
			str[i++] = '0';
		}
		else
			i++;
	}
}


//方法三：方法二是从前往后扫描字符串，后面的字符串需要移动多次
//        方法三从后往前扫描，所有字符可以只移动一次，前提是需要知道移动后字符串有多长。
void ReplaseBlankSpace3(char *str){
	if (str == nullptr)
		return;

	int count = 0, i = 0;
	while (str[i] != '\0'){
		if (str[i] == ' '){
			count++;
		}
		i++;
	}

	int p = strlen(str)-1;
	int q = p + count * 2;

	while (p != -1){
		if (str[p] != ' '){
			str[q] = str[p];
			p--;
			q--;
		}
		else{
			str[q--] = '0';
			str[q--] = '2';
			str[q--] = '%';
			p--;
		}
	}
}



void TestReplaseBlanckSpace(){
	std::cout << "\n------------------------------------test ReplaseBlanckSpace------------------------------------" << std::endl;
	
	char str1[1024] = " hello world, i am lixiang. ";
	char str2[1024] = "hello";
	char *str3 = nullptr;
	char str4[1024] = "";
	char str5[1024] = " ";
	char str6[1024] = "    ";
	std::cout << "源字符串1：" << str1 << std::endl;
	std::cout << "源字符串2：" << str2 << std::endl;
	//std::cout << "源字符串3：" << str3 << std::endl;
	std::cout << "源字符串4：" << str4 << std::endl;
	std::cout << "源字符串5：" << str5 << std::endl;
	std::cout << "源字符串6：" << str6 << std::endl;
	
	//std::cout << "方法一：" << std::endl;
	//ReplaseBlankSpace1(str1);
	//std::cout << "目标字符串1：" << str1 << std::endl;
	//ReplaseBlankSpace1(str2);
	//std::cout << "目标字符串2：" << str2 << std::endl;
	////ReplaseBlankSpace1(str3);
	////std::cout << "目标字符串3：" << str3 << std::endl;
	//ReplaseBlankSpace1(str4);
	//std::cout << "目标字符串4：" << str4 << std::endl;
	//ReplaseBlankSpace1(str5);
	//std::cout << "目标字符串5：" << str5 << std::endl;
	//ReplaseBlankSpace1(str6);
	//std::cout << "目标字符串6：" << str6 << std::endl;

	//std::cout << "方法二：" << std::endl;
	//ReplaseBlankSpace2(str1);
	//std::cout << "目标字符串1：" << str1 << std::endl;
	//ReplaseBlankSpace2(str2);
	//std::cout << "目标字符串2：" << str2 << std::endl;
	////ReplaseBlankSpace2(str3);
	////std::cout << "目标字符串3：" << str3 << std::endl;
	//ReplaseBlankSpace2(str4);
	//std::cout << "目标字符串4：" << str4 << std::endl;
	//ReplaseBlankSpace2(str5);
	//std::cout << "目标字符串5：" << str5 << std::endl;
	//ReplaseBlankSpace2(str6);
	//std::cout << "目标字符串6：" << str6 << std::endl;

	std::cout << "方法三：" << std::endl;
	ReplaseBlankSpace3(str1);
	std::cout << "目标字符串1：" << str1 << std::endl;
	ReplaseBlankSpace3(str2);
	std::cout << "目标字符串2：" << str2 << std::endl;
	//ReplaseBlankSpace3(str3);
	//std::cout << "目标字符串3：" << str3 << std::endl;
	ReplaseBlankSpace3(str4);
	std::cout << "目标字符串4：" << str4 << std::endl;
	ReplaseBlankSpace3(str5);
	std::cout << "目标字符串5：" << str5 << std::endl;
	ReplaseBlankSpace3(str6);
	std::cout << "目标字符串6：" << str6 << std::endl;


}



/**
* 题目：面试题四相关题目：有两个升序排序的数组A1和A2，A1有足够内存空间能够容纳A1和A2,
        实现一个方法将A2插入到A1中，保证A1仍然有序。
* 时间：2018-08-08 17:23
* 作者：李祥
* 来源：剑指offer P48
* 难点：
*/


void MergeTwoOrderArray(int *arr1,int len1, int *arr2,int len2){
	int i = len1 - 1;
	int j = len2 - 1;
	int k = len1 + len2 - 1;
	while (k != -1){
		if (arr1[i] >= arr2[j]){
			arr1[k] = arr1[i];
			i--;
		}
		else{
			arr1[k] = arr2[j];
			j--;
		}
		k--;
	}
}


void TestMergeTwoOrderArray(){
	int arr1[20] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	int arr2[10] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };

	MergeTwoOrderArray(arr1,10, arr2,10);
	for (int i = 0; i < 20;i++){
		std::cout << arr1[i] << " ";
	}
	std::cout << std::endl;

}