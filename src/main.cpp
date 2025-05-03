#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

double distance(float x, float y, float x2, float y2) {
    double dx = x2 - x;
    double dy = y2 - y;
    return std::sqrt(dx * dx + dy * dy);
}

#define damp 0.2
#ifndef damp2
#define damp2 0.2
#endif
class particle {
	public:
	float x = 0;
	float y = 0;
	float velX = 0;
	float velY = 0;
	float accX = 0;
	float accY = 0;
	sf::CircleShape shape;
	particle(float x, float y, float velX, float velY, float accX, float accY) {
		this->x = x;
		this->y = y;
		this->velX = velX;
		this->velY = velY;
		this->accX = accX;
		this->accY = accY;
		sf::CircleShape shape(1);
		this->shape = shape;
		this->shape.setFillColor(sf::Color::Green);
	}
	void display(sf::RenderWindow &win) {
		shape.setPosition({static_cast<float>(x), static_cast<float>(y)});
		win.draw(shape);
	};
	void sim() {
		velX += accX;
		velY += accY;
		x += velX;
		y += velY;
	};

	bool collidew() {
		bool ret=false;
		if(y > 100) {
			y = 99;
			//velY=0;
			ret = true;
			velY=-velY;
			velY*=damp2;
		}
		if(x > 100) {
			x = 99;
			//velX=0;
			ret = true;
			velX=-velX;
			velX*=damp2;
		}
		if(x < 0) {
			x = 1;
			//velX=0;
			ret = true;
			velX=-velX;
			velX*=damp2;
		}
		return ret;
	}
	void collide(float x, float y, float x2, float y2, particle &other) {
		float angle = atan2(x2-x, y2-y);
		for(;;) {
		collidew();
		other.collidew();
		x-=cos(angle);
		y-=sin(angle);
		other.x+=cos(angle);
		other.y+=sin(angle);
		
	/*	velX-=cos(angle)*damp;
		velY-=sin(angle)*damp;
		other.velX+=cos(angle)*damp;
		other.velY+=sin(angle)*damp;
		sim();
		other.sim();*/
		
		if(! ( distance( x, y, x2, y2 ) < 2)  ) break;
		}
	}
};

int main()
{
	std::vector<particle> parts;
	int h = 0;
	int a = 0;
	//int apart = 4;
	//int count = 20;
	//for(int i = 0; i<count*apart; i+=apart) {
//	}
	sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}	
		window.clear();
		for(int i = 0; i < parts.size(); i++) {
			//parts.at(i).sim();
			parts.at(i).sim();
			parts.at(i).collidew();
			}

		for(int i = 0; i < parts.size(); i++) {
			for(int j = 0; j<parts.size(); j++) {
				if(j==i) continue;
			//	for(int k = 0; k < 10; k++) {
				if( ( distance( parts.at(j).x, parts.at(j).y, parts.at(i).x, parts.at(i).y ) < 2)  ) {
					parts.at(j).collide(parts.at(j).x, parts.at(j).y, parts.at(i).x, parts.at(i).y, parts.at(i));
					//std::cout << "hehe";
			//	}
				}
			}
		parts.at(i).display(window);
		}
		window.display();
		if(!h/* && a < 120*/) {
		particle part(0, 0, 1, 0, 0, 0.03);
		parts.push_back(part);
		h++;
		} else h--;
	//	a++;
		//sf::sleep(sf::milliseconds(12));
		sf::sleep(sf::milliseconds(14));
	}
}
