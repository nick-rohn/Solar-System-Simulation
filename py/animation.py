import py.readfile as readfile
import matplotlib.pyplot as plt
import matplotlib.animation as an
from mpl_toolkits.mplot3d.axes3d import Axes3D
from matplotlib.widgets import Slider
import numpy as np
import datetime
import math



def animation( filename ):
    
    file = open( filename )

    info = readfile.header( file )

    n = info["planets"]
    planets = readfile.planets( file, n )

    l = info["iterations"]



    pos = readfile.matrix( file, n )

    # graph
    plt.rcParams["axes.prop_cycle"] = plt.cycler("color", plt.cm.jet_r(np.linspace(0,1,n)))
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    ax: Axes3D
    fig.subplots_adjust(bottom=0.25)
    ax.set_title( info["propagator"] + " propagator" )
    # planets
    points = ax.scatter( pos[:,0], pos[:,1], pos[:,2],
                     c = range(n), cmap='jet_r' )



    # scale
    lim = 1.1 * abs( max( pos.max(), pos.min(), key = abs ) )
    ax.set_xlim3d( [-lim, +lim] )
    ax.set_ylim3d( [-lim, +lim] )
    ax.set_zlim3d( [-lim, +lim] )
    ax.set_aspect('equal')
    


    #tracks
    keys = list( planets.keys() )
    lines = [ax.plot([],[],[], alpha=0.3)[0] for i in range(n)]

    
    # legend
    handles = points.legend_elements()[0]
    fig.legend( handles, keys, title = 'Planets')



    # info
    textstr = ""
    for item in info:
        textstr += ( item + " = " + str(info[item]) + '\n' )
    textstr = textstr.rstrip('\n')
    props = dict(boxstyle='round', facecolor = 'w', alpha = 0.3)

    fig.text(0.05, 0.95, textstr, verticalalignment='top', bbox = props, linespacing=1.5)



    # time passed
    time = datetime.datetime(2021,11,28)
    time_str = time.strftime('%d/%m/%Y')
    time_text = fig.text(0.05, 0.05, time_str, verticalalignment='top', bbox = props)
    


    # slider
    axspeed = fig.add_axes([0.3, 0.1, 0.4, 0.03])
    slider = Slider(ax=axspeed, label='Simulation speed',
                    valmin=0, valmax=10, valinit=0, valstep = 1 )


    past_pos = [[x,x] for x in pos]
    circles = np.zeros(n, dtype=int)
    k = 0
    def update(frame):
        nonlocal k
        nonlocal pos
        nonlocal n
        nonlocal past_pos
        if not slider.val == 0:
            for i in range(2**(slider.val-1)):
                k += 1
                pos = readfile.matrix( file, n )
                for j in range(n):
                    past_pos[j].append( pos[j] )
                '''
                if math.atan2(past_pos[j][0][1],past_pos[j][0][2])<math.atan2(past_pos[j][-1][1],past_pos[j][-1][2]):
                    circles[j]+= 1
                if circles[j] >= 2:
                    past_pos[j].pop(0)
                '''
            
            for j in range(n):
                xs = [coor[0] for coor in past_pos[j]]
                ys = [coor[1] for coor in past_pos[j]]
                zs = [coor[2] for coor in past_pos[j]]
                lines[j].set_data( xs, ys )
                lines[j].set_3d_properties( zs )
            points.set_offsets( pos[:,0:2] )
            points.set_3d_properties( pos [:,2], 'z' )
            time_delta = k * info["frame length"] * info["timestep"]
            time = datetime.datetime(2021,11,28)+datetime.timedelta(seconds=time_delta)
            time_str = time.strftime('%d/%m/%Y')
            time_text.set_text( time_str )
        return points,


    animat = an.FuncAnimation( fig, update, l, interval=100 )

    plt.show()

    return