/**
* ��Ŀ���������ģ�ʵ��һ�����������ַ����еĿո��滻�ɡ�%20"��
* ʱ�䣺2018-08-07 10:46
* ���ߣ�����
* ��Դ����ָoffer P44
* �ѵ㣺ʱ��Ϳռ临�Ӷ�
*/

#include <iostream>
#include <string>

//����һ���½��µ��ַ��������µ��ַ������滻

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

//������ʹ�ø����ڴ棬ֻ����Դ�ַ��������޸ģ���Դ�ַ����������㹻ʣ��
//����������ǰ����ɨ�裬�����ո�ͽ�������ַ������������ַ����ȣ���"%20"�����ȥ
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


//���������������Ǵ�ǰ����ɨ���ַ�����������ַ�����Ҫ�ƶ����
//        �������Ӻ���ǰɨ�裬�����ַ�����ֻ�ƶ�һ�Σ�ǰ������Ҫ֪���ƶ����ַ����ж೤��
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
	std::cout << "Դ�ַ���1��" << str1 << std::endl;
	std::cout << "Դ�ַ���2��" << str2 << std::endl;
	//std::cout << "Դ�ַ���3��" << str3 << std::endl;
	std::cout << "Դ�ַ���4��" << str4 << std::endl;
	std::cout << "Դ�ַ���5��" << str5 << std::endl;
	std::cout << "Դ�ַ���6��" << str6 << std::endl;
	
	//std::cout << "����һ��" << std::endl;
	//ReplaseBlankSpace1(str1);
	//std::cout << "Ŀ���ַ���1��" << str1 << std::endl;
	//ReplaseBlankSpace1(str2);
	//std::cout << "Ŀ���ַ���2��" << str2 << std::endl;
	////ReplaseBlankSpace1(str3);
	////std::cout << "Ŀ���ַ���3��" << str3 << std::endl;
	//ReplaseBlankSpace1(str4);
	//std::cout << "Ŀ���ַ���4��" << str4 << std::endl;
	//ReplaseBlankSpace1(str5);
	//std::cout << "Ŀ���ַ���5��" << str5 << std::endl;
	//ReplaseBlankSpace1(str6);
	//std::cout << "Ŀ���ַ���6��" << str6 << std::endl;

	//std::cout << "��������" << std::endl;
	//ReplaseBlankSpace2(str1);
	//std::cout << "Ŀ���ַ���1��" << str1 << std::endl;
	//ReplaseBlankSpace2(str2);
	//std::cout << "Ŀ���ַ���2��" << str2 << std::endl;
	////ReplaseBlankSpace2(str3);
	////std::cout << "Ŀ���ַ���3��" << str3 << std::endl;
	//ReplaseBlankSpace2(str4);
	//std::cout << "Ŀ���ַ���4��" << str4 << std::endl;
	//ReplaseBlankSpace2(str5);
	//std::cout << "Ŀ���ַ���5��" << str5 << std::endl;
	//ReplaseBlankSpace2(str6);
	//std::cout << "Ŀ���ַ���6��" << str6 << std::endl;

	std::cout << "��������" << std::endl;
	ReplaseBlankSpace3(str1);
	std::cout << "Ŀ���ַ���1��" << str1 << std::endl;
	ReplaseBlankSpace3(str2);
	std::cout << "Ŀ���ַ���2��" << str2 << std::endl;
	//ReplaseBlankSpace3(str3);
	//std::cout << "Ŀ���ַ���3��" << str3 << std::endl;
	ReplaseBlankSpace3(str4);
	std::cout << "Ŀ���ַ���4��" << str4 << std::endl;
	ReplaseBlankSpace3(str5);
	std::cout << "Ŀ���ַ���5��" << str5 << std::endl;
	ReplaseBlankSpace3(str6);
	std::cout << "Ŀ���ַ���6��" << str6 << std::endl;


}



/**
* ��Ŀ���������������Ŀ���������������������A1��A2��A1���㹻�ڴ�ռ��ܹ�����A1��A2,
        ʵ��һ��������A2���뵽A1�У���֤A1��Ȼ����
* ʱ�䣺2018-08-08 17:23
* ���ߣ�����
* ��Դ����ָoffer P48
* �ѵ㣺
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