#include "main.h"

class imp_res : public Restaurant
{
	bool dontAdd;
	customer *cur;
	customer *qHead, *qCur;
	customer *first, *last;
	customer *queueOrder;
	int curSize,qSize;
	public:	
		imp_res() {
			cur=qHead = qCur = first = last =  nullptr;
			queueOrder = nullptr;
			curSize = qSize =  0;
			dontAdd = false;
		}
		void deleteInOrder(customer* p ){
			customer* tmp = p;
			if(p == first){
				first = first->next;
				if(first)
					first->prev = nullptr;
				else{
					last = 0;
				}
			}
			else if( p== last){
				last = last->prev;
				if(last) last->next = nullptr;
				else first = 0;
			}
			else{
				customer*	pPrev = p->prev;
				customer*	pNext = p->next;
				pPrev->next = pNext;
				pNext->prev = pPrev;
			}
			delete tmp; 
		}
		void deleteNodeInQueue(customer* p){
			customer* tmp = p;
			if(p == qHead){
				qHead = qHead->next;
				if(qHead)
					qHead->prev = nullptr;
				else{
					qCur = 0;
				}
			}
			else if( p== qCur){
				qCur = qCur->prev;
				if(qCur) qCur->next = nullptr;
				else qHead = 0;
			}
			else{
				customer*	pPrev = p->prev;
				customer*	pNext = p->next;
				pPrev->next = pNext;
				pNext->prev = pPrev;
			}
			delete tmp;
			qSize --;
		}
		customer* cloneQueue(customer* head){
			int i = 1;
			customer* p = nullptr;
			customer* newHead = p;
			if(head){
				p = new customer(head->name, i, nullptr,nullptr);	
				newHead = p;
				head = head->next;
				i++;
			} 
			while (head)
			{
				customer* pNew = new customer(head->name, i , p, nullptr);
				p->next = pNew;
				p = p->next;
				head = head->next;
				i++;
			}
			return newHead;
		}
		void deleteNode(customer* p){
			customer* pPrev = p->prev;
			customer* pNext = p->next;
			if(pPrev == pNext){
				cur = pPrev;
				if(cur)
					cur->next = cur->prev = 0;
			}
			else{
				cur = p;
				if (cur->energy > 0)
					cur = cur->next;
				else
					cur = cur->prev;
				pPrev->next = pNext;
				pNext->prev = pPrev;
			}
			delete p;
			curSize--;
			// if(curSize==1)
			// 	cur->next = cur->prev = nullptr;
		}
		void popQueue(){
			
			customer * temp = qHead;
			qHead = qHead->next;
			
			// temp->next = temp->prev = nullptr;
			delete temp;
			if(qHead)
				qHead->prev = nullptr;
			else{
				qCur = 0;
			}
			qSize--;
		}
		void RED(string name, int energy)
		{
			if(!energy){
				return;
			}
			if(first && !dontAdd){
				customer* t = first;
				while(t){
					if(t->name == name) return;
					t = t->next;
				}
			}
			if(curSize >= MAXSIZE){
				if(qSize < MAXSIZE){
					if(!qSize){
						qHead = qCur = new customer(name,energy,nullptr,nullptr);
					}
					else {
						qCur->next = new customer(name,energy,qCur,nullptr);
						qCur = qCur->next;
					}
					if(!dontAdd){
						if(!first) first = last = new customer(name,energy,nullptr,nullptr);
						else {
							last->next = new customer(name, energy, last, nullptr);
							last = last->next;
						}
					}
					
					qSize++;
				}
				else return;
			}
			else {
				if(curSize < MAXSIZE/2){
					if(!cur){
						cur = new customer (name, energy, nullptr, nullptr);
					}
					else{
						if(energy >= cur->energy){
							customer *cusNext = cur->next;
							if(cusNext){
								cur->next = new customer(name,energy,cur,cusNext);
								cur = cur->next;
								cusNext->prev = cur;
							}
							else {
								cur->next = new customer(name, energy, cur,nullptr);
								/// make cirly linked list
								
								cusNext= cur->next;
								cusNext->next = cur;
								cur->prev = cusNext;
								cur = cur->next;
								
							}
						}
						else{
							customer *cusPrev = cur->prev;
							if(cusPrev){
								cur->prev = new customer(name, energy, cusPrev, cur);
								cur  = cur->prev;
								cusPrev->next = cur;
							}
							else{
								cur->prev = new customer(name, energy, nullptr, cur);
								cusPrev = cur->prev;
								cusPrev->prev=  cur;
								cur->next = cusPrev;
								cur = cur->prev;
								///make cirly ll
							}
						}
					}
					curSize++;
				}
				else{
					bool isNegative = false;
					int res = 0;
					customer* p =cur;
					customer* pos = cur;
					for(int i=0; i<curSize; i++){
						if( res < abs(energy- p->energy)){
							res = abs(energy- p->energy);
							(energy- p->energy<0)? isNegative = true : isNegative = false;
							pos = p;
						}
						p = p->next;
					}
					cur = pos;
					if(!cur){
						cur = new customer (name, energy, nullptr, nullptr);
						
					}
					else{
						if(!isNegative){ //them ben phai
							customer *cusNext = cur->next;
							if(cusNext){
								cur->next = new customer(name,energy,cur,cusNext);
								cur = cur->next;
								cusNext->prev = cur;
							}
							else {
								cur->next = new customer(name, energy, cur,nullptr);
								cusNext= cur->next;
								cusNext->next = cur;
								cur->prev = cusNext;
								cur = cur->next;
								
							}
						}
						else{
							customer *cusPrev = cur->prev;
							if(cusPrev){
								cur->prev = new customer(name, energy, cusPrev, cur);
								cur  = cur->prev;
								cusPrev->next = cur;
							}
							else{
								cur->prev = new customer(name, energy, nullptr, cur);
								cusPrev = cur->prev;
								cusPrev->prev=  cur;
								cur->next = cusPrev;
								cur = cur->prev;
							}
						}
						
					}
					curSize++;
				}
				if(!dontAdd){
					if(!first) first = last = new customer(name,energy,nullptr,nullptr);
					else {
						last->next = new customer(name, energy, last, nullptr);
						last = last->next;
					}
				}
				
			}
			
		}
		void BLUE(int num)
		{
			
			if(num >= curSize){
				num = curSize;
			}
			customer* p = first;
			for(int i=0; i< num && p; i++){
				customer* cus = cur;
				
				bool foundInTable = false;

				for(int j=0; j<curSize && !foundInTable ; j++){
					if(cus->name == p->name){
						deleteNode(cus);
						foundInTable = true;
					}
					cus = cus->next;
				}
				if(foundInTable){
					if(p == first){
						customer *del = first;
						first = first->next;
						p = p->next;
						if(first){
							first->prev = nullptr;
						}
						else{
							last = nullptr; // = first
						}
						delete del;
					}
					else{
					   	customer* pPrev = p->prev;
						customer* pNext = p->next;
						customer* temp = p;
						p = p->next;
						pPrev->next = pNext;
						pNext->prev = pPrev;
						delete temp;
					}
				}
				else{
					p = p->next;
					i--;
				}
			}
			for(int i=0; i < num  && qSize; i++){	
				dontAdd = true;
				string name = qHead->name;
				int energy = qHead->energy;
				popQueue();
				RED(name,energy);
				dontAdd = false;
			}
		}
		int inssort(customer*p, int n , int incr){
			int N = 0;
			for(int i = incr; i<n; i+=incr){
				int q = incr;
				while(q--){
					p = p->next;
				}
 				customer* p1 = p;
				for(int j =i; j>= incr; j-=incr){
					q = incr;
					customer* p2 = p1;
					while(q--){
						p2 = p2->prev;
					}
					if(incr != 1){
						if(abs(p2->energy) < abs(p1->energy)){
							if(p==p1){
								p = p2;
							}
							customer* prevP2 = p2->prev;
							customer* nextP2 = p2->next;
							customer* prevP1 = p1->prev;
							customer* nextP1 = p1->next;
							customer* temp = p2;
							p2 = p1;
							p1 = temp;
							if(prevP2){
								prevP2 ->next = p2;
								p2->prev = prevP2;
							}
							else{
								qHead = p2;
								p2->prev = nullptr;
							}
							p2->next = nextP2;
							nextP2->prev = p2;

							if(nextP1){
								nextP1 ->prev = p1;
								p1->next = nextP1;
							}
							else{
								qCur = p1;
								p1->next = nullptr;
							}
							p1->prev = prevP1;
							prevP1->next = p1;
							N++;
						}
						else if(abs(p2->energy) == abs(p1->energy)){
							int o1 =0 ,o2 = 0;
							customer* k = queueOrder;
							while(k){
								if(k->name == p1->name){
									o1 = k->energy;
								}
								if(k->name == p2->name){
									o2 = k->energy;
								}
								k = k->next;
							}
							if(o2 > o1){
								if(p==p1){
									p = p2;
								}
								customer* prevP2 = p2->prev;
								customer* nextP2 = p2->next;
								customer* prevP1 = p1->prev;
								customer* nextP1 = p1->next;
								customer* temp = p2;
								p2 = p1;
								p1 = temp;
								if(prevP2){
									prevP2 ->next = p2;
									p2->prev = prevP2;
								}
								else{
									qHead = p2;
									p2->prev = nullptr;
								}
								p2->next = nextP2;
								nextP2->prev = p2;

								if(nextP1){
									nextP1 ->prev = p1;
									p1->next = nextP1;
								}
								else{
									qCur = p1;
									p1->next = nullptr;
								}
								p1->prev = prevP1;
								prevP1->next = p1;
								N++;
							}
						}
					}
					else{
						if(abs(p2->energy) < abs(p1->energy)){
							if(p==p1) p = p2;
							customer* prevNode = p2->prev;
							customer* nextNode = p1->next;
							customer* temp = p2;
							p2 = p1;
							p1 = temp;
							p2->next = p1;
							p1->prev = p2;
							p1->next = nextNode;
							if(nextNode) nextNode->prev = p1;
							else qCur = p1;
							p2->prev = prevNode;
							if(prevNode) prevNode->next = p2;
							else qHead  = p2;
							N++;
						}
						else if(abs(p2->energy) == abs(p1->energy)){
							int o1 =0 ,o2 = 0;
							customer* k = queueOrder;
							while(k){
								if(k->name == p1->name){
									o1 = k->energy;
								}
								if(k->name == p2->name){
									o2 = k->energy;
								}
								k = k->next;
							}
							if(o2 > o1){
								if(p==p1) p = p2;
								customer* prevNode = p2->prev;
								customer* nextNode = p1->next;
								customer* temp = p2;
								p2 = p1;
								p1 = temp;
								p2->next = p1;
								p1->prev = p2;
								p1->next = nextNode;
								if(nextNode) nextNode->prev = p1;
								else qCur = p1;
								p2->prev = prevNode;
								if(prevNode) prevNode->next = p2;
								else qHead  = p2;
								N++;
							}
						}
					}
					
					q = incr;
					while(q--){
						p1= p1->prev;
					}
				}
			}
			return N;
		}
		int shellSort(int n){
			if(n == 0) return 0;
			int N = 0;
			customer* p = qHead;
			for(int i= n/2; i>2; i/=2){
				p = qHead;
				for(int j =0; j<i; j++){
					N+=inssort(p,n-j, i);
					p = qHead;
					int pos = j;
					while(pos--){
						p = p->next;
					}
					p = p->next;
				}
				customer * tt = qHead;
			}
			N+=inssort(qHead,n,1);
			return N;
		}
		void PURPLE() 
		{
			queueOrder = cloneQueue(first);
			int MAX_ENERGY = 0;
			customer* p = qCur;
			int pos = 0;
			for (int i = qSize; p; i--)
			{
				if (MAX_ENERGY <  abs(p->energy))
				{
					MAX_ENERGY = abs(p->energy);
					pos = i;
				}
				p = p->prev;
			}
			int q = shellSort(pos) % MAXSIZE;
			BLUE(q);
			// xoa queueoreder
			while(queueOrder){
				customer* temp = queueOrder;
				queueOrder= queueOrder->next;
				delete temp;
			}
		}
		void REVERSAL() 
		{

			if(curSize > 1){
				customer* p = cur;
				while(p->energy * cur->energy > 0){
					p = p->prev;
					if(p->name == cur->name){
						for(int i=0; i<curSize; i++){
							customer* tmp = p->next;
							p->next = p->prev;
							p->prev = tmp;
							p = p->prev;
						}
						return;
					}
				}
				customer *p1 = cur;
				customer* p2 = cur->next;
				while(p1->energy * p2->energy < 0){
					p2 = p2->next;
				}
				bool stop = false;
				
				while(!stop){
					if(p2->next != p1 && p1->next != p2){
						customer* p2Prev = p2->prev;
						customer* p2Next = p2->next;
						customer* p1Prev = p1->prev;
						customer* p1Next = p1->next;
						customer* temp = p1;
						p1 = p2;
						p2 = temp;
						p1->prev = p1Prev;
						p1Prev->next = p1;
						p1->next = p1Next;
						p1Next->prev = p1;
						p2->prev = p2Prev;
						p2Prev->next = p2;
						p2->next = p2Next;
						p2Next->prev = p2;
					}
					else if(p2->next == p1) {
						customer* p2Prev = p2->prev;
						customer* p1Next = p1->next;
						customer* temp = p1;
						p1 = p2;
						p2 = temp;
						p1->next = p1Next;
						p1Next->prev = p1;
						p1->prev = p2;
						p2->next = p1;
						p2->prev = p2Prev;
						p2Prev->next = p2;
					}
					else{
						customer* p1Prev = p1->prev;
						customer* p2Next = p2->next;
						customer* temp = p1;
						p1 = p2;
						p2 = temp;
						p1->prev = p1Prev;
						p1Prev->next = p1;
						p1->next = p2;
						p2->prev = p1;
						p2->next = p2Next;
						p2Next->prev = p2;
					}
					int sign = p1->energy / abs(p1->energy);
					p1 = p1->prev;
					while(sign* p1->energy < 0){
						p1 = p1->prev;
					}
					if(p1 == p2){
						stop = 1;
					}
					p2 = p2->next;
					while(sign * p2->energy < 0){
						p2 = p2->next;
					}
					if(p1 == p2){
						stop = 1;
					}

				}
				//---------------------
				p1 = p;
				p2 = p->next;
				while(p1->energy * p2->energy < 0){
					p2 = p2->next;
				}
				stop = false;
				while(!stop){
					
					if(p2->next != p1 && p1->next != p2){
						customer* p2Prev = p2->prev;
						customer* p2Next = p2->next;
						customer* p1Prev = p1->prev;
						customer* p1Next = p1->next;
						customer* temp = p1;
						p1 = p2;
						p2 = temp;
						p1->prev = p1Prev;
						p1Prev->next = p1;
						p1->next = p1Next;
						p1Next->prev = p1;
						p2->prev = p2Prev;
						p2Prev->next = p2;
						p2->next = p2Next;
						p2Next->prev = p2;
					}
					else if(p2->next == p1) {
						customer* p2Prev = p2->prev;
						customer* p1Next = p1->next;
						customer* temp = p1;
						p1 = p2;
						p2 = temp;
						p1->next = p1Next;
						p1Next->prev = p1;
						p1->prev = p2;
						p2->next = p1;
						p2->prev = p2Prev;
						p2Prev->next = p2;
					}
					else{
						customer* p1Prev = p1->prev;
						customer* p2Next = p2->next;
						customer* temp = p1;
						p1 = p2;
						p2 = temp;
						p1->prev = p1Prev;
						p1Prev->next = p1;
						p1->next = p2;
						p2->prev = p1;
						p2->next = p2Next;
						p2Next->prev = p2;
					}
					int sign = p1->energy / abs(p1->energy);
					p1 = p1->prev;
					while(sign* p1->energy < 0){
						p1 = p1->prev;
					}
					if(p1 == p2){
						stop = 1;
					}
					p2 = p2->next;
					while(sign * p2->energy < 0){
						p2 = p2->next;
					}
					if(p1 == p2){
						stop = 1;
					}
				}
			}
			
		}
		void UNLIMITED_VOID()
		{
			if(curSize < 4) return;
			customer* finalMinPos = cur;
			customer* minPos = cur; 
			customer* target = cur;
			int res = INT8_MAX;
			int targetSize = 0;
			int fullSize = 0;
			customer* p = cur;
			for(int i =0; i<curSize; i++){
				for(int size = 1; size <= curSize; size++){
					
					int sum = 0;
					customer* pp =p;
					int minEnergy = pp->energy;
					minPos = pp;
					sum += pp->energy;
					int len = 0;
					for(int k=1; k< size; k++){
						pp = pp->next;
						sum+= pp->energy;
						if(pp->energy < minEnergy){
							minEnergy = pp->energy;
							minPos = pp;
							len = k;
						}
					}
					if(res >= sum && size >= 4){
						if(sum == res){
							if(fullSize <= size){
								res = sum;
								targetSize = size - len;
								fullSize = size;
								target = p;
								finalMinPos = minPos;
							}
						}
						else {
							res = sum;
							targetSize = size - len;
							fullSize = size;
							target = p;
							finalMinPos = minPos;
						}
					}
				}
				p = p->next;
			}
			p = finalMinPos;
			for(int i= 0 ; i<targetSize; i++){
				p->print();
				p = p->next;
			}
			p = target;
			for(int i =0; i< fullSize - targetSize; i++){
				p->print();
				p = p->next;
			}
		}
		void DOMAIN_EXPANSION()
		{
			customer* temp = nullptr;
			int pos = 0;
			int all = 0;
			customer *p = first;
			while(p){
				if(p->energy > 0){
					pos += p->energy;
				}
				all += p->energy;
				p = p->next;
			}
			
			if( abs(all) > pos){
				customer* p = first;
				while(p){
					if(p->energy > 0){
						customer* del = p;
						if(!temp) temp = new customer(p->name, p->energy,nullptr, nullptr);
						else{
							temp->next = new customer(p->name, p->energy, temp, nullptr);
							temp = temp->next;
						}
						bool inTable = false;
						customer* cusInTable = cur;
						for(int i=0; i< curSize && !inTable && cusInTable; i++){
							if(cusInTable->name == p->name){
								deleteNode(cusInTable);
								inTable = true;
							}
							cusInTable = cusInTable->next;
						}

						if(!inTable){
							customer* cusInQueue = qHead;
							while (cusInQueue)
							{
								if(cusInQueue->name == p->name){
									deleteNodeInQueue(cusInQueue);
									break;
								}
								cusInQueue = cusInQueue->next;
							}
							
						}
						p = p->next;
						deleteInOrder(del);

					}
					else 
						p = p->next;
				}
			}
			else {
				customer* p = first;
				while(p){
					if(p->energy < 0){
						customer* del = p;
						if(!temp) temp = new customer(p->name, p->energy,nullptr, nullptr);
						else{
							temp->next = new customer(p->name, p->energy, temp, nullptr);
							temp = temp->next;
						}
						bool inTable = false;
						customer* cusInTable = cur;
						for(int i=0; i< curSize && !inTable && cusInTable; i++){
							if(cusInTable->name == p->name){
								deleteNode(cusInTable);
								inTable = true;
							}
							cusInTable = cusInTable->next;
						}

						if(!inTable){
							customer* cusInQueue = qHead;
							while (cusInQueue)
							{
								if(cusInQueue->name == p->name){
									deleteNodeInQueue(cusInQueue);
									break;
								}
								cusInQueue = cusInQueue->next;
							}
							
						}
						p = p->next;
						deleteInOrder(del);
					}
					else 
						p = p->next;
				}
			}
			while(curSize < MAXSIZE && qSize){
				dontAdd = true;
				customer* cus = qHead;
				string name = cus->name;
				int energy = cus->energy;
				popQueue();
				RED(name,energy);
				dontAdd = false;
			}
			while(temp){
				customer *tt = temp;
				temp->print();
				temp = temp->prev;
				delete tt;
			}
		}
		void LIGHT(int num)
		{
			// cout<<query++<<" --------------------"<<endl;
			if(num > 0){
				customer *p = cur;
				// cout<<curSize<<endl;
				for(int i =0; i<curSize; i++){
					p->print();
					p = p->next;
				}
			}
			else if(num < 0){
				customer * p = cur;
				// cout<<curSize<<endl;
				for(int i=0; i<curSize; i++){
					p->print();
					p = p->prev;
				}
			}
			else {
				customer *p = qHead;
				// cout<<qSize<<endl;
				for(int i=0; i<qSize ; i++){
					p->print();
					p = p->next;
				}
			}
		}
};