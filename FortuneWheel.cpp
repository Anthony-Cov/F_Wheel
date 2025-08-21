// main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

int main() {
    const int radius = 250;
    const int window_size = 600;
    const float PI = 3.14159265f;
    const int fontsize=28;
    int n = -1; // Number of slots on the wheel
    float angle = 0.f;
    float theta = 0.f;
    float spin_speed = 0.f;
	bool spinning = true;
	int spin_ticks = 0;
	int c=0;
	int chosen=1;

    // Init random generator
    srand(static_cast<unsigned>(time(0))); // Different random state each run
    const int size = 36; //Max amount
    int numbers[size-1];
    for (int i = 0; i < size-1; i++) {
        numbers[i] = i+2; // Available numbers
    }
    do {
		std::cout<<"How many numbers?\n";
		std::cin>>n;
		std::cout<<"Got "<<n<<"\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (std::find(std::begin(numbers), std::end(numbers), n) == std::end(numbers));
	
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Fortune Wheel");
    sf::Event event;
    for (int i = 0; i < 20; i++) {
		window.pollEvent(event);
	}
    window.clear(sf::Color::Yellow);
	sf::Font font;
	font.loadFromFile("arial.ttf"); // font file required in the project directory
    // The wheel
    sf::CircleShape wheel(radius);
    wheel.setFillColor(sf::Color::Green);
    wheel.setOrigin(radius, radius);
    wheel.setPosition(window_size/2, window_size/2);
    wheel.setOutlineThickness(8);
    wheel.setOutlineColor(sf::Color::Cyan);
    window.draw(wheel);
    
    sf::Text text1;
    text1.setFont(font);
	text1.setCharacterSize(fontsize+2);
	text1.setFillColor(sf::Color::Blue);
	text1.setString("Lucky number");
	text1.setPosition(window_size/2 - 100, window_size/2 - 300);
	window.draw(text1);
	
	sf::Text text;
    text.setFont(font);
	text.setCharacterSize(fontsize-5);
	text.setFillColor(sf::Color::Magenta);
	text.setString("Click to start spinning");
	text.setPosition(window_size/2 - 100, window_size - 40);
	window.draw(text);
    
    for (int i = 0; i < n; ++i) {
		float theta = (2*PI*i)/n + angle;
		sf::RectangleShape slot(sf::Vector2f(radius, 8));
		slot.setOrigin(0, 4);
		slot.setPosition(window_size/2, window_size/2);
		slot.setRotation(theta*180/PI);
		slot.setFillColor(i%2 ? sf::Color::Red : sf::Color::Cyan);
		window.draw(slot);
		sf::Text num;
		num.setFont(font);
		num.setCharacterSize(fontsize);
		num.setFillColor(sf::Color::Black);
		num.setString(std::to_string(i+1));
		float tx = window_size/2 + (radius-30)*cos(theta+PI/n);
		float ty = window_size/2 + (radius-30)*sin(theta+PI/n);
		num.setPosition(tx-8, ty-8);
		window.draw(num);
	}
	window.display();

	bool go = false;
while (window.isOpen()) {
	sf::Event event;
	window.pollEvent(event);
    if (event.type == sf::Event::Closed){
		window.close();
		int i=0;
	}
	if (event.type == sf::Event::MouseButtonPressed){
		go=true;
		// Choose random slot
		chosen = rand() % n + 1; // Number between 1 and n[4]
		// For animation
		spin_speed = 5.f+chosen/2; // Initial speed
		spinning = true;
		spin_ticks = 0;
		c=0;
	}
    while (go) {
        window.clear(sf::Color::Yellow);
        // The wheel
        sf::CircleShape wheel(radius);
        wheel.setFillColor(sf::Color::Green);
        wheel.setOrigin(radius, radius);
        wheel.setPosition(window_size/2, window_size/2);
        wheel.setOutlineThickness(8);
        wheel.setOutlineColor(sf::Color::Cyan);
        window.draw(wheel);
        // Numbered slots
        for (int i = 0; i < n; i++) {
            theta = (2*PI*i)/n + angle;
            sf::RectangleShape slot(sf::Vector2f(radius, 8));
            slot.setOrigin(0, 4);
            slot.setPosition(window_size/2, window_size/2);
            slot.setRotation(theta*180/PI);
            slot.setFillColor(i%2 ? sf::Color::Red : sf::Color::Cyan);
            window.draw(slot);
            // Numbers
            sf::Text num;
            num.setFont(font);
            num.setCharacterSize(fontsize);
            num.setFillColor(i%2 ? sf::Color::Red : sf::Color::Black);
            num.setString(std::to_string(i+1));
            float tx = window_size/2 + (radius-30)*cos(theta+PI/n);
            float ty = window_size/2 + (radius-30)*sin(theta+PI/n);
            num.setPosition(tx-8, ty-8);
            window.draw(num);
        }
		// Pointer        
        sf::ConvexShape triangle;
		triangle.setPointCount(3); 
		triangle.setPoint(0, sf::Vector2f(window_size-10, window_size/2-10 ));
		triangle.setPoint(1, sf::Vector2f(window_size-50, window_size/2 ));  
		triangle.setPoint(2, sf::Vector2f(window_size-10, window_size/2+10 )); 
		triangle.setFillColor(sf::Color::Red);
		window.draw(triangle);
		
		sf::Text text;
        text.setFont(font);
		text.setCharacterSize(fontsize-5);
		text.setFillColor(sf::Color::Magenta);
		text.setString("Click to start spinning");
		text.setPosition(window_size/2 - 100, window_size - 40);
		window.draw(text);
        // Spinning
        if (spinning) {
            angle += spin_speed * 0.01;
            if (angle>=2*PI){
				angle -= 2*PI;
            }
            spin_speed *= 0.98; // Slow down
            ++spin_ticks;
            if (spin_speed < 0.2 && spin_ticks > 120) { // Stop in time
                spinning = false;
            }
        }
        // Display the lucky number
        if (!spinning) {
			c=std::lround((2*PI-angle-PI/n)*n/(2*PI)+1.);
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(fontsize+2);
            text.setFillColor(sf::Color::Blue);
            text.setString("Lucky number is: " + std::to_string(c) + (c%2 ? ", black, odd" : ", red, even"));
            text.setPosition(window_size/2 - 200, window_size/2 - 300);
            window.draw(text);
            go=false;
        }
        window.display();
        sf::sleep(sf::milliseconds(16));
    }
}
    return 0;
}
