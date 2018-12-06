#include "functionbuildhelper.h"
#include<stack>
using namespace std;
FunctionBuildHelper::FunctionBuildHelper(QString m)
{
    this->function=m;
    position=0;
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

bool FunctionBuildHelper::helperBuilderFunction(vector<Function> lists)
{
    if(functions.size()!=0) functions.clear();

    for(unsigned i=0;i<lists.size();i++)

     functions.push_back(lists[i]);

    if(!getVirtualName()) return false;


    if(!dealHeader())
    {
       if(!dealExpression())
        return false;
    }
    if(!centerDeal()) return false;

    if(!save()) return false;

    if(!isWrong()) return false;

    dealCHeader();

    return true;
}
//-------------------------------------------------------------

bool FunctionBuildHelper::getVirtualName()
{
    QString name;
    if(function[0]=='F')
    {
        for(position=0;position<function.size();position++) if(function[position]==' ') break;

        if(position==function.size()) return false;

        position++;

        do
        {
            name.push_back(function[position]);
            position++;
        }
         while(position<function.size()&&function[position]!='('&&function[position]!='=');

         if(position==function.size()||!checkName(name)) return false;

         new_function.virtualName=name;
    }
    return true;
}

bool FunctionBuildHelper::dealHeader()
{
    if(function[position]!='(') return false;
    QString virtualname;
    do
    {
        position++;
        if(function[position]!=','&&function[position]!=')') virtualname.append(function[position]);
        else
        {
            if(!checkName(virtualname)) return false;
            new_function.virtualNames.push_back(virtualname);
            virtualname="";
        }
    }
        while (position<function.size()&&function[position]!=')');
        return true;
}

bool FunctionBuildHelper::checkName(QString name)
{
    if(name.size()==0) return false;
    if(!(name[0]>='a'&&name[0]<='z')) return false;
    for(int i=1;i<name.size();i++)
    {
        if(!((name[i]>='a'&&name[i]<='z')||(name[i]>='0'&&name[i]<='9')||(name[i]=='_')))
            return false;
    }
    return true;
}

bool FunctionBuildHelper::centerDeal()
{
    for(unsigned i=0;i<new_function.virtualNames.size();i++)
    new_function.virtualValues.push_back(0);
    position++;
    if(position>=function.size()-1&&function[position]!='=') return false;
    position++;
    for(int i=position;i<function.size()-1;i++)
        new_function.function.append(function[i]);
    new_function.virtualSize=new_function.virtualNames.size();
    return true;
}
//---------------------------------------------------------------
bool FunctionBuildHelper::save()
{
    if(new_function.saves.size()!=0)
        new_function.saves.clear();
    while (position<function.size()-1)
    {
        C c=returnMode(function[position]);
        if(c.isTrue)
        {
            new_function.saves.push_back(c);
        }
        else
        {
                return false;
        }
    }
    return true;
}

C FunctionBuildHelper::returnMode(QChar m)
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
        for(unsigned i=0;i<new_function.virtualNames.size();i++)
        {
            if(new_function.virtualNames[i]==name)
            {
                c.isTrue=true;
                c.mode=3;
                c.x=i;
            }
        }
    }
    }
    return c;
}

QString FunctionBuildHelper::getName()
{
    QString name;
    while(position<function.size()&&!isOpertate(function[position]))
    {
        name.append(function[position]);
        position++;
    }
    return name;
}

bool FunctionBuildHelper::isOpertate(QChar m)
{
    if(m=='*'||m=='+'||m=='/'||m=='-'||m=='('||m==')'||m==','||m==';')
       return true;
       return false;
}
bool FunctionBuildHelper::isNumber()
{
    QString number="";
    bool isOK;
     while(position<function.size()-1&&!isOpertate(function[position])) {
         number.push_back(function[position]);
         position++;
     }
     saveNumber=number.toDouble(&isOK);
     return isOK;
}

//-----------------------------------
bool FunctionBuildHelper::isWrong()
{
    C pre=new_function.saves[0];
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
    while (i<new_function.saves.size())
    {
        next=new_function.saves[i];
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
            pre=new_function.saves[i];
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
bool FunctionBuildHelper::PreNC(C next)
{
    if(next.mode==2&&next.chars!='(')
    {
     return true;
    }
    return false;
}
bool FunctionBuildHelper::PreFU(C next)
{

    if(next.mode!=2&&next.chars!='(')
        return false;
    return true;
}
bool FunctionBuildHelper::PreOP(C pre, C next)
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
bool FunctionBuildHelper::PowCheck(unsigned &position)
{
    C pre=new_function.saves[position];
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
        if(position>new_function.saves.size()-1) return false;

        next=new_function.saves[position];

       switch (pre.mode)
       {
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
                    if(position<new_function.saves.size())
                   {
                    position++;
                    next=new_function.saves[position];
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
                    if(next.chars!='+'&&next.chars!='-'&&next.chars!='(')
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

void FunctionBuildHelper::dealCHeader()
{
    if(new_function.saves[0].mode==2)
    {
        if(new_function.saves[0].chars=='+')
        {
            for(unsigned i=0;i<new_function.saves.size()-1;i++)
                 new_function.saves[i]=new_function.saves[i+1];
            new_function.saves.pop_back();
        }
        else if(new_function.saves[0].chars=='-')
        {
            C c;
            c.mode=1;
            c.number=-1;
            new_function.saves[0]=c;
            vector<C> s;
            c.mode=2;
            c.chars='*';
            s.push_back(c);
            new_function.saves.insert(new_function.saves.begin()+1,s.begin(),s.end());
        }
    }
}
//------------------------------------------------------------------
bool FunctionBuildHelper::dealExpression()
{
    combinedFunctionSize=0;
    has_operator=false;
    if(position>=function.size()-1&&function[position]!='=') return false;
    position++;
    if(!combideExpression()) return false;
    position=0;
    function.clear();
    function.push_back("f");
    function.push_back("=");
    for(unsigned i=0;i<new_function.function.size();i++)
    function.push_back(new_function.function[i]);
    new_function.function="";
    return true;
}
bool FunctionBuildHelper::combideExpression()
{
    for(unsigned i=0;i<functions.size();i++)
          signal.push_back(0);

    for(;position<function.size();)
    {
        if(function[position]>='a'&&function[position]<='z')
        {
            int a=checkVirtulName();
            if(a==-1) return false;
            signal[a]=1;
            if(a==-1) return false;
            else
            {
                new_function.function.push_back('(');
                for(unsigned i=0;i<functions[a].function.size();i++)
                new_function.function.push_back(functions[a].function[i]);
                new_function.function.push_back(')');
                combinedFunctionSize++;
            }
        }
        else
        {
            if(function[position]!=';')
                has_operator=true;
            if(function[position]>='0'&&function[position]<='9')
            {
                new_function.function.push_back(function[position]);
            }
            else
           {
                switch (function[position].toLatin1())
           {
               case '+':
               case '-':
               case '*':
               case '/':
               case'(' :
               case ')':
               case ';':
               case ',':
               case'.':
               new_function.function.push_back(function[position]);
               break;
           default:
               for(;position<function.size();position++)
               {
                   if(function[position]=='(') break;
                   else
                   new_function.function.push_back(function[position]);
               }
               position--;
               break;
           }

           }

            position++;
        }
    }
    cleanExpression();
    bool first=true;

    for(unsigned i=0;i<signal.size();i++)
    {
        if(signal[i]!=0)
        {
            if(first)
            {
                first=false;
                for(unsigned j=0;j<functions[i].virtualNames.size();j++)
                new_function.virtualNames.push_back(functions[i].virtualNames[j]);
            }
            else
            {
                for(unsigned j=0;j<functions[i].virtualNames.size();j++)
                {
                    QString name=functions[i].virtualNames[j];
                    bool isOk=true;
                    for(unsigned k=0;k<new_function.virtualNames.size();k++)
                    {
                        if(new_function.virtualNames[k]==name)
                        {
                            isOk=false;
                            break;
                        }
                    }
                    if(isOk) new_function.virtualNames.push_back(name);
                }
            }
        }
    }
    return true;
}

int FunctionBuildHelper::checkVirtulName()
{
    QString name;
    for(;position<function.size();position++)
    {

        if(function[position]=='+'||function[position]=='-'||function[position]=='*'||function[position]=='/'||function[position]=='('||function[position]==')'||function[position]==';'||function[position]==',')
            break;
        name.append(function[position]);
    }
    for(unsigned i=0;i<functions.size();i++)
        if(functions[i].virtualName==name) return i;
    return -1;
}
void FunctionBuildHelper::cleanExpression()
{
    stack<int> position;

    for(int i=0;i<new_function.function.size();i++)
    {
        if(new_function.function[i]=='(') position.push(i);
        else if(new_function.function[i]==')')
        {
            int k=position.top();
             position.pop();
            if(k!=0&&new_function.function[k-1]>='a'&&new_function.function[k-1]<='z')
            {
            }
            else
            {
               if(i==new_function.function.size()-2)
               {
                   if(k==0)
                   {
                       new_function.function[k]=' ';
                       new_function.function[i]=' ';
                   }
                   else
                   {
                       if(new_function.function[k-1]=='+'||new_function.function[k-1]=='(')
                       {
                           new_function.function[k]=' ';
                           new_function.function[i]=' ';
                       }
                       else if(new_function.function[k-1]!='/')
                       {
                           int count=0;
                           bool isBlock=true;
                           for(int m=k+1;m<i;m++)
                           {
                               if(new_function.function[m]=='(') count++;
                               else if(new_function.function[m]==')') count--;
                               else if(count==0&&(new_function.function[m]=='+'||new_function.function[m]=='-'))
                               {
                                   isBlock=false;
                                   break;
                               }

                           }
                           if(isBlock)
                           {
                               new_function.function[k]=' ';
                               new_function.function[i]=' ';
                           }
                       }
                   }
               }
               else
               {
                   if(k==0)
                   {
                       if(new_function.function[i+1]=='+'||new_function.function[i+1]==')')
                       {
                           new_function.function[k]=' ';
                           new_function.function[i]=' ';
                       }
                   }
                   else
                   {
                       if((new_function.function[k-1]=='+'||new_function.function[k-1]=='(')&&(new_function.function[i+1]=='+'||new_function.function[i+1]=='-'||new_function.function[i+1]==')'))
                       {
                           new_function.function[k]=' ';
                           new_function.function[i]=' ';
                       }
                       else if(new_function.function[k-1]!='/')
                       {
                           int count=0;
                           bool isBlock=true;
                           for(int m=k+1;m<i;m++)
                           {
                               if(new_function.function[m]=='(') count++;
                               else if(new_function.function[m]==')') count--;
                               else if( count==0&&(new_function.function[m]=='+'||new_function.function[m]=='-'))
                               {
                                   isBlock=false;
                                   break;
                               }

                           }
                           if(isBlock)
                           {
                               new_function.function[k]=' ';
                               new_function.function[i]=' ';
                           }
                       }
                   }
               }
            }
      }
   }
            QString f="";
    for(unsigned i=0;i<new_function.function.size();i++)
    {
        if(new_function.function[i]!=' ')
            f.append(new_function.function[i]);
    }
    new_function.function=f;

}
//--------------------------------------------------------------------------

bool FunctionBuildHelper::isExpression()
{
     is_expression=true;

    for(int i=0;i<function.size();i++)
        if(function[i]=='=')
         is_expression=false;

    return is_expression;
}

bool FunctionBuildHelper::dealFunctionExpression(vector<Function> f)
{
    if(functions.size()!=0) functions.clear();

    for(unsigned i=0;i<f.size();i++)functions.push_back(f[i]);

        QString fun;

        if(isExpression())
        {
            fun.push_back("Function f=");
        }
        else
        {
            fun.push_back("Function ");
        }

      for(int i=0;i<function.size();i++)
          fun.push_back(function[i]);

      function=fun;

      return helperBuilderFunction(f);

}
