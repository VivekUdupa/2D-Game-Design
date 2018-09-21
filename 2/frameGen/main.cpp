#include "main.h"


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
    SDL_SetRenderDrawColor( renderer, 135, 206, 250, 255 ); //light skyblue
    SDL_RenderClear(renderer);

// ********************DRAWING CODE HERE***********************************************

	//Clouds co-ordinates
	SDL_Point center1 = {83, 102};
	SDL_Point center2 = {143, 102};
	SDL_Point center3 = {193, 102};
	
	SDL_Point center4 = {440, 90};
	SDL_Point center5 = {490, 90};
	SDL_Point center6 = {530, 90};

	//center7 used inside DrawBase function
	SDL_Point center8 = {460, 420};
	SDL_Point center9 = {510, 420};
	
	SDL_Point center10 = {60, 320};
	SDL_Point center11 = {95, 320};
	SDL_Point center12 = {130, 320};

	// Render The ART
	
	DrawClouds(renderer, center9, 40, lightGrey);
	DrawClouds(renderer, center8, 70, smoke);
	
	DrawBase(renderer);

	SDL_RenderPresent(renderer);

	DrawGrass(renderer);

	SDL_RenderPresent(renderer);

	DrawClouds(renderer, center1, 40, smoke);
	DrawClouds(renderer, center2, 70, lightGrey);
	DrawClouds(renderer, center3, 37, smoke);
	
	DrawTree(renderer);

	SDL_RenderPresent(renderer);
	
	DrawMountain(renderer);
	
	SDL_RenderPresent(renderer);
	
	DrawClouds(renderer, center6, 45, smoke);
	DrawClouds(renderer, center5, 60, lightGrey);
	DrawClouds(renderer, center4, 40, smoke);

	SDL_RenderPresent(renderer);

	DrawClouds(renderer, center10, 40, smoke);
	DrawClouds(renderer, center11, 55, silverGrey);
	DrawClouds(renderer, center12, 40, smoke);
	
	
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

//Functions

void DrawBase(SDL_Renderer* renderer)
{

	//Layer 1 - Black Base
	//left base
	Vector2f t0(100,250);
	Vector2f t1(300,250);
	Vector2f t2(200,380);

	//center base
	Vector2f t3(200,250);
	Vector2f t4(440,250);
	Vector2f t5(320,450);

	//Right base
	Vector2f t6(340,250);
	Vector2f t7(540,250);
	Vector2f t8(440,420);

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


	DrawFilledTriangle triangle1(renderer, t0, t1, t2, dimGrey);
	triangle1.draw(); //left	
	
	DrawFilledTriangle triangle3(renderer, t6, t7, t8, dimGrey);
	triangle3.draw();	//right
	
	SDL_Point center7 = {380, 420};
	DrawClouds(renderer, center7, 80, smoke);
	
	DrawFilledTriangle triangle2(renderer, t3, t4, t5, darkGrey);
	triangle2.draw(); // center

	DrawFilledTriangle triangle4(renderer, s1, s2, s3, darkGrey);
	triangle4.draw();	//center-s1
	
	DrawFilledTriangle triangle5(renderer, s4, s5, s6, silverGrey);
	triangle5.draw();	//center-s2

	DrawFilledTriangle triangle6(renderer, s7, s8, s9, grey);
	triangle6.draw();	//center-s3
	
}

void DrawGrass(SDL_Renderer* renderer)
{
	//Layer2 - Green Base
	//G1
	Vector2f t10(72,214);
	Vector2f t11(119,283);
	Vector2f t12(200,250);

	//G2
	Vector2f t13(72,214);
	Vector2f t14(235,180);
	Vector2f t15(200,250);

	//G3
	Vector2f t16(440,180);
	Vector2f t17(235,180);
	Vector2f t18(200,250);

	//G4
	Vector2f t19(440,180);
	Vector2f t20(596,185);
	Vector2f t21(401,251);

	//G5
	Vector2f t22(200,250);
	Vector2f t23(440,180);
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
	Vector2f t50(235,180);
	Vector2f t51(456,180);

	//Layer2

	DrawFilledTriangle tri4(renderer, t10, t11, t12, green);
	tri4.draw();	

	DrawFilledTriangle tri5(renderer, t13, t14, t15, green );
	tri5.draw();	

	DrawFilledTriangle tri6(renderer, t16, t17, t18, yellowGreen );
	tri6.draw();	

	DrawFilledTriangle tri7(renderer, t19, t20, t21, yellowGreen );
	tri7.draw();	

	DrawFilledTriangle tri8(renderer, t22, t23, t24, yellowGreen);
	tri8.draw();	

	DrawFilledTriangle tri9(renderer, t25, t26, t27, yellowGreen);
	tri9.draw();

	SDL_RenderPresent(renderer);

	//Layer 3 - shade

	DrawFilledTriangle tri10(renderer, t31, t32, t33, forestGreen );
	tri10.draw();	

	DrawFilledTriangle tri11(renderer, t34, t35, t36, limeGreen );
	tri11.draw();

	DrawFilledTriangle tri12(renderer, t37, t38, t39, darkGreen );
	tri12.draw();

	DrawFilledTriangle tri13(renderer, t40, t41, t42, green );
	tri13.draw();

	DrawFilledTriangle tri14(renderer, t43, t44, t45,slDarkGreen );
	tri14.draw();

	DrawFilledTriangle tri15(renderer, t46, t47, t48, darkGreen );
	tri15.draw();

	DrawFilledTriangle tri16(renderer, t49, t50, t51, limeGreen );
	tri16.draw();

}

void DrawTree(SDL_Renderer* renderer)
{
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


	//Layer 4 - trees
	DrawFilledTriangle tri17(renderer, t52, t53, t54, chocolateBrown );
	tri17.draw();

	DrawFilledTriangle tri18(renderer, t55, t56, t57, sienna );
	tri18.draw();

	DrawFilledTriangle tri19(renderer, t58, t59, t60, saddleBrown );
	tri19.draw();

	SDL_RenderPresent(renderer);

	//Leaves1
	DrawFilledTriangle tri20(renderer, t61, t62, t63, darkGreen );
	tri20.draw();

	DrawFilledTriangle tri21(renderer, t64, t65, t66, green );
	tri21.draw();

	DrawFilledTriangle tri22(renderer, t67, t68, t69, forestGreen );
	tri22.draw();

	SDL_RenderPresent(renderer);

	//Leaves2
	DrawFilledTriangle tri23(renderer, t70, t71, t72, darkGreen20 );
	tri23.draw();

	DrawFilledTriangle tri24(renderer, t73, t74, t75, green20 );
	tri24.draw();

	DrawFilledTriangle tri25(renderer, t76, t77, t78, forestGreen20);
	tri25.draw();

	//Leaves3
	DrawFilledTriangle tri26(renderer, t79, t80, t81, darkGreen40 );
	tri26.draw();

	DrawFilledTriangle tri27(renderer, t82, t83, t84, green40 );
	tri27.draw();

	DrawFilledTriangle tri28(renderer, t85, t86, t87, forestGreen40 );
	tri28.draw();

}

void DrawMountain(SDL_Renderer* renderer)
{
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


	//Mountain
	//M1
	DrawFilledTriangle mnt1(renderer, m1, m2, m3, saddleBrown );
	mnt1.draw();	

	//M2
	DrawFilledTriangle mnt2(renderer, m4, m5, m6, chocolateBrown );
	mnt2.draw();	
	
	//M3
	DrawFilledTriangle mnt3(renderer, m7, m8, m9, sandyBrown );
	mnt3.draw();	
	
	//M4
	DrawFilledTriangle mnt4(renderer, m10, m11, m12, saddleBrown );
	mnt4.draw();	
	
	//M5
	DrawFilledTriangle mnt5(renderer, m13, m14, m15, chocolateBrown );
	mnt5.draw();	
	
	//M6
	DrawFilledTriangle mnt6(renderer, m16, m17, m18, saddleBrown );
	mnt6.draw();	
	
	//M9
	DrawFilledTriangle mnt9(renderer, m25, m26, m27, chocolateBrown );
	mnt9.draw();	
	
	//M10
	DrawFilledTriangle mnt10(renderer, m28, m29, m30, saddleBrown );
	mnt10.draw();	
	
	//M7
	DrawFilledTriangle mnt7(renderer, m19, m20, m21, sandyBrown );
	mnt7.draw();	
	
	//M8
	DrawFilledTriangle mnt8(renderer, m22, m23, m24, chocolateBrown );
	mnt8.draw();	

}

void DrawClouds(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color)
{
	
	DrawFilledSemiCircle clud(renderer, center, radius, color, WIDTH, HEIGHT);
	clud.draw();
}

