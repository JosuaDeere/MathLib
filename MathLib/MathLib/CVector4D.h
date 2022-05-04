#ifndef _CVECTOR4D_H_
#define _CVECTOR4D_H_
#include <math.h>
#include <iostream>
class CVector4D
{
public:
	/*Default constructors*/
	CVector4D() = default;
	~CVector4D() = default;
	/*Constructor with params*/
	CVector4D(float in_fXValue, float in_fYValue, float in_fZValue, float in_fWValue)
	{
		X = in_fXValue;
		Y = in_fYValue;
		Z = in_fZValue;
		W = in_fWValue;
	}


	/*Member values*/
	/*X,Y,Z components, in an union so all share the same memory and if we change the X value automatically  the B, m_fX value changes with the same value as well as the arrays*/
	union
	{
		struct
		{
			float X, Y, Z, W;
		};
		struct
		{
			float B, G, R, A;
		};
		struct
		{
			float m_fX, m_fY, m_fZ, m_fW;
		};
		float f_Values[4];
	};


	/*Operators & similar functions*/

	/*Operator for access []*/
	float& operator[](int i)
	{
		return (f_Values[i]);
	}
	const float& operator[](int i) const
	{
		return(f_Values[i]);
	}
	
	/*Multiplication by scalar*/

	CVector4D operator*(float s)
	{
		return(CVector4D(X * s, Y * s, Z * s, W * s));
	}
	CVector4D& operator*=(float s)
	{
		X *= s;
		Y *= s;
		Z *= s;
		W *= s;
		return (*this);
	}
	friend inline CVector4D operator *(const CVector4D& v, const float s)
	{
		return(CVector4D(v.X * s, v.Y * s, v.Z * s, v.W * s));
	}
	inline void MulS(float in_fScalar)
	{
		(*this)* in_fScalar;
	}

	/*division by scalar*/
	CVector4D operator /(float s)
	{
		s = 1.0f / s;
		return(CVector4D(X * s, Y * s, Z * s, W * s));
	}
	CVector4D& operator /=(float s)
	{
		s = 1.0f / s;
		X *= s;
		Y *= s;
		Z *= s;
		W *= s;
		return (*this);
	}
	inline void DivS(float in_fScalar)
	{
		(*this) / in_fScalar;
	}

	/*Sum of vectors*/
	CVector4D& operator +(CVector4D& v)
	{
		X = X + v.X;
		Y = Y + v.Y;
		Z = Z + v.Z;
		W = W + v.W;
		return (*this);
	}
	CVector4D& operator +=(CVector4D& v)
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		W += v.W;
		return (*this);
	}
	inline void SumVectors(CVector4D& in_SumVector)
	{
		(*this) + in_SumVector;
	}
	friend inline CVector4D operator +(const CVector4D& a, const CVector4D& b)
	{
		return (CVector4D(a.X + b.X, a.Y + b.Y, a.Z + b.Z, a.W + a.W));
	}

	/*Subtract vectors*/
	CVector4D& operator-(CVector4D& v)
	{
		X = X - v.X;
		Y = Y - v.Y;
		Z = Z - v.Z;
		W = W - v.W;
		return (*this);
	}
	const CVector4D& operator-(const CVector4D& v)
	{
		X = X - v.X;
		Y = Y - v.Y;
		Z = Z - v.Z;
		W = W - v.W;
		return (*this);
	}
	CVector4D& operator-=(CVector4D& v)
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		W -= v.W;
		return (*this);
	}
	inline void SubVectors(CVector4D& in_SubVector)
	{
		(*this) - in_SubVector;
	}
	/*Magnitude*/
	inline float Magnitude(const CVector4D& v)
	{
		//sqrt x^2+y^2+z^2
		return( Magnitude(v.X, v.Y, v.Z, v.W) );
	}
	inline float Magnitude(const float in_fX, const float in_fY, const float in_fZ, const float in_fW)
	{
		return(sqrtf((in_fX * in_fX) + (in_fY * in_fY) + (in_fZ * in_fZ)+ (in_fW * in_fW)));
	}

	/*Normalize vector*/
	inline CVector4D Normalize(CVector4D& v)
	{
		return(v / Magnitude(v));
	}
	inline void Normalize()
	{
		(*this) / Magnitude((*this));
	}

	/*Dot product  A.x * B.x + A.y * B.y +  A.z * B.z + A.w * B.w*/
	friend inline float DotProduct(const CVector4D& in_VectorA, const CVector4D& in_VectorB)
	{
		return((in_VectorA.X * in_VectorB.X) + (in_VectorA.Y * in_VectorB.Y) + (in_VectorA.Z * in_VectorB.Z) + (in_VectorA.W * in_VectorB.W) * 1.0f);
	}

	/*Cross product */
	friend CVector4D& CrossProduct(const CVector4D& in_VectorA, const CVector4D& in_VectorB)
	{
		CVector4D CrossResult
		(					
			(in_VectorA.Y * in_VectorB.Z) - (in_VectorA.Z * in_VectorB.Y),	//X
			(in_VectorA.Z * in_VectorB.X) - (in_VectorA.X * in_VectorB.Z),	//Y
			(in_VectorA.X * in_VectorB.Y) - (in_VectorA.Y * in_VectorB.X),	//Z
			(1.0f)															//W
		);
		return CrossResult;
	}

	/*Projection and perpendicular(rejection), B * A.B/ B^2 */
	friend inline CVector4D Projected(const CVector4D& in_VectorA, const CVector4D& in_VectorB)
	{

		/*make check to see if B is unit lenght, in that case we can omit the dot product B.B*/
		return ( in_VectorB * ( DotProduct(in_VectorA, in_VectorB) / DotProduct(in_VectorB, in_VectorB)) );
	}
	friend inline CVector4D Rejected(const CVector4D& in_VectorA, const CVector4D& in_VectorB)
	{
		CVector4D ProjectedVector = Projected(in_VectorA, in_VectorB);
		CVector4D TempA = in_VectorA;
		return (TempA - ProjectedVector);
	}

	
}; 


#endif // !__CVector4D__