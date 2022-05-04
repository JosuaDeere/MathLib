#ifndef _CMATRIX4D_H_
#define _CMATRIX4D_H_
#include "CVector4D.h"

#define MATRIX_SIZE 4
class CMatrix4D : public CVector4D
{
public:

	/* Default Constructor*/
	CMatrix4D() = default;
	
	/*Constructor with params */
	CMatrix4D(	float in_fM00, float in_fM01, float in_fM02, float in_fM03,
				float in_fM10, float in_fM11, float in_fM12, float in_fM13,
				float in_fM20, float in_fM21, float in_fM22, float in_fM23,
				float in_fM30, float in_fM31, float in_fM32, float in_fM33);

	/*Constructor with vectors for basic 3x3 matrix*/
	CMatrix4D(CVector4D& in_VectorX, CVector4D& in_VectorY, CVector4D& in_VectorZ);

	/*Constructor with vectors for 4x4 matrix*/
	CMatrix4D(CVector4D& in_VectorX, CVector4D& in_VectorY, CVector4D& in_VectorZ, CVector4D& in_VectorW);
	CMatrix4D(	float** m_fppMatrix);

	/*default destructor*/
	~CMatrix4D() = default;
	
	/*Member variables*/
	float m_faMatrixValues[4][4];

	/*OPERATOR FUNCTIONS*/
	
	float& operator()(unsigned short i, unsigned short j)
	{
		return m_faMatrixValues[ j ][ i ];
	}

	const float& operator()(unsigned short i, unsigned short j) const
	{
		return m_faMatrixValues[j][i];
	}

	CVector4D& operator[](unsigned short j)
	{
		return (*reinterpret_cast<CVector4D*>(m_faMatrixValues[j]));
	}

	const CVector4D& operator[](unsigned short j) const
	{
		return (*reinterpret_cast<const CVector4D*>(m_faMatrixValues[j]));
	}

	friend CMatrix4D operator*(const CMatrix4D& A, const CMatrix4D& B) 
	{
		return CMatrix4D
		(
			//First row
			(A(0, 0) * B(0, 0)) + (A(0, 1) * B(1, 0)) + (A(0, 2) * B(2, 0)) + (A(0, 3) * B(3, 0)), //m00
			(A(0, 0) * B(0, 1)) + (A(0, 1) * B(1, 1)) + (A(0, 2) * B(2, 1)) + (A(0, 3) * B(3, 1)), //m01
			(A(0, 0) * B(0, 2)) + (A(0, 1) * B(1, 2)) + (A(0, 2) * B(2, 2)) + (A(0, 3) * B(3, 2)), //m02
			(A(0, 0) * B(0, 3)) + (A(0, 1) * B(1, 3)) + (A(0, 2) * B(2, 3)) + (A(0, 3) * B(3, 3)), //m03

			//Second row
			(A(1, 0) * B(0, 0)) + (A(1, 1) * B(1, 0)) + (A(1, 2) * B(2, 0)) + (A(1, 3) * B(3, 0)), //m10
			(A(1, 0) * B(0, 1)) + (A(1, 1) * B(1, 1)) + (A(1, 2) * B(2, 1)) + (A(1, 3) * B(3, 1)), //m11
			(A(1, 0) * B(0, 2)) + (A(1, 1) * B(1, 2)) + (A(1, 2) * B(2, 2)) + (A(1, 3) * B(3, 2)), //m12
			(A(1, 0) * B(0, 3)) + (A(1, 1) * B(1, 3)) + (A(1, 2) * B(2, 3)) + (A(1, 3) * B(3, 3)), //m13

			//Third row
			(A(2, 0) * B(0, 0)) + (A(2, 1) * B(1, 0)) + (A(2, 2) * B(2, 0)) + (A(2, 3) * B(3, 0)), //m20
			(A(2, 0) * B(0, 1)) + (A(2, 1) * B(1, 1)) + (A(2, 2) * B(2, 1)) + (A(2, 3) * B(3, 1)), //m21
			(A(2, 0) * B(0, 2)) + (A(2, 1) * B(1, 2)) + (A(2, 2) * B(2, 2)) + (A(2, 3) * B(3, 2)), //m22
			(A(2, 0) * B(0, 3)) + (A(2, 1) * B(1, 3)) + (A(2, 2) * B(2, 3)) + (A(2, 3) * B(3, 3)), //m23
			
			//Fourth row
			(A(3, 0) * B(0, 0)) + (A(3, 1) * B(1, 0)) + (A(3, 2) * B(2, 0)) + (A(3, 3) * B(3, 0)), //m30
			(A(3, 0) * B(0, 1)) + (A(3, 1) * B(1, 1)) + (A(3, 2) * B(2, 1)) + (A(3, 3) * B(3, 1)), //m31
			(A(3, 0) * B(0, 2)) + (A(3, 1) * B(1, 2)) + (A(3, 2) * B(2, 2)) + (A(3, 3) * B(3, 2)), //m32
			(A(3, 0) * B(0, 3)) + (A(3, 1) * B(1, 3)) + (A(3, 2) * B(2, 3)) + (A(3, 3) * B(3, 3))  //m33
		
		);
	}
	
	friend CVector4D operator*(const CMatrix4D& M, const CVector4D& V)
	{
		return CVector4D
		{
			/*A vector can be treated as a 1column matrix. */
			(M(0, 0) * V.X) + (M(0, 1) * V.Y) + (M(0, 2) * V.Z) + (M(0, 3) * V.W), //m00
			(M(1, 0) * V.X) + (M(1, 1) * V.Y) + (M(1, 2) * V.Z) + (M(1, 3) * V.W), //m10
			(M(2, 0) * V.X) + (M(2, 1) * V.Y) + (M(2, 2) * V.Z) + (M(2, 3) * V.W), //m20
			(M(3, 0) * V.X) + (M(3, 1) * V.Y) + (M(3, 2) * V.Z) + (M(3, 3) * V.W)  //m30
		};
	}


	
	/*Determinants*/
	friend inline float Determinant3x3(CMatrix4D& M)
	{
		return (M(0, 0) * (M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1))
			+ M(0, 1) * (M(1, 2) * M(2, 0) - M(1, 0) * M(2, 2))
			+ M(0, 2) * (M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0)));
	}

	//*Inverse
	CMatrix4D Inverse(CMatrix4D& M);

	friend inline void PrintMatrix(CMatrix4D& M)
	{
		std::cout << "[";
		for ( unsigned short  i = 0; i < MATRIX_SIZE; i++)
		{
			
			for (unsigned short j = 0; j < MATRIX_SIZE; j++)
			{
				std::cout <<M(j, i) << ", ";
			}
			if( i == MATRIX_SIZE - 1)
				std::cout << "]";
			else
				std::cout << std::endl;
		}
		
	}
};

#endif // !_CMATRIX3d_H_

