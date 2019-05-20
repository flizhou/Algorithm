#include <iostream>
#include <vector>

using namespace std;

class MinHeap{

public:
  MinHeap(int[], int);
  void PercolateDown();
  int Pop();
  bool IsMaxHeap();
  void Print();

private:
  void PercolateDownHepler(int);
  void ReBalance(int);
  int* minHeap;
  int size;
  bool maxHeap;
  void swap(int, int);
};

  
int main(){

  int N, k, num;
  int*  numVec;

  while(cin>>N>>k){
	
  	numVec = new int[N];
  
  	for(int i=0; i<N; ++i){

    	cin>>num;
    	numVec[i] = num;
  	}
  
  	MinHeap minHeap(numVec, N);

  	minHeap.PercolateDown();
  	for(int i=0; i<k-1; ++i){
    	minHeap.Pop();
  	}

  	if(minHeap.IsMaxHeap()){
    	cout<<'Y'<<"  ";
  	}else{
    	cout<<'N'<<"  ";
  	}

  	cout<<minHeap.Pop()<<'\n';
  
  	delete[] numVec;

  }
  
  return 0;
}


void MinHeap::swap(int a, int b){

  int temp_a = minHeap[a];
  minHeap[a] = minHeap[b];
  minHeap[b] = temp_a;

}


MinHeap::MinHeap(int* vec, int N):minHeap(vec), size(N), maxHeap(true){

}


void MinHeap::PercolateDown(){

  PercolateDownHepler(size-1);
}


int MinHeap::Pop(){

  --size;
  swap(size, 0);
  ReBalance(0);
  return minHeap[size];
}


bool MinHeap::IsMaxHeap(){

  return maxHeap;
}


void MinHeap::PercolateDownHepler(int index){

  if(index <= 0){
    return;
  }
  
  if (index == size-1 and (index-1)/2 != (index-2)/2){

    if(minHeap[(index-1)/2]>minHeap[index]){
      swap((index-1)/2, index);

    }else{
      maxHeap = false;
    }
    
    PercolateDownHepler(index-1);

  } else {

    if(minHeap[(index-1)/2]<minHeap[index] or minHeap[(index-1)/2]<minHeap[index-1]){
      maxHeap = false;
    }

    if(minHeap[(index-1)/2]>minHeap[index] or minHeap[(index-1)/2]>minHeap[index-1]){

      if(minHeap[index] > minHeap[index-1]){
	swap((index-1)/2, index-1);
	ReBalance(index-1);

      }else{
	swap((index-1)/2, index);
	ReBalance(index);
      }

    }
    PercolateDownHepler(index-2);
  }
}


void MinHeap::ReBalance(int index){

  if(index*2+2<size-1){

    if(minHeap[index] > minHeap[index*2+1] or minHeap[index] > minHeap[index*2+2]){
      
		if(minHeap[index*2+1] < minHeap[index*2+2]){
			swap(index*2+1, index);
			ReBalance(index*2+1);
    	}else{
			swap(index*2+2, index);
			ReBalance(index*2+2);
    	}
    }

  }else if(index*2+1<size-1 and minHeap[index] > minHeap[index*2+1]){
	  swap(index*2+1, index);

  } 
}

void MinHeap::Print(){
 
  int count = 1;
  for (int i=0; i<size; ++i){

    cout<<minHeap[i]<<' ';
    if((i+1)/count != (i+2)/count){
      cout<<endl;
      count*= 2;
    }
  }
  cout<<endl;
}
