#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"

#include <cmath>
using std::sqrt;

#define DEBUG 0

#if DEBUG

	template <typename T>
	void logD(T t){ // prints single value
	    std::cout << t;
	}

	template<typename T, typename... Args>
	void logD(T t, Args... args){ // recursive variadic function
	    logD(t);
	    logD(args...) ;
	}

	template<typename T, typename... Args>
	void logDLn(T t, Args... args) // recursive variadic function with new line
	{
	    logD(t,args...);
	    std::cout << std::endl;
	}

#define mLog(format, ...) printf(format, ##__VA_ARGS__);
#define logD(start, ...) logD(start, ##__VA_ARGS__)
#define logDLn(start, ...) logDLn(start, ##__VA_ARGS__)
#else
#define mLog(format, ...)
#define logD(start, ...)
#define logDLn(start, ...)
#endif

class Sudoku : public Searchable{

	public:

		typedef typename std::vector<int> intSet;

	private:

		size_t _size;

		int _hauristic_value;

		vector<intSet> _grid;

		void init();

		bool setContains(const intSet & set, const int & value);

		int findAndRemove(intSet & set, const int & value, const size_t & index);

		void printSet(const intSet & set) const;

		const size_t getIndex(const size_t & x, const size_t & y) const;

		const size_t getBestIndex() const;

		const bool checkRows(const size_t & x, const int & value, const size_t & currentIndex) const;

		const bool checkColumns(const size_t & y, const int & value, const size_t & currentIndex) const;

		const bool checkSquare(const size_t & x, const size_t & y, const int & value) const;

		const bool checkPosible(const size_t & x, const size_t & y, const int & value) const;

		bool updateRows(const size_t & x, const int & value);

		bool updateColumns(const size_t & y, const int & value);

		bool updateSquare(const size_t & x, const size_t & y, const int & value);

		void calculateHeuristic();

	public:

		Sudoku(const int & size);

		~Sudoku(){ logDLn("I was called"); }

		bool setSquare(const size_t & y, const size_t & x, const int & value);

		const int getSquare(const size_t & y, const size_t & x);

		void printGrid() const;

		bool isSolution() const;    
    	
    	vector<unique_ptr<Searchable> > successors() const;
    
 		void write(ostream & o) const;
    
    	int heuristicValue() const{ return _hauristic_value; }
};

//  ##  functions for Sudoku defined below  ##  //

	//  --  public functions --  //

	Sudoku::Sudoku(const int & size) :
	_size(size),
	_hauristic_value(_size*_size){
		
		logDLn("made a Sudoku class with size of ",_size," x ",_size);
		init();
	}

	bool Sudoku::setSquare(const size_t & y, const size_t & x, const int & value){

		logDLn("setSquare called :",value);

		const size_t index = getIndex(x,y);

		if( getSquare(y,x) == value){ return true; }

		#if DEBUG 
		mLog("\n");
		printGrid();
		mLog("\n");
		#endif

		if( !checkPosible(x,y,value) ) { logDLn("setSquare ended false :",value);return false; }

		_grid[index].clear();
		_grid[index].push_back(value);

		if ( !updateSquare(x,y,value) ) return false;
		if ( !updateRows(x,value) ) return false;
		if ( !updateColumns(y,value) ) return false;

		#if DEBUG 
		mLog("\n");
		printGrid();
		mLog("\n");
		#endif

		logDLn("setSquare enedd true :",value);
		--_hauristic_value;

		return true;

	}

	const int Sudoku::getSquare(const size_t & y, const size_t & x){

		const size_t index = getIndex(x,y);

		if(_grid[index].size() == 1) return _grid[index][0];

		else return -1;
	}

	void Sudoku::printGrid() const{

		for(size_t i = 0 ; i < (_size * _size) ; ++i){

			std::cout << " \t" << _grid[i].size() << ":";
			printSet(_grid[i]);
			if(i%_size == (_size - 1)) std::cout << std::endl;
		}
	}

	bool Sudoku::isSolution() const{
		
		return _hauristic_value == 0 ? true : false;
	}

	vector<unique_ptr<Searchable> > Sudoku::successors() const{

		logDLn("called successors hauristic_value : ",_hauristic_value);

		vector<unique_ptr<Searchable> > vec (0);

		size_t index = getBestIndex();

		const int size = _grid[index].size();

		for(int i = 0 ; i < size ; ++i){

			Sudoku* s = new Sudoku(0);

			s->_grid = _grid;
			s->_size = _size;

			logDLn("size inside loop : ",s->_size);

			const size_t x = index % _size;

			const size_t y = index / _size;

			const int value = _grid[index][i];

			if(checkPosible(x,y,value)){

				if( s->setSquare(y,x,value) ){

					s->calculateHeuristic();
					logDLn("heuristicValue : ",s->heuristicValue());

					vec.push_back( unique_ptr<Searchable>(s) );
				}else{
					delete s;
				}

				
			}else{

				delete s;

			}

			logDLn("x : ", x, " y : ", y, " value", value);
		}

		return vec;
	}

	void Sudoku::write(ostream & o) const{
		for(size_t i = 0 ; i < (_size*_size) ; ++i){

			o << " \t" << _grid[i].size() << ":";
			
			if(_grid[i].size() == 1){

				o << "{" << _grid[i][0] << "}";
			
			}else{

				o << "{-1}";
			}
			
			if(i%_size == (_size - 1)) o << "\n" << std::endl;
		}
	}

	//  --  private functions --  //

	void Sudoku::init(){

		if(_size == 0) return;

		vector<int> set;

		for(size_t i = 1 ; i <= _size ; ++i){
			
			set.push_back(i);
		}

		logDLn("size : ",set.size());

		for(size_t i = 0 ; i < (_size*_size) ; ++i){

			_grid.push_back(set);
		}
	}

	bool Sudoku::setContains(const intSet & set, const int & value){

		for(auto & n : set){

			if (n == value) return true;
		}

		return false;
	}

	int Sudoku::findAndRemove(intSet & set, const int & value, const size_t & index){

		logDLn("finding and removing : ",value, " at index : ",index);

		for(size_t i = 0 ; i < set.size() ; ++i){

			if (set[i] == value){

				if(set.size() == 2){

					int nexVal;

					for(auto & n : set){

						if(n != value){

							nexVal = n;

							const size_t x = index % _size;

							const size_t y = index / _size;

							logDLn("next value : ",nexVal, " index : ",index, " x : ",x, " y : ",y);

							if( !checkPosible(x,y,nexVal) ){
								logDLn("not posible");
								return -1;
							}

						}
					}
				}

				set.erase(set.begin() + i);

				if(set.size() == 1) --_hauristic_value;

				return i;

			}
		}

		return 0;
	}

	void Sudoku::printSet(const intSet & set) const{

		std::cout << "{";
		
		for(auto & n : set){

			std::cout << n;
		}

		std::cout << "}";
	}

	const size_t Sudoku::getIndex(const size_t & x, const size_t & y) const{

		return ((y * _size) + x);
	}

	const size_t Sudoku::getBestIndex() const{

		logDLn("finding best index size : ",_size);
		size_t lowest_size = _size;
		size_t best_index = 0;

		for(size_t i = 0 ; i < (_size*_size) ; ++i){

			const size_t size = _grid[i].size();

			if(size == 2){

				best_index = i;
				break;

			}else if(size < lowest_size && size > 1 ){

				best_index = i;

			}
		}
		logDLn("getBestIndex :",best_index, " size : ",lowest_size);

		logDLn("inside set :");
		
		#if DEBUG

			for(auto & n : _grid[best_index]){
				logDLn(n);
			}

		#endif

		return best_index;
	}

	const bool Sudoku::checkRows(const size_t & x, const int & value, const size_t & currentIndex) const{

		size_t index = getIndex(x,0);

		for(size_t i = 0 ; i < _size ; ++i){

			if( (_grid[index]).size() == 1){

				if( _grid[index][0] == value && index != currentIndex ) {

					return false;

				}
			} 

			index += _size;
		}

		return true;
	}

	const bool Sudoku::checkColumns(const size_t & y, const int & value, const size_t & currentIndex) const{

		size_t index = getIndex(0,y);

		for(size_t i = 0 ; i < _size ; ++i){

			if( (_grid[index]).size() == 1){

				if( _grid[index][0] == value && index != currentIndex ){ return false; }
			}

			index += 1;
		}

		return true;
	}

	const bool Sudoku::checkSquare(const size_t & x, const size_t & y, const int & value) const{

		size_t sec = std::sqrt(_size);
		size_t xPos = x/sec;
		size_t yPos = y/sec;
		size_t index = getIndex((xPos*sec),(yPos*sec));
		const size_t currentIndex = getIndex(x,y);

		for(size_t i = 0 ; i < _size ; ++i){

			if( (_grid[index]).size() == 1){

				if( _grid[index][0] == value && index != currentIndex ) return false;
			} 

			if(i % sec == sec-1){

				index -= sec-1;
				index += _size;
			
			}else{

				++index;
			}
		}

		return true;
	}

	const bool Sudoku::checkPosible(const size_t & x, const size_t & y, const int & value) const{

		const size_t index = getIndex(x,y);

		if(!checkSquare(x,y,value)){ 

			logDLn("returned false on checkPosible square x : ",x, " y : ", y, " value : ",value);
			return false; 
		}

		if(!checkColumns(y,value,index)){ 

			logDLn("returned false on checkPosible column x : ",x, " y : ", y, " value : ",value);
			return false; 
		}

		if(!checkRows(x,value,index)){ 

			logDLn("returned false on checkPosible row x : ",x, " y : ", y, " value : ",value);
			return false; 
		}

		return true;
	}

	bool Sudoku::updateRows(const size_t & x, const int & value){

		size_t index = getIndex(x,0);

		for(size_t y = 0 ; y < _size ; ++y){

			if( (_grid[index]).size() > 1){

				int toRemove = findAndRemove(_grid[index],value,index);

				const size_t set_x = (index - (_size*y));

				if( toRemove != -1){

					intSet & set = _grid[index];

					if(set.size() == 1){

						logDLn("index : ",index," value : ",set[0]);

						if(checkPosible(set_x,y,set[0])){
						
							updateSquare(set_x,y,set[0]);
					
							updateRows(set_x,set[0]);
					
							updateColumns(y,set[0]);
						}
						
						logDLn("finished re-updating others");
					}
				
				}else{

					logDLn("returned false on row toRemove : ",toRemove);
					return false;
				}
			}
			index += _size;
		}

		logDLn("finished updating row for :",value);
		
		#if DEBUG 
		mLog("\n");
		printGrid();
		mLog("\n");
		#endif

		return true;
	}

	bool Sudoku::updateColumns(const size_t & y, const int & value){

		size_t index = getIndex(0,y);
		logDLn("updating column for value : ",value);

		for(size_t x = 0 ; x < _size ; ++x){

			if( (_grid[index]).size() > 1){

				int toRemove = findAndRemove(_grid[index],value,index);

				if( toRemove != -1){

					intSet & set = _grid[index];

					if(set.size() == 1){

						const size_t set_y = (index - x)/_size;

						if(checkPosible(x,set_y,set[0])){
						
							updateSquare(x,set_y,set[0]);
					
							updateRows(x,set[0]);
					
							updateColumns(set_y,set[0]);
						}
						logDLn("finished re-updating others");
					
					}
				
				}else{
					logDLn("returned false on col");
					return false;
				}
			}

			index += 1;
		}
		#if DEBUG 
		mLog("\n");
		printGrid();
		mLog("\n");
		#endif

		return true;
	}

	bool Sudoku::updateSquare(const size_t & x, const size_t & y, const int & value){

		size_t sec = sqrt(_size);
		size_t xPos = x/sec;
		size_t yPos = y/sec;
		size_t index = getIndex( (xPos*sec), (yPos*sec) );
		logDLn("updating square for value : ", value, "starting pos : ", xPos, " , ", yPos);

		for(size_t j = (yPos*sec) ; j < ((yPos*sec)+sec) ; ++j){

			for(size_t i = (xPos*sec) ; i < ((xPos*sec)+sec) ; ++i){

				logDLn("i : ", i, " j : ", j);

				if( (_grid[index]).size() > 1){

					int toRemove = findAndRemove(_grid[index],value,index);

					if( toRemove != -1){

						logDLn("found at index : ",toRemove," in index[",index,"]", " value : ",value);
						intSet & set = _grid[index];

						if(set.size() == 1){

							logDLn("\n j : ",j," i : ",i);

							if(checkPosible(i,j,set[0])){
							
								updateSquare(i,j,set[0]);
								updateRows(i,set[0]);
								updateColumns(j,set[0]);
							}
							
							logDLn("finished re-updating others");
						}
					}else {
						logDLn("returned false on row");
						return false;
					}
				} 

				if(i % sec == sec-1){

					index -= sec-1;
					index += _size;
				
				}else{

					++index;
				}
			}
		}

		logDLn("finished updating square for value : ", value);
		#if DEBUG 
		mLog("\n");
		printGrid();
		mLog("\n");
		#endif

		return true;
	}

	void Sudoku::calculateHeuristic(){

		size_t val = 0;

		for(auto & s : _grid){

			if(s.size() != 1) ++val;
		}

		_hauristic_value = val;
	}

//################################################//

#endif
