import py.readfile as readfile
import matplotlib.pyplot as plt
import numpy as np

def v_graph( filename ):

    with open( filename ) as file:

        info = readfile.header( file )

        n = info["planets"]

        planets = readfile.planets( file, n )

        pos = readfile.matrix( file, n )
        vel = readfile.matrix( file, n )
        grav = readfile.matrix( file, n )


    # ax = plt.figure().add_subplot(projection='3d')
    fig1, ax = plt.subplots()
    ax.set_title( info["propagator"] + " propagator" )

    # velocity
    velocity = ax.quiver( pos[:,0], pos[:,1],
                           #pos[:,2],
                           vel[:,0], vel[:,1],
                           #vel[:,2],
                           units='dots', angles = 'xy', width = 2,
                           color = 'b' )
    dk = ax.quiverkey(velocity, 0.95, 0.1, 10,
                      r'velocity$(\left(\frac{m}{s}\right))$', labelpos='W' )
    
    # gravity
    gravity = ax.quiver( pos[:,0], pos[:,1],
                         #pos[:,2],
                         grav[:,0], grav[:,1],
                         #grav[:,2],
                         units='dots', angles = 'xy', width = 2,
                         color = 'g' )
    gk = ax.quiverkey(gravity, 0.95, 0.05, 10,
                      r'gravity$(\left(\frac{m}{s^2}\right))$', labelpos='W' )

    # planets
    keys = list( planets.keys() )
    sc = ax.scatter( pos[:,0], pos[:,1], pos[:,2], c = range(n), cmap='jet_r' )
    handles = sc.legend_elements()[0]
    ax.legend( handles, keys, title = 'Planets')

    '''
    for i, txt in enumerate( keys ):
        ax1.annotate(txt, xy=(pos[i,0], pos[i,1]), xycoords='data',
                          xytext=(5, 0), textcoords='offset points' )
    '''

    # scale
    lim = 1.1 * abs( max( pos.max(), pos.min(), key = abs ) )
    ax.set_xlim( -lim, +lim )
    ax.set_ylim( -lim, +lim )
    #ax.set_zlim( -lim, +lim )

    plt.show()

    return