import numpy
import subprocess
from PyQt5.QtGui import QPainter, QBrush, QPen, QColor, qBlue
from PyQt5.QtCore import Qt, QPoint



class graphapp:

    def update_vars(self, equation, width, height, depth, numcalculations, theta):
        self.equation = equation
        self.width = str(width)
        self.height = str(height)
        self.depth = str(depth)
        self.numcalculations = str(numcalculations)
        self.theta = str(theta)
        return [self.equation, self.width, self.height, self.depth, self.numcalculations, self.theta]

    def __init__(self, filepath):
        self.app = subprocess.Popen(filepath, stdin=subprocess.PIPE,
                                    stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
        self.filepath = filepath
        self.equation = "z^2=25-(10-sqrt(x^2+y^2))^2"
        self.width = '3'
        self.height = '3'
        self.depth = '3'
        self.numcalculations = '180'
        self.swidth = '10'
        self.sheight = '10'
        self.theta = '0'
        self.drawing = False

    def draw(self, event, WIDTH, HEIGHT, screen):
        if(self.drawing == False):
            self.drawing = True
            self.equation=self.equation.replace('∗','*')
            splitequation = self.equation.split("=")
            eql = "y"
            eqr = "z"
            if(len(splitequation) >= 2):
                if(splitequation[0] != ''):
                    eql = splitequation[0]
                if(splitequation[1] != ''):
                    eqr = splitequation[1]
            print("L"+eql+"R"+eqr)
            self.app.stdin.write(bytes(eql+'\n', "utf-8"))
            self.app.stdin.write(bytes(eqr+'\n', "utf-8"))
            self.app.stdin.write(bytes(self.width+'\n', "utf-8"))
            self.app.stdin.write(bytes(self.height+'\n', "utf-8"))
            self.app.stdin.write(bytes(self.depth+'\n', "utf-8"))
            self.app.stdin.write(bytes(str(WIDTH)+'\n', "utf-8"))
            self.app.stdin.write(bytes(str(HEIGHT)+'\n', "utf-8"))
            self.app.stdin.write(bytes(self.numcalculations+'\n', "utf-8"))
            self.app.stdin.write(bytes(self.theta+'\n', "utf-8"))
            self.app.stdin.flush()
            painter = QPainter(screen)
            color = QColor()
            for y in range(HEIGHT):
                row = self.app.stdout.readline().decode(
                    "utf-8").strip('\n').strip('\r').strip('\0').split(',')
                # print(row)
                for x in range(WIDTH):
                    try:
                        QColor.setRgbF(color, float(row[x]), 0,0)
                    except:
                        pass
                    painter.setPen(color)
                    painter.drawPoint(x, y)
            painter.end()
            self.drawing=False

    def __del__(self):
        self.app.kill()
        self.app.wait()
