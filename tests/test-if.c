// test file for if/else 
int start = 0;
int end = 10;
int sum = 0;

// Starting main
void main()
{
	int i = start;
 	if(i)
 	{
 		if(i<2)
 		{ 
	 		if(start)
	 		{
	 			if(!i)
	 			{ 
	 				sum = 255; 
	 			}
	 			sum = 3;
	 		}
	 		else
			{
				if(start > end)
				{
					sum = 4;
				}
				else
				{
					sum = 2;
				}	
			}
 		}
 		else
 		{
 			sum = 1;
 		}
 	}
 	else
 	{
 		sum = 0;
 	}	
	// if(!(i<(2+1))){ } // bug here : see known bug 1
}
