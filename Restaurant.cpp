#include "main.h"

class imp_res : public Restaurant
{
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
		}
		void swapNode(customer* a, customer* b){
			customer* aPrev = a->prev;
			customer* aNext = a->next;
			customer* bPrev = b->prev;
			customer* bNext = b->next;
			if(aNext == b || bNext == a){
				if(aNext == b){
					aPrev->next = b;
					b->prev = aPrev;
					b->next = a;
					a->prev = b;
					a->next = bNext;
					bNext->prev = a;
				}
				else if( bNext == a){
					bPrev->next = a;
					a->prev = bPrev;
					a->next = b;
					b->prev = a;
					b->next = aNext;
					aNext->prev = b;
				}
			}
			else if( aPrev == nullptr || bNext == nullptr){
				
			}
			else{

			}
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
			if(cur){
				customer *p = cur;
				for(int i =0; i<curSize; i++){
					if(name == p->name){
						return;
					}
					p = p->next;
				}
			}
			
			if(qHead){
				customer *p = qHead;
				for(int i=0; i<qSize; i++){
					if(name == p->name)
						return;
					p = p->next;
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
					qSize++;
				}
				else return;
			}
			else {
				if(curSize < MAXSIZE/2){
					if(!cur){
						cur = new customer (name, energy, nullptr, nullptr);
						first = last = new customer(name, energy,nullptr,nullptr);
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
						last->next = new customer(name,energy,last,nullptr);
						last = last->next;
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
						first = last = new customer(name, energy,nullptr,nullptr);
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
						last->next = new customer(name,energy,last,nullptr);
						last = last->next;
					}
					curSize++;
				}

			}
			
		}
		void BLUE(int num)
		{
			
			if(num >= curSize){
				num = curSize;
			}
			
			for(int i=0; i< num; i++){
				customer* cus = cur;
				for(int j=0; j<curSize; j++){
					if(cus->name == first->name){
						deleteNode(cus);
						break;
					}
					else{
						cus = cus->next;
					}
				}
				customer *del = first;
				first = first->next;
				if(first){
					first->prev = nullptr;
				}
				else{
					last = nullptr; // = first
				}
				delete del;
			}
			for(int i=0; i < num; i++){	
				if(qSize){
					string name = qHead->name;
					int energy = qHead->energy;
					popQueue();
					RED(name,energy);
				}
				else break;
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
			queueOrder = cloneQueue(qHead);
			
			// cout<<"---------"<<endl;
			// customer* t = first;
			// while(t){
			// 	t->print();
			// 	t = t->next;
			// }
			// cout<<endl<<"---------"<<endl;

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
			// cout<<q<<endl;
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
			int pos = 0;
			int neg = 0;
			customer *p = cur;
			for(int i =0; i<curSize; i++){
				if(p->energy < 0){
					neg +=p->energy;
				}
				else 
					pos+= p->energy;
				p = p->next;

			}
			p = qHead;
			for(int i =0; i< qSize; i++){
				if(p->energy < 0){
					neg +=p->energy;
				}
				else 
					pos+= p->energy;
				p = p->next;
			}
			
			if((-neg) > pos){
				customer* p = qCur;
				while(p){
					if(p->energy > 0){
						p->print();
						qSize--;
						customer * temp = p;
						customer* nextPos = p->next;
						customer* prevPos = p->prev;
						if(prevPos) prevPos->next = nextPos;
						else {
							qHead = p->next;
						}
						if(nextPos) nextPos->prev = prevPos;
						else{
							qCur = p->prev;
						}
						p = p->prev;
						delete temp;
					}
					else p = p->prev;
				}
				p = last;
				while (p)
				{
					if(p->energy > 0){
						customer * temp = p;
						
						customer* nextPos = p->next;
						customer* prevPos = p->prev;
						if(prevPos) prevPos->next = nextPos;
						else {
							first = p->next;
						}
						if(nextPos) nextPos->prev = prevPos;
						else{
							last = p->prev;
						}

						customer* cus= cur;
						for(int i=0; i< curSize; i++){
							if(cus->name == temp->name){
								cus->print();
								deleteNode(cus);
								break;
							}
							cus = cus->next;
						}
						p = p->prev;
						delete temp;
					}
					else p = p->prev;
				}
			}
			else {
				customer* p = qCur;
				while(p){
					if(p->energy < 0){
						p->print();
						qSize--;
						customer * temp = p;
						customer* nextPos = p->next;
						customer* prevPos = p->prev;
						if(prevPos) prevPos->next = nextPos;
						else {
							qHead = p->next;
						}
						if(nextPos) nextPos->prev = prevPos;
						else{
							qCur = p->prev;
						}
						p = p->prev;
						delete temp;
					}
					else p = p->prev;
				}
				p = last;
				while (p)
				{
					if(p->energy < 0){
						customer * temp = p;
						customer* nextPos = p->next;
						customer* prevPos = p->prev;
						if(prevPos) prevPos->next = nextPos;
						else {
							first = p->next;
						}
						if(nextPos) nextPos->prev = prevPos;
						else{
							last = p->prev;
						}

						customer* cus= cur;
						for(int i=0; i< curSize; i++){
							if(cus->name == temp->name){
								cus->print();
								deleteNode(cus);
								break;
							}
							cus = cus->next;
						}
						p = p->prev;
						delete temp;
					}
					else p = p->prev;
				}
			}
			while(curSize < MAXSIZE){
				if(qSize){
					customer* cus = qHead;
					string name = cus->name;
					int energy = cus->energy;
					popQueue();
					RED(name,energy);
				}
				else break;
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