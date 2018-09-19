#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "frameGenerator.h"
#include "drawFilledTriangle.h"
#include "drawFilledCircle.h"
#include "drawFilledRectangle.h"

const std::string TITLE = "Vivek Udupa's Best Try";
const std::string NAME = "vkoodli";

const int WIDTH = 640;
const int HEIGHT = 480;

Vector2f v0{500,100};
Vector2f v1{150,200};
Vector2f v2{350,200};

//Drawing a rectangle
SDL_Rect posi;

void writeName(SDL_Renderer* renderer) {
  TTF_Init();
  TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  SDL_Color textColor = {0xff, 0, 0, 0};
  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, TITLE.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {20, HEIGHT-40, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

int main(void) {
  try {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
      std::cout << "Failed to initialize SDL2" << std::endl;
      return EXIT_FAILURE;
    }
    SDL_Window* window = SDL_CreateWindow(
      TITLE.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN
    );
    
    // Apparently we can't use hardware acceleration with
    // SDL_GetWindowSurface
    SDL_Renderer* renderer = SDL_CreateRenderer( 
      window, -1, SDL_RENDERER_SOFTWARE
    );

	//Background
    SDL_SetRenderDrawColor( renderer, 135, 206, 250, 255 ); //skyblue
    SDL_RenderClear(renderer);
   	

/*
	//Grid
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
		//Vertical grid
		for(int a = 0; a < WIDTH; a+=20)
		{
			SDL_RenderDrawLine( renderer, a, 0, a, HEIGHT );
			SDL_RenderPresent( renderer );
		}
		//Horizontal grid
		for(int b = 0; b < WIDTH; b+=20)
		{
			SDL_RenderDrawLine( renderer, 0, b, WIDTH, b );
			SDL_RenderPresent( renderer );
		}
*/

/*
	Vector2f v0(400,200);
	Vector2f v1(200,400);
	Vector2f v2(600,400);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	DrawFilledTriangle tri1(renderer, v0, v1, v2 );
	tri1.draw();	
*/

// ********************DRAWING CODE HERE***********************************************

//Layer 1 - Brown Base 
//Triangle 1
Vector2f t1(100,250);
Vector2f t2(300,250);
Vector2f t3(200,420);

//Triangle 2
Vector2f t4(200,250);
Vector2f t5(440,250);
Vector2f t6(320,450);

//Triangle 3
Vector2f t7(340,250);
Vector2f t8(540,250);
Vector2f t9(440,420);

//Layer2 - Green Base
//G1
Vector2f t10(72,214);
Vector2f t11(119,283);
Vector2f t12(200,250);

//G2
Vector2f t13(72,214);
Vector2f t14(235,167);
Vector2f t15(200,250);

//G3
Vector2f t16(440,167);
Vector2f t17(235,167);
Vector2f t18(200,250);

//G4
Vector2f t19(440,167);
Vector2f t20(596,185);
Vector2f t21(401,251);

//G5
Vector2f t22(200,250);
Vector2f t23(440,167);
Vector2f t24(401,251);

//G6
Vector2f t25(596,185);
Vector2f t26(541,251);
Vector2f t27(401,251);

//Layer 3 - green shade

//G7
Vector2f t28(127,266);
Vector2f t29(200,251);
Vector2f t30(72,214);
//G8
Vector2f t31(127,266);
Vector2f t32(119,283);
Vector2f t33(200,251);
//G9
Vector2f t34(127,266);
Vector2f t35(119,283);
Vector2f t36(72,214);

//G10
Vector2f t37(200,251);
Vector2f t38(368,221);
Vector2f t39(437,260);
//G11
Vector2f t40(368,221);
Vector2f t41(437,260);
Vector2f t42(454,197);
//G12
Vector2f t43(596,182);
Vector2f t44(437,260);
Vector2f t45(454,197);
//G13
Vector2f t46(541,251);
Vector2f t47(437,260);
Vector2f t48(596,182);

//G14
Vector2f t49(454,197);
Vector2f t50(235,167);
Vector2f t51(456,170);

//Layer 4 - trees

//Trunk 1
Vector2f t52(141,210);
Vector2f t53(146,216);
Vector2f t54(156,81);

//Trunk 2
Vector2f t55(146,216);
Vector2f t56(166,216);
Vector2f t57(156,81);

//Trunk 3
Vector2f t58(171,210);
Vector2f t59(166,216);
Vector2f t60(156,81);

//Leaves layer 1
//L1
Vector2f t61(94,155);
Vector2f t62(114,176);
Vector2f t63(154,80);
//L2
Vector2f t64(114,176);
Vector2f t65(194,176);
Vector2f t66(154,80);
//L3
Vector2f t67(194,176);
Vector2f t68(214,155);
Vector2f t69(154,80);

//Leaves layer 2
//L1
Vector2f t70(105,125);
Vector2f t71(117,146);
Vector2f t72(154,50);
//L2
Vector2f t73(117,146);
Vector2f t74(191,146);
Vector2f t75(154,50);
//L3
Vector2f t76(191,146);
Vector2f t77(203,125);
Vector2f t78(154,50);

//Leaves layer 3
//L1
Vector2f t79(115,95);
Vector2f t80(119,116);
Vector2f t81(154,20);
//L2
Vector2f t82(119,116);
Vector2f t83(194,116);
Vector2f t84(154,20);
//L3
Vector2f t85(189,116);
Vector2f t86(195,95);
Vector2f t87(154,20);

//Cloud
SDL_Rect posi1, posi2, posi3;

//cloud 1
SDL_Point center1 = {471,57};
SDL_Point center2 = {533,51};
SDL_Point center3 = {591,54};

posi1.x = 425;
posi1.y = 63;
posi1.h = 90;
posi1.w = 300;

//cloud 2
SDL_Point center4 = {97,57};
SDL_Point center5 = {127,51};
SDL_Point center6 = {142,54};

posi2.x = 57;
posi2.y = 60;
posi2.h = 90;
posi2.w = 400;

//cloud 3
SDL_Point center7 = {437,412};
SDL_Point center8 = {497,402};
SDL_Point center9 = {537,412};

posi3.x = 397;
posi3.y = 412;
posi3.h = 90;
posi3.w = 400;

//Mountain
//M1
Vector2f m1(258,185);	
Vector2f m2(302,179);	
Vector2f m3(384,187);	

//M2
Vector2f m4(339,168);	
Vector2f m5(302,179);	
Vector2f m6(384,187);	
	
//M3
Vector2f m7(339,168);	
Vector2f m8(399,170);	
Vector2f m9(384,187);	

//M4
Vector2f m10(453,197);	
Vector2f m11(399,170);	
Vector2f m12(384,187);	

//M5
Vector2f m13(453,197);	
Vector2f m14(399,170);	
Vector2f m15(459,171);	

//M6
Vector2f m16(453,197);	
Vector2f m17(596,183);	
Vector2f m18(459,171);	

//M7
Vector2f m19(341,169);	
Vector2f m20(461,177);	
Vector2f m21(401,77);	

//M8
Vector2f m22(341,169);	
Vector2f m23(401,173);	
Vector2f m24(401,77);	

//M9
Vector2f m25(594,183);	
Vector2f m26(401,173);	
Vector2f m27(510,0);	

//M9
Vector2f m28(510,183);	
Vector2f m29(401,173);	
Vector2f m30(510,0);	

//Bottom Rock Shade

//shade1
Vector2f s1(200,250);
Vector2f s2(440,250);
Vector2f s3(320,350);
//shade2
Vector2f s4(320,350);
Vector2f s5(440,250);
Vector2f s6(320,450);
//shade3
Vector2f s7(200,250);
Vector2f s8(320,450);
Vector2f s9(320,350);








	//Layer 1
	SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255); //dim grey
	DrawFilledTriangle tri1(renderer, t1, t2, t3 );
	tri1.draw();	
	
	DrawFilledTriangle tri2(renderer, t7, t8, t9 );
	tri2.draw();	
	
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); //dark grey
	DrawFilledTriangle tri3(renderer, t4, t5, t6 );
	tri3.draw();	
    
	SDL_RenderPresent(renderer);

	//Bottom Rock Shade
	DrawFilledTriangle shad1(renderer, s1, s2, s3 );
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); //dark grey
	shad1.draw();	
	
	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); //silver
	DrawFilledTriangle shad2(renderer, s4, s5, s6 );
	shad2.draw();	

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); //grey
	DrawFilledTriangle shad3(renderer, s7, s8, s9 );
	shad3.draw();	


	SDL_RenderPresent(renderer);
	
	//Cloud 2
	SDL_Color color1 = {245,245,245,255};
	SDL_Color color2 = {220,220,220,255};
	SDL_Color color3 = {255,255,255,255};

	DrawFilledCircle cir4(renderer, center4, 20, color1);
	DrawFilledCircle cir5(renderer, center5, 40, color2);
	DrawFilledCircle cir6(renderer, center6, 25, color3);

	cir4.draw();
	cir5.draw();
	cir6.draw();


    SDL_SetRenderDrawColor( renderer, 135, 206, 250, 255 ); //skyblue
	DrawFilledRectangle rect2(renderer, posi2);
    rect2.draw();
	SDL_RenderPresent(renderer);

	//Layer2

	SDL_SetRenderDrawColor(renderer, 0, 170, 0, 255); // green
	DrawFilledTriangle tri4(renderer, t10, t11, t12 );
	tri4.draw();	
	
	DrawFilledTriangle tri5(renderer, t13, t14, t15 );
	tri5.draw();	
	
	SDL_SetRenderDrawColor(renderer, 154, 205, 50, 255); //yellow green
	//SDL_SetRenderDrawColor(renderer, 0, 255, 127, 255); //spring green
	DrawFilledTriangle tri6(renderer, t16, t17, t18 );
	tri6.draw();	
	
	//SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255); //Lime green
	DrawFilledTriangle tri7(renderer, t19, t20, t21 );
	tri7.draw();	

	//SDL_SetRenderDrawColor(renderer, 0, 255, 127, 255); //spring green
	DrawFilledTriangle tri8(renderer, t22, t23, t24 );
	tri8.draw();	

	//SDL_SetRenderDrawColor(renderer, 0, 255, 127, 255); //spring green
	DrawFilledTriangle tri9(renderer, t25, t26, t27 );
	tri9.draw();	
	
	SDL_RenderPresent(renderer);

	//Layer 3 - shade

	SDL_SetRenderDrawColor(renderer, 34,139,34, 255); //forest green
	DrawFilledTriangle tri10(renderer, t31, t32, t33 );
	tri10.draw();	
	
	SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255); //Lime green
	DrawFilledTriangle tri11(renderer, t34, t35, t36 );
	tri11.draw();

	SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255); //Dark green
	DrawFilledTriangle tri12(renderer, t37, t38, t39 );
	tri12.draw();

	SDL_SetRenderDrawColor(renderer, 10, 170, 10, 255); // green
	DrawFilledTriangle tri13(renderer, t40, t41, t42 );
	tri13.draw();
	
	SDL_SetRenderDrawColor(renderer, 10, 140, 10, 255); //slight dark green 
	DrawFilledTriangle tri14(renderer, t43, t44, t45 );
	tri14.draw();
	
	SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255); //Dark green
	DrawFilledTriangle tri15(renderer, t46, t47, t48 );
	tri15.draw();

	SDL_SetRenderDrawColor(renderer, 173, 205, 47, 255); //Lime green
	DrawFilledTriangle tri16(renderer, t49, t50, t51 );
	tri16.draw();
    SDL_RenderPresent(renderer);
	
	//Layer 4 - trees
	SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255); //chocolate brown
	DrawFilledTriangle tri17(renderer, t52, t53, t54 );
	tri17.draw();
	
	SDL_SetRenderDrawColor(renderer, 160, 82, 45, 255); //sienna brown
	DrawFilledTriangle tri18(renderer, t55, t56, t57 );
	tri18.draw();
	
	SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); //saddle brown
	DrawFilledTriangle tri19(renderer, t58, t59, t60 );
	tri19.draw();
	
    SDL_RenderPresent(renderer);
	
	//Leaves1
	SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255); //dark green
	DrawFilledTriangle tri20(renderer, t61, t62, t63 );
	tri20.draw();

	SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); //green
	DrawFilledTriangle tri21(renderer, t64, t65, t66 );
	tri21.draw();

	SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); //forest green
	DrawFilledTriangle tri22(renderer, t67, t68, t69 );
	tri22.draw();
	
    SDL_RenderPresent(renderer);
	
	//Leaves2
	SDL_SetRenderDrawColor(renderer, 0, 120, 0, 255); //dark green *20
	DrawFilledTriangle tri23(renderer, t70, t71, t72 );
	tri23.draw();

	SDL_SetRenderDrawColor(renderer, 0, 148, 0, 255); //green * 20
	DrawFilledTriangle tri24(renderer, t73, t74, t75 );
	tri24.draw();

	SDL_SetRenderDrawColor(renderer, 34, 159, 34, 255); //forest green *20
	DrawFilledTriangle tri25(renderer, t76, t77, t78 );
	tri25.draw();
	
	//Leaves3
	SDL_SetRenderDrawColor(renderer, 0, 140, 0, 255); //dark green *40
	DrawFilledTriangle tri26(renderer, t79, t80, t81 );
	tri26.draw();

	SDL_SetRenderDrawColor(renderer, 0, 168, 0, 255); //green * 40
	DrawFilledTriangle tri27(renderer, t82, t83, t84 );
	tri27.draw();

	SDL_SetRenderDrawColor(renderer, 34, 179, 34, 255); //forest green *40
	DrawFilledTriangle tri28(renderer, t85, t86, t87 );
	tri28.draw();

    SDL_RenderPresent(renderer);

	//Clouds 2

	DrawFilledCircle cir1(renderer, center1, 40, color1);
	DrawFilledCircle cir2(renderer, center2, 80, color2);
	DrawFilledCircle cir3(renderer, center3, 50, color3);

	cir1.draw();
	cir2.draw();
	cir3.draw();


    SDL_SetRenderDrawColor( renderer, 135, 206, 250, 255 ); //skyblue
	DrawFilledRectangle rect1(renderer, posi1);
    rect1.draw();
	SDL_RenderPresent(renderer);
	
	//Clouds 3
	
	DrawFilledCircle cir7(renderer, center7, 30, color1);
	DrawFilledCircle cir8(renderer, center8, 70, color2);
	DrawFilledCircle cir9(renderer, center9, 45, color3);

	cir7.draw();
	cir8.draw();
	cir9.draw();


    SDL_SetRenderDrawColor( renderer, 135, 206, 250, 255 ); //skyblue
	DrawFilledRectangle rect3(renderer, posi3);
    rect3.draw();
	SDL_RenderPresent(renderer);
	
	//Mountain
	//M1
	SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); //saddle brown
	DrawFilledTriangle mnt1(renderer, m1, m2, m3 );
	mnt1.draw();	
	//M2
	SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255); //chocolate
	DrawFilledTriangle mnt2(renderer, m4, m5, m6 );
	mnt2.draw();	
	//M3
	SDL_SetRenderDrawColor(renderer, 244,164,96, 255); //sandy brown
	DrawFilledTriangle mnt3(renderer, m7, m8, m9 );
	mnt3.draw();	
	//M4
	SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); //saddle brown
	DrawFilledTriangle mnt4(renderer, m10, m11, m12 );
	mnt4.draw();	
	//M5
	SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255); //chocolate
	DrawFilledTriangle mnt5(renderer, m13, m14, m15 );
	mnt5.draw();	
	//M6
	SDL_SetRenderDrawColor(renderer, 155, 69, 19, 255); //saddle brown*
	DrawFilledTriangle mnt6(renderer, m16, m17, m18 );
	mnt6.draw();	
	//M9
	SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255); //chocolate
	DrawFilledTriangle mnt9(renderer, m25, m26, m27 );
	mnt9.draw();	
	//M10
	SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); //saddle brown
	DrawFilledTriangle mnt10(renderer, m28, m29, m30 );
	mnt10.draw();	
	//M7
	SDL_SetRenderDrawColor(renderer, 244,164,96, 255); //sandy brown
	DrawFilledTriangle mnt7(renderer, m19, m20, m21 );
	mnt7.draw();	
	//M8
	SDL_SetRenderDrawColor(renderer, 210, 105, 30, 255); //chocolate
	DrawFilledTriangle mnt8(renderer, m22, m23, m24 );
	mnt8.draw();	

	SDL_RenderPresent(renderer);

//***************************************************************************//
    writeName(renderer);
    SDL_RenderPresent(renderer);
    FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
    frameGen.makeFrame();

    SDL_Event event;
    const Uint8* keystate;

	  while ( true ) {
      keystate = SDL_GetKeyboardState(0);
      if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
		if(event.type == SDL_MOUSEMOTION)
		{
			std::cout << event.motion.x << "," << event.motion.y << '\n';
		}
      }
  }


  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  }
  catch (const std::string& msg) { std::cout << msg << std::endl; }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
  }
  return EXIT_SUCCESS;
}
