#include "s_value_trans.h"
//Find the object in chars
int find_object_in_chars(unsigned char *s,unsigned char o)
{
	int l = 0;
	while(*s != o && *s != '\0')
	{
		s++;
		l++;
	}
	return l;
}
//Get rid of head
//If it's a negative num
void char_2_float_get_rid_of_head(unsigned char **s)
{
	**s = '0';
	
}
//Trans char to int
int char_2_int(unsigned char * s)
{
	int p_n_sign = 1;
	int num = 0,temp_num = 1;
	int i = 0,j = 0;
	int len = 0;
	
	if(s[0] == '-')
	{
		p_n_sign = 0;
	}
	else if(s[0] == ' ')
	{
		p_n_sign = 2;	//Sometimes there will be some symbol you don'twant
	}
	len = find_object_in_chars(s,'\0');

	
	if(p_n_sign == 1)
	{
		//Get the int part
		for(i = len; i > 0;i--)
		{
			for(j = 0; j < i-1; j++)
			{
				temp_num *= 10;
			}
			temp_num *= (s[len - i] - 48);		//Without this you will not get a correct value

			num += temp_num;
			temp_num = 1;
		}
	}
	else if(p_n_sign == 0)
	{
	    //Get the int part
		for(i = len; i > 1;i--)
		{
			for(j = 0; j < i-2; j++)
			{
				temp_num *= 10;
			}
			temp_num *= (s[len - i + 1] - 48);		//Without this you will not get a correct value
			

			num += temp_num;
			temp_num = 1;
		}
		num *= (-1);
	}
	else
	{
		//Get the int part
		for(i = len; i > 1;i--)
		{
			for(j = 0; j < i-2; j++)
			{
				temp_num *= 10;
			}
			temp_num *= (s[len - i + 1] - 48);		//Without this you will not get a correct value
			

			num += temp_num;
			temp_num = 1;
		}
	}
		
	
	
	return num;	
}
//Trans char to float
float char_2_float(unsigned char * s)
{
	int p_n_sign = 1;
	float num = 0.0,temp_num = 1.0;
	int i = 0,j = 0;
	int dot_p = 0;
	int len = 0;
	
	if(s[0] == '-')
	{
		p_n_sign = 0;
	}
	else if(s[0] == ' ')
	{
		p_n_sign = 2;	//Sometimes there will be some symbol you don'twant
	}
	dot_p = find_object_in_chars(s,'.');
	len = find_object_in_chars(s,'\0');

	if(dot_p != len)
	{
		if(p_n_sign == 1)
		{
			//Get the int part
			for(i = dot_p; i > 0;i--)
			{
				for(j = 0; j < i-1; j++)
				{
					temp_num *= 10;
				}
				temp_num *= (s[dot_p - i] - 48);		//Without this you will not get a correct value
	
				num += temp_num;
				temp_num = 1.0;
			}
			//Get the dot part
			for(i = dot_p + 1; i < len;i++)
			{
				for(j = dot_p; j < i; j++)
				{
					temp_num /= 10.0;
				}
				
				
				temp_num *= (s[i] - 48);		//Without this you will not get a correct value
	
				num += temp_num;
				temp_num = 1.0;
			}
		}
		else if(p_n_sign == 0)
		{
			//Get the int part
			for(i = dot_p; i > 1;i--)
			{
				for(j = 0; j < i-2; j++)
				{
					temp_num *= 10;
				}
				temp_num *= (s[dot_p - i + 1] - 48);		//Without this you will not get a correct value
				
	
				num += temp_num;
				temp_num = 1.0;
			}
			//Get the dot part
			for(i = dot_p + 1; i < len;i++)
			{
				for(j = dot_p; j < i; j++)
				{
					temp_num /= 10.0;
				}
				
				
				temp_num *= (s[i] - 48);		//Without this you will not get a correct value
	
				num += temp_num;
				temp_num = 1.0;
			}
			num *= (-1.0);
		}
		else
		{
			//Get the int part
			for(i = dot_p; i > 1;i--)
			{
				for(j = 0; j < i-2; j++)
				{
					temp_num *= 10;
				}
				temp_num *= (s[dot_p - i + 1] - 48);		//Without this you will not get a correct value
				
	
				num += temp_num;
				temp_num = 1.0;
			}
			//Get the dot part
			for(i = dot_p + 1; i < len;i++)
			{
				for(j = dot_p; j < i; j++)
				{
					temp_num /= 10.0;
				}
				
				
				temp_num *= (s[i] - 48);		//Without this you will not get a correct value
	
				num += temp_num;
				temp_num = 1.0;
			}
		}
		
	}
	else
	{
		
		if(p_n_sign == 1)
		{
			//Get the int part
			for(i = dot_p; i > 0;i--)
			{
				for(j = 0; j < i-1; j++)
				{
					temp_num *= 10;
				}
				temp_num *= (s[dot_p - i] - 48);		//Without this you will not get a correct value

				num += temp_num;
				temp_num = 1.0;
			}
		}
		else if(p_n_sign == 0)
		{
		    //Get the int part
			for(i = dot_p; i > 1;i--)
			{
				for(j = 0; j < i-2; j++)
				{
					temp_num *= 10;
				}
				temp_num *= (s[dot_p - i + 1] - 48);		//Without this you will not get a correct value
				
	
				num += temp_num;
				temp_num = 1.0;
			}
			num *= (-1.0);
		}
		else
		{
			//Get the int part
			for(i = dot_p; i > 1;i--)
			{
				for(j = 0; j < i-2; j++)
				{
					temp_num *= 10;
				}
				temp_num *= (s[dot_p - i + 1] - 48);		//Without this you will not get a correct value
				
	
				num += temp_num;
				temp_num = 1.0;
			}
		}
		
	}
	return num;	
}
//Trans the char to float
//*s for the char
//i1 for the first num
//i2 fot the last num
//eg. *s = "wo1234";
//The i1 = 2 and i2 = 5
float char_2_float_with_index(unsigned char *s,unsigned char i1,unsigned char i2)
{
	unsigned char i = 0;
	unsigned char ctemp[20];
	for(;i < i1;i++)
	{
		s++;
	}
	for(;i <= i2;i++)
	{
		ctemp[i - i1] = *s;
		s++;	
	}

	ctemp[i - i1] = '\0';
	return (char_2_float(ctemp));
}
//Trans the char to float
//*s for the char
//c1 for the first num's fronter char
//c2 fot the last num's backer char
//eg. *s = "wo1234";
//The c1 = 'o' and c2 = '\0'
float char_2_float_with_char(unsigned char *s,unsigned char c1,unsigned char c2)
{
	unsigned char i = 0;
	unsigned char i1,i2;
	i1 = find_object_in_chars(s,c1);
	i2 = find_object_in_chars(s,c2);

	unsigned char ctemp[20];
	for(;i <= i1;i++)
	{
		s++;
	}
	for(;i < i2;i++)
	{
		ctemp[i - i1 -1] = *s;
		s++;	
	}

	ctemp[i - i1 - 1] = '\0';
	return (char_2_float(ctemp));
}


//Trans the char to int
//*s for the char
//i1 for the first num
//i2 fot the last num
//eg. *s = "wo1234";
//The i1 = 2 and i2 = 5
int char_2_int_with_index(unsigned char *s,unsigned char i1,unsigned char i2)
{
	unsigned char i = 0;
	unsigned char ctemp[9];
	for(;i < i1;i++)
	{
		s++;
	}
	for(;i <= i2;i++)
	{
		ctemp[i - i1] = *s;
		s++;	
	}

	ctemp[i - i1] = '\0';
	return (char_2_int(ctemp));
}
//Trans the char to int
//*s for the char
//c1 for the first num's fronter char
//c2 fot the last num's backer char
//eg. *s = "wo1234";
//The c1 = 'o' and c2 = '\0'
int char_2_int_with_char(unsigned char *s,unsigned char c1,unsigned char c2)
{
	unsigned char i = 0;
	unsigned char i1,i2;
	i1 = find_object_in_chars(s,c1);
	i2 = find_object_in_chars(s,c2);

	unsigned char ctemp[9];
	for(;i <= i1;i++)
	{
		s++;
	}
	for(;i < i2;i++)
	{
		ctemp[i - i1 -1] = *s;
		s++;	
	}

	ctemp[i - i1 - 1] = '\0';
	return (char_2_int(ctemp));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Translate int to char
unsigned char * int_2_char(int tnum)
{
	static unsigned char int_2_char_buf[10];
	unsigned char first_not_zero = 0;
	int k;
	unsigned char p_n_sign = 1;		//1 for positive num and 0 for negative
	if(tnum < 0)
	{
		p_n_sign = 0;
	}
	//For positive num
	if(p_n_sign)
	{
		k = 9;
		do{
	      int_2_char_buf[k] = tnum%10 + 48; //without "+48" you can't get a right result
	       //uart_val[k] = n%10 + 48; //without "+48" you can't get a right result
	       tnum=tnum/10;
	       k--;
	    }while(k >= 0);
		
		//Find the first num which is not zero,certainly,we should keep at least one if the arry just contains '0'
		for(;first_not_zero < 9;first_not_zero++)		
		{
			if(int_2_char_buf[first_not_zero] != 48)	//In char type,0x30 means zero
					break;		
		}
		//Reassigned the arry
		for(k = 0;first_not_zero < 10;)//first_not_zero++)
		{
			int_2_char_buf[k++] = int_2_char_buf[first_not_zero++];
		}
		//Creat a end
		int_2_char_buf[k] = '\0';
	}
	//For negative num
	else
	{
		tnum *= -1;
		k = 9;
		do{
	      int_2_char_buf[k] = tnum%10 + 48; //without "+48" you can't get a right result
	       //uart_val[k] = n%10 + 48; //without "+48" you can't get a right result
	       tnum=tnum/10;
	       k--;
	    }while(k >= 0);
		
		//Find the first num which is not zero,certainly,we should keep at least one if the arry just contains '0'
		for(first_not_zero = 1;first_not_zero < 9;first_not_zero++)		
		{
			if(int_2_char_buf[first_not_zero] != 48)	//In char type,0x30 means zero
					break;		
		}
		//Reassigned the arry
		for(k = 1;first_not_zero < 10;)//first_not_zero++)
		{
			int_2_char_buf[k++] = int_2_char_buf[first_not_zero++];
		}
		//Creat a end
		int_2_char_buf[k] = '\0';
		int_2_char_buf[0] = '-';
	}
	

	return int_2_char_buf;
}

//Get the length of int
unsigned char get_int_length(int i)
{
	unsigned char k = 0;
	while(i > 0)
	{
		k++;
		i /= 10;
	}
	return k;
} 

//Send it to the buf
void float_2_char_valuetrans(unsigned char *s1,int *s1_len,unsigned char *s2)
{
  int len = *s1_len; 
  while(*s2 != '\0')
  {
    s1[len++] = *s2;
    s2++;
  }
  *s1_len = len;
  //*s1 = '\0';
}

//Translate float to char
unsigned char * float_2_char(float f,unsigned char accuracy)
{
	static unsigned char float_2_int_buf[32];
	int float_2_int_len = 0;
	int i = 0;
//	unsigned char p_n_sign = 1;		//1 for positive num and 0 for negative
//	if(f < 0)
//	{
//		p_n_sign = 0;
//	}
	//unsigned char f_len = 32;
	int tp = (int)f;	
	float_2_char_valuetrans(float_2_int_buf,&float_2_int_len,int_2_char(tp));
	//f_len -= get_int_length(tp);			//I designed this to calculate,but I found it's not suit.
	if(f < 0)
	{
		f *= -1.0;
		tp *= -1;
	}
	
	f -= tp;				//Get the rest value
	for(tp = 0;tp < accuracy;tp++)
	{
		f *= 10;
	}
	tp = (int)f;
	//float_2_char_valuetrans(".");		//Maybe not use function will be fast
	float_2_int_buf[float_2_int_len++] = '.';
	for(;get_int_length(tp)+i < accuracy;i++)
	{
		float_2_int_buf[float_2_int_len++] = '0';
	}
	float_2_char_valuetrans(float_2_int_buf,&float_2_int_len,int_2_char(tp));
	float_2_int_buf[float_2_int_len++] = '\0';
	return float_2_int_buf;
}
