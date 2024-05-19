import re
from cyaron import *
import random


def count_matching_strings(pattern, strings):
    pattern = pattern.replace('+', '[A-Z]+').replace('?', '[A-Z]')

    regex = re.compile(pattern)
    count = sum(1 for s in strings if regex.fullmatch(s))
    return count


def remove_duplicates(input_string):
    unique_characters = set(input_string)
    sorted_result = ''.join(sorted(unique_characters))
    return sorted_result


def rand_char():
    return String.random(None,
                         charset=letters * 5 + ['+', '?'] * 5 + set_array * 3);


set_array = []

if __name__ == "__main__":
    letters = list(string.ascii_uppercase)
    # for i in range(random.randint(20, 50)):
    #     a = String.random((3, 15), charset="ABCDEFGHIGKLMNOPQRSTUVWXYZ")
    #     a = '[' + remove_duplicates(a) + ']'
    #     set_array.append(a)

    for i in range(1, 6):

        data = IO(file_prefix="regex", data_id=i)

        l = randint(200, 300)
        real = 0

        str = ''

        while len(str) < l:
            str = str + rand_char()
            real += 1

        print(str)
        data.input_writeln(str)

        n = randint(70, 101)

        print(n)
        data.input_writeln(n)

        data_set = []

        for i in range(n):
            pp_str = ''

            if randint(1, 500) % 10 < 7:
                pp_str = String.random_regular(str.replace('+', '[A-Z]+').replace('?', '[A-Z]'))
            else:
                pp_str = String.random((real - 20, real + 20), charset="ABCDEFGHIGKLMNOPQRSTUVWXYZ")
            data_set.append(pp_str)
            print(data_set[len(data_set) - 1])
            data.input_writeln(data_set[len(data_set) - 1])

        # print(count_matching_strings(str, data_set))
        # data.output_writeln(count_matching_strings(str, data_set))
        data.output_gen("E:\\OI-Code\\test\\regex\\std.exe")
