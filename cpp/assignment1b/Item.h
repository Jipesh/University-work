#ifndef ITEM_H
#define ITEM_H

#include <ostream>
#include <cmath>
#include <vector>

#define R 6373000
#define getRad(degree) (degree * M_PI)/180 

using std::string;
using std::ostream;
using std::cos;
using std::sin;
using std::tan;
using std::pow;
using std::atan2;
using std::sqrt;
using std::vector;

class Item {

	private:
		double _latitude, _longitude;
		string _id;
		int _time;
	
	public:
		Item(const double & latitude, const double & longitude,
			const string & id, const int & time);
		
		const double distanceTo(const Item & itm) const;
		
		const double getLatitude() const{ return _latitude; } 

		const double getLongitude() const{ return _longitude; }

		const string getID() const{ return _id; }

		const int getTime() const{ return _time; }
};

class MapOfItems {

	private:
		const int MAX_ITEM_TIME = (15 * 60);
		const int MAX_TOUR_TIME = 3600;
		vector<Item> _items;
		
		const double getTime(const Item & itm1, const Item & itm2, const float & walkingSpeed) const;
		
		const int visitClosestItem(const Item & current, const int & currentTime, float & timePassed,
				const vector<Item> & items, const float & walkingSpeed);
	
	public:
		void addItem(const Item & item);
		
		const vector<Item> getTour(const float & walkingSpeed);
		
		const int size() const{ return _items.size(); }
};

Item::Item(const double & latitude, const double & longitude,
                        const string & id, const int & time) :
	_latitude(latitude),
	_longitude(longitude),
	_id(id),
	_time(time){}

const double Item::distanceTo(const Item & itm) const{
	
	const double lat1 = getRad(_latitude);
	const double long1 = getRad(_longitude);
	const double lat2 = getRad(itm.getLatitude());
	const double long2 = getRad(itm.getLongitude());
	
	const double dlon = long2 - long1;
	const double dlat = lat2 - lat1;
	const double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);
	const double c = 2 * atan2( sqrt(a), sqrt(1-a) );
	const double distance = (R * c);

	return distance;
}

ostream & operator<<(ostream & o, const Item & itm){
	
	o << "{"<< itm.getLatitude() << ", "
	  	<< itm.getLongitude() << ", \""
	  	<< itm.getID() << "\", "
	  	<< itm.getTime() << "}";
	
	return o;
}

void MapOfItems::addItem(const Item & item) { _items.push_back(item); }

const vector<Item> MapOfItems::getTour(const float & walkingSpeed){
	
	vector<Item> visited;
	if(_items.size() >= 1){
		
		vector<Item> unvisited = _items;
		const int currentTime = unvisited[0].getTime();
		float timePassed = 0;
		Item current = unvisited[0];
		
		visited.push_back(current);
		unvisited.erase(unvisited.begin());

		while(timePassed <= MAX_TOUR_TIME){
			
			const int index =	visitClosestItem(current, currentTime, timePassed, unvisited, walkingSpeed);
			
			if(index == -1) break;

			Item island = unvisited[index];
			current = island;

			visited.push_back(island);
			unvisited.erase(unvisited.begin() + index);
		}
	}

	return visited;
}

const int MapOfItems::visitClosestItem(const Item & current, const int & currentTime, float & timePassed,
		const vector<Item> & items, const float & walkingSpeed){
			
			const int timeNow = (currentTime + ((int)timePassed)) % 3600;
			float bestTime = MAX_TOUR_TIME + 1;
			int itemIndex = -1;

			for(int i = 0 ; i < items.size() ; ++i){
				
				const Item itm = items[i];
				float time = getTime(current,itm,walkingSpeed);
				float itemTime = items[i].getTime();
				const int timeAfter = (timeNow + ((int)time)) % 3600;

				if( timeAfter < itemTime ){
					
					time = itemTime - timePassed;
				
				}else if( timeAfter >= itemTime + MAX_ITEM_TIME ) {
					
					time = -1;
				
				}
				
				if( time != -1 && time < bestTime ){
						
					itemIndex = i;
					bestTime = time;
			
				}
			}
			
			if( itemIndex != -1 && timePassed + bestTime <= MAX_TOUR_TIME ){
				
				timePassed += bestTime;
				return itemIndex;
			
			}else{
				
				return -1;
			
			}
}

const double MapOfItems::getTime(const Item & itm1, const Item & itm2, const float & walkingSpeed) const{
	
	const double distance = itm2.distanceTo(itm1);
	
	return (distance/walkingSpeed);

}
	
// don't write any code below this line

#endif

