from mvg_helper import *

DEBUG = False
RECURSE_DEBUG = False

def main():
    args = argument_parser_helper()
    bp = read_board_position_from_file(args[0])

    depth = min(int(args[2]), 16)

    #write_board_position_to_file(args[1], flipped_bp)

    final_static_estimation, desirable_move, static_estimation_count = MinMaxAlgorithmGame(bp, 0, depth)

    print_final_static_estimation_data(
        final_static_estimation, 
        desirable_move, 
        static_estimation_count
    )

def GenerateMovesMidgameEndgameBlack(bp):
    black_bp = flip_board_position(bp)
    black_moves_as_white = GenerateMovesMidgameEndgame(black_bp)

    return [ flip_board_position(black_move) for black_move in black_moves_as_white ]
    
def MinMaxAlgorithmGame(bp, level, max_depth):
    # Flip the Board to Black as White
    black_board_position_as_white = flip_board_position(bp)
    # Generate Moves for Black as White
    L = GenerateMovesMidgameEndgame(black_board_position_as_white)
    # Play the Game for Black as White
    static_estimates, static_est_count = MaxMin(L, level, max_depth)
    max_est = max(static_estimates)
    # Get the most desirable move for Black as White 
    desirable_move_black_as_white = L[ static_estimates.index(max_est) ]
    # Flip the Board back to Black
    desirable_move = flip_board_position(desirable_move_black_as_white)

    return max_est, desirable_move, static_est_count

def MaxMin(L, level, max_depth):
    #if x is a leaf return static(x)
    #else 
    # v = INTEGER.MIN
    # for bp in L
    #    for child in GenerateNodes(bp)
    # v = max(v, MinMax(child)
    # return v

    if RECURSE_DEBUG:
        print("Level:" + str(level))
        pprint("Evaluating: " + str(L))

    if ( level == max_depth ):
        static_estimates = [ static_est_midgame_endgame(bp) for bp in L ]
        return static_estimates, len(static_estimates)
    
    else:
        level_static_estimations = list()
        level_static_est_count = 0
        
        for bp in L:
            new_L = GenerateMovesMidgameEndgame(bp)
            static_estimations, static_est_count = MinMax(new_L, level + 1, max_depth)
            max_est = max(static_estimations)
            level_static_est_count += static_est_count

            level_static_estimations.append(max_est)

        return level_static_estimations, level_static_est_count

def MinMax(L, level, max_depth):
    #if x is a leaf return static(x)
    #else 
    # v = INTEGER.MAX
    # for bp in L
    #    for child in GenerateNodes(bp)
    # v = min(v, MaxMin(child)
    # return v

    if RECURSE_DEBUG:
        print("Level:" + str(level))
        pprint("Evaluating: " + str(L))

    if ( level == max_depth ):
        static_estimates = [ static_est_midgame_endgame(bp) for bp in L ]
        return static_estimates, len(static_estimates)
    
    else:
        level_static_estimations = list()
        level_static_est_count = 0
        
        for bp in L:
            new_L = GenerateMovesMidgameEndgameBlack(bp)
            static_estimations, static_est_count = MaxMin(new_L, level + 1, max_depth)
            min_est = min(static_estimations)
            level_static_est_count += static_est_count

            level_static_estimations.append(min_est)

        return level_static_estimations, level_static_est_count

main()