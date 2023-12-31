﻿// created by Mark O. Brown
#pragma once

#include "rerngMoveStructures.h"
#include <vector>

/*
 this is more  or less a wrapper for a const 3-Dimensional vector. E.g. I could also implement this as
 std::vector<std::vector<std::array<rearrangementMove>, 4>> where the first two dimensions select move / row, and
 the 4 elements in that select the direction.

 This class is used to hold move info, calibrations, etc. where I need one element for each possible move in the 
 atom grid.

 rerng is short for rearrange
*/


template <class type> 
class rerngContainer
{
	public:
		rerngContainer( unsigned rowsInGrid, unsigned colsInGrid );
		rerngContainer( unsigned rowsInGrid, unsigned colsInGrid, type initValue );
		type operator()( unsigned row, unsigned col, dir direction ) const;
		type & operator()( unsigned row, unsigned col, dir direction );
		bool hasBeenFilled( );
		void setFilledFlag( );
		unsigned getRows( );
		unsigned getCols( );
		// typename tells the compiler that std::vector<type>::iterator will be a type.
		typename std::vector<type>::iterator begin( ) { return obj.begin( ); }
		typename std::vector<type>::iterator end( ) { return obj.end( ); }
	private:
		std::vector<type> obj;
		unsigned rows, cols;
		bool filledFlag=false;
};


// the array gets sized only once in the constructor.
template<class type> 
rerngContainer<type>::rerngContainer( unsigned rowsInGrid, unsigned colsInGrid ) :
	rows( rowsInGrid ),
	cols( colsInGrid ),
	obj( rowsInGrid*colsInGrid * 4 )
{}
template<class type>
rerngContainer<type>::rerngContainer( unsigned rowsInGrid, unsigned colsInGrid, type initValue ) :
	rows( rowsInGrid ),
	cols( colsInGrid ),
	obj( rowsInGrid*colsInGrid * 4, initValue )
{}

template<class type> 
bool rerngContainer<type>::hasBeenFilled( )
{
	return filledFlag;
}


template<class type> 
void rerngContainer<type>::setFilledFlag( )
{
	filledFlag = true;
}

template<class type> 
type rerngContainer<type>::operator()( unsigned row, unsigned col, dir direction ) const
{
	if ( row > rows )
	{
		thrower ( "ERROR: row index out of range during rearrangementMoveContainer access!" );
	}
	if ( col > cols )
	{
		thrower ( "ERROR: col index out of range during rearrangementMoveContainer access!" );
	}
	unsigned rowOffset( row * cols * 4 );
	unsigned colOffset( col * 4 );
	unsigned index = rowOffset + colOffset + direction;
	return obj[index];
}

template<class type> 
type & rerngContainer<type>::operator()( unsigned row, unsigned col, dir direction )
{
	if ( row >= rows )
	{
		thrower ( "ERROR: row index out of range during rearrangementMoveContainer access!" );
	}
	if ( col >= cols )
	{
		thrower ( "ERROR: col index out of range during rearrangementMoveContainer access!" );
	}
	unsigned rowOffset( row * cols * 4 );
	unsigned colOffset( col * 4 );
	unsigned index = rowOffset + colOffset + static_cast<int>(direction);
	return obj[index];
}


template <class type>
unsigned rerngContainer<type>::getCols( )
{
	return cols;
}


template <class type>
unsigned rerngContainer<type>::getRows( )
{
	return rows;
}

