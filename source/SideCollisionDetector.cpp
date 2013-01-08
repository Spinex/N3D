#include "naglowek.hpp"

int sprawdzKat(DIRECTION dKierunek)
{
    int angle;
		switch(dKierunek)
		{
			case FORWARD: 
                 angle = 270; 
                 break;
			case BACKWARD: 
                 angle = 90; 
                 break;
			case LEFT: 
                 angle = 180; 
                 break;
			case RIGHT: 
                 angle = 0; 
                 break;
			case LEFT | FORWARD: 
                 angle = 180 + 45; 
                 break;
			case RIGHT | FORWARD: 
                 angle = 0 - 45; 
                 break;
			case LEFT | BACKWARD: 
                 angle = 180 - 45;
                 break;
			case RIGHT | BACKWARD: 
                 angle = 0 + 45;
                 break;
			default:
                 angle = 270;
                 break;
		}
		
		return angle;
    
}    

SideCollisionDetector::SideCollisionDetector()
{
    /*   Skladnia potrzebnej metody
    
      addCubeSceneNode 	( 	f32  	size = 10.0f,
		                        ISceneNode *  	parent = 0,
	                         	s32  	id = -1,
	                         	const core::vector3df &  	position = core::vector3df(0, 0, 0),
	                          	const core::vector3df &  	rotation = core::vector3df(0, 0, 0),
	                          	const core::vector3df &  	scale = core::vector3df(1.0f, 1.0f, 1.0f) 
                          	)     */                                                                      
                                              
                                              
           forwardZnacznik = _menage->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.15f, 1.0f, 1.0f));
           backZnacznik = _menage->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.15f, 1.0f, 1.0f));
           upZnacznik = _menage->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(1.0f, 0.15f, 1.0f));
           downZnacznik = _menage->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(1.0f, 0.15f, 1.0f));
           
           rightZnacznik = _menage->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(1.0f, 1.0f, 0.15f));
           leftZnacznik = _menage->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(1.0f, 1.0f, 0.15f));
           
           
    // -------------------------------------------------------------
    
    forwardAnimator = _menage->createCollisionResponseAnimator
    (_metaSelector, forwardZnacznik, core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));  
    backAnimator = _menage->createCollisionResponseAnimator
    (_metaSelector, backZnacznik, core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));      
    upAnimator = _menage->createCollisionResponseAnimator
    (_metaSelector, upZnacznik, core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0)); 
    downAnimator = _menage->createCollisionResponseAnimator
    (_metaSelector, downZnacznik, core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0)); 
    
    rightAnimator = _menage->createCollisionResponseAnimator
    (_metaSelector, rightZnacznik, core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0)); 
    leftAnimator = _menage->createCollisionResponseAnimator
    (_metaSelector, leftZnacznik, core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));
    
    forwardZnacznik->addAnimator(forwardAnimator);
    downZnacznik->addAnimator(downAnimator);
    backZnacznik->addAnimator(backAnimator);
    upZnacznik->addAnimator(upAnimator);
    leftZnacznik->addAnimator(leftAnimator);
    rightZnacznik->addAnimator(rightAnimator);
           
                                              
                                              
                                              
}   

void SideCollisionDetector::setPosition(Wektor v, float fRotate, DIRECTION dKierunek) 
{
     // Wiem ze implementacja toporna, pisana na kolanie, lenistwo
            
        int angle = sprawdzKat(dKierunek);
        int radius = 5;
        
        Wektor originalCoordinates = v;
     
     // Odpowiednia translacja
        v.Z += radius * cos(( PI * (fRotate - 90 + angle)) / 180);
		v.X += radius * sin(( PI * (fRotate - 90 + angle)) / 180);
		v.Y += 15;
		
		forwardZnacznik->setPosition( v );
		
		// *******************************************************
		
		 v = originalCoordinates;
		 
		 v.Z -= radius * cos(( PI * (fRotate - 90 + angle)) / 180);
		v.X -= radius * sin(( PI * (fRotate - 90 + angle)) / 180);
		v.Y += 15;
		
		backZnacznik->setPosition( v );
		
		// ********************************************************
	
        v = originalCoordinates;
        
        v.Y += 22;
        
        upZnacznik->setPosition( v );
        
        // ********************************************************
        
        v = originalCoordinates;
        
        v.Y += 3;
        
        downZnacznik->setPosition( v );
        
        // *********************************************************
        
        v = originalCoordinates;
        
        angle += 90;
         
        v.Z += radius * cos(( PI * (fRotate - 90 + angle)) / 180);
		v.X += radius * sin(( PI * (fRotate - 90 + angle)) / 180);
		v.Y += 15;
		
		rightZnacznik->setPosition( v );
		
		// *********************************************************
        
        v = originalCoordinates;
                         
        v.Z -= radius * cos(( PI * (fRotate - 90 + angle)) / 180);
		v.X -= radius * sin(( PI * (fRotate - 90 + angle)) / 180);
		v.Y += 15;
		
		leftZnacznik->setPosition( v );
     
}          

void SideCollisionDetector::setRotation(float fRotate, DIRECTION dKierunek)
{
     
     int angle = sprawdzKat(dKierunek);
     
     forwardZnacznik->setRotation( Wektor( 0, fRotate + angle, 0 ) );
     backZnacznik->setRotation(  Wektor( 0, fRotate + angle, 0 )  );
     upZnacznik->setRotation(  Wektor( 0, fRotate + angle, 0 )  );
     downZnacznik->setRotation(  Wektor( 0, fRotate + angle, 0 )  );
     
     rightZnacznik->setRotation(  Wektor( 0, fRotate + angle, 0 )  );
     leftZnacznik->setRotation(  Wektor( 0, fRotate + angle, 0 )  );
     
}  

void SideCollisionDetector::setVisible(bool bV)
{
     
          leftZnacznik->setVisible(bV);
          rightZnacznik->setVisible(bV);
          forwardZnacznik->setVisible(bV);
          backZnacznik->setVisible(bV);
          upZnacznik->setVisible(bV);
          downZnacznik->setVisible(bV);
     
}        

vector<bool> SideCollisionDetector::getCollisionState() 
{
    vector<bool> stany(6, false);
    
  //  for (int i = 0; i < 6; i++) stany[i] = false;
    
    if (leftAnimator->collisionOccurred()) stany[0] = true;
    if (rightAnimator->collisionOccurred()) stany[1] = true;
    if (forwardAnimator->collisionOccurred()) stany[2] = true;
    if (backAnimator->collisionOccurred()) stany[3] = true;
    if (upAnimator->collisionOccurred()) stany[4] = true;
    if (downAnimator->collisionOccurred()) stany[5] = true;
    
    return stany;
     
         
     
}                                             
