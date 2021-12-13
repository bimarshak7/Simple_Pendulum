#ifndef PENDU_H
#define PENDU_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<math.h>
#include "constants.h"

class Pendu{
	sf::RenderWindow* window;
    sf:: VideoMode videoMode;
    sf:: Event ev;
        
    //Mouse pos
    sf:: Vector2i mousePosWindow;
    sf :: Vector2f mousePosView;
    sf :: Vector2f endPos;

    //pendulum pos
    sf :: Vector2f originPos;
    sf :: Vector2f bobPos;
    int len;
    float angle;
    float accl;
    float vel;

    //pendulum structure
    sf:: CircleShape bob;
    sf::Vertex vertices[2];
    sf::VertexBuffer vb;

    sf:: VertexArray cb;
    
    
    //privateFunction
    void initVars();
    void initWindow();
    void initPendu();
	public:
		Pendu();
		virtual ~Pendu();

        bool running() const;

        void pollEvents();
        void updatePendu();
        void update();
        void renderPendu(sf::RenderTarget& target);
        void render();
};

#endif