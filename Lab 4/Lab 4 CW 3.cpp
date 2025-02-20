#include<iostream>
using namespace std;
class DynamicArray{
	int *arr;
	int size;
	public:
		DynamicArray(){
			arr=new int[0];
			size=0;
		}
		DynamicArray(int n){
			arr=new int [n];
			for(int i=0;i<n;i++){
				arr[i]=0;
			}
		}
		DynamicArray(const DynamicArray&d){
			size=d.size;
			arr = new int[size];
			for(int i=0;i<size;i++){
				arr[i]=d.arr[i];
			}
		}
		DynamicArray&operator(const DynamicArray &d){
			if(this!=&d){
				delete[]arr;
				size=d.size;
				arr=new int[size];
			    for(int i=0;i<size;i++){
			    	arr[i]=d.arr[i];
				}
			}
			return *this
		}
		DynamicArray&operator(Dynamic&&d){
			p.arr=nullptr;
			p.size=0;
		}
		~DynamicArray(){
			delete[] arr;
		}
};
int main() {
    DynamicArray d(5);
    DynamicArray d1(move(d));
    d1.resize(10);
    d1.display();
    return 0;
}