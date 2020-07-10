/*  |=================================|
    | SHIPYARD PROJECT                |	|                                 |
    |                                 |
    | Demonstrates the working of a   |
    | shipyard by allowing input of   |
    | new ship, viewing its contents  |
    | and storing the values in a     |
    | file.                           |
    | ENJOY!                          |
    |=================================|
*/
#include<fstream>
#include<ctype.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<graphics>
#include<stdlib.h>

#include<HOME.H>

const int size = 7;
int num = -1;
int i=0,j=0;

//--------------------------------------------------------------------------------
//CLASS CARGO
class CARGO
{
   public:
   int Cont_num;
   int No_of_items;
   char contents[10][10];
   void Cont_enter(int,int);
};

void CARGO::Cont_enter(int a,int b)
 {
     Cont_num=a;
     No_of_items=b;
     cout<<"Enter the contents of the container:\n";
     for(j=0;j<No_of_items;j++)
      {
	cout<<"Item number "<<j+1<<": ";
	gets(contents[j]);
      }
 }

//--------------------------------------------------------------------------------
//CLASS SHIP
class SHIP
{  public:
   char Name[20];
   char ID[10];
   CARGO cargo[7];
   char DOA[10];
   int No_cargo;
  //public
   void arrival();        //TO INSERT
   void QSdisplay();        //TO DISPLAY IN QUEUE
   void Cargo_enter(int); //TO ENTER CARGO DETAILS

};

//CLASS FUNCTIONS
void SHIP::Cargo_enter(int num)
{
   for(i=0;i<num;i++)
   {
      int num1=0,num2=0;
      clrscr();
      cout<<"For CONTAINER "<<i+1<<":\n";
      cout<<"Enter the container number: ";
      cin>>num1;
      cout<<"Enter the number of items(max 10): ";
      cin>>num2;
      cargo[i].Cont_enter(num1,num2);
   }

}
void SHIP::arrival()
  {
     int check_date;
     clrscr();
     cout<<"Name of the ship: ";
     gets(Name);
     cout<<"Ship ID: ";
     gets(ID);
     do
     {
	check_date=0;
	clrscr();
	cout<<"Enter date of arrival(dd/mm/yy): ";
	gets(DOA);
	 for(int dte=0;dte<8;dte++)
	   {
	      if((DOA[dte]>=0)&&(DOA[dte]<=9))
		{
		  continue;
		}
	      if((DOA[2]=='/')&&(DOA[5]=='/'))
		{
		  continue;
		}
	       else
		  {
		     check_date=1;
		     break;
		  }
	   }
	   if(check_date==1)
	   {
	     cout<<"\nPlease enter the date in the correct  format!(press any key to continue)";
	     getch();
	   }
     }while(check_date==1);
     //puts(DOA);
     //getch();
     cout<<"Enter the number of containers(max 6): ";
     cin>>No_cargo;
     Cargo_enter(No_cargo);

  }
void SHIP::QSdisplay()
  {
    cout<<"SHIP NAME: ";puts(Name);
    cout<<"ntSHIP ID: ";puts(ID);
    cout<<"\nDATE OF ARRIVAL: "; puts(DOA);
  }

//--------------------------------------------------------------------------------------
//GRAPHICS FUNCTION

void SHIP_DISPLAY(SHIP S)

{   int nb;
   nb=S.No_cargo;
    char str[10];
  if(nb>6)
   {
	 cout<<"";
	 getch();
	 return;
   }

  int gd = DETECT,gm;
  detectgraph(&gd,&gm);
  initgraph(&gd, &gm, "C:\TCC");

  int poly1[10];
  int poly2[10];
   setcolor(0);
   setfillstyle(10,4);

   /* 1st vertex */
   poly1[0] = 20;
   poly1[1] = 90;
   /*2nd vertex*/
   poly1[2] = 149;
   poly1[3] = 90;
   /* 3rd */
   poly1[4] = 149;
   poly1[5] = 290;
   /* Closing the polygon*/
   poly1[6] = poly1[0];
   poly1[7] = poly1[1];
   /* draw the polygon */
   fillpoly(4, poly1);

   /* Draw the bar*/
   bar(150, 90, 450,290);

   /*draw 2nd triangle */
   poly2[0] = 451;
   poly2[1] = 90;

   poly2[2] = 580;
   poly2[3] = 90;

   poly2[4] = 451;
   poly2[5] = 290;

   poly2[6] = poly2[0];
   poly2[7] = poly2[1];
   fillpoly(4, poly2);

   /*CONTAIN boxes*/
  setcolor(7);
  setfillstyle(0,0);

  //1st line of containers
  bar3d(175,110,225,160, 5, 1);
  bar3d(275,110,325,160, 5, 1);
  bar3d(375,110,425,160, 5, 1);

  //2nd line of containers
  bar3d(175,210,225,260, 5, 1);
  bar3d(275,210,325,260, 5, 1);
  bar3d(375,210,425,260, 5, 1);


  //INFO
   int x=180;
   int y=0;
  char A[7][10]={"BOX 1","BOX 2","BOX 3","BOX 4","BOX 5","BOX 6","EMPTY"};
  for(int i=1;i<nb+1;i++)
  {
   if(i%4==0)
   {
   x=180;y=100 ;
   }
   itoa(S.cargo[i-1].Cont_num,str,10);
   outtextxy(x,y+125,A[i-1]);
   outtextxy(x,y+135,"ID:");
   outtextxy(x,y+145,str);
   x+=100;
  }


  for(i = nb+1;i<=6;i++)
   {
	 if(i%4==0)
   {
   x=180;y=100 ;
   }
   outtextxy(x,y+125,A[6]);
   x+=100;
   }
  char *head="SHIP NAME: ";
  settextstyle(0,0,2);
  outtextxy(getmaxx()/2-textwidth(head),getmaxy()/7,head);
  outtextxy((getmaxx()/2),getmaxy()/7,S.Name);

  x=-150;
  y=310;
  int y1;
  settextstyle(1,0,1);

  for(i=0;i<nb;i++)
  {
     x+=150;
     y1=y+3;
     outtextxy(x,y,A[i]);
     outtextxy(x,y+10,"CONTENTS: ");
     for(int l=0; l<(S.cargo[i].No_of_items);l++)
      {
	 y1=y1+20;
	 outtextxy(x,y1,(S.cargo[i].contents[l]));

      }

  }

  getch();
  cleardevice();
  closegraph();
  clrscr();
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------


//GLOBAL VARIABLES AND FUNCTIONS
SHIP SHIPS[size];
int front=-1,rear=-1,res;

void Write_to_file(SHIP S)
   {
      fstream file;
      file.open("ship.txt",ios::in|ios::out|ios::app);
      file.write((char *) &S,sizeof(S));
      file.close();

   }

void Read_from_file()
   {
	  clrscr();
	  SHIP S;
	  fstream file;
	  front=0;
	  rear=-1;
	  file.open("ship.txt",ios::in|ios::out);
	  while(!file.eof())
	   {
	  file.read((char *) &S,sizeof(S));
		 rear++;
		 SHIPS[rear]=S;
	   }
	  rear--;
   }

int insert(SHIP SHIPS[])        //INSERTING SHIP IN QUEUE
 {
   if(front==size-1)
	  {
	return -1;
	  }
   else if(rear==-1)
	 {
	   front=rear=0;
	   SHIPS[rear].arrival();
	   //Write_to_file(SHIPS[rear]);
	 }
	else
	 {
	  rear++;
	  SHIPS[rear].arrival();
	 }
	 return 0;
 }

void Qdisplay(SHIP SHIPS[],int front,int rear)
 {
	 clrscr();
	 if(front==-1)
	   {
	      cout<<"There are no SHIPS in the shipyard";
	      return;
	   }
	 cout<<"The Queue is:\n\n";
	 for(int m=front;m<rear;m++)
	  {
	cout<<m+1<<".\n";
	SHIPS[m].QSdisplay();
	cout<<"\n\t/\\"<<endl;
	cout<<"\t||"<<endl;
	cout<<"\t||"<<endl;
	  }
	cout<<rear+1<<".\n";
	  SHIPS[rear].QSdisplay();
	  cout<<endl;
 }

void Ship_depart()
{
	if(front==-1)
	  {
	cout<<"ALL SHIPS HAVE LEFT THE PORT";
	return;
	  }
	else
	{
	   if(front==rear)
	 {
	   cout<<"The SHIP " <<SHIPS[front].Name<<" has departed!\n";
	   front=rear=-1;

	 }
	   else
	{
	  cout<<"The SHIP " <<SHIPS[front].Name<<" has departed!\n";
	  front++;
	}
	}
}


void Search(char *id)
{
	   int P1;
	   int C1;
	for(int u=front;u<=rear;u++)
	{

	 P1=strcmpi((SHIPS[u].ID),id);


	 if(P1==0)
		{
		SHIP_DISPLAY(SHIPS[u]);
		  C1=0;
		  break;
		}
	 else
	 {
		C1=1;
	 }

	}
	if(C1==1)
	{
	 cout<<"SHIP NOT FOUND :(";
	}


}
//----------------------------------------------------------------------------------
void MENU()
{
  clrscr();
  int opt;
  cout<<"What would you like to do?:\n1.Ship Arrival\n2.Display Queue\n3.Search Ship\n4.Ship Departure\n5.Save data\n6.Get data\n7.EXIT\nPlease choose your option: ";
  cout<<"\nPlease enter a number: ";
  cin>>opt;
  switch(opt)
   {
	 case 1:
		{
		 res=insert(SHIPS);
		 if(res==-1)
		  { cout<<"OVERFLOW! Aborting...\n";
			exit(1);
		  }
		 else
		 {
		   cout<<"\n\nDON'T FORGET TO SAVE YOUR DATA(option 5) BEFORE LEAVING!";
		 }
		break;
		}
	 case 2:
		{
		 Qdisplay(SHIPS,front,rear);
		 break;
		}

     case 3:
	    {
		     char *id;
		     clrscr();
		     cout<<"Enter the ID of the SHIP: ";
		     gets(id);
		     Search(id);
		     break;
	    }

     case 4:
	    {
		  Ship_depart();
		  break;
	    }
     case 5:
		{
		remove("ship.txt");
		for(int k=front;k<=rear;k++)
		{
		 //cout<<k;
		 Write_to_file(SHIPS[k]);
		}
		 break;
	    }
     case 6:
	    {
		char R;
		clrscr();
		cout<<"WARNING ALL UNSAVED DATA WILL BE LOST!!\n\nWould you like ot continue?: ";
		cin>>R;
		if((R=='y')||(R=='Y'))
		   {
		     Read_from_file();
		    cout<<"\n\nDATA succesfully taken from file";
		   }
		else
		  {
		     cout<<"\n\nABORTED";
		  }
		break;
	    }
     case 7:
	    {
	     exit(1);
	    }
     default:
	    {
	      cout<<"\n\nPLEASE CHOOSE ONE OF THE GIVEN OPTIONS!";
	      break;
	    }
   }
}

//-------------------------------------------------------------------------------------
void main()
{


   char flag;
   clrscr();
   HOME();
   cout<<"WELCOME TO A.S.A SHIPYARD DATABASE!!\nPress any key to enter";
   getch();
   for(;;)
   {
   clrscr();
   MENU();
   cout<<"\n\nPress any key to continue";
   getch();
   }
}