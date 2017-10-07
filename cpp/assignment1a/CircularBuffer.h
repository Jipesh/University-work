#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "vector.h"
using pep::vector;


/** 
 * CircularBuffer functions:
 * - count() which returns how many things are in the buffer
 * - full() which returns true iff the buffer is full
 * - add() which takes an element and adds it to the buffer (you can assume the buffer is not full)
 * - remove() which removes the next element from the buffer (you can assume the buffer is not empty)
 */
class CircularBuffer {
	
	private : 
		int _size, _last, _current;
		vector<char> _buffer; 
	public :
		CircularBuffer(const int size)
		: _size(0),
                _current(0),
                _buffer(size){};
		~CircularBuffer();
		int count() const;
		void add(const char c);
		bool full() const;
		char remove();
};

CircularBuffer::~CircularBuffer(){
	_buffer.clear();
}

int CircularBuffer::count() const {
	return _size;
}

void CircularBuffer::add(const char c){
	if(_size == 0){
		_last = _current;
		_buffer [_current] = c;
		_current = (_current + 1) % _buffer.size();
		++_size;
	}else if(_size != _buffer.size()){
		_buffer [_current] = c;
		_current = (_current + 1) % _buffer.size();
		++_size;
	}
}

bool CircularBuffer::full() const {
	return _size == _buffer.size(); 
}

char CircularBuffer::remove(){
	char removed = _buffer[_last];
	if(removed != '\0'){
		_buffer[_last] = '\0';
		_size--;
		_last = (_last + 1) % _buffer.size();
		return removed;
	}else{
		return '\0';
	}
}


// don't write any code below this line

#endif