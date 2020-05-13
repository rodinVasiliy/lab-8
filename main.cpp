#include<chrono>
#include"AVLTree.h"
#include"OrderedVector.h"
#include"UnorderedSet.h"
using namespace std;
template<class T> using CollectionType = Set<T>;
int main() {
	chrono::steady_clock time1;
    CollectionType <int> collection;
	size_t size = 100;
	//srand(time((time_t)0));
	auto start = time1.now();
	for (size_t i = 0; i < size; ++i) {
        collection.Insert(rand()%150);
	}
	auto end = time1.now();
	chrono::duration<double> diff = end - start;
	cout << "\nTime insert = " << diff.count() << endl;
    collection.Print();
    cout<<"\n";
    system("pause");
	start = time1.now();
	for (size_t i = 0;i < size;++i) {
        cout<<collection.Contains(i)<<endl;
	}
	end = time1.now();
    diff = end - start;
    cout << "\nTime Contains=  " << diff.count() << endl;
    system("pause");
	start = time1.now();
	for (size_t i = 0;i < size;++i) {
        collection.Remove(i);
	}
	end = time1.now();
	diff = end - start;
	cout << "\nTime Remove= " << diff.count() << endl;
    collection.Print();
    cout<<"\n";
	system("pause");
	return 0;
}
