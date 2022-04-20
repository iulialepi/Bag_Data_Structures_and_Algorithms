#include <exception>
#include "BagIterator.h"
#include "Bag.h"



using namespace std;
/*
//alle kompl sind theta(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	int index = 0;
	int nrOcc;
	
}

void BagIterator::first() {
	this->index = 0;
}

bool BagIterator::valid() const {

	if (!bag.isEmpty() && index != NULL) {
		return true;
	}
	return false;

}

void BagIterator::next() {

	exception ex;

	//next inkrementiert den Iterator falls die naechte Pos ok ist
	
	if (valid() == true) {    //wir verwenden valid()
		this->index++;
	}
	else
		throw ex;
		//throw exception; geht nicht wir muessen es initialisieren
}
*/

TElem BagIterator::getCurrent() const
{
	if (valid() == true) {
		return bag.vector[this->index];
	}
	else {
		return NULL_TELEM 
	}
}
