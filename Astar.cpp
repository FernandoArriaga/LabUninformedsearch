#include<stdio.h>
	#include <stdlib.h>
	#include <string>
	#include <vector>
	#include <iostream>
	#include <queue>
	#include <stack>
	#include<list>
	bool flag;
	class statenode {
	public:
	int pathcost;
	unsigned int Nstart;
	unsigned int Nfinish;
	statenode* parent;
	std::vector<std::stack<char> > stacks;
	//std::list<statenode*> children;
	void cpc(void)
	{
	    this->pathcost=(parent->pathcost)+1+abs(Nstart-Nfinish);
	}
	

	friend class UCS;
	};
	

	unsigned int hn(statenode* p, statenode* gs)
	{
	    int h=0;
	    statenode current;
	    statenode goal;
	    std::stack<char> buff;
	    std::vector<std::stack<char> >tempc;
	    std::vector<std::stack<char> >tempg;
	

	    for(unsigned int i=0; i < p->stacks.size(); i++)
	{
	current.stacks.push_back(p->stacks[i]);
	}
	 for(unsigned int i=0; i < gs->stacks.size(); i++)
	{
	goal.stacks.push_back(gs->stacks[i]);
	}
	

	 for(unsigned int i=0; i < current.stacks.size(); i++)
	{
	    while(!current.stacks[i].empty())
	    {
	buff.push(current.stacks[i].top());
	current.stacks[i].pop();
	    }
	    tempc.push_back(buff);
	    while(!buff.empty())
	        buff.pop();
	}
	for(unsigned int i=0; i < goal.stacks.size(); i++)
	{
	    while(!goal.stacks[i].empty())
	    {
	buff.push(goal.stacks[i].top());
	goal.stacks[i].pop();
	    }
	    tempg.push_back(buff);
	    while(!buff.empty())
	        buff.pop();
	}
	

	 for (unsigned int i=0; i<tempc.size();i++)
	    {
	

	

	        while (!tempc[i].empty()&&!tempg[i].empty())
	        {
	         if(!(tempg[i].top()=='X'||tempg[i].top()=='x'))
	         {
	            if (tempc[i].top()!=tempg[i].top())
	                h+=3;
	

	            tempc[i].pop();
	

	            tempg[i].pop();
	

	        }
	        else
	            break;
	        }
	        if(!tempg[i].empty())
	        {
	        if(!(tempg[i].top()=='X'||tempg[i].top()=='x'))
	        h+=(abs(tempc[i].size()-tempg[i].size()));
	        }
	        h+=(abs(tempc[i].size()-tempg[i].size()));
	    }
	

	    return h;
	}
	

	

	bool comp (statenode* curr, statenode* gs)
	{
	statenode current;
	    statenode goal;
	    for(unsigned int i=0; i < curr->stacks.size(); i++)
	{
	current.stacks.push_back(curr->stacks[i]);
	}
	 for(unsigned int i=0; i < gs->stacks.size(); i++)
	{
	goal.stacks.push_back(gs->stacks[i]);
	}
	

	

	    for (unsigned int i=0; i<current.stacks.size();i++)
	    {
	

	

	        while (!current.stacks[i].empty()&&!goal.stacks[i].empty())
	        {
	         if(!(goal.stacks[i].top()=='X'||goal.stacks[i].top()=='x'))
	         {
	            if (current.stacks[i].top()!=goal.stacks[i].top())
	                return false;
	

	            current.stacks[i].pop();
	

	            goal.stacks[i].pop();
	

	        }
	        else
	        {
	

	            break;
	        }
	

	        }
	        if((current.stacks[i].empty()!=goal.stacks[i].empty()))
	            {
	            if(!goal.stacks[i].empty())
	            {
	                if((!(goal.stacks[i].top()=='X'||goal.stacks[i].top()=='x')))
	            return false;
	            }
	            else
	                return false;
	            }
	

	

	    }
	    return true;
	}
	

	

	

	

	

	

	statenode* shift(statenode* node, int start, int finish)
	{
	statenode* next=new statenode;
	for(unsigned int i=0; i<node->stacks.size();i++)
	{
	next->stacks.push_back(node->stacks[i]);
	}
	next->stacks[finish].push(next->stacks[start].top());
	next->stacks[start].pop();
	next->parent=node;
	next->Nstart=start;
	next->Nfinish=finish;
	next->cpc();
	return next;
	}
	

	class UCS {
	    public:
	unsigned int height;
	statenode* Instate;
	statenode* Goalstate;
	std::vector<statenode*> Pqueue;
	std::vector<statenode*> Visited;
	

	

	statenode* fn(void)
	{
	unsigned int lowestpathcost=4294967295;;
	    int j=0;
	    statenode* temp;
	    unsigned int pcost;
	

	 for (unsigned int i=0;i<Pqueue.size();i++)
	 {
	     pcost=(Pqueue[i]->pathcost)+hn(Pqueue[i],this->Goalstate);
	     if(pcost<lowestpathcost)
	     {
	         lowestpathcost=pcost;
	         temp=Pqueue[i];
	         j=i;
	     }
	 }
	 if(Pqueue.empty())
	 {
	     flag=1;
	     return temp;
	 }
	 Pqueue.erase(Pqueue.begin()+j);
	 Visited.push_back(temp);
	 return temp;
	}
	

	bool visit (statenode* p)
	{
	    for (unsigned int i =0;i < Visited.size();i++)
	    {
	        if (comp(Visited[i],p))
	        {
	            return true;}
	    }
	    return false;
	}
	

	void expand (statenode* p)
	{
	    statenode* bfer;
	for(unsigned int s=0;s < p->stacks.size();s++)
	{
	    for(unsigned int f=0;f < p->stacks.size();f++)
	    {
	        if (!(p->stacks[s].empty())&&(p->stacks[f].size() < this->height)&&(f!=s)&&(s!=p->Nfinish))
	        {
	

	            bfer=shift(p,s,f);
	            if(!(visit(bfer)))
	            this->Pqueue.push_back(bfer);
	        }
	    }
	}
	

	}
	

	friend class statenode;
	};
	

	

	statenode* initialize(std::string buffer, unsigned int maxs){
	statenode* temp=new statenode;
	std::stack<char> sbuffer;
	int j=0;
	for(unsigned int i=0;i<buffer.length();i++)
	{
	    if(buffer[i]>='A' && buffer[i]<='z')
	    {
	    sbuffer.push(buffer[i]);
	    }
	

	    if(buffer[i]==';')
	    {
	    if(sbuffer.size()>maxs)
	    {
	        flag=1;
	        return temp;
	    }
	    temp->stacks.push_back(sbuffer);
	    j++;
	        while(!sbuffer.empty())
	        {
	        sbuffer.pop();
	        }
	    }
	}
	if(sbuffer.size()>maxs)
	    {
	        flag=1;
	        return temp;
	    }
	temp->stacks.push_back(sbuffer);
	

	temp->parent=0;
	temp->Nstart=0;
	temp->Nfinish=0;
	temp->pathcost=0;
	return temp;
	}
	

	

	

	void solution(statenode* temp)
	{
	    if (temp->parent==0)
	    {
	        std::cout<<"("<<temp->Nstart<<", "<<temp->Nfinish<<")";
	        return;
	    }
	    if (temp->parent->parent==0)
	    {
	        std::cout<<"("<<temp->Nstart<<", "<<temp->Nfinish<<")";
	

	        return;
	    }
	    solution(temp->parent);
	

	    std::cout<<"; "<<"("<<temp->Nstart<<", "<<temp->Nfinish<<")";
	

	    return;
	}
	

	

	int main(int argc, char* argv[]) {
	std::stack<char> out;
	UCS SS;
	statenode* P;
	

	std::string line;
	std::vector<std::string> lines;
	std::cin>>SS.height;
	std::getline(std::cin,line);
	scanf("%d",&SS.height);
	

	std::getline(std::cin, line);
	SS.Instate=initialize(line,SS.height);
	

	std::getline(std::cin, line);
	

	SS.Goalstate=initialize(line,SS.height);
	SS.Goalstate->parent=SS.Instate;
	

	if (!flag)
	{
	SS.Pqueue.push_back(SS.Instate);
	P = SS.fn();
	while(!comp(P,SS.Goalstate))
	{
	    SS.expand(P);
	    P=SS.fn();
	    if (flag)
	        break;
	}
	if (!flag)
	{
	

	std::cout<<P->pathcost<<std::endl;
	solution(P);
	}
	}
	if (flag){
	    std::cout<<"No solution found"<<std::endl;
	}
	

	

	  return 0;
	}
