from mvg_helper import *

DEBUG = False
RECURSE_DEBUG = False

def main():
    args = argument_parser_helper()
    bp = read_board_position_from_file(args[0])

    depth = min(int(args[2]), 16)

    final_static_estimation, desirable_move, static_estimation_count = ABAlgorithmOpening(bp, 0, depth)

    print_final_static_estimation_data(
        final_static_estimation, 
        desirable_move, 
        static_estimation_count
    )

    write_board_position_to_file(args[1], desirable_move)


def GenerateMovesOpeningBlack(bp):

    black_bp = flip_board_position(bp)
    black_moves_as_white = GenerateMovesOpening(black_bp)
    return [ flip_board_position(black_move) for black_move in black_moves_as_white ]
    
def ABAlgorithmOpening(bp, level, max_depth):
    pos_inf = sys.maxsize
    neg_inf = ( ( -1 * sys.maxsize ) - 1 )
    
    final_static_estimation, static_estimation_count, desirable_move =\
          ABMaxMin(bp, neg_inf, pos_inf, level, max_depth)
    
    return final_static_estimation, desirable_move, static_estimation_count

def ABMaxMin(board_position, alpha, beta, level, max_depth):
    # MaxMin(x, α, β):
    # 1. if x is a leaf return static(x).
    # 2. else do steps 2.1, 2.2, 2.3
    # 2.1. set v = −INFINITY
    # 2.2 for each child y of x:
    # 2.2.1 v = max(v, MinMax(y, α, β))
    # 2.2.2 if(v ≥ β) return v
    # 2.2.3 else α = max(v, α)
    # 2.3. return v

    if RECURSE_DEBUG:
        print("Level:" + str(level))
        pprint("Evaluating: " + str(L))

    if ( level == max_depth ):
        return ( static_est_opening(board_position), 1, None )

    else:
        v =  ( -1 * sys.maxsize ) - 1 
        level_static_est_count = 0

        L = GenerateMovesOpening(board_position)

        pos = None

        for bp in L:
            min_max_val, static_est_count, desirable_move = ABMinMax(bp, alpha, beta, level + 1, max_depth)

            tmp = max(v, min_max_val) # new min

            # if there is a new min, there is a new desirable board position
            if ( tmp != v ): 
                pos = bp

            v = max(v, min_max_val)

            if ( v >= beta ):
                return ( v, level_static_est_count + static_est_count, pos )
            else:
                alpha = max(v, alpha)
                level_static_est_count += static_est_count
        
        return ( v, level_static_est_count, pos )

def ABMinMax(board_position, alpha, beta, level, max_depth):
    # MinMax(x, α, β):
    # 3. if x is a leaf return static(x).
    # 4. else do steps 2.1, 2.2, 2.3
    # 4.1 set v = +INFINITY
    # 4.2 for each child y of x:
    # 4.2.1 v = min(v, MaxMin(y, α, β))
    # 4.2.2 if(v ≤ α) return v
    # 4.2.3 else β = min(v, β)
    # 4.3 return v

    if RECURSE_DEBUG:
        print("Level:" + str(level))
        pprint("Evaluating: " + str(L))

    if ( level == max_depth ):
        return ( static_est_opening(board_position), 1, None )

    else:
        v =  sys.maxsize
        level_static_est_count = 0

        L = GenerateMovesOpeningBlack(board_position)

        pos = None

        for bp in L:
            max_min_val, static_est_count, desirable_move = ABMaxMin(bp, alpha, beta, level + 1, max_depth)

            tmp = min(v, max_min_val) # new min

            # if there is a new min, there is a new desirable board position
            if ( tmp != v ): 
                pos = bp

            v = min(v, max_min_val)

            if ( v <= alpha ):
                return ( v, level_static_est_count + static_est_count, pos )
            else:
                beta = min(v, beta)
                level_static_est_count += static_est_count
        
        return ( v, level_static_est_count, pos )

main()