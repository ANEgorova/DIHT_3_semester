#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>


#define _USE_MATH_DEFINES
#define PI 3.14159
#define INFINITY 1e+10
#define EPS 1e-10


typedef std::pair<double, double> Point;
typedef std::pair<Point, Point> Segment;
typedef std::vector<Point> arr;


double Det(double a, double b, double c, double d){
	return a * d - b * c;
}


class Shape {

public:
	virtual double getSq() = 0; 
	virtual bool Edge(Point) = 0; 
	virtual bool Belong(Point) = 0; 
	virtual arr Cross(Segment) = 0; 
};

class Circle : Shape{

public:
	Circle() {}

	Circle(Point pcenter, double pradius) : center(pcenter), radius(pradius) {}

	virtual double getSq(){
		return PI * std::pow(radius, 2);
	}

	virtual bool Edge(Point p){
		return std::abs(std::pow(p.first - center.first, 2) + std::pow(p.second - center.second, 2) - std::pow(radius, 2)) <= EPS;
	}

	virtual bool Belong(Point p){
		return std::pow(p.first - center.first, 2) + std::pow(p.second - center.second, 2) <= std::pow(radius, 2);
	}

	virtual arr Cross(Segment s){
		
		arr result;
		double x1 = s.first.first;
		double y1 = s.first.second;
		double x2 = s.second.first;
		double y2 = s.second.second;

		
		double x_max = std::max(x1, x2);
		double x_min = std::min(x1, x2);
		double y_max = std::max(y1, y2);
		double y_min = std::min(y1, y2);


		
		double A = y1 - y2;
		double B = x2 - x1;
		double C = x1*y2 - x2*y1 + A*center.first + B*center.second;

		
		double x0 = -A*C / (A*A + B*B);
		double y0 = -B*C / (A*A + B*B);

		if (C*C > radius*radius*(A*A + B*B))
		{
			std::cout << "No points!" << std::endl;
		}

		else 
			if (std::abs(C*C - radius*radius*(A*A + B*B)) < EPS){
				if ((x0 <= x_max) && (x0 >= x_min) && (y0 <= y_max) && y0 >= y_min){
					Point p1(x0, y0);
					result.push_back(p1);
				}
		}
		else {
			double D = radius*radius - C*C / (A*A + B*B);
			double mult = std::sqrt(D / (A*A + B*B));
			double ax, ay, bx, by;
			ax = x0 + B * mult;
			bx = x0 - B * mult;
			ay = y0 - A * mult;
			by = y0 + A * mult;
			
			if ((ax <= x_max) && (ax >= x_min) && (ay <= y_max) && (ay >= y_min)){
				Point p1(ax, ay);
				result.push_back(p1);
			}
			
			if ((bx <= x_max) && (bx >= x_min) && (by <= y_max) && (by >= y_min)){
				Point p1(bx, by);
				result.push_back(p1);
			}
		}
		return result;
	}

private:
	Point center;
	double radius;
};



class Poligon : Shape{

public:
	Poligon() {};

	Poligon(arr& some) : buf(some) {}

	virtual double getSq(){
		double Sq = 0;

		if (size)
			Sq = (buf[0].first - buf[size].first) * (buf[0].second + buf[size].second);

		for (int i = 1; i <= size; i++)
			Sq += (buf[i].first - buf[i - 1].first) * (buf[i].second + buf[i - 1].second);
		return abs(Sq);
	}

	virtual bool Edge(Point p){

		for (int i = 1; i <= size; i++){
			
			
			double x1 = buf[i].first;
			double y1 = buf[i].second;
			double x2 = buf[i - 1].first;
			double y2 = buf[i - 1].second;

			
			double a = y1 - y2;
			double b = x2 - x1;
			double c = -a * x1 - b * y1;

			
			if (a * p.first + b * p.second + c < EPS && p.first >= std::min(x1, x2), p.first <= std::max(x1, x2) && p.second >= std::min(y1, y2) && p.second <= std::max(y1, y2))
				return true;
		}
		return false;
	}

	virtual bool Belong(Point p){
		int size = buf.size();
		double angle = 0;
		for (int i = 1; i <= size; i++){
			double x1 = buf[i % size].first - p.first;
			double y1 = buf[i % size].second - p.second;
			double x2 = buf[i - 1].first - p.first;
			double y2 = buf[i - 1].second - p.second;
			angle += abs(atan2(x1 * y2 - x2 * y1, x1 * y1 + x2 * y2));
		}
		if (abs(angle - 2 * PI) < EPS)
			return true;
		else
			return false;
	}

	virtual arr Cross(Segment S){

		arr result;

		
		for (int i = 1; i <= size; i++){
			
			Point P;
			Point P1(buf[i].first, buf[i].second);
			Point P2(buf[i - 1].first, buf[i - 1].second);
			Segment S2(P1, P2);

			if (crossing(S, S2, P)) result.push_back(P);
		}
		return result;
	}


	bool Poligon::belong(Segment S,Point p){
	
		double x1 = S.first.second;
		double x2 = S.second.first;
		double y1 = S.first.second;
		double y2 = S.second.second;

		double xp = p.first;
		double yp = p.second;

		double xMin = std::min(x1, x2);
		double xMax = std::max(x1, x2);
		double yMin = std::min(y1, y2);
		double yMax = std::max(y1, y2);

		
		if (!((xMin <= xp) && (xp <= xMax) && (yMin <= yp) && (yp <= yMax))) return false;

	
		double itX1 = x1 - xp;
		double itY1 = y1 - yp;
		double itX2 = x2 - xp;
		double itY2 = y2 - yp;

		if (itX1 * itY2 - itX2 * itY1 == 0) return true;
		else return false;
	}

	bool Poligon::crossing(Segment S1, Segment S2, Point& papa){

		double x1 = S1.first.first;
		double y1 = S1.first.second;
		double x2 = S1.second.first;
		double y2 = S1.second.second;


		double a1 = y1 - y2;
		double b1 = x2 - x1;
		double c1 = -a1 * x1 - b1 * y1;


		double sec_x1 = S2.first.first;
		double sec_y1 = S2.first.second;
		double sec_x2 = S2.second.first;
		double sec_y2 = S2.second.second;

		double a2 = sec_y1 - sec_y2;
		double b2 = sec_x2 - sec_x1;
		double c2 = -a2 * sec_x1 - b2 * sec_y1;

		double D = Det(a1, a2, b1, b2);

		double DX = -Det(c1, c2, b1, b2);

		double DY = -Det(a1, a2, c1, c2);

		if (D == 0){
			if (DX == 0 && DY == 0)
				return false;
			else
				return false;
		}
		else{
			papa.first = DX / D;
			papa.second = DY / D;

			if (belong(S1, papa) && belong(S2, papa))
				return true;
			else
				return false;
		}
	}
	
private:
	arr buf; 
	int size = buf.size() - 1;
};


