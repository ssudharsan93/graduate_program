from mvg_helper import *

DEBUG = False
RECURSE_DEBUG = False

def main():
    args = argument_parser_helper()
    bp = read_board_position_from_file(args[0])

    depth = min(int(args[2]), 16)

    #write_board_position_to_file(args[1], flipped_bp)

    #final_static_estimation, desirable_move, static_estimation_count = MinMaxAlgorithmOpening([bp], 0, depth)

    # print_final_static_estimation_data(
    #     final_static_estimation, 
    #     desirable_move, 
    #     static_estimation_count
    # )

def MinMaxAlgorithmOpening(L, level, max_depth):
    static_est_count = None

    if ( RECURSE_DEBUG ):
        print("\n")
        print(
            "\tLevel: " + str(level) 
            + "\tSize of Nodes to Calculate for: " 
            + str(len(L))
        )
        print(
            "Evaluating: " + 
            str(L)
        )


    if ( level == max_depth ):
        static_est_count = 0
        static_estimations = [ static_est_opening(bp) for bp in L ]

        if ( ( level % 2 ) == 1 ): #Min Level
            max_est = max(static_estimations)
            return ( 
                    max_est, 
                    L[static_estimations.index(max_est)], 
                    static_est_count + len(static_estimations) 
            )
        else: #Max Level
            min_est = min(static_estimations)
            return ( 
                    min_est, 
                    L[static_estimations.index(min_est)], 
                    static_est_count + len(static_estimations)
            )
        
    else:
        best_static_estimations = list()
        desirable_move = None
                
        for bp in L:
            if ( ( level % 2 ) == 1 ): #Min Level
                bp = flip_board_position(bp)
                potential_moves = GenerateMovesOpening(bp) 
                potential_moves = [ 
                    flip_board_position(x)
                    for x in potential_moves
                ]
            else: #Max Level
                potential_moves = GenerateMovesOpening(bp)
            
            best_propagated_static_est, desirable_move, static_est_count =\
                MinMaxAlgorithmOpening(potential_moves, level + 1, max_depth)
        
            best_static_estimations.append(best_propagated_static_est)

            if ( DEBUG ):
                print("\n")
                print("\t" + str(level))
                print_final_static_estimation_data(
                    best_propagated_static_est, 
                    desirable_move, 
                    static_est_count
                )
        
        if ( level == 0 ):
            return ( 
                static_est_opening(desirable_move), 
                desirable_move, 
                static_est_count
            )
        else:
            if ( ( level % 2 ) == 1 ): #Min Level
                max_est = max(best_static_estimations)
                return ( 
                        max_est, 
                        L[best_static_estimations.index(max_est)], 
                        static_est_count + len(best_static_estimations) 
                )
            else: #Max Level
                min_est = min(best_static_estimations)
                return ( 
                        min_est, 
                        L[best_static_estimations.index(min_est)], 
                        static_est_count + len(best_static_estimations)
                )
    
    
def determine_static_est_data(L, static_estimations, level, static_est_count):
    if ( not static_estimations ):
        static_estimations = [ static_est_opening(bp) for bp in L ]

    if ( ( level % 2 ) == 1 ): #Min Level
        max_est = max(static_estimations)
        return ( 
                max_est, 
                L[static_estimations.index(max_est)], 
                static_est_count + len(static_estimations) 
        )
    else: #Max Level
        min_est = min(static_estimations)
        return ( 
                min_est, 
                L[static_estimations.index(min_est)], 
                static_est_count + len(static_estimations)
        )

def print_final_static_estimation_data(final_static_estimation, 
                                       desirable_move, 
                                       static_estimation_count):
    print("\tBoard Position: " + convert_board_position_to_string(desirable_move))
    print("\tPositions evaluated by static estimation: " + str(static_estimation_count))
    print("\tMINIMAX estimate: " + str(final_static_estimation))

main()