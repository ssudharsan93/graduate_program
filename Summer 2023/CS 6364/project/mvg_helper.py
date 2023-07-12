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

def convert_board_position_to_string(bp):
    bp_str = str()
    for board_location in bp:
        bp_str += board_location
    return bp_str

def convert_board_position_string_to_position(bp_str):
    return [ x for x in bp_str ]


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