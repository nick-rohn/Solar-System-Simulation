import os.path
import py.animation as anim
import py.vectorplot as vplot

while True:
    filename = input("File:\t")
    if not os.path.isfile( filename ):
        print('File not found')
        continue
    if filename.startswith('static'):
        vplot.v_graph( filename )
    else: anim.animation( filename )