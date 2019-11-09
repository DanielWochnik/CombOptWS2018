# by Johannes Staib TIN17IN
# Algorithmus von http://www.inf.fh-flensburg.de/lang/algorithmen/graph/connected-components.htm

from tkinter  import Tk
try: import tkinter.filedialog as filedialog           # Py3
except ImportError: import tkFileDialog as filedialog  # Py2
import re

class Vertex:
    c = 0    
    vertexes = {}
    edges = []
    def __init__(self,nr):
        self.nr = nr
        self.marked = 0
    

    def neighbours(self):
        for e in Vertex.edges:
            if self.nr in e:
                temp = list(e)
                temp
                yield Vertex.vertexes[temp.pop()]
    def execute(self):
        self.marked = Vertex.c
        for n in self.neighbours():
            if n.marked == 0:
                n.execute()
        pass
    @staticmethod
    def find():        
        for v in Vertex.vertexes.values():
            if v.marked == 0 :
                Vertex.c = Vertex.c+1
                v.execute()  
        pass
    @staticmethod
    def output():
        for i in range(1,Vertex.c+1):
            print(" ".join([ str(v.nr) for v in Vertex.vertexes.values() if v.marked == i ]))
        pass

Tk().withdraw()
fpath = filedialog.askopenfilename()
if fpath:
    with open(fpath,"r") as fh:
        # read edges
        for line in fh.readlines():
            line  = [ int(n) for n in re.findall(r'[0-9]+',line)] # fine vertex numbers in each line
            # create vertexes
            for vertexNr in line:
                if not vertexNr in Vertex.vertexes.keys():
                    Vertex.vertexes[vertexNr] = Vertex(vertexNr)
            # add edge if exist in line
            if len(line) == 2:
                Vertex.edges.append((line[0],line[1]))

    # find connected component
    Vertex.find()
    Vertex.output()
