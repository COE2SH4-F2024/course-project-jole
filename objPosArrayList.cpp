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

    for(int i = listSize; i > 0; i--)
        aList[i] = aList[i-1]; // move elements toward the tail

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i < listSize -1; i++){
        aList[i] = aList[i +1]; // move elements toward the head
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
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
    // make sure the index provided is not outside of bounds and set it to the closest value if not
    if(index < 0) index = 0;  
    else if(index >= listSize) index = listSize - 1;

    return aList[index];
}