/*
 * math_lib.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: clckwrkmnd
 */

#define ALPHA 383
#define BETA 383

#include "math_lib.h"

//INCLUDES //////////////////////////////////////////////////////////////
#ifndef MATH_LIB_CPP_
#define MATH_LIB_CPP_

//EXTERNALS ////////////////////////////////////////////////////////////

//GLOBALS ////////////////////////////////////////////////////////////

//FUNCTIONS //////////////////////////////////////////////////////////
int Float_To_Integer_Type(float f)
{
	int i=(int)f;
	float temp=(float)i;
	if(f-temp<=0.5)
		return(i);
	else
		return(i+1);
}
////////////////////////////////////////////////////////////////////////
MAT22 Matrix_Multiplication_22_22(MAT22_PTR aptr,MAT22_PTR bptr)
{
	//unsigned short row,col,index;
	MAT22 m(0,0,0,0);
	MAT22_PTR mptr=&m;
	mptr->e00=aptr->e00*bptr->e00+aptr->e01*bptr->e10;
	mptr->e01=aptr->e00*bptr->e01+aptr->e01*bptr->e11;
	mptr->e10=aptr->e10*bptr->e00+aptr->e11*bptr->e10;
	mptr->e11=aptr->e10*bptr->e01+aptr->e11*bptr->e11;
    return(m);
}
//////////////////////////////////////////////////////////////////////
MAT33 Matrix_Multiplication_33_33(MAT33_PTR aptr,MAT33_PTR bptr)
{
	unsigned short row,col,index;
	MAT33 m(0,0,0,0,0,0,0,0,0);
	MAT33_PTR mptr=&m;
	for(row=0;row<3;row++)
	{
		for(col=0;col<3;col++)
		{
			for(index=0;index<3;index++)
				mptr->mat[row][col]+=aptr->mat[row][index]*bptr->mat[index][col];
		}
	}
    return(m);
}
/////////////////////////////////////////////////////////////////////////
MAT44 Matrix_Multiplication_44_44(MAT44_PTR aptr,MAT44_PTR bptr)
{
	unsigned short row,col,index;
	MAT44 m(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	MAT44_PTR mptr=&m;
	for(row=0;row<4;row++)
	{
		for(col=0;col<4;col++)
		{
			for(index=0;index<4;index++)
				mptr->mat[row][col]+=aptr->mat[row][index]*bptr->mat[index][col];
		}
	}
    return(m);
}
/////////////////////////////////////////////////////////////////////////
PT4D Matrix_Multiplication_14_44(PT4D_PTR pptr,MAT44_PTR mptr)
{
	unsigned short col,index;
	PT4D n(0,0,0,0);
	PT4D_PTR nptr=&n;
	for(col=0;col<4;col++)
	{
		for(index=0;index<4;index++)
		{
			nptr->pt[col]+=pptr->pt[index]*mptr->mat[index][col];
		}
	}
	return(n);
}
//////////////////////////////////////////////////////////////////////////
float Vector_Dot_Product_4D(PT4D_PTR pptr1,PT4D_PTR pptr2)
{
	float *n;
	*n=pptr1->x*pptr2->x+pptr1->y*pptr2->y+pptr1->z*pptr2->z;
	return(*n);
}
/////////////////////////////////////////////////////////////////////////

#endif
