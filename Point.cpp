#include "pch.h"
#include "Point.h"
#include "utils.h"

Point::Point(const Point2f& pos, const float radius):
	m_Pos{pos},
	m_Radius{radius}
{
}

void Point::Draw() const
{
	Ellipsef ellipse{ Ellipsef(m_Pos, m_Radius, m_Radius) };
	utils::FillEllipse(ellipse);
}

Point2f Point::GetPos() const
{
	return m_Pos;
}
