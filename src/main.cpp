#include "MainWindow.h"
#include <QApplication>
#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include<vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
	
    return a.exec();
}
