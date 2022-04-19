/*
* 题目：一棵树存储在数据库中，有ID（自增主键），parentId，name三个字段
*       现在树已经加载到了内存中，存储在一个链表nodeList中，请完成函数
*       Delete(id)函数，删除id指定节点及其子节点。
* 时间：2018-08-07  10:25
* 作者：李祥
* 来源：面试题
* 难点：需要节点存储无序，需要找到所有需要删除的节点
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

//递归法
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

//队列辅助方法
//targetId入队
//对头出队，遍历链表，删除targetId对应节点，并找到targetId为parentId的节点，入队
//如果队列不为空，则对头出队，重复上一步操作，直到队列为空

void bar(node *head, int id){
	std::queue<int> tmp;
	tmp.push(id);   //把父节点入队

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
	//将所要删除的targetid入队
	std::queue<int>tmp;
	tmp.push(targetid);

	//删除targetid
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

	//开始循环
	while (!tmp.empty())//如果队列不为空
	{
		int now = tmp.front();//记录当前对头id
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