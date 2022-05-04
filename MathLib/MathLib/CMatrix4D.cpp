#include "CMatrix4D.h"

CMatrix4D::CMatrix4D(float in_fM00, float in_fM01, float in_fM02, float in_fM03,
	float in_fM10, float in_fM11, float in_fM12, float in_fM13,
	float in_fM20, float in_fM21, float in_fM22, float in_fM23,
	float in_fM30, float in_fM31, float in_fM32, float in_fM33)
{
	m_faMatrixValues[0][0] = in_fM00;
	m_faMatrixValues[0][1] = in_fM01;
	m_faMatrixValues[0][2] = in_fM02;
	m_faMatrixValues[0][3] = in_fM03;
	m_faMatrixValues[1][0] = in_fM10;
	m_faMatrixValues[1][1] = in_fM11;
	m_faMatrixValues[1][2] = in_fM12;
	m_faMatrixValues[1][3] = in_fM13;
	m_faMatrixValues[2][0] = in_fM20;
	m_faMatrixValues[2][1] = in_fM21;
	m_faMatrixValues[2][2] = in_fM22;
	m_faMatrixValues[2][3] = in_fM23;
	m_faMatrixValues[3][0] = in_fM30;
	m_faMatrixValues[3][1] = in_fM31;
	m_faMatrixValues[3][2] = in_fM32;
	m_faMatrixValues[3][3] = in_fM33;

}

CMatrix4D::CMatrix4D(CVector4D& in_VectorX, CVector4D& in_VectorY, CVector4D& in_VectorZ)
{
	/*Vector X*/
	m_faMatrixValues[0][0] = in_VectorX.X;
	m_faMatrixValues[0][1] = in_VectorX.Y;
	m_faMatrixValues[0][2] = in_VectorX.Z;
	m_faMatrixValues[0][3] = 1;

	/*Vector Y*/
	m_faMatrixValues[1][0] = in_VectorY.X;
	m_faMatrixValues[1][1] = in_VectorY.Y;
	m_faMatrixValues[1][2] = in_VectorY.Z;
	m_faMatrixValues[1][3] = 1;

	/*Vector Z*/
	m_faMatrixValues[2][0] = in_VectorZ.X;
	m_faMatrixValues[2][1] = in_VectorZ.Y;
	m_faMatrixValues[2][2] = in_VectorZ.Z;
	m_faMatrixValues[2][3] = 1;

	/*Vector W*/
	m_faMatrixValues[3][0] = 1;
	m_faMatrixValues[3][1] = 1;
	m_faMatrixValues[3][2] = 1;
	m_faMatrixValues[3][3] = 1;
}

CMatrix4D::CMatrix4D(CVector4D& in_VectorX, CVector4D& in_VectorY, CVector4D& in_VectorZ, CVector4D& in_VectorW)
{
	/*Vector X*/
	m_faMatrixValues[0][0] = in_VectorX.X;
	m_faMatrixValues[0][1] = in_VectorX.Y;
	m_faMatrixValues[0][2] = in_VectorX.Z;
	m_faMatrixValues[0][3] = in_VectorX.W;

	/*Vector Y*/
	m_faMatrixValues[1][0] = in_VectorY.X;
	m_faMatrixValues[1][1] = in_VectorY.Y;
	m_faMatrixValues[1][2] = in_VectorY.Z;
	m_faMatrixValues[1][3] = in_VectorY.W;

	/*Vector Z*/
	m_faMatrixValues[2][0] = in_VectorZ.X;
	m_faMatrixValues[2][1] = in_VectorZ.Y;
	m_faMatrixValues[2][2] = in_VectorZ.Z;
	m_faMatrixValues[2][3] = in_VectorZ.W;

	/*Vector W*/
	m_faMatrixValues[3][0] = in_VectorW.X;
	m_faMatrixValues[3][1] = in_VectorW.Y;
	m_faMatrixValues[3][2] = in_VectorW.Z;
	m_faMatrixValues[3][3] = in_VectorW.W;
}

CMatrix4D::CMatrix4D(float** m_fppMatrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			m_faMatrixValues[i][j] = m_fppMatrix[i][j];
		}

	}
}



CMatrix4D CMatrix4D::Inverse(CMatrix4D& M)
{																
	//Define vectors a,b,c,d
	const CVector4D& a = reinterpret_cast<const CVector4D&>(M[0]);//first column
	const CVector4D& b = reinterpret_cast<const CVector4D&>(M[1]);//second column
	const CVector4D& c = reinterpret_cast<const CVector4D&>(M[2]);//third column
	const CVector4D& d = reinterpret_cast<const CVector4D&>(M[3]);//fourth

	//assign fourth row entries
	const float& x = M(3, 0);
	const float& y = M(3, 1);
	const float& z = M(3, 2);
	const float& w = M(3, 3);

	//Define vectors s,t,u,v
	CVector4D s = CrossProduct(a, b);
	CVector4D t = CrossProduct(c, d);
	CVector4D u = (a * y) - (b * x);
	CVector4D v = (c * w) - (d * z);

	const float& fInvDet = 1.0f / (DotProduct(s, v) + DotProduct(t, u));
	s *= fInvDet;
	t *= fInvDet;
	u *= fInvDet;
	v *= fInvDet;

	CVector4D Row0 = (CrossProduct(b, v) + (t * y));
	CVector4D Row1 = (CrossProduct(v, a) - (t * x));
	CVector4D Row2 = (CrossProduct(d, u) + (s * w));
	CVector4D Row3 = (CrossProduct(u, c) - (s * z));

	return (CMatrix4D(
						Row0.X, Row0.Y, Row0.Z, -(DotProduct(b, t)),
						Row1.X, Row1.Y, Row1.Z, (DotProduct(a, t)),
						Row2.X, Row2.Y, Row2.Z, -(DotProduct(d, s)),
						Row3.X, Row3.Y, Row3.Z, (DotProduct(b, t))
					  )
			);

}

