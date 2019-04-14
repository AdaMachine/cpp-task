#include <iostream>
#include <sstream>
#include <stdexcept>
#include "PhysicalNumber.h"
#include "Unit.h"
using namespace std;
 namespace ariel{

ariel::Unit u;
double key;


 PhysicalNumber::PhysicalNumber(double value, Unit u){
	this->u=u;
	this->key=value;
 }
 
 PhysicalNumber::PhysicalNumber(const PhysicalNumber &a) {
	this->key=a.key;
	this->u=a.u;
 }

 PhysicalNumber PhysicalNumber::operator+ (const PhysicalNumber &a) const {
	double sum = change(*this, a)+key;
	return PhysicalNumber(sum,u);
 }

 PhysicalNumber PhysicalNumber::operator+= (const PhysicalNumber &a)  {
	this->key = change(*this, a) + key;
	return *this;
 }
 PhysicalNumber PhysicalNumber::operator++ () {//prefix ++
	++key;
	return *this;
 }
 PhysicalNumber PhysicalNumber::operator++(int) {//postfix ++
	PhysicalNumber pN(*this);
        key++;
	return pN;
 }
 PhysicalNumber PhysicalNumber::operator+ () const{
        return *this;
 }
 PhysicalNumber PhysicalNumber::operator- (const PhysicalNumber &a) const{
	double diff = key-change(*this, a);
	return PhysicalNumber(diff,u);
 }
 PhysicalNumber PhysicalNumber::operator-= (const PhysicalNumber &a) {
	this->key = key - change(*this, a);
	return *this;
  }
 PhysicalNumber PhysicalNumber::operator-- () {
       key--;
	return *this;
 }
 PhysicalNumber PhysicalNumber::operator--(int) {
       PhysicalNumber pN(this->key,this->u);
        key--;
	return pN;
 }
 PhysicalNumber PhysicalNumber::operator- (){
        return  PhysicalNumber(key*-1,u);
 }
 bool PhysicalNumber::operator<(const PhysicalNumber &a){
        double num = change(*this, a);
        if (key < num) return true;
        return false;      
 }
 bool PhysicalNumber::operator>(const PhysicalNumber &a){
        double num = change(*this, a);
        if (key > num) return true;
        return false; 
 }
 bool PhysicalNumber::operator<=(const PhysicalNumber &a){
        double num = change(*this, a);
        if (key<= num) return true;
        return false;      
 }
 bool PhysicalNumber::operator>=(const PhysicalNumber &a){
        double num = change(*this, a);
        if (key>= num) return true;
        return false;      
 }
 bool PhysicalNumber::operator!=(const PhysicalNumber &a){
        double num = change(*this, a);
        if (key == num) return false;
        return true;      
 }
 bool PhysicalNumber::operator==(const PhysicalNumber &a){
        double num = change(*this, a);
        if (key== num) return true;
        return false;      
 }

   ostream& operator<<(ostream& os, const PhysicalNumber& p){

	if(p.u == Unit::G) os<<p.key<<"[g]";
	else  if(p.u == Unit::KG) os<<p.key<<"[kg]";
        else  if(p.u == Unit::TON) os<<p.key<<"[ton]";
        else  if(p.u == Unit::CM) os<<p.key<<"[cm]";
        else  if(p.u == Unit::M) os<<p.key<<"[m]";
        else  if(p.u == Unit::KM) os<<p.key<<"[km]";
        else  if(p.u == Unit::SEC) os<<p.key<<"[sec]";
        else  if(p.u == Unit::MIN) os<<p.key<<"[min]";
        else  if(p.u == Unit::HOUR) os<<p.key<<"[hour]";
	return os;
  }

  istream& operator>>(istream& is, PhysicalNumber& p){
    string s;
    is>>s;
    bool error = false;
    int unitStart = s.find("[");
    int unitEnd= s.find("]");
    if(unitStart<0||unitEnd<0||unitEnd!=s.length()-1) error = true;
    if(!error) {
      string newUnit=s.substr(unitStart+1,unitEnd-unitStart-1);	
      if(newUnit.compare("cm")== 0 || newUnit.compare("CM")== 0) p.u = Unit::CM;
      else if (newUnit.compare("m")== 0 || newUnit.compare("M")== 0) p.u = Unit::M;
      else if (newUnit.compare("km")== 0 || newUnit.compare("KM")== 0) p.u = Unit::KM;
      else if (newUnit.compare("sec")== 0 || newUnit.compare("SEC")== 0) p.u = Unit::SEC;
      else if (newUnit.compare("min")== 0 || newUnit.compare("MIN")== 0) p.u = Unit::MIN;
      else if (newUnit.compare("hour")== 0 || newUnit.compare("HOUR")== 0) p.u = Unit::HOUR;
      else if (newUnit.compare("g")== 0 || newUnit.compare("G")== 0) p.u = Unit::G;
      else if (newUnit.compare("kg")== 0 || newUnit.compare("KG")== 0) p.u = Unit::KG;
      else if (newUnit.compare("ton")== 0 || newUnit.compare("TON")== 0) p.u = Unit::TON;
      else  error=true;
    }
    double newKey;
    if (error) auto errorState = is.rdstate();
    else {
          try {
             newKey = stod(s.substr(0,unitStart));
	  }
	  catch (exception &e) { 
		  auto errorState = is.rdstate();
		  return is;
	  }
            p.key=newKey;
    }  
    return is;
  }

double PhysicalNumber::change(const PhysicalNumber &a,const PhysicalNumber &b) const
{
	switch (a.u)
        {	
	  case Unit::CM://first number is CM
	    switch(b.u)
            {
		case Unit::CM:
		 return b.key;
		case Unit::M:
		 return b.key*100;
		case Unit::KM:
		 return b.key*100000;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }
	 case Unit::M://first number is M
	    switch(b.u)
            {
		case Unit::CM:
		 return b.key/100;
		case Unit::M:
		 return b.key;
		case Unit::KM:
		 return b.key*1000;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }
	 case Unit::KM://first number is KM
	    switch(b.u)
            {
		case Unit::CM:
		 return b.key/100000;
		case Unit::M:
		 return b.key/1000;
		case Unit::KM:
		 return b.key;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }

	  case Unit::SEC://first number is SEC
	    switch(b.u)
            {
		case Unit::SEC:
		 return b.key;
		case Unit::MIN:
		 return b.key*60;
		case Unit::HOUR:
		 return b.key*3600;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }
	 case Unit::MIN://first number is MIN
	    switch(b.u)
            {
		case Unit::SEC:
		 return b.key/60;
		case Unit::MIN:
		 return b.key;
		case Unit::HOUR:
		 return b.key*60;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }
	 case Unit::HOUR://first number is HOUR
	    switch(b.u)
            {
		case Unit::SEC:
		 return b.key/3600;
		case Unit::MIN:
		 return b.key/60;
		case Unit::HOUR:
		 return b.key;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }
  	case Unit::G://first number is G
	    switch(b.u)
            {
		case Unit::G:
		 return b.key;
		case Unit::KG:
		 return b.key*1000;
		case Unit::TON:
		 return b.key*1000000;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }
	 case Unit::KG://first number is KG
	    switch(b.u)
            {
		case Unit::G:
		 return b.key/1000;
		case Unit::KG:
		 return b.key;
		case Unit::TON:
		 return b.key*1000;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }
	 case Unit::TON://first number is TON
	    switch(b.u)
            {
		case Unit::G:
		 return b.key/1000000;
		case Unit::KG:
		 return b.key/1000;
		case Unit::TON:
		 return b.key;
		default:
		  throw std::invalid_argument( "Incompatible Dimensions!" );
	    }

	}
}


};
