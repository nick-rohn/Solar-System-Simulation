import py.readfile as readfile
import matplotlib.pyplot as plt
import matplotlib.animation as an
from mpl_toolkits.mplot3d.axes3d import Axes3D
from matplotlib.widgets import Slider
import numpy as np
import datetime
import os.path



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
    time_text = fig.text(0.5, 0.95, time_str, verticalalignment='top', bbox = props)
    


    # slider
    axspeed = fig.add_axes([0.3, 0.1, 0.4, 0.03])
    slider = Slider(ax=axspeed, label='Simulation speed',
                    valmin=0, valmax=10, valinit=0, valstep = 1 )


    past_pos = []
    for planet in pos:
        pl = [[],[],[]]
        for i in range(3):
            pl[i].append(planet[i])
        past_pos.append(pl)


    iter = 0
    def update(frame):
        nonlocal iter
        nonlocal pos
        nonlocal n
        nonlocal past_pos
        points_circle = 200
        if not slider.val == 0:
            for i in range(2**(slider.val-1)):
                iter += 1
                pos = readfile.matrix( file, n )
                for j in range(n):
                    x0 = np.zeros(3)
                    for k in range(3):
                        x0[k] = past_pos[j][k][-1]
                    x1 = pos[j]
                    if np.linalg.norm(x1-x0)/np.linalg.norm(x0)>(2*np.pi/points_circle):
                        for k in range(3):
                            past_pos[j][k].append(pos[j][k])
                '''
                if math.atan2(past_pos[j][0][1],past_pos[j][0][2])<math.atan2(past_pos[j][-1][1],past_pos[j][-1][2]):
                    circles[j]+= 1
                if circles[j] >= 2:
                    past_pos[j].pop(0)
                '''
            
            for j in range(n):
                lines[j].set_data( past_pos[j][0], past_pos[j][1] )
                lines[j].set_3d_properties( past_pos[j][2] )
            points.set_offsets( pos[:,0:2] )
            points.set_3d_properties( pos [:,2], 'z' )
            time_delta = iter * info["frame length"] * info["timestep"]
            time = datetime.datetime(2021,11,28)+datetime.timedelta(seconds=time_delta)
            time_str = time.strftime('%d/%m/%Y')
            time_text.set_text( time_str )
        return points,


    animat = an.FuncAnimation( fig, update, l, interval=100 )

    plt.show()

    return





def order_files( filename1: str, filename2: str ):

    file1 = open( filename1 )
    info1 = readfile.header( file1 )
    ts1 = info1["frame length"] * info1["timestep"]
    info1["ts_str"] = filename1.split('_')[1]

    file2 = open( filename2 )
    info2 = readfile.header( file2 )
    ts2 = info2["frame length"] * info2["timestep"]
    info2["ts_str"] = filename2.split('_')[1]
    if ts1 >= ts2:
        return file1, info1, ts1, file2, info2, ts2
    else:
        return file2, info2, ts2, file1, info1, ts1
    



def compare():
    while True:
        filename1 = input("File 1:\t")
        if not os.path.isfile( filename1 ):
            print('File not found')
            continue
        break
    
    while True:
        filename2 = input("File 2:\t")
        if not os.path.isfile( filename2 ):
            print('File not found')
            continue
        break

    
    file1, info1, ts1, file2, info2, ts2 = order_files( filename1, filename2 )

    n1 = info1["planets"]
    planets1 = readfile.planets( file1, n1 )

    
    n2 = info2["planets"]
    planets2 = readfile.planets( file2, n2 )

    l = max( info1["iterations"], info2["iterations"] )




    pos1 = readfile.matrix( file1, n1 )
    pos2 = readfile.matrix( file2, n2 )

    # graph
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    ax: Axes3D
    fig.subplots_adjust(bottom=0.25)
    ax.set_title( info1["propagator"] + " vs " + 
                  info2["propagator"] + " propagator" )
    # planets
    points1 = ax.scatter( pos1[:,0], pos1[:,1], pos1[:,2],
                     c = range(n1), cmap='jet_r', marker='x' )
    points2 = ax.scatter( pos2[:,0], pos2[:,1], pos2[:,2],
                     c = range(n2), cmap='jet_r', marker='+' )



    # scale
    lim = 1.1 * abs( max( pos1.max(), pos1.min(), key = abs ) )
    ax.set_xlim3d( [-lim, +lim] )
    ax.set_ylim3d( [-lim, +lim] )
    ax.set_zlim3d( [-lim, +lim] )
    ax.set_aspect('equal')
    

    
    # legend
    keys1 = list( planets1.keys() )
    handles = points1.legend_elements()[0]
    leg1 = fig.legend( handles, keys1, loc='upper left',
                       title = (info1["propagator"]+' ('+info1["ts_str"]+')') )
    fig.add_artist(leg1)
    keys2 = list( planets2.keys() )
    handles = points2.legend_elements()[0]
    fig.legend( handles, keys2, loc='center left',
                title = (info2["propagator"]+' ('+info2["ts_str"]+')') )


    # info
    textstr = ""
    for item in info1:
        textstr += ( item + " = " + str(info1[item]) + '\n' )
    textstr = textstr.rstrip('\n')
    props = dict(boxstyle='round', facecolor = 'w', alpha = 0.3)

    fig.text(0.1, 0.95, textstr, verticalalignment='top', bbox = props, linespacing=1.5)

    textstr = ""
    for item in info2:
        textstr += ( item + " = " + str(info2[item]) + '\n' )
    textstr = textstr.rstrip('\n')
    props = dict(boxstyle='round', facecolor = 'w', alpha = 0.3)

    fig.text(0.1, 0.5, textstr, verticalalignment='top', bbox = props, linespacing=1.5)



    # time passed
    time = datetime.datetime(2021,11,28)
    time_str = time.strftime('%d/%m/%Y')
    time_text = fig.text(0.5, 0.95, time_str, verticalalignment='top', bbox = props)
    


    # slider
    axspeed = fig.add_axes([0.3, 0.1, 0.4, 0.03])
    slider = Slider(ax=axspeed, label='Simulation speed',
                    valmin=0, valmax=10, valinit=0, valstep = 1 )
    
    diff = int( ts1 / ts2 )

    iter = 0
    def update(frame):
        nonlocal iter
        nonlocal pos1
        nonlocal pos2
        nonlocal n1
        nonlocal n2
        nonlocal diff
        if not slider.val == 0:
            for i in range(2**(slider.val-1)):
                iter += 1
                pos1 = readfile.matrix( file1, n1 )
                for j in range(diff):
                    pos2 = readfile.matrix( file2, n2 )
            points1.set_offsets( pos1[:,0:2] )
            points1.set_3d_properties( pos1[:,2], 'z' )
            points2.set_offsets( pos2[:,0:2] )
            points2.set_3d_properties( pos2[:,2], 'z' )
            time_delta = iter * info1["frame length"] * info1["timestep"]
            time = datetime.datetime(2021,11,28)+datetime.timedelta(seconds=time_delta)
            time_str = time.strftime('%d/%m/%Y')
            time_text.set_text( time_str )
        return points1, points2,


    animat = an.FuncAnimation( fig, update, l, interval=100 )

    plt.show()