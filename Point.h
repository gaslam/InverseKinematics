#pragma once
class Point
{
public:
	Point(const Point2f& pos, const float radius);
	
	void Draw() const;
	Point2f GetPos() const;
private:
	Point2f m_Pos;
	float m_Radius;
};

