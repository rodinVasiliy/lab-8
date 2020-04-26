#include<iostream>
#include<cstdio>
#include "C:\Rodin\lab-3/Vector.h"
template<typename T>
std::size_t binSearch(T* arr,const std::size_t size,const T& key) {
	if (!arr)return 0;
	int l = 0, r = size - 1;
	int mid;
	while (l <= r) {
		mid = (r + l) / 2;
		if (key < arr[mid])r = mid - 1;
		else if (arr[mid] < key)l = mid + 1;
		else return mid;
	}
	return l;
}
template<typename T>
class OrderedVector {
	T* _data;
	size_t _size;
public:
	OrderedVector() :_data(nullptr),_size(0) {}
	OrderedVector(const size_t size) {
		if (size == 0) {
			_size = 0;
			_data = nullptr;
		}
		else {
			_size = size;
			_data = new T[size];
			for(std::size_t i=0;i<size;++i)_data[i]=0;
		}
	}
	~OrderedVector() {
		delete [] _data;
		_data = nullptr;
		_size = 0;
	}

	OrderedVector(const OrderedVector& ) = delete;

	OrderedVector(OrderedVector&& ) = delete;

	OrderedVector& operator=(const OrderedVector& ) = delete;

	OrderedVector& operator=(OrderedVector&& ) = delete;

	void Print()const {
		for (std::size_t i = 0;i < _size;++i) cout << _data[i]<<"  ";
	}
	bool Insert(const T& value){
        if (_size == 0) {
            _data = new T[1];
            _data[0] = value;
            ++_size;
            return true;
        }
        if (_size == 1) {
            auto tmp = _data[0];/// 5
            std::size_t ind = binSearch(_data, _size, value);
            delete [] _data;
            _data = new T[2];
            if (ind == 1) {
                _data[0] = tmp;
                _data[1] = value;
                ++_size;
                return true;
            }
            else {
                _data[0] = value;
                _data[1] = tmp;
                ++_size;
                return true;
            }
        }
        else {
            std::size_t ind = binSearch(_data,_size,value);
            T* newArr = new T[_size + 1];
            for (std::size_t i = 0;i < ind;++i) {
                newArr[i] = _data[i];
            }
            newArr[ind] = value;
            for (std::size_t i = ind + 1;i < _size+1 ;++i) {
                newArr[i] = _data[i - 1];////////// 4 41 44 56 59 66
            }////////////////////////////////////// 4 41 44 50 56 59 66
            delete[] _data;
            _data = newArr;
            ++_size;
            return true;
        }
        return false;
	}
	bool Contains(const T& key){
	    if(_size==0)return false;
	    if(_size==1)return !(_data[1]!=key);
	    auto i=binSearch(_data,_size,key);
	    if(i==_size)return false;
        return !(_data[i] != key);
	}
	bool Remove(const T& key){
	    if(_size==0)return false;
	    if(_size==1){
	        if(_data[0]!=key)return false;
	        else delete [] _data;
	        _data= nullptr;
	        --_size;
	        return true;
	    }
	    else{
	        auto ind=binSearch(_data,_size,key);
	        if(ind==_size)return false;
	        if(_data[ind]!=key)return false;
	        else{
	            auto tmp=new T[_size-1];
	            for(std::size_t i=0;i<ind;++i)tmp[i]=_data[i];
	            for(std::size_t i=ind+1;i<_size;++i)tmp[i-1]=_data[i];
	            delete [] _data;
	            _data=tmp;
	            --_size;
	            return true;
	        }
	    }
	    return false;
	}
};
/*IteratorV<T> begin()const {
    if (_data)
        return IteratorV<T>(_data);
    return end();
}
IteratorV<T> end()const {
    if (_size == 0) {
        return nullptr;
    }
    IteratorV<T> it(_data);
    it += _size;
    return it;
}
IteratorV<T> Insert(const T& value) {
    if (_size == 0) {
        _data = new T[1];
        _data[0] = value;
        IteratorV<T> resIt(_data);
        ++_size;
        return resIt;
    }
    if (_size == 1) {
        auto tmp = _data[0];/// 5
        size_t ind = binSearch(_data, _size, value);
        delete _data;
        _data = new T[2];
        if (ind == 1) {
            _data[0] = tmp;
            _data[1] = value;
            IteratorV<T> resIt(_data);
            ++resIt;
            ++_size;
            return resIt;
        }
        else {
            _data[0] = value;
            _data[1] = tmp;
            IteratorV<T> resIt(_data);
            ++_size;
            return resIt;
        }
    }
    else {
        IteratorV<T> begin=begin();
        IteratorV<T> end=end();
        int ind = binSearch(_data, _size , value);//����� ������� � �������
        auto tmp = _data[ind];//��������� ������� �� ������� �������� ����� �������� �����
        auto newArr = new T[_size + 1];//����� ������
        _data = newArr;
        while (*begin!=tmp) {
            *newArr = *begin;
            ++newArr;
            ++begin;
        }
        *newArr = value;
        IteratorV<T> resIt(_data);
        ++newArr;
        while (begin != end) {
            *newArr = *begin;
            ++newArr;
            ++begin;
            }
        ++_size;
        return resIt;
    }
}
IteratorV<T> Insert(const T& value, int) {
    if (_size == 0) {
        _data = new T[1];
        _data[0] = value;
        IteratorV<T> resIt(_data);
        ++_size;
        return resIt;
    }
    if (_size == 1) {
        auto tmp = _data[0];/// 5
        size_t ind = binSearch(_data, _size , value);//� �������� ����� ���������� ������ �������� �������
        delete _data;///////////////////////////////////�� ���� ������ �������� + 1
        _data = new T[2];
        if (ind == 1) {
            _data[0] = tmp;
            _data[1] = value;
            IteratorV<T> resIt(_data);
            ++resIt;
            ++_size;
            return resIt;
        }
    }
    else {
        int ind = binSearch(_data,_size,value);
        T* newArr = new T[_size + 1];
        for (int i = 0;i < ind;++i) {
            newArr[i] = _data[i];
        }
        newArr[ind] = value;
        for (size_t i = ind + 1;i < _size ;++i) {
            newArr[i] = _data[i - 1];////////// 4 41 44 56 59 66
        }////////////////////////////////////// 4 41 44 50 56 59 66
        _data = newArr;
        IteratorV<T> resIt(begin());
        resIt += ind;
        ++_size;
        return resIt;
    }
}
IteratorV<T> Find(const T value) {
    if (_size == 0) {
        IteratorV<T> resIt(nullptr);
        return resIt;
    }
    else if (_size == 1) {
        if (*_data == value) {
            IteratorV<T> resIt(_data);
            return resIt;
        }
        else {
            IteratorV<T> resIt(nullptr);
            return resIt;
        }
    }
    else {
        int pos = binSearch(_data,_size,value);
        if (_data[pos] == value) {
            IteratorV<T> resIt(begin());
            while (pos!=0) {
                ++resIt;
                --pos;
            }
            return resIt;
        }
        else {
            IteratorV<T> resIt(nullptr);
            return resIt;
        }
    }
}
IteratorV<T> Find(const T& value, int) {
    if (_size == 0) {
        IteratorV<T> resIt(nullptr);
        return resIt;
    }
    else if (_size == 1) {
        if (*_data == value) {
            IteratorV<T> resIt(_data);
            return resIt;
        }
        else {
            IteratorV<T> resIt(nullptr);
            return resIt;
        }
    }
    else {
        int ind = binSearch(_data, _size, value);
        if (_data[ind] != value)return nullptr;
        else {
            IteratorV<T> resIt(begin());
            resIt += ind;
            return resIt;
        }
    }
}
IteratorV<T> Remove(IteratorV<T>& pos) {
    if (_size == 0)return pos;
    else if (_size == 1) {
        delete _data;
        _data = nullptr;
        --_size;
        IteratorV<T> resIt(nullptr);
        return resIt;
    }
    else {
        IteratorV<T> begin(begin());
        IteratorV<T> end(end());
        T* tmp = new T[_size - 1];
        //delete _data;
        _data = tmp;
        --_size;
        while (begin != pos) {
            *tmp = *begin;
            ++tmp;
            ++begin;
        }
        ++begin;
        IteratorV<T> resIt(begin);
        while (begin != end) {
            *tmp = *begin;
            ++tmp;
            ++begin;
        }
        return resIt;
    }
}
IteratorV<T> Remove(const T& value) {
    int ind = binSearch(_data,_size,value);
    if (_data[ind] != value)throw"element not find";//������ ���������� �������
        if (_size == 1) {
            delete _data;
            _data = nullptr;
            --_size;
            return nullptr;
        }
        else {
            IteratorV<T> begin=begin();
            IteratorV<T> end=end();
            IteratorV<T> resIt=find(value);
            auto newArr = new T[_size - 1];
            _data = newArr;
            while (begin != resIt) {
                *newArr = *begin;
                ++newArr;
                ++begin;
            }
            ++begin;
            resIt = begin;
            while (begin != end) {
                *newArr = *begin;
                ++newArr;
                ++begin;
            }
            --_size;
            return resIt;
        }
}
IteratorV<T> Remove(const T& value,int) {
    int ind = binSearch(_data, _size, value);
    if (_data[ind] != value)throw"element not find";//������ ���������� ������� �� ������� ������ ���� ��������� �������
    if (_size == 1) {/////////////////////////////////���� �� ������� �� ������ ����� ������� ��� �������
        delete _data;
        _data = nullptr;
        --_size;
        return nullptr;
    }
    else {
        auto newArr = new T[_size - 1];
        for (int i = 0;i < ind;++i) {
            newArr[i] = _data[i];
        }
        for (size_t i = ind + 1;i < _size;++i) {
            newArr[i-1] = _data[i];//
        }
        --_size;
        delete _data;
        _data = newArr;
        IteratorV<T> resIt(begin());
        resIt += ind;
        return resIt;
    }
}*/
