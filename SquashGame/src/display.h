#pragma once
void displayInit();
void displayEye();
void displayReshape(int width, int height);
void displayProject(double fov, double asp, double dim);
void display();
void redisplayAll();

/*Animation*/
void stepBall(int ms);

/*Raquete move*/
void mouseCallback(int x, int y);