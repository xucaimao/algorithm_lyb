
#include<cstdio>
const int maxn=5;
int arr[maxn];

void print_permutation(int* arr, int cur,int n){
	if(cur==n){						//到了数组尾
		for(int i=0;i<n;i++)
			printf("%d ",arr[i]);
		printf("\n");
	}
	else for(int i=1;i<=n;i++){
		int ok=1;
		for(int j=0;j<cur;j++)
			if(arr[j]==i) ok=0;
		if(ok){
			arr[cur]=i;
			print_permutation(arr,cur+1,n);
		}
	}
}

int main(){
	print_permutation(arr,0,3);
}