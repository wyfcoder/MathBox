#include "showhelpdoc.h"
#include<QIcon>
#include<QMenu>
#include<QFile>
#include<QTextStream>
#include<QFontDialog>
#include<QMessageBox>

using namespace std;

ShowHelpDoc::ShowHelpDoc(QWidget *parent) : QWidget(parent)
{

    creatAction();
    creatMenuBar();

    setWindowTitle("Help Document");
    setWindowIcon(QIcon(":/picture/file.png"));
    setFixedSize(300,500);
    text = new QTextBrowser(this);
    text ->move(0,25);
    text ->setFixedSize(300,475);
    ShowFile(i,text);
}
void ShowHelpDoc::creatAction()
{
    previous = new QAction("Previous",this);
    connect(previous,SIGNAL(triggered(bool)),this,SLOT(PreviousType()));
    next = new QAction("Next",this);
    connect(next,SIGNAL(triggered(bool)),this,SLOT(NextType()));
    fonts = new QAction("Font",this);
    connect(fonts,SIGNAL(triggered(bool)),this,SLOT(setFont()));


}
void ShowHelpDoc::creatMenuBar()
{
    menuBar = new QMenuBar(this);
    menuBar ->addAction(previous);
    menuBar ->addAction(next);
    menuBar ->addAction(fonts);
}

void ShowHelpDoc::PreviousType()
{
    if(i==1)
        QMessageBox::information(this,("Warn"),("This is the first file!"));
    else
        i = i-1;
    ShowFile(i,text);
}

void ShowHelpDoc::NextType()
{
    if(i==33)
        QMessageBox::information(this,("Warn"),("This is the last file!"));
    else
        i = i+1;
    ShowFile(i,text);
}

void ShowHelpDoc::ShowFile(int i,QTextBrowser* text)
{

    QFile Matrix_MainFile(":/file/Matrix.txt");//1
    QTextStream matrixmain(&Matrix_MainFile);
    QFile Pro_MatrixDetFile(":/file/Pro_MatrixDet.txt");//2
    QTextStream promatrixdet(&Pro_MatrixDetFile);
    QFile Pro_MatrixPowFile(":/file/Pro_MatrixPow.txt");//3
    QTextStream promatrixpow(&Pro_MatrixPowFile);
    QFile Pro_MatrixtoDownTriangelFile(":/file/Pro_MatrixtoDownTriangel.txt");//4
    QTextStream promatrixtodowntriangel(&Pro_MatrixtoDownTriangelFile);
    QFile Pro_MatrixtoLadderFile(":/file/Pro_MatrixtoLadder.txt");//5
    QTextStream promatrixladder(&Pro_MatrixtoLadderFile);
    QFile Pro_MatrixtoUpTriangleFile(":/file/Pro_MatrixtoUpTriangle.txt");//6
    QTextStream promatrixtouptriangle(&Pro_MatrixtoUpTriangleFile);
    QFile Pro_MatrixTraceFile(":/file/Pro_MatrixTrace.txt");//7
    QTextStream promatrixtrace(&Pro_MatrixTraceFile);
    QFile Pro_MatrixTransformFile(":/file/Pro_MatrixTransform.txt");//8
    QTextStream promatrixtransform(&Pro_MatrixTransformFile);
    QFile Number_MainFile(":/file/Number.txt");//9
    QTextStream numbermain(&Number_MainFile);
    QFile Function_MainFile(":/file/Function.txt");//10
    QTextStream functionmain(&Function_MainFile);
    QFile MathBox_PlotFile("://file/MathBox_Plot.txt");//11
    QTextStream mathboxplot(&MathBox_PlotFile);
    QFile Pro_Plot2DFile(":/file/Pro_Plot2D.txt");//12
    QTextStream proplot2D(&Pro_Plot2DFile);
    QFile Pro_RandFile(":/file/Pro_Rand.txt");//13
    QTextStream prorand(&Pro_RandFile);
    QFile Pro_RandMatrixFile(":/file/Pro_RandMatrix.txt");//14
    QTextStream prorandmatrix(&Pro_RandMatrixFile);
    QFile Pro_RandFunctionFile(":/file/Pro_RandFunction.txt");//15
    QTextStream prorandfunction(&Pro_RandFunctionFile);
    QFile Pro_Regression_MultipleVirtualsRegressionFile(":/file/Pro_Regression_MultipleVirtualsRegression.txt");//16
    QTextStream proregressionmultiplevirtualsregression(&Pro_Regression_MultipleVirtualsRegressionFile);
    QFile Pro_Regression_PlecrveRegression_TreeItemFile(":/file/Pro_Regression_PlecrveRegression.txt");//17
    QTextStream proregressionplecrveregression(&Pro_Regression_PlecrveRegression_TreeItemFile);
    QFile Pro_Regression_UnifiedRegression_TreeItemFile(":/file/Pro_Regression_UnifiedRegression.txt");//18
    QTextStream proregressionunifiedregression(&Pro_Regression_UnifiedRegression_TreeItemFile);
    QFile Pro_IntegrationSolving_GuassFivePointFile(":/file/Pro_IntegrationSolving_GuassFivePoint.txt");//19
    QTextStream prointegrationsolvingguassfivepoint(&Pro_IntegrationSolving_GuassFivePointFile);
    QFile Pro_IntegrationSolving_RombergFile(":/file/Pro_IntegrationSolving_Romberg.txt");//20
    QTextStream prointegrationsolvingromberg(&Pro_IntegrationSolving_RombergFile);
    QFile Pro_IntegrationSolving_SimpsonFile(":/file/Pro_IntegrationSolving_Simpson.txt");//21
    QTextStream prointegrationsolvingsimpson(&Pro_IntegrationSolving_SimpsonFile);
    QFile Pro_IntegrationSolving_StepSimpsonFile(":/file/Pro_IntegrationSolving_StepSimpson.txt");//22
    QTextStream prointegrationsolvingstepsimpson(&Pro_IntegrationSolving_StepSimpsonFile);
    QFile Pro_EquationSolvingFile(":/file/Pro_EquationSolving.txt");//23
    QTextStream proequationsolving(&Pro_EquationSolvingFile);
    QFile Pro_LinearDiagonalEquationsSolvingFile(":/file/Pro_LinearDiagonalEquationsSolving.txt");//24
    QTextStream prolineardiagonalequationssolving(&Pro_LinearDiagonalEquationsSolvingFile);
    QFile Pro_LinearEquationsSolvingFile(":/file/Pro_LinearEquationsSolving.txt");//25
    QTextStream prolinearequationssolving(&Pro_LinearEquationsSolvingFile);
    QFile Pro_LinearEquationsSolving_IterationFile(":/file/Pro_LinearEquationsSolving_Iteration.txt");//26
    QTextStream prolinearequationssolvingiteration(&Pro_LinearEquationsSolving_IterationFile);
    QFile Pro_LinearEquationsSolving_MainGuassFile("://file/Pro_LinearEquationsSolving_MainGuass.txt");//27
    QTextStream prolinearequationssolvingmainguass(&Pro_LinearEquationsSolving_MainGuassFile);
    QFile Pro_OutputMatrixFile(":/file/Pro_OutputMatrix.txt");//28
    QTextStream prooutputmatrix(&Pro_OutputMatrixFile);
    QFile Pro_InputMatrixFile(":/file/Pro_InputMatrix.txt");//29
    QTextStream proinputmatrix(&Pro_InputMatrixFile);
    QFile Pro_SetDigitFile(":/file/Pro_SetDigit.txt");//30
    QTextStream prosetdigit(&Pro_SetDigitFile);
    QFile ResultFile(":/file/Result.txt");//31
    QTextStream result(&ResultFile);
    QFile Pro_ClearFile(":/file/Pro_Clear.txt");//32
    QTextStream proclear(&Pro_ClearFile);
    QFile Pro_EraserFile(":/file/Pro_Eraser.txt");//33
    QTextStream proeraser(&Pro_EraserFile);

    switch(i)
    {

    case 1:
        if(!Matrix_MainFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
        {
            while(!matrixmain.atEnd())
            {
                text->setPlainText(matrixmain.readAll());
            }
        }
        Matrix_MainFile.close();

        break;
    case 2:
        if(!Pro_MatrixDetFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!promatrixdet.atEnd())
            {
                text->setPlainText(promatrixdet.readAll());
            }
        Pro_MatrixDetFile.close();

        break;
    case 3:

        if(!Pro_MatrixPowFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!promatrixpow.atEnd())
            {
                text->setPlainText(promatrixpow.readAll());
            }
        Pro_MatrixPowFile.close();
        break;
    case 4:

        if(!Pro_MatrixtoDownTriangelFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!promatrixtodowntriangel.atEnd())
            {
                text->setPlainText(promatrixtodowntriangel.readAll());
            }
        Pro_MatrixtoDownTriangelFile.close();
        break;
    case 5:

        if(!Pro_MatrixtoLadderFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!promatrixladder.atEnd())
            {
                text->setPlainText(promatrixladder.readAll());
            }
        Pro_MatrixtoLadderFile.close();
        break;
    case 6:

        if(!Pro_MatrixtoUpTriangleFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!promatrixtouptriangle.atEnd())
            {
                text->setPlainText(promatrixtouptriangle.readAll());
            }
        Pro_MatrixtoUpTriangleFile.close();
        break;
    case 7:

        if(!Pro_MatrixTraceFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!promatrixtrace.atEnd())
            {
                text->setPlainText(promatrixtrace.readAll());
            }
        Pro_MatrixTraceFile.close();
        break;
    case 8:

        if(!Pro_MatrixTransformFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!promatrixtransform.atEnd())
            {
                text->setPlainText(promatrixtransform.readAll());
            }
        Pro_MatrixTransformFile.close();
        break;
    case 9:

        if(!Number_MainFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!numbermain.atEnd())
            {
                text->setPlainText(numbermain.readAll());
            }
        Number_MainFile.close();
        break;
    case 10:

        if(!Function_MainFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!functionmain.atEnd())
            {
                text->setPlainText(functionmain.readAll());
            }
        Function_MainFile.close();
        break;
    case 11:

        if(!MathBox_PlotFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!mathboxplot.atEnd())
            {
                text->setPlainText(mathboxplot.readAll());
            }
        MathBox_PlotFile.close();
        break;
    case 12:

        if(!Pro_Plot2DFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proplot2D.atEnd())
            {
                text->setPlainText(proplot2D.readAll());
            }
        Pro_Plot2DFile.close();
        break;
    case 13:

        if(!Pro_RandFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prorand.atEnd())
            {
                text->setPlainText(prorand.readAll());
            }
        Pro_RandFile.close();
        break;
    case 14:

        if(!Pro_RandMatrixFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prorandmatrix.atEnd())
            {
                text->setPlainText(prorandmatrix.readAll());
            }
        Pro_RandMatrixFile.close();
        break;
    case 15:

        if(!Pro_RandFunctionFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prorandfunction.atEnd())
            {
                text->setPlainText(prorandfunction.readAll());
            }
        Pro_RandFunctionFile.close();
        break;
    case 16:

        if(!Pro_Regression_MultipleVirtualsRegressionFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proregressionmultiplevirtualsregression.atEnd())
            {
                text->setPlainText(proregressionmultiplevirtualsregression.readAll());
            }
        Pro_Regression_MultipleVirtualsRegressionFile.close();
        break;
    case 17:

        if(!Pro_Regression_PlecrveRegression_TreeItemFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proregressionplecrveregression.atEnd())
            {
                text->setPlainText(proregressionplecrveregression.readAll());
            }
        Pro_Regression_PlecrveRegression_TreeItemFile.close();
        break;
    case 18:

        if(!Pro_Regression_UnifiedRegression_TreeItemFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proregressionunifiedregression.atEnd())
            {
                text->setPlainText(proregressionunifiedregression.readAll());
            }
        Pro_Regression_UnifiedRegression_TreeItemFile.close();
        break;
    case 19:

        if(!Pro_IntegrationSolving_GuassFivePointFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prointegrationsolvingguassfivepoint.atEnd())
            {
                text->setPlainText(prointegrationsolvingguassfivepoint.readAll());
            }
        Pro_IntegrationSolving_GuassFivePointFile.close();
        break;
    case 20:

        if(!Pro_IntegrationSolving_RombergFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prointegrationsolvingromberg.atEnd())
            {
                text->setPlainText(prointegrationsolvingromberg.readAll());
            }
        Pro_IntegrationSolving_RombergFile.close();
        break;
    case 21:

        if(!Pro_IntegrationSolving_SimpsonFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prointegrationsolvingsimpson.atEnd())
            {
                text->setPlainText(prointegrationsolvingsimpson.readAll());
            }
        Pro_IntegrationSolving_SimpsonFile.close();
        break;
    case 22:

        if(!Pro_IntegrationSolving_StepSimpsonFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prointegrationsolvingstepsimpson.atEnd())
            {
                text->setPlainText(prointegrationsolvingstepsimpson.readAll());
            }
        Pro_IntegrationSolving_StepSimpsonFile.close();
        break;
    case 23:

        if(!Pro_EquationSolvingFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proequationsolving.atEnd())
            {
                text->setPlainText(proequationsolving.readAll());
            }
        Pro_EquationSolvingFile.close();
        break;
    case 24:

        if(!Pro_LinearDiagonalEquationsSolvingFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prolineardiagonalequationssolving.atEnd())
            {
                text->setPlainText(prolineardiagonalequationssolving.readAll());
            }
        Pro_LinearDiagonalEquationsSolvingFile.close();
        break;
    case 25:

        if(!Pro_LinearEquationsSolvingFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prolinearequationssolving.atEnd())
            {
                text->setPlainText(prolinearequationssolving.readAll());
            }
        Pro_LinearEquationsSolvingFile.close();
        break;
    case 26:

        if(!Pro_LinearEquationsSolving_IterationFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prolinearequationssolvingiteration.atEnd())
            {
                text->setPlainText(prolinearequationssolvingiteration.readAll());
            }
        Pro_LinearEquationsSolving_IterationFile.close();
        break;
    case 27:

        if(!Pro_LinearEquationsSolving_MainGuassFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prolinearequationssolvingmainguass.atEnd())
            {
                text->setPlainText(prolinearequationssolvingmainguass.readAll());
            }
        Pro_LinearEquationsSolving_MainGuassFile.close();
        break;
    case 28:

        if(!Pro_OutputMatrixFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prooutputmatrix.atEnd())
            {
                text->setPlainText(prooutputmatrix.readAll());
            }
        Pro_OutputMatrixFile.close();
        break;
    case 29:

        if(!Pro_InputMatrixFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proinputmatrix.atEnd())
            {
                text->setPlainText(proinputmatrix.readAll());
            }
        Pro_InputMatrixFile.close();
        break;
    case 30:

        if(!Pro_SetDigitFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!prosetdigit.atEnd())
            {
                text->setPlainText(prosetdigit.readAll());
            }
        Pro_SetDigitFile.close();
        break;
    case 31:

        if(!ResultFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!result.atEnd())
            {
                text->setPlainText(result.readAll());
            }
        ResultFile.close();
        break;
    case 32:

        if(!Pro_ClearFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proclear.atEnd())
            {
                text->setPlainText(proclear.readAll());
            }
        Pro_ClearFile.close();
        break;
    case 33:

        if(!Pro_EraserFile.open(QIODevice::ReadOnly))
            QMessageBox::information(this,("Text File"),("Can't Open The File"));
        else
            while(!proeraser.atEnd())
            {
                text->setPlainText(proeraser.readAll());
            }
        Pro_EraserFile.close();
        break;
    default:
        break;
    }
}

void ShowHelpDoc::setFont()
{
        bool ok;
        QFont font = QFontDialog::getFont(&ok);
        if(ok)
        {
            text->setFont(font);
        }
}




