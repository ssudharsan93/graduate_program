from mvg_helper import *

DEBUG = False

def main():
    args = argument_parser_helper()
    bp = read_board_position_from_file(args[0])

    depth = min(int(args[2]), 16)

    #write_board_position_to_file(args[1], flipped_bp)

    #MinMaxAlgorithmOpening([bp], 0, depth)
    final_static_estimation = MinMaxAlgorithmOpening([bp], 0, depth)

    print(final_static_estimation)

def MinMaxAlgorithmOpening(L, level, max_depth):
    if ( level == ( max_depth ) ):
        static_estimations = [ static_est_opening(bp) for bp in L ]

        if ( ( level % 2 ) == 1 ): #Min Level
            return max(static_estimations)
        else: #Max Level
            return min(static_estimations)

    else:           
        for bp in L:
            if ( ( level % 2 ) == 1 ): #Min Level
                bp = flip_board_position(bp)
                potential_moves = [ 
                    flip_board_position(x)
                    for x in GenerateMovesOpening(bp)
                ]
            else: #Max Level
                potential_moves = GenerateMovesOpening(bp)
            
            return MinMaxAlgorithmOpening(potential_moves, level + 1, max_depth)


main()