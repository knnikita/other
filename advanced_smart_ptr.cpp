struct Expression;
struct Number;
struct BinaryOperation;

struct SharedPtr
{
    // реализуйте следующие методы
    //
    // explicit SharedPtr(Expression *ptr = 0)
    // ~SharedPtr()
    // SharedPtr(const SharedPtr &)
    // SharedPtr& operator=(const SharedPtr &)
    // Expression* get() const
    // void reset(Expression *ptr = 0)
    // Expression& operator*() const
    // Expression* operator->() const
    
    explicit SharedPtr(Expression *ptr = 0) {
        this->ptr_ = ptr;
        //this->counter = new int(1) ? ptr_ : this->counter = 0;
        if (this->ptr_)
            this->counter = new int(1);
        else
            this->counter = 0;
    }
    
    SharedPtr(const SharedPtr &exp) {
        this->ptr_ = exp.ptr_;
        this->counter = exp.counter;
        if (exp.ptr_)
            ++(*counter);
    }
    
    void dec_counter(){
        if (this->counter && this->ptr_ && !--(*counter)) {
            delete ptr_;
            delete counter;
            counter = 0;
        }
    }
    
    SharedPtr& operator=(const SharedPtr & exp) {
        if(this != &exp) {
            dec_counter();
            ptr_ = exp.ptr_;
            counter = exp.counter;
            if (exp.ptr_) 
                ++(*counter);
        }
    } 
    
    void reset(Expression *ptr = 0){
            dec_counter();
            ptr_ = ptr;
            if (ptr) {
                counter = new int(0);
                if (ptr_)
                    ++(*counter);
            }
        
	}
    
    ~SharedPtr() { dec_counter();	}
    
    Expression& operator*()  const      {  return *ptr_;  }
	Expression* operator->() const      {  return  ptr_;  }
    Expression* get()        const      {  return  ptr_;  }
    
    private:
        Expression *ptr_;
        int *counter;
        
};