#import numpy

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

def closeMill(board_position, my_board_positions):
    piece_type = my_board_positions[BOARD_MAP_POS_TO_INDEX[board_position]]
    for close_mill_inst in CLOSE_MILL_PARTICIPATION[board_position]:
        for neighbor_board_pos in close_mill_inst:
            neighbor_piece_type = my_board_positions( BOARD_MAP_POS_TO_INDEX[neighbor_board_pos] )
            if ( neighbor_piece_type!= piece_type ):
                return False
        return True
    
def GenerateMovesOpening(input_board_positions):
    return GenerateAdd(input_board_positions)
    
def GenerateAdd(my_board_positions):
    L = list()
    for board_index in range(0,21):
        if my_board_positions[board_index] == "x":
            b = list(my_board_positions)
            b[board_index] = "W"
            if ( closeMill(BOARD_MAP_INDEX_TO_POS[board_index], b) ):
                GenerateRemove(b, L)
            else:
                L.append(b)
    return L

def GenerateHopping(my_board_positions):
    L = list()
    for alpha in range(0,21):
        if my_board_positions[alpha] == "W":
            for beta in range(0,21):
                if my_board_positions[beta] == "x":
                    b = list(my_board_positions)
                    b[alpha] = "x"
                    b[beta] = "W"
                    if ( closeMill(BOARD_MAP_INDEX_TO_POS[beta], b) ):
                        GenerateRemove(b, L)
                    else:
                        L.append(b)
    return L

def GenerateMove(my_board_positions):
    L = list()
    for board_index in range(0,21):
        if my_board_positions[board_index] == "W":
            n = neighbors[board_index]
            for neighbor in n:
                neighbor_index = BOARD_MAP_POS_TO_INDEX[neighbor]
                if my_board_positions[neighbor_index] == "x":
                    b = list(my_board_positions)
                    b[board_index] = "x"
                    b[neighbor_index] = "W"
                    if ( closeMill(BOARD_MAP_INDEX_TO_POS[neighbor_index], b) ):
                        GenerateRemove(b, L)
                    else:
                        L.append(b)
    return L

def GenerateRemove(my_board_positions, L):
    for board_index in range(0,21):
        if my_board_positions[board_index] == "B":
            if ( not closeMill(BOARD_MAP_INDEX_TO_POS[board_index], my_board_positions) ):
                b = list(my_board_positions)
                b[board_index] = "x"
                L.append(b)
    return L

def num_black_pieces(my_board_positions):
    return sum([ 1 if x == 'B' else 0 for x in my_board_positions ])

def num_white_pieces(my_board_positions):
    return sum([ 1 if x == 'W' else 0 for x in my_board_positions ])
    
    # Static Estimation Functions Begin
    
def static_est_midgame_endgame(my_board_positions):
    if ( num_black_pieces(my_board_positions) <= 2 ):
        return 10000
    elif ( num_white_pieces(my_board_positions) <= 2 ):
        return (-10000)
    # elif ( numBlackMoves === 0 ):
    #     return 10000 
    # else:
    #     return 1000 * ( self.num_white_pieces - self.num_black_pieces ) - numBlackMoves

def static_est_opening(self):
    return ( self.num_white_pieces - self.num_black_pieces )

# Static Estimation Functions End

def get_participating_close_mill(board_position):
    return CLOSE_MILL_PARTICIPATION[board_position]

def print_board_positions(input_board_positions):
    print(input_board_positions)

def GenerateMovesMidgameEndgame():
    print("Moves Midgame Endgame")

def main():
    print("Running")
    game_board = [ "x" for i in range(0,21) ]
    print_board_positions(game_board)

    if ( DEBUG ):
        for board_index in range(0,21):
            pos_neighbors = neighbors(board_index)
            print("\n")

            print(
                "Index : " + str(board_index) + 
                "\nBoard Position: " + BOARD_MAP_INDEX_TO_POS[board_index] + 
                "\nNeighbors: " + str(pos_neighbors) + 
                "\nNeighbor Indices: " + str([BOARD_MAP_POS_TO_INDEX[x] for x in pos_neighbors])
            )

        for i in range(0,21):
            print(
                "\nIndex : " + str(i) + 
                "\nBoard Position: " + BOARD_MAP_INDEX_TO_POS[board_index] + 
                "\nClose Mills the Position Participates in:" + 
                "\n" + str(get_participating_close_mill(BOARD_MAP_INDEX_TO_POS[board_index]))
            )

    print("Number of Black Pieces: " + str(num_black_pieces(game_board)))
    print("Number of White Pieces: " + str(num_white_pieces(game_board)))

main()
