#include "../inc/Pendu.h"
#include "../inc/constants.h"

Pendu:: Pendu(){
    //this->initVariables();
    this->initWindow();
    this->initPendu();
}

Pendu::~Pendu(){
    delete this->window;
}

void Pendu:: initPendu(){
    float center = this->window->getSize().x/2;
    this->angle = 45*(pi/180);
    this->accl = -g*sin(this->angle)/this->len;
    this->vel = 0;
    this->len=sqrt(pow((400-endPos.x),2)+pow((10-endPos.y),2));
	this->endPos = sf::Vector2f(400+len*cos(this->angle),10+len*-sin(this->angle));
	this->vb.create(2);
    this->vb.setPrimitiveType(sf::LinesStrip);
    
    this->vertices[0].position = sf::Vector2f(center, 70.f);
	this->vertices[0].color  = sf::Color::Red;
	this->vertices[1].position = endPos;
	this->vertices[1].color = sf::Color::Red;
  
    vb.update(vertices);
    
    this->bob.setPosition(endPos.x-10,endPos.y);
    this->bob.setRadius(20.f);
    this->bob.setOrigin(10.f,10.f);
    this->bob.setFillColor(sf::Color::Cyan);

    //this->cb.setPrimitiveType(sf::LinesStrip);
} 

bool Pendu::running() const{
    return this->window->isOpen();
}

void Pendu:: initWindow(){
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode,"Simple Pendulum",sf::Style::Titlebar); 
    this->window->setFramerateLimit(60);
}

void Pendu:: pollEvents(){
    while(this->window->pollEvent(this->ev)){
            switch(this->ev.type){
                case sf::Event:: Closed:
                    this->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if(this->ev.key.code==sf::Keyboard::Escape)
                        this->window->close();
                    break;
            }
        }
}

void Pendu:: updatePendu(){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                this->mousePosWindow = sf:: Mouse::getPosition(*this->window);
    			this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
                if(this->bob.getGlobalBounds().contains(this->mousePosView)){
                    this->cb.clear();
	    			this->endPos = this->mousePosView;                 	
	                this->vertices[1].position = this->endPos;
                    this->angle = atan((endPos.x-400)/(endPos.y-10));
	                vb.update(vertices);
	             	this->bob.setPosition(endPos.x-10,endPos.y);
	             	this->len = sqrt(pow((400-endPos.x),2)+pow((10-endPos.y),2));   
                }
    }
    else{
    	this->accl = -g*sin(this->angle)/this->len;
	    this->vel +=this->accl; 
	    this->angle+=(this->vel)*(pi/180);
        this->vel *=damp; //damping
	    this->endPos = sf::Vector2f(400.f+len*sin(this->angle),10.f+len*cos(this->angle));
		this->vertices[1].position = endPos;
		this->bob.setPosition(endPos.x-10,endPos.y-10);   
		vb.update(vertices);

        this->cb.append(sf::Vertex(endPos,sf::Color::Red));
    }


}

void Pendu::update(){
    this->pollEvents();
    this->updatePendu();
}
void Pendu:: renderPendu(sf::RenderTarget& target){
    target.draw(this->vb);
    target.draw(this->bob);
    target.draw(this->cb);

}
void Pendu:: render(){
    this->window->clear();
    this->renderPendu(*this->window);
    this->window->display();

}
