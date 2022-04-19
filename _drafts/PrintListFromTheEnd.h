/**
* ��Ŀ���������壺�����ӡ����
* ʱ�䣺2018-08-08 18:38
* ���ߣ�����
* ��Դ����ָoffer P51
* �ѵ㣺
*/

#include <iostream>
#include <stack>


struct node{
	int m_key;
	node *m_next;
};


void PrintListFromTheEnd1(node *head){
	std::stack<node *> tmp;

	node *p = head;
	while (p){
		tmp.push(p);
		p = p->m_next;
	}

	while (!tmp.empty()){
		node *t = tmp.top();
		std::cout << t->m_key << "  ";
		tmp.pop();
	}
}


void PrintListFromTheEnd2(node *arg){
	if (arg->m_next){
		PrintListFromTheEnd2(arg->m_next);
	}
	std::cout << arg->m_key << "  ";
}







void TestPrintListFromTheEnd(){
	std::cout << "\n------------------------------------test PrintListFromTheEnd------------------------------------" << std::endl;

	node *head;
	node *tmp = nullptr;
	node *now = nullptr;
	for (int i = 0; i < 20; i++){
		tmp = new node;
		tmp->m_key = i;
		tmp->m_next = nullptr;
		if (i == 0){
			head = tmp;
			now = tmp;
		}
		now->m_next = tmp;
		now = tmp;
	}

	PrintListFromTheEnd1(head);
	std::cout << "\n-----------------------------------------------" << std::endl;

	PrintListFromTheEnd2(head);


}






