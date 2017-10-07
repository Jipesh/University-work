#ifndef STACK_H
#define STACK_H

#include <sstream>
#include <string>

#include "vector.h"

using std::string;
using std::stod;
using pep::vector;

class Stack {

	private :
		vector<double> _stack;

	public :
		
		Stack();
		
		~Stack();

		const bool empty() const;

		const double pop();

		void push(const double & value);

};

Stack::Stack(){}

Stack::~Stack(){
	_stack.clear();
}

const bool Stack::empty() const{
	return _stack.size() == 0 ? true : false;
}

void Stack::push(const double & value){
	_stack.push_back(value);
}

const double Stack::pop(){
	if(!empty()){
		double value = _stack[ _stack.size() - 1];
		_stack.pop_back();
		return value;
	}
	return 0;
}

const double evaluate(string s){

	string filtered (s);
	vector<string> output;
	Stack stack;
	std::stringstream i_stream (filtered);

	for(;i_stream >> filtered;){
		
		output.push_back(filtered);
	} 

	double prevResult = 0;

	for(int i = 0 ; i < output.size() ; ++i){
		
		if( output[i] == "+" || output[i] == "-" || output[i] == "*" || output[i] == "/" ){

			const string operation = output[i];
			
			const int firstoperation = i == 2 ? 1 : 0;

			double left, right;

			if(firstoperation == 1){
				left =  stod( output[ i - 2 ] );
			}

			right = stod( output[ i - 1 ] );

			if(operation == "+"){
				
				if( firstoperation == 1){
					stack.push( left + right );
				}else{
					stack.push ( stack.pop() + right );
				}
			}else if(operation == "-"){
				if( firstoperation == 1 ){
					stack.push(  left - right );
				}else{
					stack.push ( stack.pop()  - right );
				}
			}else if(operation == "*"){
				if( firstoperation == 1){
					stack.push( left * right );
				}else{
					stack.push ( stack.pop()  * right );
				}
			}else{
				if( firstoperation == 1){
					stack.push( left / right );
				}else{
					stack.push ( stack.pop()  / right );
				}
			}

		}
	}

	return stack.pop();

}


// Do not write anything below this line

#endif
