import csv

def json_to_csv (list, filename):
    keys = list[0].keys()
    with open("csv_generated/" + filename, 'w+') as output_file:
        dict_writer = csv.DictWriter(output_file, keys, delimiter=",")
        dict_writer.writeheader()
        dict_writer.writerows(list)

def create_populate_sql_script (lists):
    with open("sql_scripts/populate.sql", "w+") as file:
        for json in lists:
            line = "COPY {} FROM '/home/joker/Documents/Unicamp/mc536/csv_generated/{}.csv' DELIMITER ',' CSV HEADER;".format(json['name'], json['name'])
            file.write(line + "\n\n")
