/*
* ��Ŀ��һ�����洢�����ݿ��У���ID��������������parentId��name�����ֶ�
*       �������Ѿ����ص����ڴ��У��洢��һ������nodeList�У�����ɺ���
*       Delete(id)������ɾ��idָ���ڵ㼰���ӽڵ㡣
* ʱ�䣺2018-08-07  10:25
* ���ߣ�����
* ��Դ��������
* �ѵ㣺��Ҫ�ڵ�洢������Ҫ�ҵ�������Ҫɾ���Ľڵ�
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>


struct node{
	int id;
	int parentId;
	std::string name;
	node *next;
};

node* NodeList;

//�ݹ鷨
void foo(node *head, int id){
	node* p = head;
	node* q;
	while (p->next&&p->next->id != id){
		p = p->next;
	}
	if (!p->next){
		return;
	}
	q = p->next;
	int ID = p->next->id;
	p->next = q->next;
	delete q;

	node *tmp = head;
	while (tmp->next){
		if (tmp->next->parentId == ID){
			foo(head, tmp->next->id);
		}
		tmp = tmp->next;
	}
}

//���и�������
//targetId���
//��ͷ���ӣ���������ɾ��targetId��Ӧ�ڵ㣬���ҵ�targetIdΪparentId�Ľڵ㣬���
//������в�Ϊ�գ����ͷ���ӣ��ظ���һ��������ֱ������Ϊ��

void bar(node *head, int id){
	std::queue<int> tmp;
	tmp.push(id);   //�Ѹ��ڵ����

	while (!tmp.empty()){  //
		int now = tmp.front();
		tmp.pop();
		node *p = head;
		node *q;
		while (p->next){
			if (p->next->parentId == now){
				tmp.push(p->next->id);
			}
			if (p->next->id == now){
				q = p->next;
				p->next = q->next;
				delete q;
			}
			p = p->next;
		}
	}
}

void Delete(int targetId){
	foo(NodeList, targetId);
}



void bar(node* head, int targetid)
{
	//����Ҫɾ����targetid���
	std::queue<int>tmp;
	tmp.push(targetid);

	//ɾ��targetid
	node *p, *q;
	p = head;
	while (p->next&&p->next->id != targetid)
		p = p->next;
	if (p->next)
	{
		q = p->next;
		p->next = q->next;
		delete q;
	}

	//��ʼѭ��
	while (!tmp.empty())//������в�Ϊ��
	{
		int now = tmp.front();//��¼��ǰ��ͷid
		tmp.pop();
		node* p, *q;
		p = head;
		while (p->next)
		{
			if (p->next->parentId == now)
			{
				tmp.push(p->next->id);
				q = p->next;
				p->next = q->next;
				delete q;
			}
			p = p->next;
		}
	}
}