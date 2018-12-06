#include "matrixbuilderhelper.h"
#include "buildhelper.h"
#include"matrixcheck.h"
#include"matrixfunction.h"
using namespace std;
using namespace MatrixFunction;
MatrixBuilderHelper::MatrixBuilderHelper()
{
    position=0;
}
bool MatrixBuilderHelper::helpBuildExpression(QString text,vector<Number> numbers, vector<Matrix> matrixs)
{
    this->text=text;

    makeVector();

    for(unsigned i=0;i<numbers.size();i++)     this->numbers.push_back(numbers[i]);

    for(unsigned i=0;i<matrixs.size();i++)     this->matrixs.push_back(matrixs[i]);

    if(!save())return false;//字符形式化

    MatrixCheck c=check1(saves);
    if(c==returnfalse())
          return false;

    this->m=c.m;
    this->n=c.n;
    this->newMatrix.m=c.m;
    this->newMatrix.n=c.n;

    newMatrix.arrays=count1(saves).arrays;

    return true;
}
bool MatrixBuilderHelper::helpBuildMatrix(QString text, QString name, vector<Number> numbers, vector<Matrix> matrixs)
{
    newMatrix.name=name;
    this->text=text;

    for(unsigned i=0;i<numbers.size();i++)
     this->numbers.push_back(numbers[i]);
    if(!setMN()) return false;
    if(text[position]!=')') return false;
     newMatrix=Matrix(m,n);
    if(position==text.size()-2)
    {
        return true;
    }
    else
    {
        position++;
        if(text[position]!='=') return false;
        position++;
        if(text[position]=='[')
        {
            position++;
            return numberBuilder();
        }
        else
        {
            makeVector();
            if(this->matrixs.size()!=0)
                matrixs.clear();

            for(unsigned i=0;i<matrixs.size();i++)
              this->matrixs.push_back(matrixs[i]);

            if(!save())return false;//字符形式化

            MatrixCheck check;
            check.set(m,n);
            if(check!=check1(saves)) return false;
            newMatrix.arrays=count1(saves).arrays;
        }
    }
    return true;
}
//---------------------------------------------------获取行，列
bool MatrixBuilderHelper::setMN()
{
    bool isOk=false;
    while (position<text.size()&&text[position]!='(')
    {
        position++;
    }
    if(position==text.size())return false;
    QString m="";//Number expression
    position++;
    while(position<text.size()&&text[position]!=',')
    {
        m.append(text[position]);
        position++;
    }
    if(position==text.size()) return false;
    this->m=m.toInt(&isOk);
    if(!isOk||this->m<=0)return false;
    position++;
    m="";
    while(position<text.size()&&text[position]!=')')
    {
        m.append(text[position]);
        position++;
    }
    this->n=m.toInt(&isOk);
    if(!isOk&&this->n<=0)return false;
    return true;
}

bool MatrixBuilderHelper::numberBuilder()
{
    QString expression="";  //, ; ]结尾
    int exit=-1;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            do
            {
                if(text[position]==',')
                {
                    position++;
                    exit=0;
                    break;
                }
                else if(text[position]==';')
                {
                    position++;
                    exit=1;
                    break;
                }
                else if(text[position]==']')
                {
                    position++;
                    exit=2;
                    break;
                }
                else
                {
                    expression.push_back(text[position]);
                    position++;
                }
            }
            while(true&&position<text.size());
            if(exit==0)
            {
                if(j>=n-1)
                {
                    return false;
                }
            }
            else if(exit==1)
            {
                if(j!=n-1)
                {
                     return false;
                }
            }
            else if(exit==2)
            {
                if(!(j==n-1&&i==m-1))
                {
                      return false;
                }
            }
            else
            {
                return false;
            }
            expression.append(';');
            buildhelper helper;
            helper.inputText(expression);
            if(!helper.helpNumberBuilder(numbers))
            {
                return false;
            }
            newMatrix.arrays[i][j]=helper.value;
            expression="";
        }
    }
    return true;
}
//----------------------------------------------------------------------------------编译开始

void MatrixBuilderHelper::makeVector()
{
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
    functionName.push_back("Sqrt");
}

bool MatrixBuilderHelper::save()
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
    return true;
}

C MatrixBuilderHelper::returnMode(QChar m)
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
                c.mode=1;
                c.number=numbers[i].value;
                return c;
            }
        }
        for(unsigned i=0;i<matrixs.size();i++)
        {
            if(matrixs[i].name==name)
            {
                c.isTrue=true;
                c.mode=5;
                c.x=i;
                return c;
            }
        }
    }
    }
    return c;
}

bool MatrixBuilderHelper::isNumber()
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

bool MatrixBuilderHelper::isOpertate(QChar m)
{
    if(m=='*'||m=='+'||m=='-'||m=='('||m==')'||m==';')return true;
    else   return false;
}

QString MatrixBuilderHelper::getName()
{
    QString name="";
    while(position<text.size()-1&&!isOpertate(text[position]))
    {
        name.append(text[position]);
        position++;
    }
    return name;
}

//----------------------------------------------------------------------------------检查错误
MatrixCheck MatrixBuilderHelper::check1(vector<C> lists)
{
    vector<C> block;
    C c=lists[0];
    int preMode;
    bool isInit=false;
    unsigned i=0;
    int count=0;
    MatrixCheck check;
    check.set(-1,-1);
    if(c.mode==2)
    {
        if(c.chars!='+'&&c.chars!='-'&&c.chars!='(')
          return check;
        if(lists.size()==1)
          return check;
        if(c.chars=='(')
          count++;
    }
    preMode=lists[0].mode;
    i++;
    block.push_back(c);
    for(;i<lists.size();i++)
    {
        c=lists[i];
        if(preMode==1||preMode==5)
        {
            if(c.mode!=2)
            {
                return  returnfalse();
            }
            else
            {
                if(c.chars=='+'||c.chars=='-')
                {
                    if(count==0)
                    {
                        //检查的出口check2
                        MatrixCheck checkm=check2(block);
                        if(checkm==returnfalse()) return  checkm;
                        if(!isInit)
                        {
                            check=checkm;
                            isInit=true;
                        }
                        else
                        {
                           if(checkm!=check) return returnfalse();
                        }
                        block.clear();
                    }
                }
                else if(c.chars=='(')
                {
                    count++;
                }
                else if(c.chars==')')
                {
                    if(count<=0) return returnfalse();
                    count--;
                }
                block.push_back(c);
                preMode=2;
            }
        }
        else if(preMode==4)
        {
            if(c.mode!=2) return  returnfalse();
            else if(c.chars!='(') return  returnfalse();
            count++;
            preMode=2;
            block.push_back(c);
        }
        else if(preMode==2)
        {
            if(c.mode==2)
            {
               C c2=lists[i-1];
               if(c2.chars=='*') return returnfalse();
               else if(c2.chars==')')
               {
                   if(c.chars=='(') return returnfalse();
                   else if(c.chars==')')
                   {
                       if(count<=0) return returnfalse();
                       count--;
                   }
                   else if(c.chars=='+'||c.chars=='-')
                   {
                       if(count==0)
                       {
                           MatrixCheck checkm=check2(block);
                           if(checkm==returnfalse()) return  checkm;
                           if(!isInit)
                           {
                               check=checkm;
                               isInit=true;
                           }
                           else
                           {
                              if(checkm!=check) return returnfalse();
                           }
                           block.clear();
                       }
                   }
               }
               else if(c2.chars=='(')
               {
                   if(c.chars=='*'||c.chars==')') return returnfalse();
               }
               else if(c2.chars=='+'||c2.chars=='-')
               {
                   if(c.chars!='(')
                   {
                       return  returnfalse();
                   }
                   count++;
               }
               else
               {
                   return returnfalse();
               }
            }
            block.push_back(c);
            preMode=c.mode;
        }
        else
        {
            return  returnfalse();
        }
        if(i==lists.size()-1)
          {
            if(count!=0)
             returnfalse();
            else
            {
             MatrixCheck checkm=check2(block);
             if(checkm==returnfalse()) return  checkm;
             if(!isInit)
             {
                 check=checkm;
                 isInit=true;
             }
             else
             {
                if(checkm!=check) return returnfalse();
             }
             block.clear();
            }
        }
    }
    if(!isInit)
    {
        check=check2(block);
    }
    return check;
}

MatrixCheck MatrixBuilderHelper::check2(vector<C> lists)
{
  bool isInit=false;
  int i=0;
  MatrixCheck check;
  MatrixCheck check2;
  int position=0;
  C c=lists[i];

  if(c.mode==2)
  {
      if(c.chars=='(')
      {
          isInit=true;
          position=returnPosition(lists,0);
          check2=check1(makeList(lists,1,position-1));
          if(check2==returnfalse()) return returnfalse();
          check=check2;
          i=position+1;
      }
  }
  else if(c.mode==4)
  {
      i++;
      position=returnPosition(lists,i);
      check2=check1(makeList(lists,2,position-1));
      if(check2==returnfalse()) return returnfalse();
      check=check2;
      i=position+1;
  }
  else if(c.mode==1)
  {
      i++;
  }
  else if(c.mode==5)
  {
      check.m=matrixs[c.x].m;
      check.n=matrixs[c.x].n;
      isInit=true;
      i++;
  }

  while(i<lists.size())
  {
      c=lists[i];
      if(c.mode==2)
      {
          if(c.chars=='(')
          {
              position=returnPosition(lists,i);
              check2=check1(makeList(lists,i+1,position-1));
              if(check2==returnfalse()) return returnfalse();
              if(isInit)
              {
                  if(check.n!=check2.m) return  returnfalse();
                  else
                      check.n=check2.n;
              }
              else
              {
                  isInit=true;
                  check=check2;
              }
              i=position;
          }
          else
          {
              i++;
          }
      }
      else if(c.mode==1)
      {
          i++;
      }
      else if(c.mode==5)
      {
          check2.m=matrixs[c.x].m;
          check2.n=matrixs[c.x].n;
          if(isInit)
         {
          if(check.n!=check2.m) return returnfalse();
          else check.n=check2.n;
         }
          else
        {
              isInit=true;
              check=check2;
        }
          i++;
      }
      else if(c.mode==4)
      {
          i++;
          position=returnPosition(lists,i);
          check2=check1(makeList(lists,i+1,position-1));
          if(check2==returnfalse()) return returnfalse();
          if(isInit)
          {
              if(check.n!=check2.m) return  returnfalse();
              else
                  check.n=check2.n;
          }
          else
          {
              isInit=true;
              check=check2;
          }
          i=position;
      }
  }
  return  check;
}

MatrixCheck MatrixBuilderHelper::returnfalse()
 {
     MatrixCheck check;
     check.set(-1,-1);
     return check;
 }

vector<C> MatrixBuilderHelper::makeList(vector<C> list,int start,int end)
{
    vector<C> cs;
    for(int i=start;i<=end;i++)
        cs.push_back(list[i]);
    return cs;
}

int MatrixBuilderHelper::returnPosition(vector<C> list,int start)
{
    int count=0;
    for(int i=start;i<list.size();i++)
    {
        C c=list[i];
        if(c.mode==2)
        {
            if(c.chars=='(') count++;
            else if(c.chars==')') count--;
            if(count==0) return i;
        }
    }
    return -1;
}

//-------------------------------------------------------------------------------------计算
Matrix MatrixBuilderHelper::count1(vector<C> list)
{
    vector<C> block;
    C c=list[0];
    unsigned i=0;
    int count=0;
    bool isInit=false;
    int is_pluss=true;
    Matrix m(this->m,this->n);
    //做一个预处理，保证开头不会是 +,-
    if(c.mode==2)
    {
         if(c.chars=='(')
          count++;
         else if(c.chars=='+');
         else if(c.chars=='-')
         {
             isInit=true;
             is_pluss=false;
         }
         i++;
         block.push_back(c);
    }
    for(;i<list.size();i++)
    {
        c=list[i];
        if(c.mode==2)
        {
            if(c.chars=='(') count++;
            else if(c.chars==')')count--;
            else if(c.chars=='+')
            {
                if(count==0)
                {
                    if(isInit)
                    {
                        if(is_pluss)
                        m=m+count2(block);
                        else
                        m=m-count2(block);
                    }
                    else
                    {
                        m=count2(block);
                        isInit=true;
                    }
                      is_pluss=true;
                      block.clear();
                      continue;
                }
            }
            else if(c.chars=='-')
            {
                if(count==0)
                {
                    if(isInit)
                    {
                        if(is_pluss)
                        m=m+count2(block);
                        else
                        m=m-count2(block);
                    }
                    else
                    {
                        m=count2(block);
                        isInit=true;
                    }
                    is_pluss=false;
                    block.clear();
                    continue;
                }
            }
        }
         block.push_back(c);
    }
    if(!isInit)
    {
        m=count2(list);
    }
    else
    {
     if(is_pluss)
     {
         m=m+count2(block);
     }
     else
     {
         m=m-count2(block);
     }
    }
    return m;
}

Matrix MatrixBuilderHelper::count2(vector<C> list)
{
    Matrix m(this->m,this->n);
    bool isInit=false;
    int position=0;
    unsigned i=0;
    vector<double> number;
    do
    {
    C c=list[i];
    if(c.mode==2)//deal ()
    {
        if(c.mode=='(')
        {
            position=returnPosition(list,i);
            if(!isInit)
            {
             isInit=true;
             m=count1(makeList(list,1,position-1));
            }
            else
            {
                m=m*count1(makeList(list,1,position-1));
            }
            i=position+1;
        }
        else
        {
            i++;
        }
    }
    else if(c.mode==4)//deal function
    {
        int function_number=c.x;
        i++;
        position=returnPosition(list,i);
        Matrix n1=count1(makeList(list,i+1,position-1));
        switch (function_number)
        {
           case 0:
            n1=Sin(n1);
            break;
          case 1:
            n1=Cos(n1);
            break;
          case 2:
            n1=Tan(n1);
            break;
          case 3:
            n1=Cot(n1);
            break;
          case 4:
            n1=ASin(n1);
            break;
          case 5:
            n1=ACos(n1);
            break;
          case 6:
            n1=ATan(n1);
            break;
          case 7:
            n1=ACot(n1);
            break;
          case 8:
            n1=Ln(n1);
            break;
          case 9:
            n1=Log(n1);
            break;
          case 10:
            n1=Exp(n1);
            break;
          case 11:
            n1=Sqrt(n1);
            break;
        }
        if(isInit)
        {
            m=m*n1;
        }
        else
        {
            m=n1;
            isInit=true;
        }
        i=position+1;
    }
    else if(c.mode==1)
    {
        number.push_back(c.number);
        i++;
    }
    else if(c.mode==5)
    {
        if(isInit)
            m=m*matrixs[c.x];
        else
        {
            m=matrixs[c.x];
            isInit=false;
        }
        i++;
    }
    }
    while(i<list.size());

    for(unsigned i=0;i<number.size();i++)
        m=number[i]*m;
    return m;
}
