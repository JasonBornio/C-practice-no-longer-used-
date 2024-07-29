#include <stdio.h>
#include <string.h>
#include <cstring>
#include "shape.h"
#include <math.h>


class Variable {
    public:
        Variable();
        Variable(float val);

        //basic ops
        Variable operator=(const Variable& arr2);
        Variable operator^(int rhs);

        //array ops
        Variable operator+(Variable& rhs);
        Variable operator-(Variable& rhs);
        Variable operator*(Variable& rhs);
        Variable operator/(Variable& rhs);

        void print();


    private:
        float val;

    protected:
        float dot = 1.;
};

Variable::Variable(){

}

Variable::Variable(float _val){
    this->val = _val;
}

Variable Variable::operator=(const Variable& var2){

    if (this == &var2)
        return *this;

    this->val = var2.val;
    this->dot = var2.dot;
    
    return *this;
}

Variable Variable::operator+(Variable& rhs){
    Variable var(this->val + rhs.val);
    var.dot = this->dot + rhs.dot;
    return var;
}

Variable Variable::operator-(Variable& rhs){
    Variable var(this->val - rhs.val);
    var.dot = this->dot - rhs.dot;
    return var;
}

Variable Variable::operator/(Variable& rhs){
    Variable var(this->val / rhs.val);
    var.dot = (this->dot * rhs.val - this->val * rhs.dot)/(rhs.val * rhs.val);
    return var;
}

Variable Variable::operator*(Variable& rhs){
    Variable var(this->val * rhs.val);
    var.dot = (this->val * rhs.dot) + (this->dot * rhs.val);
    return var;
}

Variable Variable::operator^(int rhs){
    Variable var(this->val + rhs);
    var.dot = this->dot + rhs;
    return var;
}

void Variable::print(){
    std::cout << "    var: (" << this->val << ", " << this->dot << ")" <<std::endl;
}