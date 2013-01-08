#include "naglowek.hpp"

void ConsoleManager::showMessages() 
{
      /*
      virtual void irr::gui::IGUIFont::draw 	( 	const core::stringw &  	text,
		const core::rect< s32 > &  	position,
		video::SColor  	color,
		bool  	hcenter = false,
		bool  	vcenter = false,
		const core::rect< s32 > *  	clip = 0 
	) 
    */
     
      unsigned nY = 50;     
     
      core::stringw fstr;
      
      
    for (int i = 0; i < static_cast<int>(messages.size()); i++) 
    {  
      
      fstr = messages[i];        
                      
      if (font)
      font->draw(fstr.c_str(),
      core::rect<s32>(50,nY,600,nY + 50),
      video::SColor(255,255,255,255));
      
      nY += 10;
    }   
     
}

ConsoleManager::ConsoleManager(IrrlichtDevice* device) 
{
   font = device->getGUIEnvironment()->getBuiltInFont();                                              
                                               
}                                               

void ConsoleManager::addMessage(stringw& arg)
{
     
     messages.push_back(arg);
     
}     

void ConsoleManager::setMessage(unsigned nID, stringw& arg)
{
     
     if (nID < static_cast<int>(messages.size())) messages[nID] = arg;
             
            
     
}     

void ConsoleManager::clear() 
{
     
     
}   

stringw ConsoleManager::getMessage(unsigned nID)
{
       stringw str = "!OutOfBound!"; 
        
       if (nID < static_cast<int>(messages.size())) return messages[nID];
       else return str; 
        
}              
