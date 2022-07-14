#ifndef UNIQUESET_H_INCLUDED
#define UNIQUESET_H_INCLUDED


//A set of elements that are unique i.e. a set with no duplicates.
//e.g [1,1,2] is not a unique set since element 1 is duplicated

template<class T>
class UniqueSet{
    private:
        vector<T> vec;
    public:
        UniqueSet(){};
        UniqueSet(const vector<T> &vec){
            for (unsigned int i = 0 ; i < vec.size() ; i++){
                if (searchInVector(this->vec,vec[i]) == false){
                    this->vec.push_back(vec[i]);
                }
            }
        };
        ~UniqueSet(){};
    public:
        bool push_back(const T &elem){
            if (searchInVector(this->vec,elem) == false){
                this->vec.push_back(elem);
                return true;
            }
            return false;
        };

        const vector<T>& getInternalVector(){return vec;};

    public:
        T operator[](unsigned int i) const{
            return this->vec[i];
        };
        T& operator[](unsigned int i){
            return this->vec[i];
        };
    public:
        void print(){
            cout << "[";
            for (unsigned int i = 0 ; i < vec.size() ; i++){
                cout << vec[i] << ((i == vec.size()-1) ? "" : ",");
            }
            cout << "]";
        };
    private:
        static bool searchInVector(const vector<T> &vec,const T &elem){
            for (unsigned int i = 0 ; i < vec.size() ; i++){
                if (vec[i] == elem)    return true;
            }
            return false;
        };

};

#endif // UNIQUESET_H_INCLUDED
