#include "compliedeals.h"
/*
function:4
number:1
charNumber:3
operator:2 + - * / ( ) ,
*/
ComplieDeals::ComplieDeals()
{
    className.append("Matrix");//0
    className.append("Number");//1
    className.append("Function");//2
    functionName.push_back("Sin");
    functionName.push_back("Cos");
    functionName.push_back("Tan");
    functionName.push_back("Cot");
    functionName.push_back("Asin");
    functionName.push_back("Acos");
    functionName.push_back("Atan");
    functionName.push_back("Acot");
    functionName.push_back("Ln");
    functionName.push_back("Log");
    functionName.push_back("Exp");
    functionName.push_back("Pow");
    functionName.push_back("Sqrt");
}

int ComplieDeals::getClassMode(QString text)
{
    int classMode=-1;
    position=0;
    inputText(text);
    for(int i=0;i<className.size();i++)//匹配，确定类的种类
    {
        int m;
        for(m=0;m<className[i].size();m++)
        {
         if(text[m]!=className[i][m]&&m<text.size())
             break;
        }
        if(m==className[i].size()&&text[m]==' '&&text.size()>m)
        {
            classMode=i;
            position=m;
            break;
        }
    }
    return classMode;
}

QString ComplieDeals::checkVirtulName()
{
    QString name;
    QChar c;
    position++;
    if(position>=text.size())
        return "";
    c=text[position];
    if(!(c>='a'&&c<='z'))
        return "";
    name.append(c);
    position++;
    while(text[position]!=';'&&text[position]!='='&&text[position]!='(')
    {
        c=text[position];
        if((c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_')
        {
            name.append(c);
        }
        else
        {
            return "";
        }
        position++;
    }
    virtualName=name;
    return name;
}


void ComplieDeals::inputText(QString text)
{
    this->text=text;
}


QString ComplieDeals::setVirtualName()
{
    if(virtualName.size()!=0)
        virtualName="";
    position=0;

    QChar c;

    while(text[position]!=';'&&text[position]!='='&&text[position]!='(')
    {
        c=text[position];
        if((c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_')
        {
            virtualName.append(c);
        }
        else
        {
            virtualName="";
        }
        position++;
    }
    return virtualName;
}

bool ComplieDeals::isExpression()
{
    bool is=true;
    for(int i=0;i<text.size();i++)
    {
        if(text[i]=='=')
        {
            is=false;
            break;
        }
    }
    return is;
}
//Number 类的编译 ---------------------------------------------------------------------------------
bool ComplieDeals::helpNumberBuilder(vector<Number> lists)
{
    if(numbers.size()!=0)
        numbers.clear();
    for(unsigned i=0;i<lists.size();i++)
    {
        numbers.push_back(lists[i]);
    }
    if(position==text.size()-1)
    {
        if(isExit())
        value=numbers[virtualPosition].value;
        else
        value=0;
        return true;
    }
    else
    {
       if(text[position]!='=')
           return false;
       else
       {
           position++;
           save();
           bool isOk=isWrong();
           if(!isOk)
           return false;
           dealHeader();
           value=counter(0,saves.size()-1);
           return true;
       }
    }
}
bool ComplieDeals::isExit()
{
    for(unsigned i=0;i<numbers.size();i++)
        if(virtualName==numbers[i].name)
        {
            virtualPosition=i;
            return true;
        }
    return false;

}
bool ComplieDeals::save()
{
    if(saves.size()!=0)
        saves.clear();
    while (position<text.size()-1)
    {
        C c=returnMode(text[position]);
        if(c.isTrue)
        {
            saves.push_back(c);
        }
        else
        {
                return false;
        }
    }
    return true;}
ComplieDeals::C ComplieDeals::returnMode(QChar m)
{
    C c;
    c.isTrue=false;
    if(m>='0'&&m<='9')
    {
        if(isNumber())
        {
            c.isTrue=true;
            c.mode=1;
            c.number=saveNumber;
            return c;
        }
    }
   else if(isOpertate(m))
    {
        c.isTrue=true;
        c.mode=2;
        c.chars=m;
        position++;
        return c;
    }
    else
    {
     QString name=getName();
    if(m>='A'&&m<='Z')
    {
        for(unsigned i=0;i<functionName.size();i++)
            if(functionName[i]==name)
            {
                c.isTrue=true;
                c.mode=4;
                c.x=i;
            }
    }
    else if(m>='a'&&m<='z')
    {
        for(unsigned i=0;i<numbers.size();i++)
        {
            if(numbers[i].name==name)
            {
                c.isTrue=true;
                c.mode=3;
                c.number=numbers[i].value;
            }
        }
    }
    }
    return c;
}

QString ComplieDeals::getName()
{
    QString name;
    while(position<text.size()-1&&!isOpertate(text[position]))
    {
        name.append(text[position]);
        position++;
    }
    return name;
}
bool ComplieDeals::isOpertate(QChar m)
{
    if(m=='*'||m=='+'||m=='/'||m=='-'||m=='('||m==')'||m==',')
       return true;
       return false;
}
bool ComplieDeals::isNumber()
{
    QString number="";
    bool isOK;
     while(position<text.size()-1&&!isOpertate(text[position])) {
         number.push_back(text[position]);
         position++;
     }
     saveNumber=number.toDouble(&isOK);
     return isOK;
}



bool ComplieDeals::isWrong()
{
    C pre=saves[0];
    C next;
    int count=0;
    if(pre.mode==2)
    {
        if(pre.chars!='+'&&pre.chars!='-'&&pre.chars!='(')
           return false;
        if(pre.chars=='(')
            count++;
    }
    unsigned i=1;
    bool isGoOn=true;
    bool sign=false;
    while (i<saves.size()) {
        next=saves[i];
        switch (pre.mode) {
        case 1:
        case 3:
            isGoOn=PreNC(next);
            break;
         case 2:
           {
            isGoOn=PreOP(pre,next);
           }
            break;
         case 4:
            if(pre.x!=11)
            isGoOn=PreFU(next);
            else
            {
                isGoOn=PowCheck(i);
                sign=true;
            }
           break;
        default:
            break;
        }

        if(!isGoOn)
        return false;
        if(sign)
        {
            sign=false;
            pre=saves[i];
        }
        else
       {
            pre=next;
        if(pre.mode==2)
        {
            if(pre.chars=='(')
                count++;
            else if(pre.chars==')')
                count--;
        }
      }
        i++;
    }

    if(count!=0)
        return false;

    if(pre.mode==2)
    {
        if(pre.chars!=')')
          return false;
    }
    return true;
}
bool ComplieDeals::PreNC(C next)
{
    if(next.mode==2&&next.chars!='(')
    {
     return true;
    }
    return false;
}
bool ComplieDeals::PreFU(C next)
{

    if(next.mode!=2&&next.chars!='(')
        return false;
    return true;
}
bool ComplieDeals::PreOP(C pre, C next)
{
    if(pre.chars=='('||pre.chars==')')
{
    if(pre.chars=='(')
    {
        if(next.mode==2)
        {
            if(next.chars!='+'&&next.chars!='-'&&next.chars!='(')
            return false;
        }
    }
    else
    {
        if(next.mode==2)
        {
            if(next.chars=='(')
            return false;
        }
    }
}
    else if(pre.chars==',')
    {
        return false;
    }
    else
    {
        if(next.mode==2)
        {
            if(next.chars!='(')
                return false;
        }
    }//+ - * /
    return true;
}
bool ComplieDeals::PowCheck(unsigned &position)
{
    C pre=saves[position];
    C next;
    bool isGoOn=true;
    if(pre.mode!=2&&pre.chars!='(')
    {
        return false;
    }
    int count=1;
    int dots=0;
    position++;
    do
   {
        if(position>saves.size()-1)
            return false;
        next=saves[position];
       switch (pre.mode) {
        case 1:
        case 3:
            isGoOn=PreNC(next);
            break;
        case 4:
            if(pre.x!=11)
            isGoOn=PreFU(next);
            else
            {
                isGoOn=PowCheck(position);
                if(!isGoOn)
                {
                    return false;
                }
                else
                {
                    if(position<saves.size())
                   {
                    position++;
                    next=saves[position];
                    }
                    else
                    {
                        position++;
                        continue;
                    }
                }
            }
            break;
        case 2:
            if(pre.chars==',')
            {
                dots++;
                if(next.mode==2)
                {
                    if(next.chars!='+'||next.chars!='-'||next.chars!='(')
                        return false;
                }
            }
            else
            {
                isGoOn=PreOP(pre,next);
            }
            break;
        default:
            break;
        }
        if(!isGoOn)
            return false;
        if(next.mode==2)
        {
            if(next.chars=='(')
            count++;
        else if(next.chars==')')
            count--;
        }
        pre=next;
        if(count==0)
            break;
        position++;
   }
    while(true);
    if(dots!=1)
    return false;
    return true;
}

double ComplieDeals::counter(unsigned start,unsigned end)
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

double ComplieDeals::counter_bolck(unsigned start,unsigned end)
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
int ComplieDeals::smallBolckEnd(unsigned position,unsigned end)
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
int ComplieDeals::blockEnd(unsigned position)
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
                if(K==0)
                {
                    position--;
                    break;
                }
            }
        }
        position++;
    }
    if(position==saves.size()-1)
    {
        if(K==0)
            position--;
    }
    return position;
}
double ComplieDeals::count_smallBlock(unsigned start, unsigned end)
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
            sum=counter(start+1,end-1);
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
                for(;j<end;j++)
                    if(saves[j].mode==2&&saves[j].chars==',')
                        break;
                sum=counter(start+2,j-1);

                sum=pow(sum,counter(j+1,end-1));
            }
       }
        return sum;
    }
}
void ComplieDeals::dealHeader()
{
    if(saves[0].mode==2)
    {
        if(saves[0].chars=='+')
        {
            for(unsigned i=0;i<saves.size()-1;i++)
                 saves[i]=saves[i+1];
            saves.pop_back();
        }
        else if(saves[0].chars=='-')
        {
            C c;
            c.mode=1;
            c.number=-1;
            saves[0]=c;
            vector<C> s;
            c.mode=2;
            c.chars='*';
            s.push_back(c);
            saves.insert(saves.begin()+1,s.begin(),s.end());
        }
    }
}
//————————————————————————————————————————————————————————————————————————————————
int ComplieDeals::helpMatrixBuilder(vector<Matrix> matrixs)
{
    if(this->matrixs.size()!=0)
        this->matrixs.clear();

    for(unsigned i=0;i<matrixs.size();i++)
        this->matrixs[i]=matrixs[i];

        position++;
    if(text[position]=='(')
   {
        //先提取m和n
        int m,n;
        QString number;
        bool ok;
        while (text[position]!=',') {
            number.append(text[position]);
            if(position>text.size()-1)
            {
                return 3;
            }
            position++;
        }
        m=number.toInt(&ok);
        if(!ok||m<=0)
        {
            return 3;
        }
        number.clear();
        position++;
        while (text[position]!=')')
        {
            number.append(text[position]);
            if(position>text.size()-1)
            {
                return 3;
            }
            position++;
        }
        n=number.toInt(&ok);
        if(!ok||n<=0)
        {
            return 3;
        }
        if(position==text.size()-2)
        {
            cMatrix.m=m;
            cMatrix.n=n;
            cMatrix.zeroMatrix();
        }
        else
        {
            position++;
            if(text[position]!='=')
                return 3;
            else
            {
                position++;
                if(position==';')
                   return 3;
            if(text[position]=='[')
            {
                if(!getMatrixNumber())
                {
                    return 3;
                }
            }
            else
            {
                if(!dealMatrixExpression())
                    return 3;
            }
           }
        }
   }
     else if(text[position]=='=')
   {
        //计算表达式
        if(!dealMatrixExpression())
            return 3;
   }
     else
  {
        if(position==text.size()-2)
        {
            if(text[0]=='M')
                return 3;
            else
           {
                if(!matrix_exist())
                {
                    return 3;
                }
           }
        }
        else
        {
            return 3;
        }
  }
    return 0;
}

bool ComplieDeals::matrix_exist()
{
    for(unsigned i=0;i<matrixs.size();i++)
    {
        if(matrixs[i].name==virtualName)
            return true;
    }
    return false;
}
bool ComplieDeals::getMatrixNumber()
{
    return false;
}
bool ComplieDeals::dealMatrixExpression()
{
  return false;
}
