#include "dealparams.h"
#include"buildhelper.h"
#include"functionbuildhelper.h"
#include"matrixbuilderhelper.h"
//text 格式：e,e,e,...)
 Dealparams:: Dealparams(QString text,vector<Number> n,vector<Function> f,vector<Matrix> m)
{
     //init data
     for(unsigned i=0;i<n.size();i++)
         this->numbers.push_back(n[i]);
     for(unsigned i=0;i<f.size();i++)
         this->functions.push_back(f[i]);
     for(unsigned i=0;i<m.size();i++)
         this->matrixs.push_back(m[i]);
      int end=text.size();


     if(text[end-1]!=')')
     {
         isTrue=false;
         return;
     }
     if(text.size()==1)
     {
         isNull=true;
         isTrue=true;
         return;
     }

     isNull=false;

     int position=0;
     QString expression;
     //check Pow signal
     bool has_pow=false;

     //deal chars
     while(position<=end-1)
     {
         if(text[position]==','||position==end-1)
      {
             if(!has_pow)
           {
              if(!dealOneParam(expression))
              {
                 isTrue=false;
                 return;
              }
              else expression="";
           }
            else
             {
                 has_pow=false;
                 expression.append(",");
             }
      }
         else expression.append(text[position]);

         if(text[position]=='P') has_pow=true;

         position++;
     }
     isTrue=true;
}
//-----------------------------------------------------------------------------------
 bool Dealparams::dealOneParam(QString text)
 {
     text.append(";");

     int end=text.size();

     if(end==0) return false;

     int mode=1;
     int start=0;
     while(start<end)
     {
         if(text[start]>='A'&&text[start]<='Z')
         {
             do
             {
                 start++;
             }
             while(text[start]!='('&&start<end);
         }

         if(text[start]>='a'&&text[start]<'z')
         {
             QString name="";
             while(start<end)
             {
                 if(!((text[start]>='a'&&text[start]<='z')||(text[start]>='0'&&text[start]<='9')||text[start]=='_'))
                 {
                     break;
                 }
                 name.append(text[start]);
                 start++;
             }
               mode=class_mode(name);

             if(mode==-1) return false;

             else break;
         }
         start++;
     }
     ParmType p;
     switch (mode)
     {
     case 0://处理矩阵表达式
     {
         MatrixBuilderHelper helper;
         if(!helper.helpBuildExpression(text,numbers,matrixs)) return false;
         else if(helper.saves.size()==1)
         {
             p.type=5;
             p.name=matrixs[helper.saves[0].x].name;
             p.new_matrix=helper.newMatrix;
             p.position=helper.saves[0].x;
             types.push_back(p);
         }
         else
         {
             p.type=4;
             p.new_matrix=helper.newMatrix;
             types.push_back(p);
         }
     }
         break;
     case 1://处理数字表达式     
     {
         buildhelper helper;
         helper.inputText(text);
         if(!helper.helpNumberBuilder(numbers)) return false;
         else
         {
             if(helper.saves.size()==1&&helper.saves[0].mode==3)
             {
                 p.type=1;
                 p.position=position;
                 p.number=helper.value;
                 types.push_back(p);
             }
             else
             {
                 p.type=0;
                 p.number=helper.value;
                 types.push_back(p);
             }
         }
     }
         break;
     case 2://处理方程表达式
     {
         FunctionBuildHelper funHelper(text);
         if(!funHelper.dealFunctionExpression(functions))
         {
             return false;
         }
         else
         {
             if(funHelper.combinedFunctionSize==1&&!funHelper.has_operator)
             {
                 p.type=3;
                 p.position=position;
                 p.new_function=funHelper.new_function;
                 types.push_back(p);
             }
             else if(funHelper.combinedFunctionSize>1)
             {
                 p.type=2;
                 p.new_function=funHelper.new_function;
                 types.push_back(p);
             }
             else
             {
                 return false;
             }
         }
     }
         break;
     }
     return true;
 }

 int Dealparams::class_mode(QString name)
 {
     for(unsigned i=0;i<numbers.size();i++)
     {
         if(name==numbers[i].name)
         {
             position=i;
             return 1;
         }
     }

     for(unsigned i=0;i<matrixs.size();i++)
     {
         if(name==matrixs[i].name)
           {
             position=i;
             return 0;
         }
     }

     for(unsigned i=0;i<functions.size();i++)
         if(name==functions[i].virtualName)
         {
             position=i;
             return 2;
         }
     return -1;
 }
