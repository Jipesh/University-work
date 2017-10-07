#ifndef HOW_MANY_WAYS_TO_MAKE_H
#define HOW_MANY_WAYS_TO_MAKE_H

#include <vector>
#include <algorithm>

using std::vector;


class Matrix {

	private :

		int _maxX, _maxY;

		vector<int> _matrix;

		void init(const vector<int> coins);

		const int getIndex(const int & x, const int & y) const;


	public :

		Matrix(const vector<int> coins, const int sum);

		~Matrix();

		const int getTotalCombinations(const int & sum) const;

};

Matrix::Matrix(const vector<int> coins, const int sum) :
_maxY(coins.size()),
_maxX(sum)
{
	int area = ( (_maxX + 1) * _maxY);
	_matrix.resize(area);
	init(coins);
}

Matrix::~Matrix(){
	_matrix.clear();
}

void Matrix::init(const vector<int> coins){

	vector<int> coins_sorted = coins;

	std::reverse(coins_sorted.begin(), coins_sorted.end());

	for(int j = 0 ; j < _maxY ; ++j){
		
		for(int i = 0 ; i <= _maxX ; ++i){
			
			int coin = coins_sorted[j];

			int value, index, index_top, index_left;

			if( i == 0){

				value = 1;
			
			}else if(j == 0){
				
				if(coin == 1){
					
					value = 1;
				
				}else{

					if(i < coin){
						
						value = 0;
					
					}else if(i == coin || (i % coin == 0) ){
						
						value = 1;
					
					}else{
						
						value = 0;
					
					}
				}
			
			}else if(i < coin){
				
				if(i == 0){
					
					value = 1;
				
				}else{

					index_top = getIndex(i, j - 1 );

					value = _matrix[index_top];

				}
			}else{
				
				index_top = getIndex(i, j - 1 );
				
				index_left = getIndex( (i - coin) , j );

				value = _matrix[index_top] + _matrix[index_left];
			}

			index = getIndex(i, j);

			_matrix[index] = value;
		}
	}

}

const int Matrix::getIndex(const int & x, const int & y) const{
	return (y * (_maxX+1)) + x;
}

const int Matrix::getTotalCombinations(const int & sum) const{
	if(sum > _maxX || sum < 0 ){
		
		return 0;
	
	}else if( sum == 0){
		
		return 1;
	
	}else{
		
		return _matrix[getIndex(sum, _maxY - 1 )];
	
	}
}

const int howManyWaysToMake(const int & sum, const vector<int> & coins){
	
	if( coins.size() >= 1 ){

		Matrix m (coins, sum);

		return m.getTotalCombinations(sum);
		
	}else{
		
		return 0;
	
	}
}

// Do not write any code below this line

#endif
