/*
 * math_lib.h
 *
 *  Created on: Nov 2, 2013
 *      Author: clckwrkmnd
 */

#ifndef MATH_LIB_H_
#define MATH_LIB_H_
#include <iostream>
#include "exprtk/exprtk.hpp"

using namespace std;

typedef struct MATRIX_22
{
	union
	{
		float mat[2][2];
		struct
		{
			float e00,e01;
			float e10,e11;
		};
	};
	MATRIX_22(float e00, float e01,
				   float e10, float e11)
		{
			this->e00 = e00;
			this->e01 = e01;
			this->e10 = e10;
			this->e11 = e11;
		}
}MAT22,*MAT22_PTR;

typedef struct MATRIX_33
{
	union
	{
		float mat[3][3];
		struct
		{
			float e00,e01,e02;
            float e10,e11,e12;
            float e20,e21,e22;
		};
	};
	MATRIX_33(float e00, float e01, float e02,
				   float e10, float e11, float e12,
				   float e20, float e21, float e22)
		{
			this->e00 = e00;
			this->e01 = e01;
			this->e02 = e02;
			this->e10 = e10;
			this->e11 = e11;
			this->e12 = e12;
			this->e20 = e20;
			this->e21 = e21;
			this->e22 = e22;
		}
}MAT33,*MAT33_PTR;

typedef struct MATRIX_44
{
	union
	{
		float mat[4][4];
		struct
		{
			float e00,e01,e02,e03;
            float e10,e11,e12,e13;
            float e20,e21,e22,e23;
			float e30,e31,e32,e33;
		};
	};
	MATRIX_44(void)
	{
		;
	}
	MATRIX_44(float e00, float e01, float e02, float e03,
			   float e10, float e11, float e12, float e13,
			   float e20, float e21, float e22, float e23,
			   float e30, float e31, float e32, float e33)
	{
		this->e00 = e00;
		this->e01 = e01;
		this->e02 = e02;
		this->e03 = e03;
		this->e10 = e10;
		this->e11 = e11;
		this->e12 = e12;
		this->e13 = e13;
		this->e20 = e20;
		this->e21 = e21;
		this->e22 = e22;
		this->e23 = e23;
		this->e30 = e30;
		this->e31 = e31;
		this->e32 = e32;
		this->e33 = e33;
	}
	
	void setMatrix(float e00, float e01, float e02, float e03,
			   float e10, float e11, float e12, float e13,
			   float e20, float e21, float e22, float e23,
			   float e30, float e31, float e32, float e33)
	{
		this->e00 = e00;
		this->e01 = e01;
		this->e02 = e02;
		this->e03 = e03;
		this->e10 = e10;
		this->e11 = e11;
		this->e12 = e12;
		this->e13 = e13;
		this->e20 = e20;
		this->e21 = e21;
		this->e22 = e22;
		this->e23 = e23;
		this->e30 = e30;
		this->e31 = e31;
		this->e32 = e32;
		this->e33 = e33;
	}

	void setMatrix(MATRIX_44 ref)
	{
		this->e00 = ref.e00;
		this->e01 = ref.e01;
		this->e02 = ref.e02;
		this->e03 = ref.e03;
		this->e10 = ref.e10;
		this->e11 = ref.e11;
		this->e12 = ref.e12;
		this->e13 = ref.e13;
		this->e20 = ref.e20;
		this->e21 = ref.e21;
		this->e22 = ref.e22;
		this->e23 = ref.e23;
		this->e30 = ref.e30;
		this->e31 = ref.e31;
		this->e32 = ref.e32;
		this->e33 = ref.e33;
	}

}MAT44,*MAT44_PTR;

typedef struct MATRIX_12
{
	union
    {
		float mat[2];
		struct
		{
         float e00, e01;
        };

     };
} MAT12, *MAT12_PTR;

typedef struct MATRIX_13
{
	union
    {
		float mat[3];
		struct
		{
         float e00, e01, e02;
        };

     };
} MAT13, *MAT13_PTR;

typedef struct MATRIX_14
{
	union
    {
		float mat[4];
		struct
		{
         float e00, e01, e02, e03;
        };

     };
} MAT14, *MAT14_PTR;

typedef struct MATRIX_43
{
	union
    {
		float mat[4][3];
        struct
		{
         float e00, e01, e02;
         float e10, e11, e12;
         float e20, e21, e22;
         float e30, e31, e32;
         };

    };

} MAT43, *MAT43_PTR;

typedef struct POINT_2D
{
	union
	{
		float pt[2];
		struct
		{
			float x,y;
		};
	};
}PT2D,*PT2D_PTR,VEC2D,*VEC2D_PTR;

typedef struct POINT_3D
{
	union
	{
		float pt[3];
		struct
		{
			float x,y,z;
		};
	};
}PT3D,*PT3D_PTR,VEC3D,*VEC3D_PTR;

typedef struct POINT_4D
{
	union
	{
		float pt[4];
		struct
		{
			float x,y,z,w;
		};
	};
	POINT_4D(void)
	{
		;
	}
	POINT_4D(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
	void setPoint(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
}PT4D,*PT4D_PTR,VEC4D,*VEC4D_PTR;

typedef struct CUBE_TEMPORAL
{
		PT4D vlist[8];
		PT4D dlist[8];
		PT4D loc;
}CUBT,*CUBT_PTR;

typedef struct FUNCTION_IMAGE
{
    PT4D pis[35][35];
    PT4D pid[35][35];
    PT4D ori;
}F3I, *F3I_PTR;

extern PT4D Matrix_Multiplication_14_44(PT4D_PTR pptr,MAT44_PTR mptr);
extern MAT44 Matrix_Multiplication_44_44(MAT44_PTR aptr,MAT44_PTR bptr);

// template<typename T>
// float evaluate_expression(string equation, float x_value, float y_value) {
//   string expression_string = equation;
//    T x = T(x_value);
//    T y = T(y_value);

//    exprtk::symbol_table<T> symbol_table;
//    symbol_table.add_variable("x", x);
//    symbol_table.add_variable("y", y);
//    symbol_table.add_constants();

//    exprtk::expression<T> expression;
//    expression.register_symbol_table(symbol_table);

//    exprtk::parser<T> parser;
//    parser.compile(expression_string, expression);

//    return expression.value();
// 
/*
template<typename T>
float evaluate_expression(string equation, float x_value, float y_value) {
  string expression_string = equation;
   T x = T(x_value);
   T y = T(y_value);

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_variable("x", x);
   symbol_table.add_variable("y", y);
   symbol_table.add_constants();

   exprtk::expression<T> expression;
   expression.register_symbol_table(symbol_table);

   exprtk::parser<T> parser;
   parser.compile(expression_string, expression);

   return expression.value();
}

*/
#endif /* MATH_LIB_H_ */
