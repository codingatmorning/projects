import os
import subprocess

import PyQt5
import numpy
from calcui import *
import sys
from graphapp import *

def scale(im, nR, nC):
    nR0 = len(im)     # source number of rows
    nC0 = len(im[0])  # source number of columns
    if(nR0 == 0):
        return im
    if(nC0 == 0):
        return im
    return [[im[int(nR0 * r / nR)][int(nC0 * c / nC)]
             for c in range(nC)] for r in range(nR)]


class full_app(Ui_MainWindow):

    def __init__(self, graph_app, window) -> None:
        super().__init__()
        super().setupUi(window)

        self.app_handler = graph_app
        self.Graph.paintEvent = self.drawScreen
        MainWindow.closeEvent = self.decon
        self.ebox.textChanged.connect(self.updatevars)
        self.Width.valueChanged.connect(self.updatevars)
        self.Height.valueChanged.connect(self.updatevars)
        self.Calculations.valueChanged.connect(self.updatevars)
        self.Theta.valueChanged.connect(self.updatevars)

    def updatevars(self):
        if(self.Calculations.value() == 0):
            self.Calculations.setValue(1)
        b = self.app_handler.update_vars(self.ebox.toPlainText(), self.Width.value(
        ), self.Height.value(), self.Depth.value(), self.Calculations.value(), self.Theta.value())
        self.Graph.update()

    def drawScreen(self, event):
        self.app_handler.draw(event, self.Graph.width(), self.Graph.height(),self.Graph)

    def decon(self, event):
        del self

    def __del__(self):
        del self.app_handler


if __name__ == "__main__":
    myapp = graphapp("./back.exe")
    # initialize Ui Elements
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = full_app(myapp, MainWindow)
    del myapp
    MainWindow.show()
    sys.exit( app.exec())
