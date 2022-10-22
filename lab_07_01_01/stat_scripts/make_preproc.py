# Обработка результатов

import math
import statistics
import os
import os.path
import numpy
import sys


def get_file_data(file_path) -> list:
    data = []

    with open(file_path, 'r') as f:
        for line in f:
            try:
                float(line)
            except ValueError:
                return []
            else:
                data.append(float(line))

    return data


def write_predata(file, num_of_dir, predata) -> None:
    script_dir = os.path.dirname(__file__)
    predata_dir = os.path.join(script_dir, f'../predata{num_of_dir}')
    file_path = os.path.join(predata_dir, os.path.basename(file))

    with open(file_path, 'w') as f:
        for elem in predata:
            f.write(str(elem) + '\n')


def make_predata(num_of_dir) -> int:
    script_dir = os.path.dirname(__file__)
    data_dir = os.path.join(script_dir, f'../data{num_of_dir}')
    files = [os.path.join(data_dir, f) for f in os.listdir(data_dir) if os.path.isfile(os.path.join(data_dir, f))]

    if len(files) == 0:
        return 1

    sys.stderr.write("Predata status:\n")
    i = 0
    q = len(files)
    for file in files:
        i += 1
        sys.stderr.write(f"{i}/{q}\r")

        file_data = get_file_data(file)

        if len(file_data) == 0:
            return 2

        avg = sum(file_data) / len(file_data)
        max_el, min_el = max(file_data), min(file_data)  # O(n), опытов предположительно не очень много
        med = statistics.median(file_data)
        low_quartile = float(numpy.quantile(file_data, 0.25))
        high_quartile = float(numpy.quantile(file_data, 0.75))

        predata = [avg, max_el, min_el, med, low_quartile, high_quartile]
        write_predata(file, num_of_dir, predata)

    return 0


def main():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('num_of_main')
    args = parser.parse_args()
    num_of_dir = int(args.num_of_main)

    error_code = make_predata(num_of_dir)
    if error_code:
        print(f"Data{num_of_dir}: ERROR {error_code}")
        exit(error_code)
    sys.stderr.write("SUCCESS              \n")


if __name__ == '__main__':
    main()

