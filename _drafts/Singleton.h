/**
* ��Ŀ�����������C++ʵ��singletonģʽ
* ʱ�䣺2018-08-05 16:13
* ���ߣ�����
* ��Դ����ָoffer P31
* �ѵ㣺�̰߳�ȫ��
*/

#include <iostream>
#include <mutex>

///����ģʽ������Ҫʵ����ʱ�򴴽���ֻ����һ��
///�����ж�ʵ���Ƿ���ڣ���������ڣ����������ֹ�����߳�ͬʱ�ڴ����̣߳�
///Ȼ�����ж�һ��ʵ���Ƿ���ڣ���ֹ�ڼ������������������Լ���������һ��ʵ����
///��������ڣ���newһ��ʵ��
class Singleton1{
public:
	static Singleton1* GetInstance(){
		if (instance == nullptr){
			std::lock_guard<std::mutex> lock(mtx);
			if (instance == nullptr){
				instance = new Singleton1;
			}
		}
		return instance;
	}
	
private:
	Singleton1(){}
	Singleton1(Singleton1 &s) = delete;

private:
	static Singleton1* instance;
	static std::mutex mtx;
};

Singleton1* Singleton1::instance = nullptr;
std::mutex Singleton1::mtx;


///����ģʽ���ڱ����ʱ��ʹ�����ʵ��
///�����ڱ���ʱ�ʹ�������ʵ�������ԾͲ����������ǲ�ͬ�߳��ظ�����ʵ����������������̰߳�ȫ��
class Singleton2{
public:
	static Singleton2* GetInstance(){
		return instance;
	}

private:
	Singleton2(){}
	Singleton2(Singleton2 &s) = delete;

private:
	static Singleton2* instance;
};

Singleton2* Singleton2::instance = new Singleton2;



////////////////////////////////////////////////////////////////////
//  test

void testSingleton(){
	std::cout << "\n------------------------------------test Singleton------------------------------------" << std::endl;

	Singleton1* single1 = Singleton1::GetInstance();
	std::cout << "instance1 offset: " << single1 << std::endl;
	std::cout << "instance2 offset: " << Singleton1::GetInstance() << std::endl;

	Singleton2* single2 = Singleton2::GetInstance();
	std::cout << "instance1 offset: " << single2 << std::endl;
	std::cout << "instance2 offset: " << Singleton2::GetInstance() << std::endl;
}