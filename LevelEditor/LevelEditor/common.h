#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <map>
#include <string>
#include <sstream>

#define SafePtrRelease(ptr) if(ptr){ \
							delete ptr; \
							ptr = NULL;}

inline int ContainsFlags(const int thing,int flags){
		return (thing & flags);
}
inline void RemoveFlag(unsigned int* thing,int flag){
	if(thing)
		if(ContainsFlags(*thing,flag)){
			(*thing) ^= flag;
		}
}
inline void RemoveFlags(unsigned int* thing,int flags[],int flagCount){
	if(thing){
		for(int i = 0;i < flagCount;i++){
			if(ContainsFlags(*thing,flags[i])){
				(*thing) ^= flags[i];
			}
		}
	}
}

inline std::string intToString(int i){
	std::stringstream st;
	st << i;
	return st.str();
}

template <typename T>
void SafeVectorDelete
	(std::vector<T*> vector){
	if(&vector != NULL){
		for(int i = 0;i < vector.size();i++){
			SafePtrRelease(vector[i]);
		}
		vector.clear();
	}
}
//map
template <typename T,typename V>
void SafeMapDelete
	(std::map<T,V*> map){
	if(&map != NULL){
		std::map<T,V*>::iterator iterator;
		for(iterator = map.begin();
			iterator != map.end();iterator++){
			SafePtrRelease(iterator->second);
		}
		map.clear();
	}
}
//multimap
template <typename T,typename V>
void SafeMapDelete
	(std::multimap<T,V*> map){
	if(&map != NULL){
		std::multimap<T,V*>::iterator iterator;
		for(iterator = map.begin();
			iterator != map.end();iterator++){
			SafePtrRelease(iterator->second);
		}
		map.clear();
	}
}

#endif