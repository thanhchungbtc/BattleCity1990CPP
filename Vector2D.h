#ifndef GUARD_VECTOR2D_H
#define GUARD_VECTOR2D_H

class Vector2D
{
public:
	Vector2D(float x = 0, float y = 0):m_x(x), m_y(y){}
	const float getX() const {return m_x;}
	const float getY() const {return m_y;}

	void setX(float x) {m_x = x;}
	void setY(float y) {m_y = y;}

	Vector2D operator + (const Vector2D& v2) const {
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}
	Vector2D& operator += (const Vector2D& v2){
		m_x += v2.m_x;
		m_y += v2.m_y;
		return (*this);
	}
	
	Vector2D operator - (const Vector2D& v2) const {
		return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}
	Vector2D& operator -= (const Vector2D& v2){
		m_x -= v2.m_x;
		m_y -= v2.m_y;
		return (*this);
	}

	Vector2D operator * (float scalar) const{
		return Vector2D(m_x*scalar, m_y*scalar);
	}
	Vector2D& operator *= (float scalar){
		m_x *= scalar;
		m_y *= scalar;
		return (*this);
	}

	Vector2D operator / (float scalar) const{
		return Vector2D(m_x/scalar, m_y/scalar);
	}
	Vector2D& operator /= (float scalar){
		m_x /= scalar;
		m_y /= scalar;
		return (*this);
	}


private:
	float m_x, m_y;

};
#endif