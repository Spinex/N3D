#pragma once
#include "precomp.hpp"



class ConsoleManager
{
     private:
                
       vector<core::stringw> messages;
       gui::IGUIFont* font;
       
     public:
        void showMessages();  
        void addMessage(stringw& arg);
        void setMessage(unsigned nID, stringw& arg);
        
        void clear();
        
     public:   
        stringw getMessage(unsigned nID);  
            
     
     public:
        ConsoleManager(IrrlichtDevice* device);
        ~ConsoleManager(){messages.clear();}    
            
            
            
                     
      
      
      
};      
