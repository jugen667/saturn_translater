// test file for do while loop 
int start = 0;
int end = 10;
int sum = 0;

// Starting main
void main()
{
	int i = start;
	do
	{
		// sum = sum+  2 + end*3; // bug here : see known bug 3
		sum += end*3;
		sum += 2;
		i++;
	}while(i < end);
}