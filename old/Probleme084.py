import random
# monopoly simulator
cells = [ 'GO', 'A', 'CC', 'A', 'T', 
         'R', 'B', 'CH', 'B', 'B',
         'JAIL', 'C', 'U', 'C', 'C',
         'R', 'D', 'CC', 'D', 'D',
         'FP', 'E', 'CH', 'E', 'E',
         'R', 'F', 'F', 'U', 'F',
         'G2J', 'G', 'G', 'CC', 'G',
         'R', 'CH', 'H', 'T', 'H' ]
cccards = ['DC', 'DC', 'DC', 'DC', 'DC',
           'DC', 'DC', 'DC', 'DC', 'DC',
           'DC', 'DC', 'DC', 'DC', '0', '10']
ccards = ['DC', 'DC', 'DC', 'DC', 'DC',
               'DC', '0', '10', '11', '24', 
               '39', '5', 'G2NR', 'G2NR', 'G2NU',
               'GB3']
def pe84():
    ntrial = 500000
    shuffle_cards()
    visited = sampling( ntrial )
    print visited
    print get_solution( visited )
def get_solution( visited ):
    first = get_max_index( visited )
    visited[first] = 0
    second = get_max_index( visited )
    visited[second] = 0
    third = get_max_index( visited )
    return "".join( [encode_squareface( first ), encode_squareface( second ), encode_squareface( third ) ] )
def get_max_index( lis ):
    idx = 0
    max = 0
    for i in range( 0, len( lis ) ):
        if lis[i] >= max:
            idx = i
            max = lis[i]
    return idx
              
def sampling( ntrial ):
    visited = [ 0 for i in range(0, len(cells))]
    pos = 0
    tried = 0
    # should I count first GO as visited ?
    while tried < ntrial:
        nextpos = nextcell( pos)
        #print len( visited ), " ", nextpos
        visited[nextpos]+= 1
        pos = nextpos
        tried +=1
    return visited

def nextcell( current_position):
    global prev_doubles
    score1 = random.randint( 1, 4 )
    score2 = random.randint( 1, 4 )
    if score1 == score2:
        if prev_doubles == 2:
            prev_doubles = 0
            return 10 
        else:
            prev_doubles += 1
    else:
        prev_doubles = 0
    next_position = advance( score1+score2, current_position )
    #print score, next_position
    if cells[next_position] == 'CC':
        return ccjump( next_position )
    elif cells[next_position] == 'CH':
        return cjump( next_position )
    elif cells[next_position] == 'G2J':
        return 10
    else:
        return next_position
def ccjump( current_position ): 
    card = drawcc()
    if card == 'DC':
        return current_position
    else:
        return int( card )
def cjump( current_position ):
    card = drawc()
    if card == 'DC':
        return current_position
    elif card == 'G2NR':
        return g2nr( current_position ) 
    elif card == 'G2NU':
        return g2nu( current_position )
    elif card == 'GB3':
        return back( 3, current_position )
    else:
        return int( card )
def g2nr( current_position ):
    while( True ):
        current_position = advance( 1, current_position)
        if cells[current_position] == 'R':
            return current_position
def g2nu( current_position ): 
    while( True ):
        current_position = advance( 1, current_position )
        if cells[current_position]  == 'U':
            return current_position
def advance( nsteps, current_position ):
    while nsteps > 0:
        current_position+=1
        if current_position > len( cells ) - 1:
            current_position = 0
        nsteps-=1
    return current_position
def back( nsteps, current_position ):
    while nsteps > 0:
        current_position -= 1
        if current_position < 0:
            current_position = len( cells ) - 1
        nsteps -=1
    return current_position 
def shuffle_cards():
    global ccards
    global cccards
    random.shuffle( ccards ) 
    random.shuffle( cccards )
def drawc():
    global ccards
    drawed = ccards.pop( 0 )
    ccards.append( drawed )
    return drawed 
def drawcc():
    global cccards
    drawed = cccards.pop( 0 )
    cccards.append( drawed )
    return drawed
def encode_squareface( num ):
    print "n : ", num 
    if num < 10:
        return '0'+str(num )
    else:
        return str( num )

prev_doubles = 0
pe84()

