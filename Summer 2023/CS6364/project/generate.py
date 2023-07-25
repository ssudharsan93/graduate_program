import pprint

DEBUG = False

BOARD_MAP_INDEX_TO_POS = [
    "a0",
    "g0",
    "b1",
    "f1",
    "c2",
    "e2",
    "a3",
    "b3",
    "c3",
    "e3",
    "f3",
    "g3",
    "c4",
    "d4",
    "e4",
    "b5",
    "d5",
    "f5",
    "a6",
    "d6",
    "g6"
]

BOARD_MAP_POS_TO_INDEX = {
    "a0" : 0,
    "g0" : 1,
    "b1" : 2,
    "f1" : 3,
    "c2" : 4,
    "e2" : 5,
    "a3" : 6,
    "b3" : 7,
    "c3" : 8,
    "e3" : 9,
    "f3" : 10,
    "g3" : 11,
    "c4" : 12,
    "d4" : 13,
    "e4" : 14,
    "b5" : 15,
    "d5" : 16,
    "f5" : 17,
    "a6" : 18,
    "d6" : 19,
    "g6" : 20
}

NEIGHBORS = {
    "a0" : ["g0", "a3"],
    "g0" : ["a0", "g3"],
    "b1" : ["f1", "b3"],
    "f1" : ["b1", "f3"],
    "c2" : ["e2", "c3"],
    "e2" : ["c2", "e3"],
    "a3" : ["a0", "b3", "a6"],
    "b3" : ["b1", "a3", "c3", "b5"],
    "c3" : ["c2", "b3", "c4"],
    "e3" : ["e2", "f3", "e4"],
    "f3" : ["f1", "e3", "g3", "f5"],
    "g3" : ["g0", "f3", "g6"],
    "c4" : ["c3", "d4"],
    "d4" : ["c4", "e4", "d5"],
    "e4" : ["e3", "d4"],
    "b5" : ["b3", "d5"],
    "d5" : ["d4", "b5", "f5", "d6"],
    "f5" : ["f3", "d5"],
    "a6" : ["a3", "d6"],
    "d6" : ["d5", "a6", "g6"],
    "g6" : ["g3", "d6"]
}

CLOSE_MILL_PARTICIPATION = {
    "a0" : [["a3", "a6"]],
    "g0" : [["g3", "g6"]],
    "b1" : [["b3", "b5"]],
    "f1" : [["f3", "f5"]],
    "c2" : [["c3", "c4"]],
    "e2" : [["e3", "e4"]],
    "a3" : [ ["a0", "a6"], ["b3", "c3"] ],
    "b3" : [ ["b1", "b5"], ["a3", "c3"] ],
    "c3" : [ ["c2" ,"c4"], ["a3", "b3"] ],
    "e3" : [ ["e2", "e4"], ["f3", "g3"] ],
    "f3" : [ ["f1", "f5"], ["e3", "g3"] ],
    "g3" : [ ["g0", "g6"], ["e3", "f3"] ],
    "c4" : [ ["c2", "c3"], ["d4", "e4"] ],
    "d4" : [ ["c4", "e4"], ["d5", "d6"] ],
    "e4" : [ ["e2", "e3"], ["c4", "d4"] ],
    "b5" : [ ["b1", "b3"], ["d5", "f5"] ],
    "d5" : [ ["d4", "d6"], ["b5", "f5"] ],
    "f5" : [ ["f1", "f3"], ["b5", "d5"] ],
    "a6" : [ ["a0", "a3"], ["d6", "g6"] ],
    "d6" : [ ["d4", "d5"], ["a6", "g6"] ],
    "g6" : [ ["g0", "g3"], ["a6", "d6"] ]
}

def neighbors(index):
    return NEIGHBORS[BOARD_MAP_INDEX_TO_POS[index]]

def closeMill(board_position, input_board_position):
    piece_type = input_board_position[BOARD_MAP_POS_TO_INDEX[board_position]]
    if piece_type == "x":
        return False

    close_mills_exists = list()
    
    for close_mill_inst in CLOSE_MILL_PARTICIPATION[board_position]:
        same_piece_type = list()
        for neighbor_board_pos in close_mill_inst:
            neighbor_piece_type = input_board_position[ BOARD_MAP_POS_TO_INDEX[neighbor_board_pos] ]
            if ( neighbor_piece_type != piece_type ):
                same_piece_type.append(False)
            else:
                same_piece_type.append(True)
        
        close_mills_exists.append(all(same_piece_type))
    
    return any(close_mills_exists)
    
def GenerateMovesOpening(input_board_position):
    return GenerateAdd(input_board_position)

def GenerateMovesMidgameEndgame(input_board_position):
    if ( num_white_pieces(input_board_position) == 3 ):
        return GenerateHopping(input_board_position)
    else:
        return GenerateMove(input_board_position)
    
def GenerateAdd(input_board_position):
    L = list()

    if DEBUG:
        print("Entered Generate Add. \n")
        print("Adding to: " + convert_board_position_to_string(input_board_position))
    
    for board_index in range(0,21):
        if input_board_position[board_index] == "x":
            b = list(input_board_position)
            b[board_index] = "W"
            if ( closeMill(BOARD_MAP_INDEX_TO_POS[board_index], b) ):
                GenerateRemove(b, L)
            else:
                L.append(b)
    return L

def GenerateHopping(input_board_position):
    L = list()
    for alpha in range(0,21):
        if input_board_position[alpha] == "W":
            for beta in range(0,21):
                if input_board_position[beta] == "x":
                    b = list(input_board_position)
                    b[alpha] = "x"
                    b[beta] = "W"
                    if ( closeMill(BOARD_MAP_INDEX_TO_POS[beta], b) ):
                        GenerateRemove(b, L)
                    else:
                        L.append(b)
    return L

def GenerateMove(input_board_position):
    L = list()
    for board_index in range(0,21):
        if input_board_position[board_index] == "W":
            n = neighbors(board_index)
            for neighbor in n:
                neighbor_index = BOARD_MAP_POS_TO_INDEX[neighbor]
                if input_board_position[neighbor_index] == "x":
                    b = list(input_board_position)
                    b[board_index] = "x"
                    b[neighbor_index] = "W"
                    if ( closeMill(BOARD_MAP_INDEX_TO_POS[neighbor_index], b) ):
                        GenerateRemove(b, L)
                    else:
                        L.append(b)
    return L

def GenerateRemove(input_board_position, L):
    
    # if DEBUG:
    #     print("Entered Generate Remove. \n")
    #     print("Removing for: " + convert_board_position_to_string(input_board_position))
    
    removed_black_pieces_L = list()
    for board_index in range(0,21):
        if input_board_position[board_index] == "B":
            if ( not closeMill(BOARD_MAP_INDEX_TO_POS[board_index], input_board_position) ):
                b = list(input_board_position)
                b[board_index] = "x"
                removed_black_pieces_L.append(b)
    
    if ( len(removed_black_pieces_L) == 0 ):
        L .append(list(input_board_position))
    else:
        L += removed_black_pieces_L
    
    return L

def num_black_pieces(input_board_position):
    return sum([ 1 if x == 'B' else 0 for x in input_board_position ])

def num_white_pieces(input_board_position):
    return sum([ 1 if x == 'W' else 0 for x in input_board_position ])

def get_participating_close_mill(board_position):
    return CLOSE_MILL_PARTICIPATION[board_position]

def print_board_positions(input_board_position):
    print(input_board_position)

def flip_board_position(input_board_position):
    flipped_board = list()
    for x in input_board_position:
        if ( x == "B" ):
            flipped_board.append("W")         
        elif ( x == "W" ):
            flipped_board.append("B")     
        else:
            flipped_board.append("x")  
    return flipped_board

def convert_board_position_to_string(bp):
    bp_str = str()
    for board_location in bp:
        bp_str += board_location
    return bp_str

def convert_board_position_string_to_position(bp_str):
    return [ x for x in bp_str ]
        
    
# Static Estimation Functions Begin
    
def static_est_midgame_endgame(input_board_position):
    black_board = flip_board_position(input_board_position)
    numBlackMoves = len(GenerateMove(black_board))

    if ( num_black_pieces(input_board_position) <= 2 ):
        return 10000
    elif ( num_white_pieces(input_board_position) <= 2 ):
        return (-10000)
    elif ( numBlackMoves == 0 ):
        return 10000 
    else:
        return 1000 * ( num_white_pieces(input_board_position) - 
                        num_black_pieces(input_board_position) ) - numBlackMoves

def static_est_opening(input_board_position):
    return ( num_white_pieces(input_board_position) - 
            num_black_pieces(input_board_position) )

PERSONAL_OPENING_POSITION_WEIGHTS = {
    "a0" : 3,
    "g0" : 3,
    "b1" : 1,
    "f1" : 1,
    "c2" : -2,
    "e2" : -2,
    "a3" : 2,
    "b3" : 3,
    "c3" : 0,
    "e3" : 0,
    "f3" : 3,
    "g3" : 2,
    "c4" : -2,
    "d4" : 0,
    "e4" : -2,
    "b5" : 1,
    "d5" : 3,
    "f5" : 1,
    "a6" : 3,
    "d6" : 2,
    "g6" : 3
}

PERSONAL_MIDGAME_ENDGAME_POSITION_WEIGHTS = {
    "a0" : -10,
    "g0" : -10,
    "b1" : -50,
    "f1" : -50,
    "c2" : -100,
    "e2" : -100,
    "a3" : 100,
    "b3" : 200,
    "c3" : 50,
    "e3" : 50,
    "f3" : 200,
    "g3" : 100,
    "c4" : -100,
    "d4" : 50,
    "e4" : -100,
    "b5" : -50,
    "d5" : 200,
    "f5" : -50,
    "a6" : -10,
    "d6" : 100,
    "g6" : -10
}

def personal_static_est_midgame_endgame(input_board_position):
    black_board = flip_board_position(input_board_position)
    numBlackMoves = len(GenerateMove(black_board))

    BlackScore = 0
    WhiteScore = 0

    for location in PERSONAL_MIDGAME_ENDGAME_POSITION_WEIGHTS.keys():
        if input_board_position[BOARD_MAP_POS_TO_INDEX[location]] == "W":
            WhiteScore += PERSONAL_MIDGAME_ENDGAME_POSITION_WEIGHTS[location]

        elif input_board_position[BOARD_MAP_POS_TO_INDEX[location]] == "B":
            BlackScore += PERSONAL_MIDGAME_ENDGAME_POSITION_WEIGHTS[location]

        else:
            continue
    
    if ( num_black_pieces(input_board_position) <= 2 ):
        return 10000
    elif ( num_white_pieces(input_board_position) <= 2 ):
        return (-10000)
    elif ( numBlackMoves == 0 ):
        return 10000 
    else:
        return ( WhiteScore * num_white_pieces(input_board_position) - 
                BlackScore * num_black_pieces(input_board_position) )

def personal_static_est_opening(input_board_position):
    BlackScore = 0
    WhiteScore = 0

    for location in PERSONAL_OPENING_POSITION_WEIGHTS.keys():
        if input_board_position[BOARD_MAP_POS_TO_INDEX[location]] == "W":
            WhiteScore += PERSONAL_OPENING_POSITION_WEIGHTS[location]

        elif input_board_position[BOARD_MAP_POS_TO_INDEX[location]] == "B":
            BlackScore += PERSONAL_OPENING_POSITION_WEIGHTS[location]

        else:
            continue     

    return ( WhiteScore * num_white_pieces(input_board_position) - 
            BlackScore * num_black_pieces(input_board_position) )

# Static Estimation Functions End
