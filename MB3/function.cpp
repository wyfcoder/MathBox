#include "function.h"

Function::Function()
{

}


void Function::setParms(double v)
{
    virtualValues[0]=v;
}


void Function::setParms(vector<double> values)
{
    for(int i=0;i<virtualSize;i++)
        virtualValues[i]=values[i];
}

double Function::calculate(vector<double> v)
{
    setParms(v);
    for(unsigned i=0;i<saves.size();i++)
    {
        if(saves[i].mode==3)
        {
            saves[i].number=virtualValues[saves[i].x];
        }
    }
    return counter(0,saves.size()-1);
}

double Function::counter(unsigned start,unsigned end)
{
    unsigned end2=0;
    unsigned position=start;
    double sum=0;
    if(start==end) return saves[start].number;
    else
    {
       end2=blockEnd(start);
       if(end2!=end)
       {
           sum=counter_bolck(start,end2);
           position=end2+1;
            while(position<end)
           {
               C c=saves[position];
               start=position+1;
               end2=blockEnd(start);
               if(c.chars=='+')
               {
                   sum+=counter_bolck(start,end2);
               }
               else if(c.chars=='-')
               {
                   sum-=counter_bolck(start,end2);
               }
               position=end2+1;
           }
       }
       else
       {
           sum=counter_bolck(start,end);
       }
    }
    return sum;
}

double Function::counter_bolck(unsigned start,unsigned end)
{
    double sum=1;
    if(start==end)
        return saves[end].number;
    else
    {
        int end2=smallBolckEnd(start,end);
        sum=count_smallBlock(start,end2);
        start=end2+1;
        while(start<=end)
        {
            C c=saves[start];
             end2=smallBolckEnd(start+1,end);
            if(c.chars=='*')
            {
             sum*=count_smallBlock(start+1,end2);
            }
            else if(c.chars=='/')
            {
                sum/=count_smallBlock(start+1,end2);
            }
            start=end2+1;
        }
    }
    return sum;
}
int Function::smallBolckEnd(unsigned position,unsigned end)
{
    int K=0;
    while (position<end)
    {
        if(saves[position].mode==2)
        {
            if(K==0&&(saves[position].chars=='*'||saves[position].chars=='/'))
            {
                      return position-1;
            }
            else{
                if(saves[position].chars=='(') K++;
                if(saves[position].chars==')') K--;
            }
        }
        position++;
    }
    return position;
}
int Function::blockEnd(unsigned position)
{
    int K=0;//括号和
    while (position<saves.size()-1)
    {
        C c=saves[position];
        if(c.mode==2)
        {
            if(c.chars=='(')
                K++;
            else if(c.chars==')')
                K--;
            else if(c.chars=='+'||c.chars=='-')
            {
                if(K<=0)
                {
                    position--;
                    break;
                }
            }
            else if(c.chars==','&&K==0)
            {
                position--;
                break;
            }
        }
        position++;
    }
    if(position==saves.size()-1)
    {
        if(K==0&&saves[position].mode==2)
        position--;
    }
    if(K<0)
        position--;

    return position;
}
double Function::count_smallBlock(unsigned start, unsigned end)
{
    double sum=0;
    if(start==end)
        return saves[start].number;
    else
    {
        C c=saves[start];
        if(c.mode==2)
        {
            sum=counter(start+1,end-1);
        }
        else if(c.mode==4)
        {
            if(c.x!=11)
           {
            sum=counter(start+2,end-1);
            switch (c.x)
            {
            case 0:
                sum=sin(sum);
                break;
             case 1:
                sum=cos(sum);
                break;
            case 2:
                sum=tan(sum);
                break;
            case 3:
                sum=1.0/tan(sum);
                break;
            case 4:
                sum=asin(sum);
                break;
             case 5:
                sum=acos(sum);
                break;
            case 6:
                sum=atan(sum);
                break;
            case 7:
                sum=atan(1.0/sum);
                break;
            case 8:
                sum=log(sum);
                break;
             case 9:
                sum=log(sum)/log(10);
                break;
              case 10:
                sum=exp(sum);
                break;
               case 12:
                sum=sqrt(sum);
                break;
            }
           }
           else
            {
                unsigned j=start+2;
                int K=1;
                for(;j<end;j++)
                {    if(saves[j].mode==2)
                    {
                        if(K==1&&saves[j].chars==',')
                         break;
                        if(saves[j].chars=='(')
                            K++;
                        else if(saves[j].chars==')')
                            K--;
                    }
                }
                sum=counter(start+2,j-1);
                sum=pow(sum,counter(j+1,end-1));
            }
       }
        return sum;
    }
}

