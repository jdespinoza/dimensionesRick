#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

bool checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) 
{
	if ( Ay+Ah < By ){
		return false; 
	}else if ( Ay > By+Bh ) {
		return false;
	}else if ( Ax+Aw < Bx ) {
		return false;
	}else if ( Ax > Bx+Bw ) {
		return false; 
	}
	return true;
}



int main( int argc, char* args[] )
{
  //inicializacion de SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  //se establece la memoria a usar de OpenGL 
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  //titulo de la ventana
  SDL_WM_SetCaption( "Pong", NULL );

  //tamanio de la ventana
  SDL_SetVideoMode(600,400,32, SDL_OPENGL );

  //color de fondo(blanco)
  glClearColor(1,1,1,1); //RED,GREEN,BLUE,ALPHA

  glViewport(0,0,600,400);

  glShadeModel(GL_SMOOTH);

  //2D rendering
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
 
  glDisable(GL_DEPTH_TEST);

  //bandera del ciclo principal del juego
  bool isRunning = true;

  //For handling with event
  SDL_Event event;


  /////////////////////////////////////////
  /////////////////////////////////////////
  //varibles del rectangulo (jugador)
  float myX = 250; //posicion X de inicio del rectangulo (jugador)
  float myY = 370; //posicion Y de inicio del rectangulo (jugador)
  float width = 80; //ancho del rectangulo
  float height = 20; //largo del rectangulo
  /////////////////////////////////////////
  /////////////////////////////////////////
  
  /////////////////////////////////////////
  /////////////////////////////////////////
  //varibles del rectangulo (jugador)
  float myX2 = 250; //posicion X de inicio del rectangulo (jugador)
  float myY2 = 10; //posicion Y de inicio del rectangulo (jugador)
  float width2 = 80; //ancho del rectangulo
  float height2 = 20; //largo del rectangulo
  /////////////////////////////////////////
  /////////////////////////////////////////
  
   //varibles del rectangulo (jugador)
  float myX3 = 10; //posicion X de inicio del rectangulo (jugador)
  float myY3 = 160; //posicion Y de inicio del rectangulo (jugador)
  float width3 = 20; //ancho del rectangulo
  float height3 = 80; //largo del rectangulo
  /////////////////////////////////////////
  /////////////////////////////////////////
  
   //varibles del rectangulo (jugador)
  float myX4 = 550; //posicion X de inicio del rectangulo (jugador)
  float myY4 = 160; //posicion Y de inicio del rectangulo (jugador)
  float width4 = 20; //ancho del rectangulo
  float height4 = 80; //largo del rectangulo
  /////////////////////////////////////////
  /////////////////////////////////////////

  //siempre se activa solo una a la vez, es el indicador para saber
  //que boton presiona el jugador y asi conocer hacia donde se debe de
  //dirigir el rectangulo
  bool left = false;
  bool right = false; 
  bool left2 = false;
  bool right2 = false;
  bool up = false;
  bool down = false;
  bool up2 = false;
  bool down2 = false; 

  /////////////////////////////////////////
  /////////////////////////////////////////
  //varibles de la bola
  float ballX = 300; //posicion X de inicio de la bola
  float ballY = 345; //posicion Y de inicio de la bola
  float ballWH = 20; //tamanio de la bola (ancho por altura)
  float vellX = 2.5; //velocidad que se desplaza la bola en X
  float vellY = -2.5; //velocidad que se desplaza la bola en Y
  /////////////////////////////////////////
  /////////////////////////////////////////


  


  //ciclo principal del juego
  while ( isRunning ) {
      //eventos
      while ( SDL_PollEvent(&event) ) {
	  //si cierran la venta del juego
	  if ( event.type == SDL_QUIT ) {
	      isRunning = false;
	    }

	  //si se preciona ESC
	  if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE ) {
	      isRunning = false;
	    }

	  //si se presiona algun boton
	  if ( event.type == SDL_KEYDOWN ) {
		  //revisa cual boton fue el que se preciono
	      if ( event.key.keysym.sym == SDLK_LEFT ) {
		  left = true;
		}

	      else if ( event.key.keysym.sym == SDLK_RIGHT ) {
		  right = true;
		}
		else if ( event.key.keysym.sym == SDLK_a ) {
		  left2 = true;
		}

	      else if ( event.key.keysym.sym == SDLK_d ) {
		  right2 = true;
		}else if ( event.key.keysym.sym == SDLK_w ) {
		  up = true;
		}else if ( event.key.keysym.sym == SDLK_s ) {
		  down = true;
		}else if ( event.key.keysym.sym == SDLK_UP ) {
		  up2 = true;
		}else if ( event.key.keysym.sym == SDLK_DOWN ) {
		  down2 = true;
		}
	       
	    }

	  //si se deja de presionar un boton
	  else if ( event.type == SDL_KEYUP ) {
		  //revisa cual se dejo de precionar
	      if ( event.key.keysym.sym == SDLK_LEFT ) {
		  left = false;
		}
	      
	      else if ( event.key.keysym.sym == SDLK_RIGHT ){
		  right = false;
		}
		else if ( event.key.keysym.sym == SDLK_a ) {
		  left2 = false;
		}
	      
	      else if ( event.key.keysym.sym == SDLK_d ){
		  right2 = false;
		}
		else if ( event.key.keysym.sym == SDLK_w ){
		  up = false;
		}
		else if ( event.key.keysym.sym == SDLK_s ){
		  down = false;
		}
		else if ( event.key.keysym.sym == SDLK_UP ){
		  up2 = false;
		}
		else if ( event.key.keysym.sym == SDLK_DOWN ){
		  down2 = false;
		}
	    }
	}

      if ( left == true ) {
	  myX -= 3;
	}

      if ( right == true ) {
	  myX += 3;
	}
	
	if ( left2 == true ) {
	  myX2 -= 3;
	}

      if ( right2 == true ) {
	  myX2 += 3;
	}
	
	if (up == true) {
		myY3 -= 3;
	}
	
	if (down == true) {
		myY3 += 3;
	}
	
	if (up2 == true) {
		myY4 -= 3;
	}
	
	if (down2 == true) {
		myY4 += 3;
	}

	  ////////////////////////////////////////////
	  //logica del rectangulo (jugador)
	  ////////////////////////////////////////////

	  //validacion para que la barra no se salga de la pantalla
      if ( myX < 0 ) {
	  myX = 0;
	}

	  //validacion para que la barra no se salga de la pantalla
      if ( myX+width > 600 ) {
	  myX = 600-width; //Move it back so it only touches the right border
	}
	
	if ( myX2 < 0 ) {
	  myX2 = 0;
	}

	  //validacion para que la barra no se salga de la pantalla
      if ( myX2+width2 > 600 ) {
	  myX2 = 600-width2; //Move it back so it only touches the right border
	}

	if (myY3 < 0) {
		myY3 = 0;
	}
	
	if (myY4 < 0) {
		myY4 = 0;
	}
	
	if (myY3 + height3 > 400) {
		myY3 = 400 - height3;
	}
	
	if (myY4 + height4 > 400) {
		myY4 = 400 - height4;
	}
      ////////////////////////////////////////////
      //logica de la bola
      ////////////////////////////////////////////
      
      //primero se mueve en el eje x
      ballX += vellX;

	  //se mueve la bola en el eje Y
      ballY += vellY;

	  


	  //validacion del limite de la pantalla, para que la bola no se salga de la pantalla
      if ( ballX < 0 ) {
	  vellX = -vellX;
	  printf("Fin de Partida\n");
	  exit(0);
	}

      else if ( ballX+ballWH>600 )
	{
	  vellX = -vellX;
	  printf("Fin de Partida\n");
	  exit(0);
	}

      if ( ballY < 0 )
	{
	  vellY = -vellY;
	  printf("Fin de Partida\n");
	  exit(0);
	}
      
      //si la bola toca el piso, el juego se reinicia
      else if ( ballY+ballWH > 400 ) { 
	  //se establecen los valores de inicio
	  myX = 250; 
	  myY = 370; 
	  width = 80; 
	  height = 20;
	  
	  myX2 = 250; 
	  myY2 = 10; 
	  width2 = 80; 
	  height2 = 20;
	  
	  left = false;
	  right = false; 
	  
	  ballX = 300;
	  ballY = 345;
	  ballWH = 20;
	  
	  vellX = 2.5;
	  vellY = -2.5;

	  printf("Fin de Partida\n");
	  exit(0);
	  
	    
	    
	    //presione enter para continuar
	}

	  //si choca con el rectangulo (jugador), rebota hacia arriba
      if ( checkCollision(ballX,ballY,ballWH,ballWH,myX,myY,width,height) == true )	{
	  vellY = -vellY;
	}
	
	if ( checkCollision(ballX,ballY,ballWH,ballWH,myX2,myY2,width2,height2) == true )	{
	  vellY = -vellY;
	}
	
	if ( checkCollision(ballX,ballY,ballWH,ballWH,myX3,myY3,width3,height3) == true )	{
	  vellX = -vellX;
	}
	
	if ( checkCollision(ballX,ballY,ballWH,ballWH,myX4,myY4,width4,height4) == true )	{
	  vellX = -vellX;
	}
      
      glClear(GL_COLOR_BUFFER_BIT);

      glPushMatrix(); 

      glOrtho(0,600,400,0,-1,1);

      glColor4ub(0,0,0,255); 

      glBegin(GL_QUADS); //dibuja el rectangulo

	  //parametros para dibujar el rectangulo
      glVertex2f(myX,myY); 
      glVertex2f(myX+width,myY);
      glVertex2f(myX+width,myY+height);
      glVertex2f(myX,myY+height);

      glEnd(); //termina de dibujar el rectangulo
      
      
      glColor4ub(0,0,0,255);
      glBegin(GL_QUADS); //dibuja el rectangulo

	  //parametros para dibujar el rectangulo
      glVertex2f(myX2,myY2); 
      glVertex2f(myX2+width2,myY2);
      glVertex2f(myX2+width2,myY2+height2);
      glVertex2f(myX2,myY2+height2);

      glEnd(); //termina de dibujar el rectangulo
      
      glColor4ub(122,0,255,255);

      glBegin(GL_QUADS); //dibuja el rectangulo

	  //parametros para dibujar el rectangulo
      glVertex2f(myX3,myY3); 
      glVertex2f(myX3+width3,myY3);
      glVertex2f(myX3+width3,myY3+height3);
      glVertex2f(myX3,myY3+height3);

      glEnd(); //termina de dibujar el rectangulo
      
      glColor4ub(122,0,255,255);

      glBegin(GL_QUADS); //dibuja el rectangulo

	  //parametros para dibujar el rectangulo
      glVertex2f(myX4,myY4); 
      glVertex2f(myX4+width4,myY4);
      glVertex2f(myX4+width4,myY4+height4);
      glVertex2f(myX4,myY4+height4);

      glEnd(); //termina de dibujar el rectangulo
      

      glColor4ub(255,0,0,255);

      glBegin(GL_QUADS); //dibuja de la bola de la misma manera que el rectangulo
      glVertex2f(ballX,ballY);
      glVertex2f(ballX+ballWH,ballY);
      glVertex2f(ballX+ballWH,ballY+ballWH);
      glVertex2f(ballX,ballY+ballWH);
      glEnd();

      glColor4ub(0,0,255,255);

      

      glEnd();

      glPopMatrix();

      SDL_GL_SwapBuffers();

      SDL_Delay(1); 
      
      
      
    } 

  SDL_Quit();

  return 0;
}
