#ifndef FIBONACCI_H
#define FIBONACCI_H
#include <iostream>
using namespace std;
/*
  This is the definition and execution file for class FIBONACCIHEAP		
*/
template <class V> class FibonacciHeap;

//The structure represents the heap node;
template <class V>
struct heapNode{
//Data Members
	heapNode<V>* prev;
	heapNode<V>* next;
	heapNode<V>* child;
	heapNode<V>* parent;
	V value;
	int degree;
	bool childCut;
//Member Functions
	friend class FibonacciHeap<V>;
	// constructor	
	heapNode(){
		prev=NULL;
		next=NULL;
		child = NULL;
		parent = NULL;
		degree=0;
		childCut = false;
	}
	//copy constructor		
	heapNode(heapNode& newNode){
		prev=newNode.prev;
		next=newNode.next;
		child = newNode.child;
		parent = newNode.parent;
		value = newNode.value;
		degree=newNode.degree;
		childCut = newNode.childCut;
	}
	//operators overloading
	heapNode<V> &operator = (const heapNode &nodeB){
		prev = nodeB.prev;
		next = nodeB.next;
		child = nodeB.child;
		parent = nodeB.parent;
		value = nodeB.value;
		degree = nodeB.degree;
		childCut = nodeB.childCut;
		return *this;
	}
	/*
	heapNode<V> *operator = (const heapNode *nodeB){
		prev = nodeB->prev;
		next = nodeB->next;
		child = nodeB->child;
		parent = nodeB->parent;
		value = nodeB->value;
		degree = nodeB->degree;
		childCut = nodeB->childCut;
		return this;
	}*/
	heapNode<V>* getPrev() {return prev;}
	heapNode<V>* getNext() {return next;}
	heapNode<V>* getChild() {return child;}
	heapNode<V>* getParent() {return parent;}
	V getValue() {return value;}
	bool ischildCut() {return childCut;}
	bool hasChildren() {return child;}
	bool hasParent() {return parent;}
};

template <class V>
class FibonacciHeap{
protected:
	heapNode<V>* heap;
public:

	FibonacciHeap();

	heapNode<V>* insert(V);

	void merge(FibonacciHeap&);

	bool isEmpty();

	V getMinimum();

	V removeMinimum();

	void decreaseKey(heapNode<V>* ,V );

	heapNode<V>* find(V value);

//private:
	heapNode<V>* _empty();

	heapNode<V>* _singleton(V);

	heapNode<V>* _merge(heapNode<V>* ,heapNode<V>* );

	void _deleteAll(heapNode<V>*);
	
	void _addChild(heapNode<V>*,heapNode<V>*);
	void _unMarkAndUnParentAll(heapNode<V>*);

	heapNode<V>* _removeMinimum(heapNode<V>*);

	heapNode<V>* _cut(heapNode<V>*,heapNode<V>*);

	heapNode<V>* _decreaseKey(heapNode<V>*,heapNode<V>*,V);

	heapNode<V>* _find(heapNode<V>*,V);

    void dump();
	void _dumpChildren(heapNode<V>*);
};

template <class V>
FibonacciHeap<V>::FibonacciHeap() {
		heap=_empty();
	}

template <class V>
heapNode<V>* FibonacciHeap<V>::insert(V value) {
	heapNode<V>* ret=_singleton(value);
	heap=_merge(heap,ret);
	return ret;
}

template<class V>
void FibonacciHeap<V>::merge(FibonacciHeap& other) {
	heap=_merge(heap,other.heap);
	other.heap=_empty();
}

template<class V>
bool FibonacciHeap<V>::isEmpty() {
	return heap==NULL;
	}

template<class V>
V FibonacciHeap<V>::getMinimum() {
		return heap->value;
	}

template<class V>
V FibonacciHeap<V>::removeMinimum() {
	heapNode<V>* old=heap;
	heap=_removeMinimum(heap);
	V ret=old->value;
	delete old;
	return ret;
}

template<class V>
void FibonacciHeap<V>::decreaseKey(heapNode<V>* n,V value) {
		heap=_decreaseKey(heap,n,value);
}

template<class V>
heapNode<V>* FibonacciHeap<V>::find(V value) {
	return _find(heap,value);
}
	
template<class V>
heapNode<V>* FibonacciHeap<V>::_empty() {
	return NULL;
}

template<class V>
heapNode<V>* FibonacciHeap<V>::_singleton(V value) {
	heapNode<V>* n=new heapNode<V>;
	n->value=value;
	n->prev=n->next=n;
	n->degree=0;
	n->childCut=false;
	n->child=NULL;
	n->parent=NULL;
	return n;
}

template<class V>
heapNode<V>* FibonacciHeap<V>::_merge(heapNode<V>* a,heapNode<V>* b) {
	if(a==NULL)return b;
	if(b==NULL)return a;
	if(a->value>b->value) {
		heapNode<V>* temp=a;
		a=b;
		b=temp;
	}
	heapNode<V>* an=a->next;
	heapNode<V>* bp=b->prev;
	a->next=b;
	b->prev=a;
	an->prev=bp;
	bp->next=an;
	return a;
}

template<class V>
void FibonacciHeap<V>::_deleteAll(heapNode<V>* n) {
	if(n!=NULL) {
		heapNode<V>* c=n;
		do {
			heapNode<V>* d=c;
			c=c->next;
			_deleteAll(d->child);
			delete d;
		} while(c!=n);
	}
}
	
template<class V>
void FibonacciHeap<V>::_addChild(heapNode<V>* parent,heapNode<V>* child) {
	child->prev=child->next=child;
	child->parent=parent;
	parent->degree++;
	parent->child=_merge(parent->child,child);
}

template<class V>
void FibonacciHeap<V>::_unMarkAndUnParentAll(heapNode<V>* n) {
	if(n==NULL)return;
	heapNode<V>* c=n;
	do {
		c->childCut=false;
		c->parent=NULL;
		c=c->next;
	}while(c!=n);
}

template<class V>
heapNode<V>* FibonacciHeap<V>::_removeMinimum(heapNode<V>* n) {
	_unMarkAndUnParentAll(n->child);
	if(n->next==n) {
		n=n->child;
	} else {
		n->next->prev=n->prev;
		n->prev->next=n->next;
		n=_merge(n->next,n->child);
	}
	if(n==NULL)return n;
		heapNode<V>* trees[64]={NULL};
		
	while(true) {
		if(trees[n->degree]!=NULL) {
			heapNode<V>* t=trees[n->degree];
			if(t==n)break;
			trees[n->degree]=NULL;
			if(n->value<t->value) {
				t->prev->next=t->next;
				t->next->prev=t->prev;
				_addChild(n,t);
			} else {
				t->prev->next=t->next;
				t->next->prev=t->prev;
				if(n->next==n) {
					t->next=t->prev=t;
					_addChild(t,n);
					n=t;
				} else {
					n->prev->next=t;
					n->next->prev=t;
					t->next=n->next;
					t->prev=n->prev;
					_addChild(t,n);
					n=t;
				}
			}
			continue;
		} else {
				trees[n->degree]=n;
			}
			n=n->next;
		}
		heapNode<V>* min=n;
		do {
			if(n->value<min->value)min=n;
			n=n->next;
		} while(n!=n);
		return min;
	}

template<class V>
heapNode<V>* FibonacciHeap<V>::_cut(heapNode<V>* heap,heapNode<V>* n) {
		if(n->next==n) {
			n->parent->child=NULL;
		} else {
			n->next->prev=n->prev;
			n->prev->next=n->next;
			n->parent->child=n->next;
		}
		n->next=n->prev=n;
		n->childCut=false;
		return _merge(heap,n);
	}

template<class V>
heapNode<V>* FibonacciHeap<V>::_decreaseKey(heapNode<V>* heap,heapNode<V>* n,V value) {
		if(n->value<value)return heap;
		n->value=value;

		if(n->parent!=NULL && n->value<n->parent->value) {
			heap=_cut(heap,n);
			heapNode<V>* parent=n->parent;
			n->parent=NULL;
			while(parent!=NULL && parent->childCut) {
				heap=_cut(heap,parent);
				n=parent;
				parent=n->parent;
				n->parent=NULL;
			}
			if(parent!=NULL && parent->parent!=NULL)parent->childCut=true;
		}
		//update the minimum pointer
		heapNode<V>* minNode = heap;
		heapNode<V>* tmpNode = heap;
		do{
			if(tmpNode->value<minNode->value)minNode = tmpNode;
			tmpNode = tmpNode->next;
		} while(tmpNode!=heap);
		heap = minNode;
		return heap;
	}


template<class V>
heapNode<V>* FibonacciHeap<V>::_find(heapNode<V>* heap,V value) {
		heapNode<V>* n=heap;
		if(n==NULL)return NULL;
		do {
			if(n->value==value)return n;
			heapNode<V>* ret=_find(n->child,value);
			if(ret)return ret;
			n=n->next;
		}while(n!=heap);
		return NULL;
	}

template<class V>
void  FibonacciHeap<V>::dump(){
		cout<<"digraph G{"<<endl;
		if(heap==NULL) {
			cout<<"empty;"<<endl<<"}"<<endl;
		}
		cout<<"minimum ->"<<heap->getValue()<<endl;
		heapNode<int>* c=heap;
		do{
			_dumpChildren(c);
			c=c->getNext();
		} while(c!=heap);
		cout<<"}"<<endl;
}


template<class V>
void  FibonacciHeap<V>::_dumpChildren(heapNode<V>* n) {
	cout<<"....."<<n->getValue()<<"....."<<n->getNext()->getValue()<<endl;
	cout<<n->getValue()<<".... "<<n->getPrev()->getValue()<<endl;
	if(n->ischildCut())cout<<n->getValue()<<endl;
		if(n->hasParent()){
			cout<<n->getValue()<<" -> "<<endl<<n->getParent()->getValue()<<endl;
		}
		cout<<n->getValue()<<endl;
		if(n->hasChildren()){
			heapNode<int>* c=n->getChild();
			do {
				cout<<n->getValue()<<"->"<<c->getValue()<<endl;
				_dumpChildren(c);
				c=c->getNext();
			} while(c!=n->getChild());
		}
}
#endif
