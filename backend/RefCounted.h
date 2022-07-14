#ifndef REFCOUNTED_H_INCLUDED
#define REFCOUNTED_H_INCLUDED

class RefCounted{
    private:
        long long int ref_count;

    public:
        RefCounted(){
            ref_count = 1;
        };

    public:
        RefCounted* ref(){
            ++ref_count;
            return this;
        };

        void unref(){
            --ref_count;
            if (ref_count <= 0){
                delete this;
            }
        };

        void unsafe_setRefCount(long long val){
            this->ref_count = val;
        };

        void unsafe_addRefCount(long long val){
            this->ref_count += val;
        };

        void unsafe_substractRefCount(long long val){
            this->ref_count -= val;
        };
};

#endif // REFCOUNTED_H_INCLUDED
