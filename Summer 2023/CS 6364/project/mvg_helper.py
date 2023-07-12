import argparse
from generate import *
from pprint import pprint

def argument_parser_helper():
    parser = argparse.ArgumentParser()
    parser.add_argument("bpinputf", help='board position input file')
    parser.add_argument("bpoutputf", help='board position output file')
    parser.add_argument("depth", help='max depth for the algorithm')
    args = parser.parse_args()

    return ( args.bpinputf, args.bpoutputf, args.depth)

def read_board_position_from_file(fname):
    with open(fname, "r") as bpfile:
        bp = bpfile.readlines()
        bp = [ x for x in bp[0] ]

    return bp

def write_board_position_to_file(fname, bp):
    with open(fname, "w") as bpfile:
        bp_str = convert_board_position_to_string(bp)
        bpfile.write(bp_str)


def debug_print_board_mappings():
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
            "\n" + str(get_participating_close_mill(BOARD_MAP_INDEX_TO_POS[board_index])) )
        
def debug_close_mill_check():
    board_position_str = "WWWWWWxWBBBBBBBBxxxxx"
    board_position_str2 = "xxxBxWxWWWBBBBxxxxxxx"
    bp = convert_board_position_to_string(board_position_str)
    bp2 = convert_board_position_to_string(board_position_str2)

    print("\n" + board_position_str + "\n")
    for board_index in range(0,21):
        print(
            BOARD_MAP_INDEX_TO_POS[board_index] + ": " + 
            str(closeMill(BOARD_MAP_INDEX_TO_POS[board_index], bp))
        ) 

    print("\n" + board_position_str2 + "\n")
    for board_index in range(0,21):
        print(
            BOARD_MAP_INDEX_TO_POS[board_index] + ": " + 
            str(closeMill(BOARD_MAP_INDEX_TO_POS[board_index], bp2))
        )

def print_final_static_estimation_data(final_static_estimation, 
                                       desirable_move, 
                                       static_estimation_count):
    print("\tBoard Position: " + convert_board_position_to_string(desirable_move))
    print("\tPositions evaluated by static estimation: " + str(static_estimation_count))
    print("\tMINIMAX estimate: " + str(final_static_estimation))