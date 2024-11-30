#include "objPosArrayList.h"
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;

    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity){
        throw std::out_of_range("List is Full.");
        return; 
    }

    for(int i = listSize; i > 0; i--)
        aList[i] = aList[i-1]; // move elements toward the tail

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity){
        throw std::out_of_range("List is Full.");
        return; 
    }
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0){
        throw std::out_of_range("List is Empty");
        return; 
    }

    for(int i = 0; i < listSize -1; i++){
        aList[i] = aList[i +1]; // move elements toward the head
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize == 0){
        throw std::out_of_range("List is Empty");
        return; 
    }

    listSize--; // lazy delete
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize -1];
}

objPos objPosArrayList::getElement(int index) const
{
    // if(index < 0) index = 0;  
    // else if(index >= listSize) index = listSize - 1;

    return aList[index];
}