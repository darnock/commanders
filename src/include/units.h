// units.h

#ifndef _UNITS_H
#define _UNITS_H
	
	enum direction {dup,ddown,dleft,dright,dupleft,dupright,ddownleft,ddownright}; 


	void inicjuj(int Tteam, unsigned short Tshield);
	void sprzatnij();

class czlowieki		//not only mens but also other like tanks maby
	{
	public:
		int x,y; 		//men position on the screen;
		int color;		//who's side are ya?
		int oldcolor; 		//kolor tla
		unsigned char type;			
		
		void hide();			//hides man from screen
		void show();			//shows man on the screen 
		void move(direction dir);	//moves man to one side; up, down, left, right and upleft, upright, downleft, downright 
		void testinit(int nx, int ny, int ncolor);
	};

class szeregowy : public czlowieki	        //primary unit
	{
	private:
	 	unsigned short int shield; 	//yes. we have shields. Number mean how strong is shield: 0 - no shield, 65535 - full shield
		float shield_modificator;	//coefficient, 1.0f...4.0f <- how good is shield  
		unsigned char gun;	//1 - knife, 2 - pistol, 3 - ak40, 4 - flame, 5 - grenate, etc..
	public:
		void init(int nx, int ny, int ncolor);		//cosntructor 
		void sprzatnij(); 	//destructor
                unsigned int hp;        //zycie	
        };
class bullet 
	{
	private:
		int x,y; 		//bullet's screen position
		float speed; 		//comment: no comments :D
		int color; 		 	
	public: 
		
	};


	//void szeregowy::inicjuj(int Tteam, unsigned short Tshield);
#endif
