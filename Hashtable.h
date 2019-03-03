// Copyright [2018] <Nanu Andrei 313CA>
#ifndef HASHTABLE__H
#define HASHTABLE__H
#include <algorithm>
#include <iterator>
#include <list>
#include <string>

unsigned int hashf(int nr){
    int nrcif = 0, n, S = 0;
    n = nr;
    while (n != 0) {
    	S += n % 10;
    	n = n/10;
    	nrcif++;
    }
    return ( (nr << nrcif) * S) % 8497;
}

unsigned int hashfunction(std::string str) {
    unsigned int a = 0;
    for (unsigned int i = 0; i < str.length(); i++)
	     a += (str[i] - i - 53) << str.length();
	  return a % 8641;
}

template <typename Tkey, typename Tvalue> struct elem_info {
	Tkey key;
	Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
 public:
	std::list<struct elem_info<Tkey, Tvalue> > * H;
	int HMAX;
	unsigned int (*hash)(Tkey);
	unsigned int size;


	Hashtable(int hmax, unsigned int (*h)(Tkey)) {
		HMAX = hmax;
		hash = h;
		H = new std::list<struct elem_info<Tkey, Tvalue> > [HMAX];
		size = 0;
	}

	~Hashtable() {
		int i;
		for (i = 0; i < HMAX; i++)
			while (!H[i].empty()) {
				H[i].pop_front();
			}
		delete[] H;
	}

	void put(Tkey key, Tvalue value) {
		struct elem_info<Tkey, Tvalue> p;
		int hkey = hash(key) % HMAX;
		int q = 0;
		for (typename std::list<struct elem_info<Tkey, Tvalue>> :: iterator
			it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				it->value = value;
				q = 1;
		 	}
		 }
		 if (q == 0){
			p.key = key;
			p.value = value;
			H[hkey].push_back(p);
			size++;
		 }
		if((float)size / (float)HMAX > 0.75)
			resize();
	}

	void remove(Tkey key) {
		int hkey = hash(key) % HMAX;
		int q = 0;
		typename std::list<struct elem_info<Tkey, Tvalue>> :: iterator it;
		for (it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				q = 1;
				break;
			}
		}
		if (it != H[hkey].end()) {
			H[hkey].erase(it);
			size--;
		}
	}

	Tvalue get(Tkey key) {
		int hkey = hash(key) % HMAX;
		for (auto it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				return it->value;
				break;
			}
		}
		return Tvalue();
	}

	bool has_value(Tvalue value) {
		for (int i = 0; i < HMAX; i++) {
			if(!H[i].empty()) {
				for (auto it = H[i].begin(); it != H[i].end(); it++) {
					if (it->value == value) {
						return true;
					}
				}
			}
		}
		return false;
	}

	void resize() {
		std::list<struct elem_info<Tkey, Tvalue> > *newH;
		newH = new std::list<struct elem_info<Tkey, Tvalue> > [2*HMAX];
		typename std::list<struct elem_info<Tkey, Tvalue> >::iterator it;
		for(int i = 0; i < HMAX ; i++){
			for(it = H[i].begin(); it != H[i].end(); ++it) {
				int index1 = hash(it -> key) % (2 * HMAX);
				newH[index1].push_back(*it);
			}
		}
		delete[] H;
		H = newH;
		HMAX = 2 * HMAX;
	}

	int get_size() {
		return size;
	}

	int get_capacity() {
		return HMAX;
	}

	float current_factor(){
		return (float)(size) / (float)(HMAX);
	}
};
#endif  // HASHTABLE__
