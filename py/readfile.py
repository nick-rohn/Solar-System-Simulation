import numpy as np
import io
from ast import literal_eval





# try to convert string to number, else return string
def convert( input: str ):
    try:
        value = literal_eval( input )
    except:
        return input
    else:
        return value





# check if block has ended, and skip separation line
def check_end( file: io.TextIOWrapper ):
    # skip blank line
    if file.readline() != '\n': raise ImportError( "Extra lines found" )
    return






# read information in the file header
def header( file: io.TextIOWrapper ):

    # create map
    info = {}

    # read until blank line
    while True:
        line = file.readline().rstrip('\n')
        if line == "":
            break

        # split 
        data = line.split(" = ")

        # fill map
        info[ data[0].strip() ] = convert( data[1].strip() )


    return info





# read planets and masses
def planets( file: io.TextIOWrapper, n: int ):

    # create map
    planets = {}

    # read all planets
    for i in range(n):
        line = file.readline().rstrip('\n').split('\t')

        #fill map
        planets[ line[0].strip() ] = convert( line[1].strip() )

    check_end( file )

    return planets





# read matrix
def matrix( file: io.TextIOWrapper, n: int ):
    
    # create matrix
    v = np.empty( ( n, 3 ) )

    # read line by line
    for i in range(n):
        table = file.readline().rstrip('\t\n').split('\t')
        # convert number by number
        v[i] = [ float( x ) for x in table ]

    check_end( file )

    return v