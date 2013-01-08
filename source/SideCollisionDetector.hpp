#pragma once

typedef scene::ISceneNodeAnimatorCollisionResponse AnimatorKolizji;

class SideCollisionDetector 
{
      
      private:
         ISceneNode* leftZnacznik;
         ISceneNode* rightZnacznik;
         ISceneNode* forwardZnacznik;
         ISceneNode* backZnacznik;
         ISceneNode* upZnacznik;
         ISceneNode* downZnacznik;
         
         AnimatorKolizji* leftAnimator;
         AnimatorKolizji* rightAnimator;
         AnimatorKolizji* forwardAnimator;
         AnimatorKolizji* backAnimator;
         AnimatorKolizji* upAnimator;
         AnimatorKolizji* downAnimator;
         
         float fRotation;
         
         Wektor relativeDetectorPosition;
         
         
         
      public: 
              
          void setRotation(float fRotate, DIRECTION dKierunek);
          void setPosition(Wektor v, float fRotate, DIRECTION dKierunek);  
          void setVisible(bool bV);  
          
      public:
             
          vector<bool> getCollisionState();       
                  
      
      public:            
          SideCollisionDetector();    
          ~SideCollisionDetector() {}       
              
      
      
      
};      
